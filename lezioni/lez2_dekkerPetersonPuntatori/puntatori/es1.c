#include <stdio.h>

int main () {
    int a=5;
    int *p=&a;
    printf("Il valore a: %d\n",a);
    printf("Il valore puntatore: %p\n",p);
    printf("Il valore dell'indirizzo della variabile: %p\n",&a);
    printf("Il valore dell'indirizzo del puntatore: %p\n",&p);
    printf("Il valore della variabile puntata: %d\n",*p);
    return 0;
}
