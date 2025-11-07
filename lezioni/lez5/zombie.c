#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    printf("pre %d(%d)\n", getpid(), getppid());

    if (fork()) {
        int status;
        pid_t stchild;
	sleep(60);

        printf("parent %d\n", getpid());
        stchild = wait(&status);
        printf("%d terminated (%d)\n", stchild, WEXITSTATUS(status));
    }
    else {
        printf("child %d (%d)\n", getpid(), getppid());
        _exit(42);
    }
    printf("post %d\n", getpid());
}
