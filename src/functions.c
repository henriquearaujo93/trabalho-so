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

/*-------------------------------- Funções de sistema --------------------------------*/

//Mostrar conteúdo do ficheiro
void mostraFicheiro(char *fileName) {

    char opcao;
    int file;

    printf("------------------------------------------------------------------\n");
    
    //Abrir arquivo
    char readBuffer[bytesFicheiro(fileName)];
    file = open(fileName, O_RDONLY);
        
    read(file, readBuffer, sizeof(readBuffer));
    write(STDIN_FILENO, readBuffer, sizeof(readBuffer));
    close(file);

    printf("\n------------------------------------------------------------------\n");

    do {
        printf("Pression 'v' para voltar:");
        scanf(" %c", &opcao);
    } while (opcao != 'v' && opcao != 'V');
}

//Copiar ficheiro
void copiarFicheiro(char *fileName) {

    int file, newFile;
    char readBuffer[bytesFicheiro(fileName)];
    char opcao;

    char *aux = ".copia";
    char newString[tamanhoString(fileName) + tamanhoString(aux)];

    concatenarString(fileName, aux, newString);

    file = open(fileName, O_RDONLY);
    newFile = open(newString, O_RDWR|O_CREAT, S_IRUSR | S_IWUSR);

    read(file, readBuffer, sizeof(readBuffer));
    int result = write(newFile, readBuffer, sizeof(readBuffer));
    close(file);
    close(newFile);

    if (result < 0) {
        perror("> Nada foi escrito!");
    } else {
        printf("> Ficheiro copiado com sucesso!\n");
        printf("    > Foram copiados: %d bytes para o ficheiro '%s'\n", result, newString);
    }

    printf("------------------------------------------------------------------\n");

    do {
        printf("Pression 'v' para voltar:");
        scanf(" %c", &opcao);
    } while (opcao != 'v' && opcao != 'V');
}

//Deletar um ficheiro
void deletarFicheiro(char *filename)
{
    char opcao;

    unlink(filename);
    printf("Ficheiro Deletado com sucesso!!\n");

    printf("------------------------------------------------------------------\n");

    do {
        printf("Pression 'v' para voltar:");
        scanf(" %c", &opcao);
    } while (opcao != 'v' && opcao != 'V');
}

/*-------------------------------- Helpers --------------------------------*/
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

void concatenarString(char *str1, char *str2, char *newString) {

    int length = 0;

    while(str1[length] != '\0') {
        newString[length] = str1[length];
        length++;
    }

    //Concatenar strings
    for (int i = 0; str2[i] != '\0'; i++) {
        newString[length] = str2[i];
        length++;
    }

    newString[length] = '\0';
}