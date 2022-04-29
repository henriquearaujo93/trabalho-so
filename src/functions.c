#include <fcntl.h>
#include <unistd.h>
#include "functions.h"

//Mostrar Menu ao utilizador
void printMenu() {
    printf("--------------------------------------\n");
    printf("---------------  MENU  ---------------\n");
    printf("--------------------------------------\n");
    printf("  [1] -> Mostrar Ficheiro\n");
    printf("  [2] -> Copiar Ficheiro\n");
    printf("  [3] -> Acrescenta Origem Destino\n");
    printf("  [4] -> Conta Linhas Ficheiro\n");
    printf("  [5] -> Apaga Ficheiro\n");
    printf("  [6] -> Informa Ficheiro\n");
    printf("  [7] -> Lista Diretoria\n");
    printf("  [0] -> SAIR\n");
    printf("opcao: ");
}

//Função para mostrar conteúdo do ficheiro
void mostraFicheiro(char *fileName) {

    int file;

    //Abrir arquivo
    if (verificarFicheiroExiste(fileName) == TRUE) {
        
        char readBuffer[bytesFicheiro(fileName)];
        file = open(fileName, O_RDONLY);
        
        read(file, readBuffer, sizeof(readBuffer));
        write(STDIN_FILENO, readBuffer, sizeof(readBuffer));
        close(file);

    } else {
        perror("Ficheiro nao existe!");
    }
}

//Helpers
int tamanhoString(char *name) {
    int counter = 0;

    while (*name != '\0') {
        counter++;
        *name++;
    }
    return(counter);
}

bool verificarFicheiroExiste(char *fileName) {

    if (open(fileName, O_RDONLY) == -1) {
        return FALSE;
    } else {
        return TRUE;
    }
}

int bytesFicheiro(char *fileName) {
    struct stat sb;

    if (stat(fileName, &sb) == -1) {
        perror("stat");
    } else {
        return sb.st_size;
    }
}
