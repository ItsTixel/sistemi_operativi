#include <stdio.h>
#include <limits.h>
#include <float.h>

int main() {
    printf("int: %zu, min=%d, max=%d \n", sizeof(int),INT_MIN,INT_MAX);
    printf("uint: %zu, min=%u, max=%u \n", sizeof(unsigned int),0,UINT_MAX);
    printf("char: %zu, min=%d, max=%d \n",sizeof(char), CHAR_MIN,CHAR_MAX);
    return 0;
}

