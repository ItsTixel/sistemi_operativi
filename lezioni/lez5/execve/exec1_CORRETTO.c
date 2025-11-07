#include <stdio.h>
#include <unistd.h> 

int main() {
	char *exec_argv[] = {"bash", NULL}; // Il primo argomento è BASH
	char *env_argv[] = { "USER=dule", "prova=sistemi operativi", NULL };
	
	printf("pre %d\n", getpid());

	// Abbiamo messo un indirizzo corretto. 
	execve("/bin/bash", exec_argv, env_argv);
	
	// Questo messaggio NON VERRÀ eseguito, dato che execve avrà successo.
	printf("post %d\n", getpid());
}
