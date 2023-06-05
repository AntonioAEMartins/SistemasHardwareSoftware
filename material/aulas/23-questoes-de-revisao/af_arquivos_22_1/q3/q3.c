// Leia o PDF ou MD antes de iniciar este exercício!

#include <signal.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int fd;

void sigint_handler(int num) {
    time_t now = time(NULL);
    struct tm *tm_struct = localtime(&now);

    int hour = tm_struct->tm_hour;
    int min = tm_struct->tm_min;
    int sec = tm_struct->tm_sec;

    char buffer[43];
    sprintf(buffer, "%02d:%02d:%02d ./q3 finished with signal sigint\n", hour, min, sec);
    write(fd, buffer, 43);

    struct sigaction handler;
    handler.sa_handler = SIG_DFL;
    handler.sa_flags = 0;
    sigemptyset(&handler.sa_mask);
    sigaction(SIGINT, &handler, NULL);
    kill(getpid(), SIGTERM);
}

void sigterm_handler(int num) {
    time_t now = time(NULL);
    struct tm *tm_struct = localtime(&now);

    int hour = tm_struct->tm_hour;
    int min = tm_struct->tm_min;
    int sec = tm_struct->tm_sec;

    char buffer[49];
    sprintf(buffer, "%02d:%02d:%02d ./q3 finished with signal sigterm\n", hour, min, sec);
    write(fd, buffer, 49);

    struct sigaction handler;
    handler.sa_handler = SIG_DFL;
    handler.sa_flags = 0;
    sigemptyset(&handler.sa_mask);
    sigaction(SIGTERM, &handler, NULL);
    kill(getpid(), SIGTERM);
}

int main(char argc, char *argv[]) {

    // Exiba o PID deste processo
    printf("%d", getpid());

    char *arquivo;
    arquivo = argv[1];

    fd = open(arquivo, O_WRONLY | O_CREAT | O_APPEND, 0700);

    time_t now = time(NULL);
    struct tm *tm_struct = localtime(&now);

    int hour = tm_struct->tm_hour;
    int min = tm_struct->tm_min;
    int sec = tm_struct->tm_sec;

    char buffer[22];
    sprintf(buffer, "%d:%d:%d ./q3 started\n", hour, min, sec);
    write(fd, buffer, 22);

    // Registre AQUI seu handler para os sinais!
    struct sigaction sigint;
    sigint.sa_handler = sigint_handler;
    sigemptyset(&sigint.sa_mask);
    sigint.sa_flags = 0;
    sigaction(SIGINT, &sigint, NULL);

    /* TODO: registar SIGTERM aqui. */
    struct sigaction sigterm;
    sigterm.sa_handler = sigterm_handler;
    sigemptyset(&sigterm.sa_mask);
    sigterm.sa_flags = 0;
    sigaction(SIGINT, &sigterm, NULL);

    while(1); // roda infinitamente

    return 0;
}