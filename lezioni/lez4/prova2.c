#include <stdio.h>      // output 
#include <stdlib.h>     // random
#include <semaphore.h>  // per sem_t
#include <assert.h>     // test??????
#include <pthread.h>    // prova...
#include <unistd.h>     // Per sleep()

int wcount=0;
int nprocessing = 0
sem_t mutex;   // Semaforo mutex
sem_t waiting; // Semaforo waiting

// Variabili globali:
#define NUM_PROCESS 9
sem_t g_check_mutex;	   // un mutex per contare
int g_processing_check=0;  // Contatore per verificare il vincolo

// Implementazione enter:
void enter() {


}

void 

