// Leia o README antes de iniciar este exercício!


// inclua as bibliotecas necessárias
// #include ...
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

typedef struct {
    sem_t *s1; //A
    sem_t *s2; //D
    sem_t *s3; //E
    sem_t *s4; //B
} sem_struct;

void *thread1(void *_arg) {
    sem_struct *dado = (sem_struct *) _arg;

    printf("A\n");
    sem_post(dado->s1); //A chegou na Barreira 1
    sem_wait(dado->s4); //Espera B
    sem_post(dado->s1); //Libera Thread 2
    sem_post(dado->s1); //Libera Thread 3
    printf("C\n");
    
    return NULL;
}

void *thread2(void *_arg) {
    sem_struct *dado = (sem_struct *) _arg;

    sem_wait(dado->s1); //Espera A
    sem_wait(dado->s4); //Espera B
    printf("D\n");
    sem_post(dado->s2); //D chegou na Barreira 2
    sem_wait(dado->s3); //Espera E
    sem_post(dado->s2); //Libera G

    return NULL;
}

void *thread3(void *_arg) {
    sem_struct *dado = (sem_struct *) _arg;

    sem_wait(dado->s1); //Espera A
    sem_wait(dado->s4); //Espera B
    printf("E\n");
    sem_post(dado->s3); //E chegou na Barreira 2
    sem_wait(dado->s2); //Espera D
    sem_post(dado->s3); //Libera G
    printf("F\n");
    
    return NULL;
}

void *thread4(void *_arg) {
    sem_struct *dado = (sem_struct *) _arg;

    printf("B\n");
    sem_post(dado->s4); //B chegou na Barreira 2
    sem_wait(dado->s1); //Espera A
    sem_post(dado->s4); //Libera D
    sem_post(dado->s4); //Libera E
    sem_wait(dado->s2); //Espera D
    sem_wait(dado->s3); //Espera E
    printf("G\n");

    return NULL;
}

int main(int argc, char *argv[]) {
    // Inicializando todas Memorias
    pthread_t *pids = malloc(sizeof(pthread_t) * 4);

    sem_t *s1 = malloc(sizeof(sem_t));
    sem_t *s2 = malloc(sizeof(sem_t));
    sem_t *s3 = malloc(sizeof(sem_t));
    sem_t *s4 = malloc(sizeof(sem_t));

    sem_struct *dados =  malloc(sizeof(sem_struct));

    sem_init(s1, 0, 0);
    sem_init(s2, 0, 0);
    sem_init(s3, 0, 0);
    sem_init(s4, 0, 0);

    dados->s1 = s1;
    dados->s2 = s2;
    dados->s3 = s3;
    dados->s4 = s4;

    pthread_create(&pids[0], NULL, thread1, dados);
    pthread_create(&pids[1], NULL, thread2, dados);
    pthread_create(&pids[2], NULL, thread3, dados);
    pthread_create(&pids[3], NULL, thread4, dados);

    pthread_join(pids[0], NULL);
    pthread_join(pids[1], NULL);
    pthread_join(pids[2], NULL);
    pthread_join(pids[3], NULL);

    sem_destroy(s1);
    sem_destroy(s2);
    sem_destroy(s3);
    sem_destroy(s4);

    free(s1);
    free(s2);
    free(s3);
    free(s4);

    free(pids);
    free(dados);

    return 0;
}