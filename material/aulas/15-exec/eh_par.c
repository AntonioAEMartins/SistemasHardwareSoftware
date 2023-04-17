#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

long main(int argc, char *argv[]){
    return !(atol(argv[1]) % 2);
}