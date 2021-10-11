#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lecturefichiers.h"


/*LIT LE PROCHAIN CARACTERE NON VIDE */
char ReadChar(FILE *f){
  char c;
  do
    c = getc(f);
  while (isspace(c));
  return c;
}

/* LECTURE DES CARACTERES JUSQU'A LA FIN DU FICHIER OU DE LA LIGNE */
void SkipLine(FILE *f){
  char c;
  do
    c = getc(f);
  while ((c!=EOF)&&(c!='\n'));
}

/*TESTE SI UN CARACTERE EST UN ESPACE OU UNE VIRGULE*/
int isCommaOrSpace(char c){
	if ((c==',') || (isspace(c))) return 1;
	return 0;
}

/*SAUT DES ESPACES ET VIRGULE LORS DE LA LECTURE DANS UN FICHIER POINTE PAR f */
void Skip(FILE *f){
  char c;
  while (isCommaOrSpace(c=getc(f)));
  ungetc(c,f);
}

/* LECTURE DE CHAINE DE CARACTERES JUSQU'A UNE VIRGULE LA FIN DE LA LIGNE OU LA FIN DE FICHIER */
/*int GetChaine(FILE *f,int taille_max,char *s){
  char c;
  int i;
  Skip(f);
  i=0;
  c = getc(f);
  while ((c!=',')&&(c!=EOF)&&(c!='\n')&&(i<taille_max-1)){
    s[i]=c;
	//printf("%c\n",c);
    c = getc(f);    
    i++;
  }
  s[i]='\0';
  ungetc(c,f);
  return (i); //longueur de la chaine lue
}*/

int LongeurLigne(FILE *f,int numligne){
  GoLigne(f,numligne);
  char a;
  int b=0;
  do{
    a=fgetc(f);
    b++;
  }while ((a!=EOF)&&(a!='\n'));
  return b-2;
}

//récup le texte d'une ligne
char* GetChaine(FILE *f,int numligne){
  int l=LongeurLigne(f,numligne);
  char* chaine=(char*)malloc(l*sizeof(char));

  GoLigne(f,numligne);
  char i=fgetc(f);
  int j=0;
  chaine[0]=i;
  //while(i!='\n'){
  while(j<l){
    i=fgetc(f);
    j++;
    chaine[j]=i;
  }
  return chaine;
}

//compte toute les lignes d'un fichier
int CompteLigne(FILE *f){
  rewind(f);                  //on se place au début du fichier, équivalent à fseek(f,0,SEEK_SET);
  char c;
  int compteur=0;
  c=getc(f);                  //récupère le charactère, avance le curseur de 1
  while(c!=EOF){              //tant que le caractère est différent de la fin du fichier
    SkipLine(f);
    compteur++;
    c=getc(f);
  }
  return (compteur);
}

//va à la ligne
void GoLigne(FILE *f, int n){
  int a=fseek(f,0,SEEK_SET);    //on se place au début du fichier
  a++;                          //ligne 1
  while(a<n){
    SkipLine(f);
    a++;
  }
}

//retourne le num de la ligne où on est placé
int NumLigne(FILE *f){
  int res=1;
  int a=ftell(f);             //donne la position du curseur
  char b;
  rewind(f);                  //on se place au début du fichier
  for (int i=0;i<a;i++){
    b=fgetc(f);               //recup le caractère
    if (b=='\n') res++;
  }
  return res;
}

int Compare(char* a,char* b){
  int m=strlen(a);
  int n=strlen(b);
  if(m!=n)return 0;
  for (int i=0;i<m-1;i++)
    if (a[i]!=b[i]) return 0;
  return 1;
}

//donne la prochaine ligne contenant c, return -1 si pas trouvé (ne trouve pas avant le curseur)(sans doute besoin de mettre un espace à la fin de c)
int RechercheLigne(FILE *f, char* c){//ne ramène aps au début
  rewind(f);
  int num=NumLigne(f);
  int total=CompteLigne(f);
  GoLigne(f,num);
  char* a=GetChaine(f,num);
  do{
    num++;
    a=GetChaine(f,num);
    if(Compare(a,c)) return num;
    SkipLine(f);
    /*printf("%s\n",a);
    printf("%s\n",c);
    printf("%d et %d\n",strlen(a), strlen(c));
    printf("%d\n",Compare(a,c));*/
  }
  while(num<total);
  free(a);
  return -1;
}

/*int main(){
  FILE* fichier=NULL;
  fichier=fopen("googleagenda/telechargement.ics","r");

  GoLigne(fichier,8);
  printf("%ld\n",ftell(fichier));
  printf("%d\n",NumLigne(fichier));

  GoLigne(fichier,1);
  printf("%ld\n",ftell(fichier));
  printf("%d\n",NumLigne(fichier));
  int a=RechercheLigne(fichier,"BEGIN:VEVENT ");
  printf("%ld\n",ftell(fichier));
  printf("%d\n",NumLigne(fichier));


  /*char* txt1="BEGIN:VEVENT ";
  int a=RechercheLigne(fichier,txt1);
  printf("ligne %d\n",a);  

  printf("%d\n",LongeurLigne(fichier,1));

  char* txt2=GetChaine(fichier,22);
  printf("%s\n",txt1);
  printf("%s\n",txt2);
  printf("%d\n",Compare(txt1,txt2));
  printf("%s\n",txt2);
  test(fichier,txt1,txt2);*/


//  return 0;
//}
