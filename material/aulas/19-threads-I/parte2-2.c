#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

void *minha_thread(void *arg) {
    int *i = (int *) arg;
    printf("Hello thread! %d\n", *i);

    return NULL;
}

pthread_t *criar_threads(int n) {
    pthread_t *tids = malloc(sizeof(pthread_t) * n);

    for (int i = 0; i < n; i++) {
        pthread_create(&tids[i], NULL, minha_thread, &i);
    }

    return tids;
}

int main() {
    pthread_t *tids = criar_threads(4);

    for (int i = 0; i < 4; i++) {
        pthread_join(tids[i], NULL);
    }

    return 0;

    // Exercicio 7:
    // O problema das funcoes na forma que sao implementadas. eh que o arquivo
    // principal pode estar rodando a main, criando novas threads ao mesmo moemntos que outras threads
    // ja estao rodando. Isso ira fazer com que o pthread_join sera rodado depois da criacao e finalizacao de algumas threads
}