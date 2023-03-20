// long ex5(long rdi, long rsi){
//     if (rdi > 0 && rsi <= 0){
//         goto bloco1;
//     }
//     return rsi - 2;

//     bloco1:
//     return rdi + 5;
// }

float ex5(float rdi, float rsi){
    if (rdi <= 0 && rsi > 0){
        return rsi - 2;
    } else{
        return rdi + 5;
    }
}