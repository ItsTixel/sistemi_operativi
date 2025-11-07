#include <stdio.h>

int main() {
	char c = 200;
	signed char sc = 200;
	unsigned char uc = 200;
	if ((c) < 0) {
		printf("char è SIGNED\n");
	} else {
		printf("char è UNSIGNED\n");
	}
	if ((sc) < 0) {
		printf("char è SIGNED\n");
	} else {
		printf("char è UNSIGNED\n");
	}
	if ((uc) < 0) {
		printf("char è SIGNED\n");
	} else {
		printf("char è UNSIGNED\n");
	}
	return 0;
}
