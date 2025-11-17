#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> // Per sleep()

// Numero di thread lettori e scrittori da creare
#define NUM_READERS 5
#define NUM_WRITERS 2

/**
 * Questa struttura rappresenta il Monitor "RWController".
 * Contiene le variabili di stato e gli strumenti di sincronizzazione.
 */
typedef struct {
    int nr; // number of readers (numero di lettori attivi)
    int nw; // number of writers (numero di scrittori attivi, sarà 0 o 1)

    // Un mutex per garantire l'esclusione reciproca all'interno
    // delle procedure del monitor (startRead, endRead, ecc.)
    pthread_mutex_t lock;

    // Variabile di condizione su cui i lettori attendono
    pthread_cond_t okToRead; // Attendi qui se nw > 0

    // Variabile di condizione su cui gli scrittori attendono
    pthread_cond_t okToWrite; // Attendi qui se nr > 0 o nw > 0

} RWController;

// Istanza globale del nostro monitor
RWController rwController;

/**
 * Inizializza le variabili del monitor.
 */
void RWController_Init(RWController *ctrl) {
    ctrl->nr = 0;
    ctrl->nw = 0;
    pthread_mutex_init(&ctrl->lock, NULL);
    pthread_cond_init(&ctrl->okToRead, NULL);
    pthread_cond_init(&ctrl->okToWrite, NULL);
}

/**
 * Distrugge gli strumenti di sincronizzazione.
 */
void RWController_Destroy(RWController *ctrl) {
    pthread_mutex_destroy(&ctrl->lock);
    pthread_cond_destroy(&ctrl->okToRead);
    pthread_cond_destroy(&ctrl->okToWrite);
}

// --- Procedure del Monitor ---

/**
 * Chiamato da un lettore prima di accedere alla risorsa.
 */
void startRead(RWController *ctrl) {
    // Entra nel monitor (acquisisce il lock)
    pthread_mutex_lock(&ctrl->lock);

    // Attende finché c'è uno scrittore attivo.
    // NOTA: Usiamo 'while' invece di 'if' per gestire "risvegli spuri".
    // È la pratica standard e più robusta per le variabili di condizione.
    while (ctrl->nw > 0) {
        // Rilascia atomicamente il lock e si mette in attesa
        pthread_cond_wait(&ctrl->okToRead, &ctrl->lock);
        // Al risveglio, ri-acquisisce atomicamente il lock
    }

    // Incrementa il contatore dei lettori attivi
    ctrl->nr++;

    // Esce dal monitor (rilascia il lock)
    pthread_mutex_unlock(&ctrl->lock);
}

/**
 * Chiamato da un lettore dopo aver avuto accesso alla risorsa.
 */
void endRead(RWController *ctrl) {
    // Entra nel monitor
    pthread_mutex_lock(&ctrl->lock);

    // Decrementa il contatore dei lettori
    ctrl->nr--;

    // Se questo era l'ULTIMO lettore, deve segnalare
    // a uno scrittore in attesa che ora può procedere.
    if (ctrl->nr == 0) {
        pthread_cond_signal(&ctrl->okToWrite);
    }

    // Esce dal monitor
    pthread_mutex_unlock(&ctrl->lock);
}

/**
 * Chiamato da uno scrittore prima di accedere alla risorsa.
 */
void startWrite(RWController *ctrl) {
    // Entra nel monitor
    pthread_mutex_lock(&ctrl->lock);

    // Attende finché ci sono lettori attivi O
    // un altro scrittore è attivo.
    while (ctrl->nr > 0 || ctrl->nw > 0) {
        pthread_cond_wait(&ctrl->okToWrite, &ctrl->lock);
    }

    // Imposta il contatore degli scrittori attivi a 1
    ctrl->nw++;

    // Esce dal monitor
    pthread_mutex_unlock(&ctrl->lock);
}

/**
 * Chiamato da uno scrittore dopo aver avuto accesso alla risorsa.
 */
void endWrite(RWController *ctrl) {
    // Entra nel monitor
    pthread_mutex_lock(&ctrl->lock);

    // Imposta il contatore degli scrittori attivi a 0
    ctrl->nw--;

    // Chi svegliare?
    // In questa implementazione (preferenza lettori):
    // 1. Sveglia TUTTI i lettori in attesa (broadcast).
    // 2. Sveglia UN solo scrittore in attesa (signal).
    //
    // I lettori svegliati controlleranno la condizione (nw == 0),
    // la troveranno vera ed entreranno. Lo scrittore svegliato
    // controllerà (nr > 0 || nw > 0), troverà nr > 0 e
    // tornerà a dormire. Questo dà preferenza ai lettori.
    pthread_cond_broadcast(&ctrl->okToRead);
    pthread_cond_signal(&ctrl->okToWrite);

    // Esce dal monitor
    pthread_mutex_unlock(&ctrl->lock);
}

// --- Processi (Thread) ---

/**
 * La funzione eseguita dal thread Lettore.
 */
void *reader_process(void *arg) {
    long id = (long)arg;

    while (1) {
        // Simula un po' di lavoro prima di provare a leggere
        sleep(rand() % 5 + 2);

        printf("[Lettore %ld] Vuole leggere.\n", id);
        startRead(&rwController);

        // --- Sezione Critica (Lettura) ---
        printf("    [Lettore %ld] STA LEGGENDO... (Lettori attivi: %d)\n", id, rwController.nr);
        sleep(rand() % 3 + 1); // Simula il tempo di lettura
        printf("    [Lettore %ld] Ha finito di leggere.\n", id);
        // --- Fine Sezione Critica ---

        endRead(&rwController);
    }
    return NULL;
}

/**
 * La funzione eseguita dal thread Scrittore.
 */
void *writer_process(void *arg) {
    long id = (long)arg;

    while (1) {
        // Simula un po' di lavoro prima di provare a scrivere
        sleep(rand() % 8 + 3);

        printf("[Scrittore %ld] Vuole scrivere.\n", id);
        startWrite(&rwController);

        // --- Sezione Critica (Scrittura) ---
        // (Notare che nr DEVE essere 0 e nw DEVE essere 1 qui)
        printf("        [Scrittore %ld] STA SCRIVENDO... (Lettori: %d, Scrittori: %d)\n", id, rwController.nr, rwController.nw);
        sleep(rand() % 4 + 2); // Simula il tempo di scrittura
        printf("        [Scrittore %ld] Ha finito di scrivere.\n", id);
        // --- Fine Sezione Critica ---

        endWrite(&rwController);
    }
    return NULL;
}

/**
 * Funzione Main: inizializza il monitor e crea i thread.
 */
int main() {
    pthread_t readers[NUM_READERS];
    pthread_t writers[NUM_WRITERS];
    long i;

    // Inizializza il generatore di numeri casuali
    srand(time(NULL));

    // Inizializza il nostro "monitor"
    RWController_Init(&rwController);

    printf("Creazione di %d Lettori e %d Scrittori...\n", NUM_READERS, NUM_WRITERS);

    // Crea i thread lettori
    for (i = 0; i < NUM_READERS; i++) {
        if (pthread_create(&readers[i], NULL, reader_process, (void *)i) != 0) {
            perror("Errore creazione thread lettore");
            return 1;
        }
    }

    // Crea i thread scrittori
    for (i = 0; i < NUM_WRITERS; i++) {
        if (pthread_create(&writers[i], NULL, writer_process, (void *)i) != 0) {
            perror("Errore creazione thread scrittore");
            return 1;
        }
    }

    // Attende la terminazione di tutti i thread (non accadrà mai
    // perché i loop sono infiniti, ma è buona pratica)
    for (i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    for (i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    // Pulisce le risorse (non verrà mai raggiunto in questo esempio)
    RWController_Destroy(&rwController);

    return 0;
}
