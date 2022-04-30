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
void mostraFicheiro(char *fileName) 
{
    char opcao;
    int file;

    printf("------------------------------------------------------------------\n");
    
    //Abrir arquivo

    char readBuffer[bytesFicheiro(fileName)];
    file = open(fileName, O_RDONLY);
        
    read(file, readBuffer, sizeof(readBuffer));
    write(STDIN_FILENO, readBuffer, sizeof(readBuffer));
    close(file);

    printf("\n----------------------------------------------------------------\n");

    do {
        printf("Pression 'v' para voltar:");
        scanf(" %c", &opcao);
    } while (opcao != 'v' && opcao != 'V');
}

void deletarFicheiro(char *filename)
{
    char opcao;


    unlink(filename);
    printf("Ficheiro Deletado com sucesso!!\n");

    do {
        printf("Pression 'v' para voltar:");
        scanf(" %c", &opcao);
    } while (opcao != 'v' && opcao != 'V');
}
int contarLinhas(char *fileName)
{
    int fd, count=0;
    int size = bytesFicheiro(fileName);
    char readBuffer[bytesFicheiro(fileName)];
    char *apont;

    fd = open(fileName, O_RDONLY);
        
    read(fd, readBuffer, sizeof(readBuffer));

    

    apont = strtok(readBuffer, "\n");

    while(apont != NULL)
    {
        count ++;
        apont = strtok(NULL, "\n");
    }
    
    close(fd);

    printf("%d", count);
    return count;
}

void listarFicheiros(char *diretoria)
{
    



    

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
