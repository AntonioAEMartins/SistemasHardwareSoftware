#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//TODO: Lista Circular
//TODO: Protecao de Buffer
//TODO: Struct (Elementos/Semaphore)

typedef struct{
    sem_t xSemaphore;
    pthread_mutex_t xMutex;
    int capacidade;
    int index;
    int elementos[10];
} threadData;

// sem_t xSemaphore;
// int elementos[10];
// int dados = 0;
// pthread_mutex_t xMutex;

void *thread_produtor(void *arg) {
    // Coletando Arg
    threadData *dados = (threadData *) arg;
    // Randomizando Dado
    srand(time(NULL));
    int r = rand() % 10;
    
    if (dados->index >= dados->capacidade){
        dados->index = 0;
        printf("Lista Cheia\n");
    }
    
    pthread_mutex_lock(&dados->xMutex);
    dados->elementos[dados->index] = r;
    dados->index ++;
    printf("Elemento Escrito: %d\n", r);
    pthread_mutex_unlock(&dados->xMutex);
    sem_post(&dados->xSemaphore);
    sleep(2);
    printf("====Produtos Loop====\n");
}

void *thread_consumidor(void *arg) {
    threadData *dados = (threadData *) arg;
    printf("Esperando Liberacao\n");
    sem_wait(&dados->xSemaphore);
    if (dados->index < 0){
        printf("Nao existem dados\n");
        return;
    }
    pthread_mutex_lock(&dados->xMutex);
    printf("Dado Lido: %d\n", dados->elementos[dados->index-1]);
    dados->index --;
    pthread_mutex_unlock(&dados->xMutex);
    printf("****Consumidor Loop****\n");
    sleep(1);
}

int main(void){
    // Definindo Variaveis
    sem_t dataSemaphore;
    pthread_mutex_t dataMutex;


    sem_init(&dataSemaphore, 0, 0);
    pthread_mutex_init(&dataMutex, NULL);
    

    threadData *dados = malloc(sizeof(threadData));

    dados->xSemaphore = dataSemaphore;
    dados->xMutex = dataMutex;
    dados->capacidade = 10;
    dados->index = 0;

    pthread_t tidProd, tidCons;
    pthread_create(&tidProd, NULL, thread_produtor, dados);
    pthread_create(&tidCons, NULL, thread_consumidor, dados);
}