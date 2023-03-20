long fun4(long rdi,long rsi){
    long eax;
    if (rdi <= 0){
        goto bloco1;
    }
    eax = 2;
    bloco2:
    return eax * rsi; 

    bloco1: 
    eax = 1;
    goto bloco2;
}

// long fun4(long rdi, long rsi){
//     long eax;
//     if (rdi > 0){
//         eax = 2;

//     } else{
//         eax = 1;
//     }
//     return eax * rsi;
// }
