#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // Per sleep
#include <stdlib.h> // Per rand

#define NUM_STUDENTI 10
#define NUM_STAMPANTI 3

typedef struct {
	int value;
	pthread_cond_t cond;
	pthread_mutex_t mutex;
} semaphore;

semaphore stampanti_disponibili;

void sem_init (semaphore *sem, int initial_value) {
	sem -> value = initial_value;
	pthread_mutex_init(&sem->mutex, NULL);
	pthread_cond_init(&sem->cond, NULL);
}

// Questo è la funzione V
void sem_post(semaphore *sem) {
	// Vede mutex, se è sbloccato va avanti e lo blocca, se è bloccato si ferma
	pthread_mutex_lock(&sem->mutex);

	sem->value++;

	// Mette la condizione vera o falsa
	pthread_cond_signal(&sem->cond);
	
	// Prende mutex, lo sblocca e va avanti. Se ci sono più mutex bloccati ne libera solo uno.
	pthread_mutex_unlock(&sem->mutex);
}

// Questo è la funzione P
void sem_wait(semaphore *sem) {
	// Vede mutex, se è sbloccato va avanti e lo blocca. Se è bloccato si ferma
	pthread_mutex_lock(&sem->mutex);

	// Controlla se può andare
	while (sem->value == 0) {
		// Se non può, si mette a dormire
		pthread_cond_wait(&sem->cond, &sem->mutex);
	}
	sem->value--;
	pthread_mutex_unlock(&sem->mutex);
}

void sem_destroy(semaphore *sem) {
	if (sem != NULL) {
		pthread_mutex_destroy(&sem->mutex);
		pthread_cond_destroy(&sem->cond);
	}
}

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
	sem_init(&stampanti_disponibili, NUM_STAMPANTI);

	// Fai print
	printf("Ci sono %d STAMPANTI e %d STUDENTI\n", NUM_STAMPANTI, NUM_STUDENTI);
	
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

	printf("Finito!\n");
	return 0;
}

