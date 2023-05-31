// Leia o PDF ou MD antes de iniciar este exercício!

#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

// Faça os includes necessários aqui
// #include ...

typedef struct {
    sem_t *s1, *s2, *s3, *s4;
} sem_struct;

void *thread1(void *_arg) {
    sem_struct *dados = (sem_struct *) _arg;

    printf("A\n");
    sem_post(dados->s1); //A chegou na Barreira 1, Libera B
    sem_post(dados->s1); //A chegou na Barreira 1, Libera C
    sem_post(dados->s1); //A chegou na Barreira 1, Libera D
    // Deve esperar a Barreira 2
    sem_wait(dados->s2); // Espera B
    sem_wait(dados->s3); // Espera C
    sem_wait(dados->s4); // Espera D
    printf("E\n");

    return NULL;
}

void *thread2(void *_arg) {
    sem_struct *dados = (sem_struct *) _arg;

    sem_wait(dados->s1); // Espera Barreira 1
    printf("B\n");
    sem_post(dados->s2); //B chegou na Barreira 2, Libera C
    sem_post(dados->s2); //B chegou na Barreira 2, Libera D
    sem_post(dados->s2); //Libera A
    sem_wait(dados->s3); //Espera C
    sem_wait(dados->s4); //Espera D

    return NULL;
}

void *thread3(void *_arg) {
    sem_struct *dados = (sem_struct *) _arg;

    sem_wait(dados->s1); // Espera Barreira 1
    printf("C\n");
    sem_post(dados->s3); //C chegou na Barreira 2, Libera B
    sem_post(dados->s3); //C chegou na Barreira 2, Libera D
    sem_post(dados->s3); //Libera A
    sem_wait(dados->s2); //Espera B
    sem_wait(dados->s4); //Espera D

    return NULL;
}

void *thread4(void *_arg) {
    sem_struct *dados = (sem_struct *) _arg;

    sem_wait(dados->s1); // Espera Barreira 1
    printf("D\n");
    sem_post(dados->s4); //D chegou na Barreira 3, Libera B
    sem_post(dados->s4); //D chegou na Barreira 3, Libera C
    sem_post(dados->s4); //Libera A
    sem_wait(dados->s2); //Espera B
    sem_wait(dados->s3); //Espera C

    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t *pids = malloc(sizeof(pthread_t) * 4);

    sem_t *s1 = malloc(sizeof(sem_t));
    sem_t *s2 = malloc(sizeof(sem_t));
    sem_t *s3 = malloc(sizeof(sem_t));
    sem_t *s4 = malloc(sizeof(sem_t));

    sem_struct *dados = malloc(sizeof(sem_struct));

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

    pthread_join(pids[0],NULL);
    pthread_join(pids[1],NULL);
    pthread_join(pids[2],NULL);
    pthread_join(pids[3],NULL);

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