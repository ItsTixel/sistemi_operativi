#include <stdio.h>
#include <unistd.h>

int main() {
	// Definisce gli argomenti per il nuovo programma, in questo caso non c'è nulla.
	// di solito il primo elemento ha lo stesso nome del programma che lanciamo
	char *exec_argv[] = {
		"bash", NULL //NULL per dire che abbiamo finito
	};

	// Definisce un nuovo ambiente per il programma
	char *env_argv[] = { "USER=dule", "prova=sistemi operativi", NULL };
	
	// Stampa l'ID del processo
	printf("pre %d\n", getpid());

	// Il sistema tenta di trovare 
	execve("/usr/bash", exec_argv, env_argv);
	
	// Questo messaggio non verrà mai eseguito
	printf("post %d\n", getpid());
}
