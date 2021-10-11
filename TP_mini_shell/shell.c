#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

void fonction_cd(char** argv){															// va dans le repertoire donné par le chemin dans argv[1]

	if(chdir(argv[1]) == -1) perror("erreur fonction cd");
}

void fonction_pwd(){

	char tampon[1024];																			// tableau de caractere qu'on affichera
	if (getcwd (tampon, 1024) == NULL) 											// on remplit le tableau
		perror("erreur fonction pwd");												// si getcwd renvoie null, on affiche une erreur
	else puts (tampon);																			// on affiche dans le terminal
}

void execution(char** argv,int argc){											// execute une commande "simple" (sans >, ; , |)

	if (argc>2 && strcmp(argv[argc-2],">")==0){							// dans ce cas on ecrit dans un fichier
		char* out=(char*)malloc(1000*sizeof(char));						// On recupere le fichier dans le quel on veut ecrire
		strcpy(out, argv[argc-1]);
		argv[argc-1]=NULL;																		// On efface les arguments qui ne servent plus (> et destination)
		argv[argc-2]=NULL;
		argc-=2;
		if(fork()==0){
			FILE *direction=freopen(out,"a",stdout);						// on change la destination
			execution(argv,argc);																// on execute dans la bonne destination
			fclose(direction);
		}
		else wait(NULL);
		free(out);
		exit(EXIT_SUCCESS);																		// on termine le processus
	}

	else{
		if (!strcmp(argv[0],"cd")){														// on regarde si la commande est cd
			if (argc>2) printf("trop d'arguments\n");						// on gere les possibles erreurs
			if (argc==1) printf("pas assez d'arguments\n");
			else fonction_cd(argv); 														// on execute cd
		}

		else if (!strcmp(argv[0],"pwd")){											// on regarde si la commande est pwd
			fonction_pwd(); 																		// on execute pwd
		}

		else {
			if (execvp(argv[0],argv) == -1) 											// on execute une commande en gerant son erreur
				perror("erreur apres avoir appelé execvp : ");
			}
		exit(EXIT_SUCCESS);
	}
}

void execution_pipe(char** argv,int argc, int* indice_pipe,int* arr, int* flag_point_virgule){

	// separation du argv en deux sous argv

	char** argvG=(char**)malloc(1000*sizeof(char*));				// commandes a gauche du pipe
	char** argvD=(char**)malloc(1000*sizeof(char*));				// commande a droite du pipe

	int argcG = *indice_pipe;																// nombre d'arguments a gauche
	int argcD=argc-(*indice_pipe)-1;												// nombre d'arguments a droite

	int i;
	for (i=0;i<argcG;i++) argvG[i]=argv[i];									// on remplit les tableaux de gauche et droite
	for (i=0;i<argcD;i++) argvD[i]=argv[(*indice_pipe)+i+1];

	int fd[2]; 																							// creation des file desciptors du pipe (0=lecture, 1=ecriture)
	if (pipe(fd) == -1){
		fprintf(stderr , "erreur de pipe en bois ");
	}

	if(fork() == 0){																				// fils qui execute cette partie de code
		close(fd[0]); 																				// ferme le fd de lecture car on va faire écrire le fils
		dup2(fd[1], 1); 																			// conecte le coté ecriture du tuyau au stdout du fils (stdout = 1)
		execution(argvG, argcG);
		// au debut du tp on utilisait execution quand il n'y avait pas tous les cas a traiter,
		// puis avec la différenciation des cas on devait donc utiliser execution_generale
		// mais cela fait une fork bomb, nous n'avons pas eu le temps de regler ce problème
		// donc quand on utilise un pipe, il n' y a que des commandes "simples" (sans ; < &)
		// qui peuvent aux deux extremités du tuyaux

		close(fd[1]); 																				// ferme le fd d'ecriture car on a fait ce qu'on voulait faire
		//exit(EXIT_SUCCESS);
	}
	else{																										// que le père qui execute cette partie du code
		close(fd[1]);																					// ferme le fd d'ecriture car on va faire lire le père
		dup2(fd[0], 0); 																			// conecte le coté lecture du tuyau au stdin du parent (stdin  0)
		execution(argvD,argcD);
		close(fd[0]);																					// ferme le fd de lecture car on fat ce qu'on a voulu faire,
																													// le tuyau anonyme est maintenant fermé des deux cotés, il ets donc supprimé
		//if (arr==0) wait(NULL);
		wait(NULL);
	}
	free(argvD);
	free(argvG);
	exit(EXIT_SUCCESS);
}

void sous_lecture_argvC(char** argv, int argc, int* indice_pipe, int *arr){		//fonction qui leve des flags de présence de certains caractère ou non dans le argv qu'on lui donne en argument

	for(int i = 0; i < argc; i++){
		if(strcmp(argv[i],"|") == 0) *indice_pipe = i;
		//else if(strcmp(argv[argc - 2],"&") == 0) *arr=1; 												//provoque une seg fault, nous n'avons pas eu le teps de nous pencher sur la question
	}
}

int execution_a_la_chaine(char** argv, int argc, int* indice_pipe, int* arr, int* flag_point_virgule){	//excetution de plusieurs commande séparés par des ;

	// decoupage de argv en sous argv nommés ici argvC pour argv Courant
	int debut_commande = 0;		//indices des mots de debut et de fin d'une commande par rapport au argv "général"
	int fin_commande = 0;


	for(int i = 0; i < argc; i++){

		if (strstr(argv[i], ";") != NULL || i == argc - 1){							// si le mot argv[i] contient ";" ou s c'est le dernier mot de argv : condition qui indique si on ce mot est la fin d'une commande ou non

			char** argvC = (char**) malloc(10 * sizeof(char*));						// on crée un argvC et alloue de la memoire pour le remplir après.
																																		// ici on a supposé que nos commandes n'allai pas faire de plus de 10 mots

			fin_commande = i;																							// on sauvegarde l'indice par rapport a argv de la fin de la commande courante

			for(int j = 0; j < fin_commande - debut_commande + 1; j++){		// remplissage de argvC
				argvC[j] = argv[debut_commande + j];

				if(j == fin_commande - debut_commande && strstr(argv[i], ";") != NULL) argvC[j][strlen(argvC[j]) - 1]  = '\0';	// on enlève ; du derniet mot de la commande courante

			}

/*
			printf("debut = %d, fin = %d\n", debut_commande, fin_commande);				// affichage de comprehension et de test

			for(int k = 0; k < fin_commande - debut_commande + 1; k++){
				printf("%s\n",argvC[k]);
			}
*/

			*indice_pipe = -1;																										// on reset tous les flags de présence de caracterespéciaux
			*arr = -1;
			*flag_point_virgule = -1;


			sous_lecture_argvC(argvC, fin_commande - debut_commande + 1, indice_pipe, arr);													// avant d'excuter une commande, on appelle sous_lecture avec le argv Courant
			execution_generale(argvC,fin_commande - debut_commande + 1, indice_pipe, arr, flag_point_virgule);			// on appelle execution_generale pour rediriger vers la bonne sous fonction d'execution

			printf("----------------\n\n" );


			free(argvC);																													// on libère le tableau de string qu'on a utilisé,
																																						// en essaynt de librer ligne par ligne
																																						// puis de liberer chaque tableau a une dimensions nous avons une seg fault, nous n'avons pas trop compris pourquoi

			debut_commande = i+1;																									// on met l'indice de debut de commmande au mot d'après pour la prochaine commande
		}

	}

	return 0;
}

int execution_generale(char** argv, int argc, int* indice_pipe, int* arr, int* flag_point_virgule){	//fonction qui redirige vers quelle sous-fonction d'exution appeler selon les flags levés.

	if(*flag_point_virgule == 1) {
		execution_a_la_chaine(argv, argc, indice_pipe, arr, flag_point_virgule);
		return 0;
	}

	else if(*indice_pipe >= 1) {
		execution_pipe(argv, argc, indice_pipe, arr, flag_point_virgule);
		//exit(EXIT_SUCCESS);
	}

	else{																										// execution pour commandes "simples" (sans <, ; |)
			if (fork() == 0){
				execution(argv,argc);
				return 0;
			}

			if (*arr==-1) wait(NULL);														//on wait que si il n'y a pas de & dans ce qu'a tapé l'utilisateur
		}

		return 0;
}

int lecture_commande(char** argv, int* indice_pipe, int* arr, int* flag_point_virgule){			//renvoie argc, rempli argv, leves des flag de presence de caractères spéciaux

	int argc=0;																				//nombre d'arguments
	*indice_pipe=-1;																	//valeur par défault
	*arr=-1;																					//valeur par défault
	*flag_point_virgule=-1;														//valeur par défault

	//char* str=(char*)malloc(LMAX);									//tableau qui contiendra les caracteres de la commande
	char str[1000];
	if(fgets(str,LMAX,stdin)==NULL)										//chaine tapé dans la variable str
		fprintf(stderr, "probleme de livraison, refaites une commande");	//verification d'erreur

	int longeur=strlen(str);
	if (str[longeur-2]=='&') *arr=1;									//on regarde si le dernier char est un &, si oui, arr vaut 1

	const char* separators="& \n";										//separateurs necessaire a strtok (\n peut etre pas absolument necessaire)
	char* token=strtok(str,separators);								//le premier token le premier argument

	while (token!=NULL){															//ici on prend chaque token qu'on met dans argv, le tableau d'arg
		argv[argc]=token;

		if(strcmp(token,"|") == 0) *indice_pipe = argc;	//on regarde ou est le pipe s'il y en a un

		else if(strstr(token, ";") != NULL)	*flag_point_virgule = 1;
		argc++;																					//on tient a jour le nombre d'arg
		token=strtok(NULL,separators);									//strtok est vraiment une fonction fourbe, les elements suivants le premier se mettent de cetet maniere
	}

	if (strcmp("exit",argv[0])==0) return -80000;			//on a une demande d'exit

	return argc;																			//on retourne le nombre d'arg
}

int main(){

	char** argv;
	int argc;
	int indice_pipe;
	int flag_point_virgule;
	int arr;

	while (1){
		argv=NULL;
		argv = (char**)malloc(1000*sizeof(char*));																//on alloue de la memoire pour argv
		printf("$ ");
		argc = lecture_commande(argv, &indice_pipe, &arr, &flag_point_virgule);		// on analyse ce qui a été entré par l'utilisateur
		if (argc == -80000){																											// cas ou l'utilisatuer a entré exit
			free (argv);
			return 0;
		}
		else argv[argc]=NULL;																											//on met la derniere case a NULL
		execution_generale(argv, argc, &indice_pipe, &arr, &flag_point_virgule);	//on execute

		free(argv);																																//on libere la memoire
		}

	return 0;
}
