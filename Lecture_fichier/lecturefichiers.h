#ifndef LECTUREFICHIERS_H
#define LECTUREFICHIERS_H

//#include <ctype.h>
#include <stdio.h>

/*LIT LE PROCHAIN CARACTERE NON VIDE */
char ReadChar(FILE *f);	
/* LECTURE DES CARACTERES JUSQU'A LA FIN DU FICHIER OU DE LA LIGNE */
void SkipLine(FILE *f); 
/*TESTE SI UN CARACTERE EST UN ESPACE OU UNE VIRGULE*/
int isCommaOrSpace(char c);
/* SAUT DES ESPACES ET VIRGULE LORS DE LA LECTURE DANS UN FICHIER POINTE PAR f */
void Skip(FILE *f);
/* LECTURE DE CHAINE DE CARACTERES JUSQU'A UNE VIRGULE LA FIN DE LA LIGNE OU LA FIN DE FICHIER */
//int GetChaine(FILE *f,int taille_max,char *s);
char* GetChaine(FILE *f,int numligne);
int CompteLigne(FILE *f);
void GoLigne(FILE *f, int n);
int NumLigne(FILE *f);
int RechercheLigne(FILE *f, char* c);
int Compare(char* a,char* b);
int LongeurLigne(FILE *f,int numligne);

#endif