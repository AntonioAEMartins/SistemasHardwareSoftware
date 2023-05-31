// Leia o PDF ou MD antes de iniciar este exercício!

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// Variável GLOBAL para armazenar o valor de PI aproximado
double pi = 0.0;

// Função que gera um numero aleatorio uniformemente entre 0.0 e 1.0
// Você não deve alterar esta função
double random_zero_one() {
    return (double)random()/(double)RAND_MAX;
}

void sigint_handler(int num) {
    printf("%lf\n", pi);

    FILE *fw = open("pi.txt", O_WRONLY | O_CREAT , 0700);
    char *buffer = (char *) malloc(sizeof(char) * 20);
    sprintf(buffer, "%f" , pi);
    printf("%s", buffer);
    int res = write(fw, buffer, 10);
    printf("RES: %d", res);
    close(fw);
    free(buffer);

    struct sigaction handler;
    handler.sa_handler = SIG_DFL;
    handler.sa_flags = 0;
    sigemptyset(&handler.sa_mask);
    sigaction(SIGINT, &handler, NULL);
    exit(SIGINT);
}

// Função que calcula o valor de pi por simulação (Monte Carlo)
// Você não deve alterar esta função
double aproxima_pi() {
    long dentro = 0;
    long total_pontos = 0;

    double x,y,d;
    while (1) {
        x = random_zero_one();
        y = random_zero_one();
        d = x*x + y*y;
        if (d<=1) {
            dentro++;
        }
        total_pontos++;
        pi = 4.0 * ((double)dentro/(double)total_pontos);
        if (random_zero_one() < 0.008) {
            sleep(1);
        }
    }
}

// Crie AQUI a função que exporta o valor de pi para um arquivo chamado pi.txt
// Esta função deve ser chamada pelo handler quando este for acionado

// Crie AQUI a função que será o handler do sinal

int main() {

    // Exiba o PID deste processo
    printf("%d\n", getpid());
    // Registre AQUI seu handler para o sinal SIGINT!
    struct sigaction handler;

    handler.sa_handler = sigint_handler;
    handler.sa_flags = 0;
    sigemptyset(&handler.sa_mask);

    sigaction(SIGINT, &handler, NULL);


    srand(time(NULL));
    aproxima_pi();

    return 0;
}