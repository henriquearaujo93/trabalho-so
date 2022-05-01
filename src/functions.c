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

//Acrescenta origem destino
void acrescentaDestino(char *fileOrigem, char *fileDestino) {

    int file1, file2;
    char readBuffer[bytesFicheiro(fileOrigem)];
    char opcao;

    file1 = open(fileOrigem, O_RDONLY);
    file2 = open(fileDestino, O_WRONLY | O_APPEND);
    
    read(file1, readBuffer, sizeof(readBuffer));
    int result = write(file2, readBuffer, sizeof(readBuffer));
    close(file1);
    close(file2);

    if (result == -1) {
        perror("> Nada foi escrito!\n");
    } else {
        printf("> Ficheiro copiado com sucesso!\n");
    }

    printf("\n------------------------------------------------------------------\n");

    do {
        printf("Pressione 'v' para voltar:");
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

//Contar linhas Ficheiro
void contarLinhas(char *fileName)
{
    int fd, count=0;
    int size = bytesFicheiro(fileName);
    char readBuffer[bytesFicheiro(fileName)];
    char *apont;
    char opcao;

    fd = open(fileName, O_RDONLY);
        
    read(fd, readBuffer, sizeof(readBuffer));

    apont = strtok(readBuffer, "\n");

    while(apont != NULL)
    {
        count ++;
        apont = strtok(NULL, "\n");
    }
    
    close(fd);

    printf("Numero de linhas: %d\n", count);

    printf("\n------------------------------------------------------------------\n");

    do {
        printf("Pressione 'v' para voltar:");
        scanf(" %c", &opcao);
    } while (opcao != 'v' && opcao != 'V');

}

void informa(char *filename)
{

    struct stat sfile;
    struct tm dt;
    char opcao;
    
    stat(filename,&sfile);

    struct passwd *pw = getpwuid(sfile.st_uid);
    struct group  *gr = getgrgid(sfile.st_gid);

    //Accessing data members of stat struct
    if(S_ISDIR(sfile.st_mode))
    {
    printf("\nTipo: Diretoria\n");
    }
    else if(S_ISREG(sfile.st_mode))
    {
    printf("\nTipo: Ficheiro Regular\n");
    }
    else if(S_ISLNK(sfile.st_mode))
    {
    printf("\nTipo: Link");
    }
    printf("\nI-node: %ld\n",sfile.st_ino);
    printf("\nUid: (        %d/       %s)\n",sfile.st_uid,pw->pw_name);
    printf("\nGrupo: %s\n", gr->gr_name);
    dt = *(gmtime(&sfile.st_ctime));
        printf("\nCriado em: %d-%d-%d %d:%d:%d\n", dt.tm_mday, dt.tm_mon + 1, dt.tm_year + 1900, dt.tm_hour + 1, dt.tm_min, dt.tm_sec);
    dt = *(gmtime(&sfile.st_mtime));
        printf("\nUltima modifcação: %d-%d-%d %d:%d:%d\n", dt.tm_mday, dt.tm_mon + 1, dt.tm_year + 1900, dt.tm_hour + 1, dt.tm_min, dt.tm_sec);
    dt = *(gmtime(&sfile.st_atime));
        printf("\nUltmo acesso: %d-%d-%d %d:%d:%d\n", dt.tm_mday, dt.tm_mon + 1, dt.tm_year + 1900, dt.tm_hour + 1, dt.tm_min, dt.tm_sec);
    printf("\n");

    do {
            printf("Pressione 'v' para voltar:");
            scanf(" %c", &opcao);
        } while (opcao != 'v' && opcao != 'V');

}

//Listar Diretorio
void listarDiretorio(char *diretoria)
{

    DIR *dir;
    struct dirent *entry;
    struct stat filestat;
    char opcao;

    if ((dir = opendir(diretoria)) == NULL) {
        perror("Erro ao abrir diretorio");
    } else {
        printf("> Conteudo de: %s: \n", diretoria);
        
        while((entry = readdir(dir))) {
            stat(entry->d_name, &filestat);

            if (S_ISDIR(filestat.st_mode)) 
            {
                printf("%s: %s\n","Dir",entry->d_name);
            }
            else if(S_ISREG(filestat.st_mode))
            {
                printf("%s: %s\n","File",entry->d_name);

            }
            else if(S_ISCHR(filestat.st_mode))
            {
                printf("%s: %s\n","Carateres ",entry->d_name);

            }
            else if(S_ISBLK(filestat.st_mode))
            {
                printf("%s: %s\n","File",entry->d_name);

            }
            else if(S_ISLNK(filestat.st_mode))
            {
                 printf("%s: %s\n","Link",entry->d_name);
            }
            else
            {
                printf("%s: %s\n","None",entry->d_name);
            }
        }
        
        closedir(dir);
    }

    printf("\n------------------------------------------------------------------\n");

    do {
        printf("Pressione 'v' para voltar:");
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