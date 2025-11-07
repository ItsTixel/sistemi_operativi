// file: target.c
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    printf("--- SONO IL TARGET ---\n");
    printf("TARGET: Il mio PID è %d\n", getpid());
    printf("TARGET: Sono stato chiamato con l'argomento: %s\n", argv[1]);
    printf("--- TARGET TERMINATO ---\n");
    return 0;
}
