#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

// Quanti cicli per ogni thread
#define NUM_ITERATIONS 1000000
int contatore_globale = 0;
sem_t semaforo_contatore;

void* funzione_thread(void* arg) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        
        // --- INIZIO SEZIONE CRITICA ---
        sem_wait(&semaforo_contatore); 

        contatore_globale++;
	
        // --- FINE SEZIONE CRITICA ---
	sem_post(&semaforo_contatore);

    }
    return NULL;
}

int main() {
    // 1. Inizializza il semaforo con valore 1
    sem_init(&semaforo_contatore, 0, 1);

    // 2. Crea i due thread
    pthread_t thread1, thread2;
    // puntatore thread, attributi thread (NULL = default), funzione_thread che eseguirà, attributi della funzione
    pthread_create(&thread1, NULL, funzione_thread, NULL);
    pthread_create(&thread2, NULL, funzione_thread, NULL);
    
    // 3. Aspetta che entrambi i thread abbiano finitoi
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    
    // 4. Distruggi il semaforo
    sem_destroy(&semaforo_contatore);

    // 5. Stampa il risultato finale
    printf("Valore finale del contatore: %d\n", contatore_globale);
    printf("Valore atteso: %d\n", NUM_ITERATIONS * 2);
    
    return 0;
}
