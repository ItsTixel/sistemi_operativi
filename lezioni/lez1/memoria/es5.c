#include <stdio.h>

typedef enum {
    READ = 1 << 0, // 0001
    WRITE = 1 << 1, // 0010
    EXEC = 1 << 2, // 0100
} Permission;

void print_bits(int number) {
    for (int i=7;i > -1; i--) {
        printf("%d", (number >> i) & 1); 
    }
    printf("\n");
}

int main() {
    Permission p = READ | WRITE; // 0011, ovvero p=3
    print_bits(p);
    p = p & ~EXEC; // 0011 & 1011 -> 0011, rimane lo stesso
    print_bits(p);
    p |= EXEC; // 0011 | 0111 -> 0111
    print_bits(p);
    p=p & ~WRITE; // 0111 & 1101 -> 0101
    print_bits(p);
    return 0;
}

