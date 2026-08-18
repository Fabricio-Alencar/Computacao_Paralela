#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define N 10000000
#define NUM_THREADS 4
int *v;
long long total=0; //global 

void *soma_trecho(void *arg) {
    long tid = (long) arg;
    long ini = tid * (N / NUM_THREADS);
    long fim = (tid + 1) * (N / NUM_THREADS);
    for (long i = ini; i < fim; i++)
        total += v[i]; // <<< CONDICAO DE CORRIDA
    return NULL;
}

int main(void){
    v = malloc(N*sizeof(int));
    pthread_t threads[NUM_THREADS]; //array de threads
    for(int i=0 ;i<N; i++){
        v[i] = 10;
    }

    for(long t=0 ;t<NUM_THREADS; t++){
        pthread_create(&threads[t],NULL, soma_trecho,(void*)t);
    }

    for(long t=0 ;t<NUM_THREADS; t++){
        pthread_join(threads[t],NULL);
    }
    
    printf("soma esperada:%lld\n", (long long)N*10);
    printf("soma calculado:%lld\n", total);
}