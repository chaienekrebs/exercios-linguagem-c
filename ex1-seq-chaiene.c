#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <time.h>

#define TAM 1000

int main(){
    int i, vet[TAM];
    int maior = 0;
    srand(time(NULL));
    for(i = 0; i < TAM; i++){
        vet[i] = rand() %TAM;
        if(maior < vet[i]){
            maior = vet[i];
        }
        printf("\nNa posição %d, número %d\n", i, vet[i]);
    }
    printf("\nO maior numero é: %d\n", maior);

}
