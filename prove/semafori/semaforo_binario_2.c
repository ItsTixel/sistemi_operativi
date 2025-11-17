#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>

// Quanti cicli per ogni thread
#define NUM_ITERATIONS 1000000
_Atomic int contatore_globale = 0; // int atomico
pthread_mutex_t mutex_contatore;

void* funzione_thread(void* arg) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        
        // --- INIZIO SEZIONE CRITICA ---
        atomic_fetch_add(&contatore_globale, 1); // aggiunge ad contatore 1 (count++)
        // --- FINE SEZIONE CRITICA ---

    }
    return NULL;
}
	
int main() {
    // 1. Inizializza il semaforo con valore 1
    pthread_mutex_init (&mutex_contatore, NULL);
    atomic_init(&contatore_globale, 0);

    // 2. Crea i due thread
    pthread_t thread1, thread2;
    // puntatore thread, attributi thread (NULL = default), funzione_thread che eseguirà, attributi della funzione
    pthread_create(&thread1, NULL, funzione_thread, NULL);
    pthread_create(&thread2, NULL, funzione_thread, NULL);
    
    // 3. Aspetta che entrambi i thread abbiano finito
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    
    // 4. Distruggi il semaforo
    pthread_mutex_destroy(&mutex_contatore);

    // 5. Stampa il risultato finale
    printf("Valore finale del contatore: %d\n", atomic_load(&contatore_globale));
    printf("Valore atteso: %d\n", NUM_ITERATIONS * 2);
    
    return 0;
}
