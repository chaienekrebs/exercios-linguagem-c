#include <stdio.h>
#include <stdlib.h>  // rand(), srand()
#include <time.h>    // time()
#include <omp.h>

#define TAM 100

//variaveis de escopo global
int vetor[TAM], maiorglobal;

int main()
{
    srandom(time(NULL));
    omp_set_num_threads (3);

    maiorglobal = 0;
    int x, z;
    #pragma omp parallel 
    { 
        int maiorlocal = 0;

        #pragma omp for private (z)
        for (z=0; z < TAM; z ++){
            vetor[z] = rand() % TAM;
        }

        #pragma omp for private (x)
        for (x=0; x < TAM; x ++){
            if(maiorlocal < vetor[x]){
                maiorlocal = vetor[x];
            }
        }
 
        #pragma omp critical
        if(maiorlocal> maiorglobal){
            maiorglobal=maiorlocal;
        }

    }

    printf("\n Soma total = %d \n\n", maiorglobal);
}
