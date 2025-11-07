#include <stdio.h>
#include <unistd.h>

int main() {
	// di solito con lo stesso nomde del programma che lanciamo
	char *exec_argv[] = {"env", NULL};
	char *env_argv[] = { "USER=DULE", "prova=sistemi operativi", NULL };
	printf("pre %d\n", getpid());

	execve("/usr/bin/env", exec_argv, env_argv);

	printf("post %d\n", getpid());
}
