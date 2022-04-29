#include "functions.h"

int main(int argc,char * argv[]) {

    int opcao;

    char *fileName;

    fileName = malloc(sizeof(fileName));

    do {
        printMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                //TODO: Mostra Ficheiro
                printf("Insira o caminho do ficheiro: ");
                scanf("%s", fileName);

                mostraFicheiro(fileName);
                
                break;
            case 2:
                //TODO: Copia Ficheiro
                break;
            case 3:
                //TODO: Acrescenta origem destino
                break;
            case 4:
                //TODO: Conta Ficheiro
                break;
            case 5:
                //TODO: Apaga Ficheiro
                break;
            case 6:
                //TODO: Informa Ficheiro
                break;
            case 7:
                //TODO: Lista Diretoria
                break;
            default:
                break;
        }

    } while (opcao != 0);

}