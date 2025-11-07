#include <stdio.h>
#include <stdlib.h>      // Per rand()
#include <unistd.h>      // Per sleep()
#include <pthread.h>
#include <semaphore.h>
#include <assert.h>      // Per il test

// --- Definizione dal tuo pseudocodice ---

int wcount = 0;
int processing = 0;
sem_t mutex;
sem_t waiting;

// --- Variabili globali per il test ---
#define NUM_PROCESSI 9   // Prova con un multiplo di 3
sem_t g_check_mutex;     // Un mutex separato per il contatore di test
int g_processing_check = 0; // Contatore per verificare il vincolo

/**
 * @brief Implementazione di enter() come da pseudocodice.
 */
void enter() {
    sem_wait(&mutex); // mutex.P()
    wcount++;
    printf("... (Processo in attesa. Totale in attesa: %d)\n", wcount);

    if (!(wcount >= 3 && processing == 0)) {
        sem_post(&mutex); // mutex.V()
        sem_wait(&waiting); // waiting.P() - Si blocca qui
    } else {
        printf("!!! Gruppo di 3 pronto (wcount=%d, processing=%d). Si parte!\n", wcount, processing);
        // NON rilascia il mutex qui. Lo passerà a catena.
    }

    // Questa parte viene eseguita solo dopo essere stato sbloccato
    // o se era il 3° processo a sbloccare.
    wcount--;
    processing++;

    if (processing < 3) {
        // "Passa il testimone" (il segnale) al prossimo processo in attesa
        sem_post(&waiting); // waiting.V()
    } else {
        // L'ultimo (il 3°) processo ad entrare rilascia il mutex
        // che il primo (quello che ha sbloccato) aveva preso.
        sem_post(&mutex); // mutex.V()
    }
}

/**
 * @brief Implementazione di exit() come da pseudocodice.
 */
void exit_section() {
    sem_wait(&mutex); // mutex.P()
    processing--;

    if (processing == 0 && wcount >= 3) {
        printf("!!! Ultimo processo uscito. Avvio nuovo gruppo (attesa: %d).\n", wcount);
        // L'ultimo ad uscire sblocca UN processo del prossimo gruppo.
        sem_post(&waiting); // waiting.V()
        // Questo processo (P_sbloccato) farà poi V() su P_sbloccato+1,
        // e P_sbloccato+1 farà V() su P_sbloccato+2.
    } else {
        sem_post(&mutex); // mutex.V()
    }
}

/**
 * @brief Simula l'elaborazione e verifica il vincolo dei 3 processi.
 */
void elabora_e_testa(long id) {
    // --- INIZIO SEZIONE CRITICA REALE ---
    
    // Controlliamo il numero di processi attivi
    sem_wait(&g_check_mutex);
    g_processing_check++;
    printf("-> Processo %ld ENTRA. (ATTIVI ORA: %d)\n", id, g_processing_check);
    
    // Questo assert fallirà se la logica è sbagliata e g_processing_check > 3
    assert(g_processing_check <= 3); 
    
    sem_post(&g_check_mutex);

    // Simula lavoro
    sleep(rand() % 3 + 1);

    // Controlliamo di nuovo prima di uscire
    sem_wait(&g_check_mutex);
    g_processing_check--;
    printf("<- Processo %ld ESCE. (ATTIVI ORA: %d)\n", id, g_processing_check);
    sem_post(&g_check_mutex);
    
    // --- FINE SEZIONE CRITICA REALE ---
}

/**
 * @brief La funzione eseguita da ogni thread (processo).
 */
void* worker_process(void* arg) {
    long id = (long)arg;

    while (1) {
        printf("Processo %ld tenta di entrare...\n", id);
        
        enter();
        
        elabora_e_testa(id);
        
        exit_section();
        
        // Pausa prima di ricominciare il ciclo
        printf("Processo %ld in pausa.\n", id);
        sleep(rand() % 5 + 2);
    }
    return NULL;
}

/**
 * @brief Main: Inizializza semafori e crea i thread.
 */
int main() {
    pthread_t threads[NUM_PROCESSI];

    // Inizializza i semafori
    // sem_init(semaforo, pshared, valore_iniziale)
    // pshared = 0 -> condiviso tra thread dello stesso processo
    sem_init(&mutex, 0, 1);
    sem_init(&waiting, 0, 0);
    sem_init(&g_check_mutex, 0, 1);
    
    printf("Avvio di %d processi...\n", NUM_PROCESSI);

    // Crea i thread
    for (long i = 0; i < NUM_PROCESSI; i++) {
        pthread_create(&threads[i], NULL, worker_process, (void*)i);
    }

    // Attende la fine dei thread (non succederà mai per via del while(1))
    for (int i = 0; i < NUM_PROCESSI; i++) {
        pthread_join(threads[i], NULL);
    }

    // Distrugge i semafori (non verrà raggiunto in questo esempio)
    sem_destroy(&mutex);
    sem_destroy(&waiting);
    sem_destroy(&g_check_mutex);

    return 0;
}
