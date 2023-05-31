// Leia o PDF ou MD antes de iniciar este exercício!

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){

    int ret;
    int wst;

    // Checando parametros

    

    do {
        char *arg[] = {"siscoin", argv[1], argv[2], argv[3], NULL};
        char prog =  "siscoin";

        execvp(prog, arg);
        waitpid(-1, &wst, 0);
        int status = WEXITSTATUS(wst);
        if (status != -1){
            ret = WEXITSTATUS(wst);
        }

    } while (ret > 0); // Repita enquanto houver falha. 
                       // Para se tem problema com o valor ou a qtde de parâmetros
                       // Esta validação está sendo feita em siscoin

    return 0;
}