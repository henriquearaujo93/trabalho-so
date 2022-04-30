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
void copiarFicheiro(char *fileName);
void concatenarString(char *str1, char *str2, char *newString);
int tamanhoString(char *name);
void acrescentaDestino(char *fileOrigem, char *fileDestino);