#include <stdio.h>
#include <string.h>
#include <stdint.h>

union Number {
	int32_t i;
	float f;
	unsigned char bytes[4];
};

void print_byte (const unsigned char *b, size_t n) {
	for (size_t k = 0; k < n ; k++ ) {
		printf("%02X ", b[k]);
	}
}

int main () {
	union Number n;
	n.i = 0x01020304;
	printf("i = 0x%08X -> byted: ",(unsigned) n.i);

	print_byte(n.bytes, sizeof n.bytes);

	n.f = 1.0f;
	printf("\nf = %.6f -> bytes: ", n.f);
	print_byte(n.bytes, sizeof n.bytes);
	printf("\ni = %d\n", n.i);
	return 0;
}
