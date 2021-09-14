#include <stdio.h>
#include <stdlib.h>  // rand(), srand()
#include <time.h>    // time()
#include <omp.h>

#define TAM 10

//variaveis de escopo global
int vetor[TAM], quantidadeglobal;

int main()
{
    srandom(time(NULL));
    omp_set_num_threads (3);

    quantidadeglobal = 0;
    int x, z;
    #pragma omp parallel 
    { 
        int quantidadelocal = 0;

        #pragma omp for private (z)
        for (z=0; z < TAM; z ++){
            int teste =vetor[z] = rand() % TAM;
        }

        #pragma omp for private (x)
        for (x=0; x < TAM; x ++){
            if((vetor[x] % 2)==0){
                quantidadelocal ++;
            }
        }
 
        #pragma omp critical
        if(quantidadelocal> quantidadeglobal){
            quantidadeglobal=quantidadelocal;
        }

    }

    printf("\n Quantidade pares = %d \n\n", quantidadeglobal);
}
