#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <fcntl.h>
#include <unistd.h>

#define clear() printf("\033[H\033[J")

typedef enum { FALSE, TRUE } bool;

//Functions Prototypes
void printMenu();
void mostraFicheiro(char *fileName);
int tamanhoString(char *name);
bool verificarFicheiroExiste(char *fileName);
int bytesFicheiro(char *fileName);
void deletarFicheiro(char *fileName);
<<<<<<< HEAD
int contarLinhas(char *fileName);
=======
void copiarFicheiro(char *fileName);
void concatenarString(char *str1, char *str2, char *newString);
int tamanhoString(char *name);
void acrescentaDestino(char *fileOrigem, char *fileDestino);
>>>>>>> 1a872b736c2c4a64ec82e68f2d22c19475c9921f
