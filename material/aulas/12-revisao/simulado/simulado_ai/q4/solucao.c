// Questao 04
// Implemente aqui uma funcao chamada ex4_solucao

int ex4(int rdi[], int rsi, int rdx, int *rcx, int *r8){
    int r11d = rdx;
    int *rcx = 0;
    int *r8 = 0;
    int r9d = 0;

    while (r9d < rsi){
        int rax = rdi[r9d];
        rdx = rax % r11d;

        if (rdx != 0){
            r9d += 1;
        }

        rax = *rcx;
        rax += 1;
        *rcx = rax;
        rax = *r10;
        *r8 = rax;
    }
    return;
}