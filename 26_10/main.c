#include "stdio.h"
#include "stdlib.h"
#include "strings.h"

/*Bruteforce method*/



void carregaInput() {
	int x, y, i = 0;
	LCords init, last;
	while (scanf("(%d,%d)\n", &x, &y) == 2) {
		if (i) {
			last->next = newLCords(x, y);
			last = last->next;
		}
		else {
			init = last = newLCords(x, y);
		}
		i++;
	}
	return init;
}

int main() {
	return 0;
}


