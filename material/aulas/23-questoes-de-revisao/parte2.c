#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

// linha de compilação: 

/* declarar tarefas aqui e lançar no main */
/* cada bloco na figura deverá ser representado por um print com sua letra */

typedef struct {
    sem_t *s1, *s2, *s3, *s4, *s5;
} t_arg;

void *threadA(void *args){
    t_arg *dado = (t_arg *) args;

    printf("A\n");
    sem_post(dado->s1); // A chegou na barreira 1
    sem_wait(dado->s2); // Checa se B chegou na barreira 2
    printf("C\n");
    return;
}

void *threadB(void *args){
    t_arg *dado = (t_arg *) args;

    printf("B\n");
    // 1 barreira
    sem_post(dado->s2); // B chegou na barreira 2
    sem_wait(dado->s1); // Checa se A chegou na barreira 1
    // 2 barreira
    sem_post(dado->s2); // B chegou na barreira 3
    sem_post(dado->s2); // B chegou na barreira 3
    sem_wait(dado->s4); // Checa se E chegou na barreira 3
    sem_wait(dado->s5); // Checa se G chegou na barreira 3
    printf("D\n");
    return;
}

void *threadE(void *args){
    t_arg *dado = (t_arg *) args;

    printf("E\n");
    sem_post(dado->s4); // E chegou na barreira 3
    sem_post(dado->s4); // E chegou na barreira 3
    sem_wait(dado->s2); // Checa se B chegou na barreira 3
    sem_wait(dado->s5); // Checa se G chegou na barreira 3
    printf("F\n");
    return;
}

void *threadG(void *args){
    t_arg *dado = (t_arg *) args;

    printf("G\n");
    sem_post(dado->s5); // E chegou na barreira 3
    sem_post(dado->s5); // E chegou na barreira 3
    sem_wait(dado->s2); // Checa se B chegou na barreira 3
    sem_wait(dado->s4); // Checa se E chegou na barreira 3
    printf("H\n");
    return;
}


int main() {
    // Alocando memoria para Operacoes
    t_arg *problem_structure = malloc(sizeof(t_arg));
    pthread_t *tids = malloc(sizeof(pthread_t) * 4);
    
    sem_t *s1 = malloc(sizeof(sem_t));
    sem_t *s2 = malloc(sizeof(sem_t));
    sem_t *s3 = malloc(sizeof(sem_t));
    sem_t *s4 = malloc(sizeof(sem_t));
    sem_t *s5 = malloc(sizeof(sem_t));

    sem_init(s1, 0, 0);
    sem_init(s2, 0, 0);
    sem_init(s3, 0, 0);
    sem_init(s4, 0, 0);
    sem_init(s5, 0, 0);

    problem_structure->s1 = s1;
    problem_structure->s2 = s2;
    problem_structure->s3 = s3;
    problem_structure->s4 = s4;
    problem_structure->s5 = s5;

    pthread_create(&tids[0], NULL, threadA, problem_structure);
    pthread_create(&tids[1], NULL, threadB, problem_structure);
    pthread_create(&tids[2], NULL, threadE, problem_structure);
    pthread_create(&tids[3], NULL, threadG, problem_structure);

    pthread_join(tids[0], NULL);
    pthread_join(tids[1], NULL);
    pthread_join(tids[2], NULL);
    pthread_join(tids[3], NULL);

    // Desalocamento de memoria e semaphores
    sem_destroy(s1);
    sem_destroy(s2);
    sem_destroy(s3);
    sem_destroy(s4);
    sem_destroy(s5);

    free(s1);
    free(s2);
    free(s3);
    free(s4);
    free(s5);

    free(tids);
    free(problem_structure);
    return 0;
}
