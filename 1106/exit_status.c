#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    printf("pre %d(%d)\n", getpid(), getppid());

    if (fork()) {
        int status;
        pid_t stchild;
        printf("parent %d\n", getpid());
        stchild = wait(&status);
        printf("%d terminated (%d)\n", stchild, WEXITSTATUS(status));
    }
    else {
        sleep(2);
        printf("child %d (%d)\n", getpid(), getppid());
        _exit(42);
    }
    printf("post %d\n", getpid());
}
