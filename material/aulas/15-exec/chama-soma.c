#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void main(){
    pid_t filho;
    char *programa = "./soma";

    filho = fork();

    if (filho == 0){
        char *argv[] = {"./soma","1","2","3","4", NULL};

        printf("Filho Comecou\n");
        execvp(programa, argv);
        perror("execvp");
        exit(EXIT_FAILURE);
    } else{
        int wstatus;

        wait(&wstatus);
        printf("Filho Terminou\n");
        printf("Terminou normal?: %d\n", WIFEXITED(wstatus)); // lê 0 ou 1
        if (WIFEXITED(wstatus)) { // se terminou normalmente
            printf("Valor de retorno: %d\n", WEXITSTATUS(wstatus)); // lê o byte menos significativo do return do filho
        }
    }
}