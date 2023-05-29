#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int dado1;
    int dado2;
} dados;

void *minha_thread(void *arg) {
    int *i = (int *) arg;
    printf("Hello thread! %d\n", *i);

    return NULL;
}

void *print_thread(void *arg){
    dados *dado = (dados *) arg;
    printf("Dado1: %d, Dado2: %d\n", dado->dado1, dado->dado2);

    return NULL;
}


int main() {
    // pthread_t tid[4];

    pthread_t tid1;
    dados *vi = malloc(sizeof(dados));
    vi->dado1 = 1;
    vi->dado2 = 2;

    // for (int i = 0; i < 4; i++) {
    //     pthread_create(&tid[i], NULL, minha_thread, &vi[i]);
    // }
    
    
    // for (int i = 0; i < 4; i++) {
    //     pthread_join(tid[i], NULL);
    // }

    pthread_create(&tid1, NULL, print_thread, vi);
    pthread_join(tid1, NULL);
    
    return 0;
}
