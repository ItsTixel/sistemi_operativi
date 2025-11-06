#include <stdio.h>
#include <unistd.h>

int main() {
	// di solito con lo stesso nomde del programma che lanciamo
	char *exec_argv[] = {
		"ls", "-1", "/",NULL //NULL per dire che abbiamo finito
	};
	printf("pre %d\n", getpid());

	execve("/usr/bin/ls", exec_argv, NULL);

	// Se l'execve viene eseguito correttamente, questa ultima riga non verrà mai eseguita.
	printf("post %d\n", getpid());
}
