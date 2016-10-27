#include "stdio.h"
#include "stdlib.h"
#include "strings.h"


int mat [100][100];
int sums [99][99];

int biggertree(int i, int j, int q) {
	int a, b;
	if (q) {
		a = biggertree(i + 1, j, q - 1);
		b = biggertree(i + 1, j + 1, q - 1);
		if (j == 5 && i == 10){
			printf("10\n");
		}
			if (mat[i][j] + a > mat[i][j] + b) {
				return a + mat[i][j];
			}
			else return b + mat[i][j];
	}
	return 0;
}

void preenche sums(int a){
	int j;
	for(j=0; j<)
}

void printMatTrig(int i) {
	int j = 0, n = 0;
	for (j = 0; j < i; j++) {
		for (n = 0; n <= j; n++) {
			printf("%d ", mat[j][n]);
		}
		printf("\n");
	}
}



int main() {
	int j = 0, i = 0;

	for (i = 0; scanf("%d", &mat[i][0]) > 0; i++) {
		for (j = 1; j <= i; j++) {
			scanf("%d", &mat[i][j]);
		}
	}
	printf("%d \n", i);

	int a = biggertree(0, 0, i);
	printf("%d\n", a);
	return 0;
}
