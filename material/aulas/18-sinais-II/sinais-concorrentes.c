#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>

int status = 0;

void operacao_lenta() {
    sleep(10);
}


void sigint_handler(int num) {
    status += 1;
    printf("Chamou Ctrl+C; status=%d\n", status);
    operacao_lenta();
    printf("SIGINT: Vou usar status agora! status=%d\n", status);
}

void sigterm_handler(int num) {
    status += 1;
    printf("Recebi SIGTERM; status=%d\n", status);
    operacao_lenta();
    printf("SIGTERM: Vou usar status agora! status=%d\n", status);
}

int main() {

    struct sigaction sigint;
    sigint.sa_handler = sigint_handler;
    sigemptyset(&sigint.sa_mask);
    sigaddset(&sigint_handler.sa_mask, SIGINT);
    sigint.sa_flags = 0;
    sigaction(SIGINT, &sigint, NULL);

    struct sigaction sigterm;
    sigterm.sa_handler = sigterm_handler;
    sigemptyset(&sigterm.sa_mask);
    sigaddset(&sa_handler.sa_mask, SIGINT);
    sigterm.sa_flags = 0;
    sigaction(SIGINT, &sigterm, NULL);

    printf("Meu pid: %d\n", getpid());

    while(1) {
        sleep(1);
    }
    return 0;
}
