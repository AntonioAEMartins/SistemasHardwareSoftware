#include <stdio.h>
#include <unistd.h>
#include <signal.h> // signaction library
#include <stdlib.h> // exit()
#include <sys/types.h> // sigaction type

#define _XOPEN_SOURCE 700

volatile int index = 0;

void sig_handler(int num) {
    index ++;
    if (index == 3){
        struct sigaction handler;
        handler.sa_handler = SIG_DFL;
        handler.sa_flags = 0;
        sigemptyset(&handler.sa_mask);
        sigaction(SIGINT, &handler, NULL);

        kill(getpid(), SIGINT);
    }
}

int main() {
    // Inicio do Handler
    struct sigaction s;
    s.sa_handler = sig_handler;
    sigemptyset(&s.sa_mask);
    s.sa_flags = 0;
    sigaction(SIGINT, &s, NULL);
    // Fim do Handler
    printf("Meu pid: %d\n", getpid());

    while(1) {
        sleep(1);
    }
    return 0;
}
