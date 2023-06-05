// Leia o enunciado antes de iniciar este exercício!

// inclua libs aqui!

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct
{
    char *palavra; // palavra a ser classificada
    int res;       // retorno da thread virá aqui!
    sem_t semaphore;
} t_arg;

#define MAX_LINE_LENGTH 256

int classifier(char *palavra)
{
    int sleep_time = rand() % 1 + 4;

    // Espera por uma qtde aleatória de segundos
    sleep(sleep_time);

    int soma = 157;
    for (int i = 0; palavra[i] != '\0'; i++)
    {
        soma += palavra[i];
    }

    int res = (soma % 3);
    return res;
}

void *classifier_thread(void *_arg)
{
    t_arg *arg = _arg;
    sem_wait(&arg->semaphore);
    arg->res = classifier(arg->palavra);
    sem_post(&arg->semaphore);
}

char *read_line(int fd) {
    // Seu código aqui!
    char buf;
    int bytes_lidos;
    int tamanho_linha = 0;
    while(1){
        bytes_lidos = read(fd, &buf, 1);
        if (buf == '\n' || bytes_lidos <= 0){
            break; // Arquivo terminou
        }
        tamanho_linha ++;
    }
    if (tamanho_linha == 0){
        return NULL;
    }

    lseek(fd, -(tamanho_linha + 1), SEEK_CUR); // Volto a linha que acabei de contar
    char *linha = (char *) malloc(sizeof(char) * tamanho_linha + 1);
    int linha_index = 0;
    while(1){
        bytes_lidos = read(fd, &buf, 1);
        if (buf == '\n' || bytes_lidos <= 0){
            break; //Acabou a linha
        }
        linha[linha_index] = buf;
        linha_index ++;
    }
    linha[linha_index] = '\0';
    return linha;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("USAGE:\n./q4 <n_threads> <file_name>\n");
        return 0;
    }
    int n_threads = atoi(argv[1]); // Info da linha de comando
    sem_t semaphore;
    sem_init(&semaphore, 0, n_threads);
    char *file_name = argv[2];     // Info da linha de comando
    int fd1 = open(file_name, O_RDONLY);
    int thread_on = 0;
    if (fd1 == -1) {
        fprintf(stderr, "Falha ao abrir o arquivo!\n");
        exit(EXIT_FAILURE);
    }
    srand(time(NULL));
    int threads_limit = 2; // Vamos começar alocando espaço para 02 threads
    pthread_t *tids = malloc(sizeof(pthread_t) * threads_limit);
    t_arg **args = malloc(sizeof(t_arg *) * threads_limit);
    int threads_created = 0; // Quantas threads criei de fato
    for (int i = 0;; i++)
    {
        // Tenta ler uma palavra
        char *palavra = read_line(fd1);
        // Para quando não conseguir mais ler
        if (palavra == NULL)
        {
            break;
        }
        t_arg *arg = malloc(sizeof(t_arg));
        // Passa a palavra para a thread
        arg->palavra = palavra;
        arg->semaphore = semaphore;
        // Realoca se necessário
        if (threads_limit == threads_created)
        {
            threads_limit *= 2;
            tids = realloc(tids, sizeof(pthread_t) * threads_limit);
            args = realloc(args, sizeof(t_arg *) * threads_limit);
        }

        args[i] = arg;
        pthread_create(&tids[i], NULL, classifier_thread, arg);
        printf("CRIOU THREAD %02d PARA PROCESSAR A PALAVRA %s\n", i, arg->palavra);
        threads_created++;
    }

    // Complete a main!
    int resultado;
    int classe0 = 0;
    int classe1 = 0;
    int classe2 = 0;
    for (int i = 0; i < threads_created; i++){
        pthread_join(tids[i], (void *) NULL);
        printf("THREAD %.2d TERMINOU COM O RESULTADO %d\n", i, args[i]->res);
        if (args[i]->res == 0){
            classe0 ++;
        } else if (args[i]->res == 1){
            classe1 ++;
        } else if (args[i]->res == 2){
            classe2 ++;
        }
        free(args[i]->palavra);
        free(args[i]);
    }

    printf("Resultado:\n");
    printf("TOTAL CLASSE 0: %d\n", classe0);
    printf("TOTAL CLASSE 1: %d\n", classe1);
    printf("TOTAL CLASSE 2: %d\n", classe2);

    free(args);
    free(tids);
    close(fd1);

    return 0;
}
