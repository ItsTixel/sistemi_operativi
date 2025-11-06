#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** generate_matrix(int y, int x) {
	int **mat = malloc(y * sizeof(*mat)); // (*mat) dato che abbiamo dichiarato ** mat come int
	
	if (!mat) {
		perror("malloc A[i]");

		return NULL;
	}
	for (int i=0; i<y;i++) {
		mat[i] = malloc (x * sizeof(int));
		if (mat[i] == NULL) {
			perror("malloc A[i]");
			for (int k = 0; k<i;k++) {
				free(mat[k]);
			}
			free(mat);
			return NULL;
		}
		for (int j=0; j<x; j++) {
			mat[i][j] = rand() % 100;
		}
	}
	return mat;
}


void print_matrix(int **mat, int y,int x) {
	for (int i=0;i<y;i++) {
		for (int j=0;j<x;j++) {
			printf("%3d   ",mat[i][j]);
		}
		printf("\n");
	}
}

void free_memory(int **mat, int y) {
	for (int i=0; i<y; i++) {
		free(mat[i]);
	}
	free(mat);
	printf("memoria liberata\n");
}

int main () {
	srand(time(NULL));
	int y=6,x=30;
	int **mat = NULL;
	mat = generate_matrix(y,x);
	print_matrix(mat,y,x);
	free_memory(mat, y);
	return 0;
}
