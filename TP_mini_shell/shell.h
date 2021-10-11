#ifndef SHELL_H
#define SHELL_H



#define LMAX 1000

void fonction_cd(char** argv);
void fonction_pwd();

int lecture_commande(char** argv, int* indice_pipe, int* arr, int* flag_point_virgule);
void sous_lecture_argvC(char** argv, int argc, int* indice_pipe, int *arr);


void execution(char** argv,int argc);
void execution_pipe(char** argv,int argc, int* indice_pipe,int* arr, int* flag_point_virgule);
int execution_a_la_chaine(char** argv, int argc, int* indice_pipe, int* arr, int* flag_point_virgule);
int execution_generale(char** argv, int argc, int* indice_pipe, int* arr, int* flag_point_virgule);


#endif
