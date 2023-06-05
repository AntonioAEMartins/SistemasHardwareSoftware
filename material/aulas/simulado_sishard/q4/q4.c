// Leia o PDF ou MD antes de iniciar este exercício!

#include "macros_correcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


char *extrai_primeira_hashtag_user (char *tweet_completo) {
    int index = 0;
    int index_escrito = 0;
    int mode_hash = 0;
    int mode_tag = 0;
    // Para responder o exercício, edite esta função
    int capacity = 2;
    char *resultado = (char *) malloc(sizeof(char) * capacity);
    char *nulo = '\0';
    while(1){ 
        if (tweet_completo[index] == '\0'){
            if (index_escrito > 0){
                resultado[capacity - 1] = '\0';
                printf("RESULTADO: %s %d\n", resultado, capacity);
                return resultado;
            }
            break;
        } else if (tweet_completo[index] == '#'){
            mode_hash = 1;
        } else if (tweet_completo[index] == '@'){
            mode_tag = 1;
        } else if ((tweet_completo[index] == ' ' || tweet_completo[index] == ',' || tweet_completo[index] == '.' ) && (mode_hash || mode_tag)){
            mode_hash = 0;
            mode_tag = 0;
            resultado[capacity - 1] = '\0';
            printf("RESULTADO: %s %d\n", resultado, capacity);
            return resultado;
        }

        if (mode_hash){
            if (index_escrito == capacity - 1){
                capacity ++;
                resultado = realloc(resultado, sizeof(char) * capacity);
            }
            resultado[index_escrito] = tweet_completo[index];
            index_escrito ++;
        } else if (mode_tag) {
            if (index_escrito == capacity - 1){
                capacity ++;
                resultado = realloc(resultado, sizeof(char) * capacity);
            }
            resultado[index_escrito] = tweet_completo[index];
            index_escrito ++;
        }
        index ++;
    }
    free(resultado);
    return nulo;
}


// Nao altere nada na Main!
int main () {
    printf("Testes D\n");
    printf("===================\n");

    {
        char *tweet = "comprei 10 crypto siscoin hoje";
        char *correto = "";
        char *primeira_hashtag_user = extrai_primeira_hashtag_user(tweet);

        printf("Testes: %s\n", tweet);
        assertExpr(primeira_hashtag_user != NULL, "Hashtag é NULL!");
        if (primeira_hashtag_user != NULL) {
            assertExpr(strcmp(primeira_hashtag_user, correto) == 0, "Hashtag tem valor incorreto!");
            free(primeira_hashtag_user);
        }
    }

    {
        char *tweet = "comprei 10 crypto siscoin hoje, sou #baleia ou nao?!";
        char *correto = "#baleia";
        char *primeira_hashtag_user = extrai_primeira_hashtag_user(tweet);

        printf("Testes: %s\n", tweet);
        assertExpr(primeira_hashtag_user != NULL, "Hashtag é NULL!");
        if (primeira_hashtag_user != NULL) {
            assertExpr(strcmp(primeira_hashtag_user, correto) == 0, "Hashtag tem valor incorreto!");
            free(primeira_hashtag_user);
        }
    }


    {
        char *tweet = "A crypto do momento é #siscoin que cresceu 20%% só hoje";
        char *correto = "#siscoin";
        char *primeira_hashtag_user = extrai_primeira_hashtag_user(tweet);

        printf("Testes: %s\n", tweet);
        assertExpr(primeira_hashtag_user != NULL, "Hashtag é NULL!");
        if (primeira_hashtag_user != NULL) {
            assertExpr(strcmp(primeira_hashtag_user, correto) == 0, "Hashtag tem valor incorreto!");
            free(primeira_hashtag_user);
        }
    }


    {
        char *tweet = "A crypto do momento é #siscoin, bora comprar?";
        char *correto = "#siscoin";
        char *primeira_hashtag_user = extrai_primeira_hashtag_user(tweet);

        printf("Testes: %s\n", tweet);
        assertExpr(primeira_hashtag_user != NULL, "Hashtag é NULL!");
        if (primeira_hashtag_user != NULL) {
            assertExpr(strcmp(primeira_hashtag_user, correto) == 0, "Hashtag tem valor incorreto!");
            free(primeira_hashtag_user);
        }
    }

    {
        char *tweet = "A Amazônia teve 2.308 focos de calor no mês passado #wwf #greenpeace #queimadas";
        char *correto = "#wwf";
        char *primeira_hashtag_user = extrai_primeira_hashtag_user(tweet);

        printf("Testes: %s\n", tweet);
        assertExpr(primeira_hashtag_user != NULL, "Hashtag é NULL!");
        if (primeira_hashtag_user != NULL) {
            assertExpr(strcmp(primeira_hashtag_user, correto) == 0, "Hashtag tem valor incorreto!");
            free(primeira_hashtag_user);
        }
    }

    {
        char *tweet = "#cultura estreou nesta semana o filme 7 Prisioneiros.";
        char *correto = "#cultura";
        char *primeira_hashtag_user = extrai_primeira_hashtag_user(tweet);

        printf("Testes: %s\n", tweet);
        assertExpr(primeira_hashtag_user != NULL, "Hashtag é NULL!");
        if (primeira_hashtag_user != NULL) {
            assertExpr(strcmp(primeira_hashtag_user, correto) == 0, "Hashtag tem valor incorreto!");
            free(primeira_hashtag_user);
        }
    }

    {
        char *tweet = "Either the well was very deep, or she fell very slowly, for she had plenty of time... #AliceinWonderland";
        char *correto = "#AliceinWonderland";
        char *primeira_hashtag_user = extrai_primeira_hashtag_user(tweet);

        printf("Testes: %s\n", tweet);
        assertExpr(primeira_hashtag_user != NULL, "Hashtag é NULL!");
        if (primeira_hashtag_user != NULL) {
            assertExpr(strcmp(primeira_hashtag_user, correto) == 0, "Hashtag tem valor incorreto!");
            free(primeira_hashtag_user);
        }
    }


    {
        char *tweet = "@alice was beginning to get very tired of sitting by her sister on the bank";
        char *correto = "@alice";
        char *primeira_hashtag_user = extrai_primeira_hashtag_user(tweet);

        printf("Testes: %s\n", tweet);
        assertExpr(primeira_hashtag_user != NULL, "Hashtag é NULL!");
        if (primeira_hashtag_user != NULL) {
            assertExpr(strcmp(primeira_hashtag_user, correto) == 0, "Hashtag tem valor incorreto!");
            free(primeira_hashtag_user);
        }
    }

    {
        char *tweet = "The @dursleys had everything they wanted, but they also had a secret";
        char *correto = "@dursleys";
        char *primeira_hashtag_user = extrai_primeira_hashtag_user(tweet);

        printf("Testes: %s\n", tweet);
        assertExpr(primeira_hashtag_user != NULL, "Hashtag é NULL!");
        if (primeira_hashtag_user != NULL) {
            assertExpr(strcmp(primeira_hashtag_user, correto) == 0, "Hashtag tem valor incorreto!");
            free(primeira_hashtag_user);
        }
    }


    {
        char *tweet = "MR @dursley always sat with his back to the window in his #office on the ninth floor";
        char *correto = "@dursley";
        char *primeira_hashtag_user = extrai_primeira_hashtag_user(tweet);

        printf("Testes: %s\n", tweet);
        assertExpr(primeira_hashtag_user != NULL, "Hashtag é NULL!");
        if (primeira_hashtag_user != NULL) {
            assertExpr(strcmp(primeira_hashtag_user, correto) == 0, "Hashtag tem valor incorreto!");
            free(primeira_hashtag_user);
        }
    }

    {
        char *tweet = "He had #forgotten all about the people in cloaks until he passed a group of them next to the @citybaker";
        char *correto = "#forgotten";
        char *primeira_hashtag_user = extrai_primeira_hashtag_user(tweet);

        printf("Testes: %s\n", tweet);
        assertExpr(primeira_hashtag_user != NULL, "Hashtag é NULL!");
        if (primeira_hashtag_user != NULL) {
            assertExpr(strcmp(primeira_hashtag_user, correto) == 0, "Hashtag tem valor incorreto!");
            free(primeira_hashtag_user);
        }
    }

    printSummary;
}
