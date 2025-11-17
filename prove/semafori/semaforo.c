#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> // Per sleep
#include <stdlib.h> // Per rand

#define NUM_STUDENTI 10
#define NUM_STAMPANTI 3

// sem_t inizializza il set di semafori.
sem_t stampanti_disponibili;

void* funzione_studente(void* arg) {
	// long id, recuperiamo l'ID dello studente
	long id = (long)arg;
	
	printf("Studente %ld è in coda per una stampante. \n", id);
	
	// P
	sem_wait(&stampanti_disponibili);

	// --- INIZIO SEZONE CRITICA (limitata a 3 thread) ---
    	printf(">>> Studente %ld STA STAMPANDO\n", id);
    	sleep(rand() % 4); // Simula il tempo di stampa
    	printf("<<< Studente %ld HA FINITO di stampare.\n", id);
    	// --- FINE SEZIONE CRITICA ---
	
	// V
	sem_post(&stampanti_disponibili);

	return NULL;
}

int main () {
	// inizializza 10 threads
	pthread_t threads[NUM_STUDENTI];

	// inizializza i semafori
	sem_init(&stampanti_disponibili, 0, NUM_STAMPANTI);

	// Fai print
	printf("Ci sono %d STAMPANTI e %d STUDENTI", NUM_STAMPANTI, NUM_STUDENTI);
	
	// Creo tutti i thread
	for (long i=0; i<NUM_STUDENTI; i++) {
		pthread_create(&threads[i], NULL, funzione_studente, (void*)i);
	}

	// Aspetta che i thread finiscano
	for (int i=0; i<NUM_STUDENTI; i++) {
		pthread_join(threads[i], NULL);
	}

	// Distruggi i semafori
	sem_destroy(&stampanti_disponibili);

	printf("Pene!");
	return 0;
}

