// file: chiamante.c
#include <stdio.h>
#include <unistd.h>
#include <errno.h> // Per stampare gli errori

int main() {
    printf("+++ SONO IL CHIAMANTE +++\n");
    printf("CHIAMANTE: Il mio PID è %d\n", getpid());
    printf("CHIAMANTE: Sto per chiamare execve...\n\n");

    // Argomenti per 'target': {"./target", "ciao", NULL}
    char *exec_argv[] = {
        "./target",       // argv[0] = nome del programma
        "ciao-da-chiamante", // argv[1] = un argomento
        NULL              // Fine della lista
    };

    // 'execve' sostituirà questo processo con "./target"
    // Passiamo NULL come ambiente per fargli ereditare il nostro.
    execve("./target", exec_argv, NULL);

    // --- QUESTA PARTE VIENE ESEGUITA SOLO SE EXECVE FALLISCE ---
    // 'perror' stampa un messaggio d'errore leggibile
    perror("CHIAMANTE: ERRORE in execve");
    printf("CHIAMANTE: Il mio PID è ancora %d\n", getpid());
    return 1;
}
