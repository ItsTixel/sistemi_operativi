#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

	printf("pre %d(%d)\n", getpid(), getppid());

	if (fork()) {
		// Dove va il genitore:
        	int status;
        	pid_t stchild;
		// Per 60 secondi, il figlio è morto. Su ps ax | grep (nomefile) ci dirà che il processo figlio è defunto.
		sleep(60);
		
        	printf("parent %d\n", getpid());
        	stchild = wait(&status);
        	printf("%d terminated (%d)\n", stchild, WEXITSTATUS(status));
	} else {
		// Cosa legge il figlio:
        	printf("child %d (%d)\n", getpid(), getppid());
        	_exit(42);
    	}
    	printf("post %d\n", getpid());
}
