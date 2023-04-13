#include <stdio.h>

int ex3(long *rsi, long *rdx){
    int rcx = rdx;
    int rax = rsi;
    rax = 5 * rax;
    rax = rax + 8 * rcx;
    int rdi = rax;
    rax = rdx;
    rax = rax + 2 * rax + 0x2;
    rsi = rax;
    rdx += 0x35;
    return rax;
}

void main(){

}

// Questao 03
// Implemente aqui uma funcao chamada ex3_solucao