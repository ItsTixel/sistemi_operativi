#include <stdio.h>
#include <unistd.h> // Per le system call POSIX
// Per chiedere all'accesso di una risorsa, il programma richiede questa system call al kernel

int main() {
	// Definisce gli argomenti per il nuovo programma, in questo caso non c'è nulla.
	// di solito il primo elemento ha lo stesso nome del programma che lanciamo
	char *exec_argv[] = {
		"bash", NULL //NULL per dire che abbiamo finito
	};

	// Definisce un nuovo ambiente per il programma. Un ambiente è un insieme di Variabili utilizzate nel programma.
	char *env_argv[] = { "USER=dule", "prova=sistemi operativi", NULL };
	// Per esempio, quando scriviamo ls nel terminale, non sa dov'è il programma ls, quindi consulta le variabili di PATH.
	// PATH contiene una lista di cartelle (es: PATH=/usr/bin:/bin:/usr/local/bin)
	// Bash controlla in /usr/bin il programma ls -> non lo trova -> lo cerca su /bin -> lo trova -> lo esegue.
	
	// Stampa l'ID del processo. getpid = GET Process ID
	printf("pre %d\n", getpid());
	
	// execve: interrompe il programma corrente (nel nostro caso exec1.c) -> butta via il codice e i dati -> carica ed esegue il nuovo programma ("bash")
	// Il sistema tenta di trovare il processo nell'environment,. Il suo output è -1. 
	execve("/usr/bash", exec_argv, env_argv);
	
	// Questo messaggio VERRÀ eseguito, dato che execve fallirà.
	printf("post %d\n", getpid());
}
