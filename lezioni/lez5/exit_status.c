#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> // Per wait

// Il processo genitore è main()
int main() {
	// Stampa il processo di main e il (genitore di main), ovvero shell.
	printf("pre %d(%d)\n", getpid(), getppid());
	
	// fork "sdoppia" il programma: crea processo figlio (clone di main)
	// 1) main restituirà l'ID del figlio
	// 2) il figlio restituisce 0
	// I PROCESSI ORA PRENDONO STRADE DIVERSE:
	if (fork()) {
		// Dato che nell'if, l'ID del main non ha valore 0, entra nel vero
		int status;

		// Possiamo anche utilizzare int stchild. Preferiamo questo perchè ci dà portabilità (capisce se è short int o long int)
        	pid_t stchild;
        	printf("parent %d\n", getpid());

		// Aspetta che il figlio finisca e salva su status l'exit del figlio (42)
        	stchild = wait(&status);

		// figlio morto :), exit=42
        	printf("%d terminated (%d)\n", stchild, WEXITSTATUS(status));
    	} else {
		// Dato il figlio ha id = 0, entra nel falso
        	sleep(10);
		// Stampa processo del figlio e del main
        	printf("child %d (%d)\n", getpid(), getppid());
        	_exit(42);
	}
	// Il figlio non arriva qua perchè muore prima
	printf("post %d\n", getpid());
}
