#include <pthread.h>
#include <stdio.h>
#include "tempo.h"
#include <pthread.h>

#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <termios.h>

#include <sys/wait.h>  //wait
#include <stdlib.h>  // rand(), srand()
#include <time.h>    // time()

#define TAM 100

//variaveis de escopo global
int vetor[TAM], maiorglobal;
pthread_mutex_t m;

void inicializa_vetor();
void *verifica_maior(void *arg);

int main(int argc, char *argv[])
{
	srandom(time(NULL));
	tempo1();

	pthread_t 	t1, t2, t3, t4;
	int 		x, y, z, w;

	inicializa_vetor();
	
	pthread_mutex_init(&m,NULL);
	maiorglobal = 0;

	x = 0;	
	pthread_create(&t1, NULL, verifica_maior, (void *)&x);

	y = TAM / 4;	
	pthread_create(&t2, NULL, verifica_maior, (void *)&y);

	z = TAM / 4 * 2;	
	pthread_create(&t3, NULL, verifica_maior, (void *)&z);

	w = TAM / 4 * 3;	
	pthread_create(&t4, NULL, verifica_maior, (void *)&w);


	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	pthread_join(t3, NULL);
	pthread_join(t4, NULL);

	printf("\n Soma total = %d \n\n", maiorglobal);

	tempo2();
	tempoFinal("mili segundos", argv[0], MSGLOG); 
}

void inicializa_vetor()
{
	int z;
	printf("\n inicializando vetor ...\n");
	for (z=0; z < TAM; z ++)
		vetor[z] = rand() % TAM;
}


void * verifica_maior(void *arg)
{
	int x, pos = *((int*)arg);
	int maiorlocal = 0;

	pthread_t pid = pthread_self();
       // sleep(5);
	printf("\n calculando %d...\n", pos);
	for (x=pos; x < (pos+TAM/4); x ++){
		if(maiorlocal < vetor[x]){
			maiorlocal = vetor[x];
		}
	}


	pthread_mutex_lock(&m);
	printf("\n maior local...%d \n", maiorlocal);
	if(maiorglobal < maiorlocal){
		maiorglobal = maiorlocal;
	}
	pthread_mutex_unlock(&m);


	pthread_exit(NULL);
}
