#include <stdio.h>
#include <unistd.h>

int main() {
	if (fork())
		printf("true\n");
	else
		printf("false\n");
	return 0;
}
