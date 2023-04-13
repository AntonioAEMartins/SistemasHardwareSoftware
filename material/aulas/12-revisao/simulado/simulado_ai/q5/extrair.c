// Faça seus includes aqui!
#include <stdio.h>
#include <stdlib.h>

void tamanho_string(char *string, int *t_string, int *t_arquivo, int *n_barra){
    int tamanho_string = 0;
    int tamanho_arquivo = 0;
    int index = 0;
    int barra = 0;

    while (1){
        if (string[index] == 0){
            tamanho_arquivo ++;
            tamanho_string ++;
            break;
        }
        if (string[index] == '/'){
            barra ++;
            tamanho_string ++;
            tamanho_arquivo = 0;
        } else{
            tamanho_arquivo ++;
            tamanho_string ++;
        }
        index ++;
    }
    *t_string = tamanho_string;
    *t_arquivo = tamanho_arquivo;
    *n_barra = barra;
}

void extrai_string(char *string, int *t_string, int *t_arquivo, char *nova_string, int *n_barra){
    int tamanho_string = *t_string;
    int tamanho_arquivo = *t_arquivo;
    int numero_barra = *n_barra;
    int index_barra = 0;
    int index = 0;

    for (int i = 0; i < tamanho_string; i++){
        if (index_barra == numero_barra){
            nova_string[index] = string[i];
            index ++;
        }

        if (string[i] == '/'){
            index_barra ++;
        }
    }
}

char *extrair_arquivo(char *url) {
    int numero_barra = 0;
    int *p_barra = &numero_barra;

    int t_string = 0;
    int *p_string = &t_string;

    int t_arquivo = 0;
    int *p_arquivo = &t_arquivo;

    tamanho_string(url, p_string, p_arquivo, p_barra);

    char *nova_string = (char*) malloc(t_arquivo * sizeof(char));

    extrai_string(url, p_string, p_arquivo, nova_string, p_barra);

    return nova_string;
}
