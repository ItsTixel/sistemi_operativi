#include <stdio.h>

void swap (int *x, int *y) {
    int tmp=*x;
    *x=*y;
    *y=tmp;
}

int main () {
    int a=5;
    int b=7;
    printf("a=%d e b=%d\n",a,b);
    swap(&a,&b);
    printf("a=%d e b=%d\n",a,b);
    return 0;
}

