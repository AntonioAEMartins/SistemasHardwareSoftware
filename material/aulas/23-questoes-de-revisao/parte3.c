#include <stdio.h>

char *proxima_linha(int fd) {
    char *buffer =  (char *) malloc(sizeof(char) * 100);
    printf("salve\n");
    int status = fscanf(fd, "%s", buffer);
    // if (status != 0 && status != -1){
    //     return buffer;
    // }
    return NULL;
}


int main() {
    FILE *fd = fopen("test.txt", "r");
    while(1){
        char *resultado = proxima_linha(fd);
        if (resultado == NULL){
            printf("Terminou de Ler\n");
            break;
        }
        printf("Resultado: %s", resultado);
        free(resultado);
    }
    
    // printf("A proxima linha eh: %s", resultado);
    return 0;
}