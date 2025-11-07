#include <stdio.h>
#include <stdlib.h>

int* genera_array(int n) {
    int *arr = (int*)malloc(n * sizeof(int)); // malloc = memory allocation
    // con n * sizeof(int), chiediamo l'allocazione della dimensione di un int 5 volte
    // quindi se sizeof(int) = 4 byte, 5*4 = 20 byte
    for (int i=0;i<n;i++) {
        arr[i]=i;
    }
    return arr;
}

int main () {
    int n=5;
    int *arr = genera_array(n);
    for (int i=0;i<n;i++) {
        printf("elemento %d dell'array: %d\n",i, arr[i]);
    }
    arr[5] = 5;
    printf("elemento 5 dell'array: %d\n", arr[5]);
    return 0;
}