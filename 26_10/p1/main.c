#include "stdio.h"
#include "stdlib.h"
#include "strings.h"

typedef struct output{
	int i,j,m;
	struct output* next;
}*Out;

void printOut(Out a){
	while(a->next){
		printf("%d %d %d\n", a->i, a->j, a->m);
		a=a->next;
	}
}

int algoritmo(int n) {
	int i = 1;
	while (n != 1) {
		if (n % 2)
			n = 3 * n + 1;
		else n /= 2;
		i++;
	}
	return i;
}


int main() {
	int i, j, n, a;
	int m = 0;
	Out init,fin;
	init = fin = (Out)malloc(sizeof(struct output));
	while (scanf("%d %d", &i, &j)>0) {
		init ->next = (Out)malloc(sizeof(struct output));
		init -> i = i;
		init -> j = j;
		for (n = i; n <= j; n++) {
			a = algoritmo(n);
			if (m < a)
				m = a;
		}
		init->m = a;
		init = init->next;
	}
	printOut(fin);
	return 0;
}

