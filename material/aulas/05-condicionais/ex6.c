int ex6(long rdi, long rsi){
    if (rdi <= rsi){
        goto bloco1;
    }

    rsi = rdi;
    bloco1:
    if (rdi <= 0){
        goto bloco2;
    }
    return -rsi;
    bloco2:
    return rsi;
}