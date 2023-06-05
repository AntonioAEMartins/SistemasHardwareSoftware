#include "macros_correcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int *extrai_primeiro_int(char *msg) {
    int capacity = 2;
    char *numero = (char *) malloc(sizeof(char) * capacity);

    int index = 0;
    int index_numero = 0;
    while(1){ //loop pela mensagem inteira
        //printf("MSG: %c\n", msg[index]);
        if (msg[index] == '\0'){
            break;
        } else if (index_numero > 0 && (msg[index] == ',' || msg[index] == '.' || msg[index] ==' ')){
            break;
        } else if (msg[index] == '9' || //Usar isdigit
                    msg[index] == '8' ||
                    msg[index] == '7' ||
                    msg[index] == '6' ||
                    msg[index] == '5' ||
                    msg[index] == '4' ||
                    msg[index] == '3' ||
                    msg[index] == '2' ||
                    msg[index] == '1' ||
                    msg[index] == '0'
                    )
            {
                //printf("Entrou: %c\n", msg[index]);
                if (index_numero == capacity - 1){
                    capacity ++;
                    numero = realloc(numero, sizeof(char) * capacity);
                }
                numero[index_numero] = msg[index];
                //printf("NUM: %c e IND: %d\n", numero[index_numero], index_numero);
                index_numero ++;
            }
        index ++;
    }
    if (index_numero > 0){
        numero[index_numero] = '\0';
        printf("NUMERO: %d\n", atoi(numero));
        int *int_num = (int *) malloc(sizeof(int) * index_numero);
        int_num[0] = atoi(numero);
        return int_num;
    }
    free(numero);
    return NULL; // Você pode alterar o retorno, se necessário!
}


// Não edite a main, caso contrário zerará a questão
int main() {

    {
        char *msg = "comprei 10 crypto siscoin hoje";
        int correto = 10;
        int *primeiro_int_user = NULL;
        primeiro_int_user = extrai_primeiro_int(msg);

        printf("Testes: %s\n", msg);
        assertExpr(primeiro_int_user != NULL, "ERRO: Primeiro é NULL!");
        if (primeiro_int_user != NULL) {
            assertExpr(*primeiro_int_user == correto, "Primeiro Int tem valor incorreto!");
            free(primeiro_int_user);
        } else {
            assertExpr(primeiro_int_user != NULL, "ERRO: Devido a ser nulo um dos testes não pode ser executado!");
        }
    }

    {
        char *msg = "(-_-)___/ R$ 71,99";
        int correto = 71;
        int *primeiro_int_user = NULL;
        primeiro_int_user = extrai_primeiro_int(msg);

        printf("Testes: %s\n", msg);
        assertExpr(primeiro_int_user != NULL, "ERRO: Primeiro é NULL!");
        if (primeiro_int_user != NULL) {
            assertExpr(*primeiro_int_user == correto, "Primeiro Int tem valor incorreto!");
            free(primeiro_int_user);
        } else {
            assertExpr(primeiro_int_user != NULL, "ERRO: Devido a ser nulo um dos testes não pode ser executado!");
        }
    }

    {
        char *msg = "Nascido em 1987, junqueira sempre soube o que fazer da vida!";
        int correto = 1987;
        int *primeiro_int_user = NULL;
        primeiro_int_user = extrai_primeiro_int(msg);

        printf("Testes: %s\n", msg);
        assertExpr(primeiro_int_user != NULL, "ERRO: Primeiro é NULL!");
        if (primeiro_int_user != NULL) {
            assertExpr(*primeiro_int_user == correto, "Primeiro Int tem valor incorreto!");
            free(primeiro_int_user);
        } else {
            assertExpr(primeiro_int_user != NULL, "ERRO: Devido a ser nulo um dos testes não pode ser executado!");
        }
    }

    {
        char *msg = "Na verdade foi em 1983, não 1987!";
        int correto = 1983;
        int *primeiro_int_user = NULL;
        primeiro_int_user = extrai_primeiro_int(msg);

        printf("Testes: %s\n", msg);
        assertExpr(primeiro_int_user != NULL, "ERRO: Primeiro é NULL!");
        if (primeiro_int_user != NULL) {
            assertExpr(*primeiro_int_user == correto, "Primeiro Int tem valor incorreto!");
            free(primeiro_int_user);
        } else {
            assertExpr(primeiro_int_user != NULL, "ERRO: Devido a ser nulo um dos testes não pode ser executado!");
        }
    }

    {
        char *msg = "É, o final do semestre está chegando!";
        int *primeiro_int_user = extrai_primeiro_int(msg);

        printf("Testes: %s\n", msg);
        assertExpr(primeiro_int_user == NULL, "ERRO: nenhum número deveria ter sido retornado!");
    }

    printSummary;
}
