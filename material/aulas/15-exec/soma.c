#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    if (argc <= 2){
        printf("ERROR Caracter\n");
        return 0;
    }
    int soma = 0;
    for (int i = 1; i < argc; i++){
        soma += atof(argv[i]);
        printf("Soma: %d\n", soma);
    }
    return soma;
}