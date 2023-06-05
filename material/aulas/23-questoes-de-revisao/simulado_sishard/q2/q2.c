// Leia o PDF ou MD antes de iniciar este exercício!

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){

    char ret;
    int wst;

    // Checando parametros

    

    do {
        char *arg[] = {"./siscoin", argv[1], argv[2], argv[3], NULL};
        char *prog =  "./siscoin";
        int filho = fork();
        if (filho == 0){
            execvp(prog, arg);
            printf("F\n");
        } else {
            waitpid(filho, &wst, 0);
            int status = WEXITSTATUS(wst);
            ret = (char) WEXITSTATUS(wst);
            if (ret > 0){
                printf("Erro ao transferir\n");
            } else if (ret == -1){
                printf("Retornou negativo\n");
            }
        }
        
        

    } while (ret > 0); // Repita enquanto houver falha. 
                       // Para se tem problema com o valor ou a qtde de parâmetros
                       // Esta validação está sendo feita em siscoin
    printf("Transferencia realizada!\n");
    return 0;


