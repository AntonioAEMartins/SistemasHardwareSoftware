#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>


int main() {
    pid_t pai, filho;
    for (int i = 1; i < 9; i++){
        filho = fork();
        if (filho == 0){
            printf("Eu sou o processo Filho %d", i);
            return 0; //exit();
        }
    }
    pai = getpid();
    printf("Eu sou o proceso pai %d", pai);
    return 0;
}