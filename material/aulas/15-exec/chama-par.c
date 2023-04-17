#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void main(){
    char *programa = "./par";
    char numero[2] = "";
    scanf("%s", numero);
    pid_t filho;

    filho = fork();

    if (filho == 0){
        char *argv[] = {"./par",numero, NULL};
        execvp(programa, argv);
    } else {
        int wstatus;
        wait(&wstatus);

        printf("Filho Terminou\n");
        printf("Terminou normal?: %d\n", WIFEXITED(wstatus)); // lê 0 ou 1
        if (WIFEXITED(wstatus)) { // se terminou normalmente
            printf("Valor de retorno: %d\n", WEXITSTATUS(wstatus)); // lê o byte menos significativo do return do filho
        }
    }
}