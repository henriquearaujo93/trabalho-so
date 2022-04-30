#include "functions.h"

int main(int argc,char * argv[]) {

    int opcao;

    char *fileName;
    char *fileName2;

    fileName = malloc(sizeof(fileName));

    do {
        printMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                clear();

                do {
                    printf("> Insira o caminho do ficheiro: ");
                    scanf("%s", fileName);

                    if (verificarFicheiroExiste(fileName) == FALSE) {
                        perror("    > Erro ao ler ficheiro!");
                    }

                } while (verificarFicheiroExiste(fileName) == FALSE);

                clear();

                mostraFicheiro(fileName);
                
                clear();
                break;
            case 2:
                clear();

                do {
                    printf("> Insira o caminho do ficheiro a ser copiado: ");
                    scanf("%s", fileName);

                    if (verificarFicheiroExiste(fileName) == FALSE) {
                        perror("    > Erro ao ler ficheiro!");
                    }

                } while (verificarFicheiroExiste(fileName) == FALSE);

                clear();

                copiarFicheiro(fileName);
                
                clear();

                break;
            case 3:
                clear();

                do {
                    printf("> Insira o caminho do ficheiro 1: ");
                    scanf("%s", fileName);

                    if (verificarFicheiroExiste(fileName) == FALSE) {
                        perror("    > Erro ao ler ficheiro!");
                    }

                } while (verificarFicheiroExiste(fileName) == FALSE);

                do {
                    printf("> Insira o caminho do ficheiro 2: ");
                    scanf("%s", fileName2);

                    if (verificarFicheiroExiste(fileName2) == FALSE) {
                        perror("    > Erro ao ler ficheiro!");
                    }

                } while (verificarFicheiroExiste(fileName2) == FALSE);

                clear();

                acrescentaDestino(fileName, fileName2);

                clear();


                break;
            case 4:
                clear();

                do {
                    printf("Insira o caminho do ficheiro: ");
                    scanf("%s", fileName);

                    if (verificarFicheiroExiste(fileName) == FALSE) {
                        perror("Erro ao ler ficheiro!\n");
                    }

                } while (verificarFicheiroExiste(fileName) == FALSE);

                clear();

                printf("Linhas: %d", contarLinhas(fileName));
                
                //TODO: Conta Ficheiro
                break;
            case 5:
                clear();

                do {
                    printf("> Insira o caminho do ficheiro: ");
                    scanf("%s", fileName);

                    if (verificarFicheiroExiste(fileName) == FALSE) {
                        perror("    > Erro ao ler ficheiro!");
                    }

                } while (verificarFicheiroExiste(fileName) == FALSE);

                clear();

                deletarFicheiro(fileName);
                
                clear();

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