#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

// QUESTO È IL CUORE DELLA SHELL

int main() {
	char cmd[1024]; //buffer di lunghezza fissa (Non si farebbe così, è brutto)
 	
	// La shell ci chiederà comandi finchè non mouore.
	for (;;) {
		// Se l'utente scrive EOF (End Of File), ovvero ctrl+D, la shell viene terminata
		if (scanf("%s", cmd) == EOF) break;
		
		if (fork()) { //legge comando
 			int status;
 		        pid_t stchild;
 		        stchild = wait(&status); // Aspetta che figlio muore e prende il suo status.
        		printf("%d terminated (%d)\n", stchild, WEXITSTATUS(status));
    		} else {
			// Figlio prende argomento ls. Se digita qualcosa oltre a ls non capisce.
			char *exec_argv[] = { "ls", "-1", "/", NULL};
			execve(cmd, exec_argv, NULL);
			_exit(-1);
    		}
    	}
}
