#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

// QUESTO È IL CUORE DELLA SHELL

int main() {
	char cmd[1024]; //buffer di lunghezza fissa, brutto
    for (;;) {
	if (scanf("%s", cmd) == EOF) break;
	if (fork()) { //legge comando
 		int status;
 	        pid_t stchild;
 	        stchild = wait(&status); // fa fork
        	printf("%d terminated (%d)\n", stchild, WEXITSTATUS(status));
    	} else {
		char *exec_argv[] = { "ls", "-1", "/", NULL};
		execve(cmd, exec_argv, NULL);
		_exit(-1);
    	}
    }
}
