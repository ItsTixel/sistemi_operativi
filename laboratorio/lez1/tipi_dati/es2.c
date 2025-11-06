#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>

int main() {
    intmax_t a = INTMAX_MAX;
    // pridmax calcola il formato corretto per stampare un intmax_t
    printf("intmax_t: %" PRIdMAX "\n", a); 
    return 0;
} 
