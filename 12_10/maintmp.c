#include "stdio.h"
#include "stdlib.h"
#include "strings.h"
#include <math.h>


/*
	Nao terminado porque cansei-me
*/
typedef struct cords {
	int x;
	int y;
} Cords;

typedef struct lcords {
	int x;
	int y;
	struct lcords* next;
}*LCords;

typedef struct mcords {
	int x;
	int y;
	struct mcords* next;
}*MCords;

typedef struct listDistPoints {
	int ax;
	int ay;
	int bx;
	int by;
	double dist;
	struct listDistPoints* next;
}*LDistPoints;

/*Converte para radianos um degree*/
double to_radians(double x) {
	return (x * M_PI) / 180;
}

/*Quando se trata de coordenadas esf´ericas, esta funcao retorna as distancias entre dois pontos*/
double haversine(int ax, int ay, int bx, int by) {
	double dx, dy, a, c, d;
	dx = to_radians(bx) - to_radians(ax);
	dy = to_radians(by) - to_radians(ay);
	a = pow((sin(dy / 2)), 2) + cos(to_radians(by)) * cos(to_radians(ay)) * pow((sin(dx / 2)), 2);
	c = 2 * atan2( sqrt(a), sqrt(1 - a) );
	d = 6373 * c; /*6373 ´e o raio da terra*/
	return d;
}

LCords newLCords(int x, int y) {
	LCords r = (LCords)malloc(sizeof(struct lcords));
	r->x = x;
	r->y = y;
	r->next	= NULL;
	return r;
}

/*faz free de todos os elementos do array*/
void freeLCords(LCords init) {
	LCords tmp;
	while (init) {
		tmp = init ->next;
		free(init);
		init = free;
	}
}

/*imprime este nodo e todos os que estao ligados a ele*/
void printLCords(LCords x, int i) {
	printf("(%d,%d)->", x->x, x->y);
	if (x->next) {
		printLCords(x->next, i + 1);
	} else printf("*%d\n", i);
}

/*imprime este nodo e todos os que estao ligados a ele*/
void printLCordsaux(LCords x, int i) {
	printf("%d, %d (%d)\n", x->x, x->y, i);
	if (x->next) {
		printLCordsaux(x->next, i + 1);
	} else printf("*%d\n", i);
}

int tamLCords(LCords x) {
	int i = 0;
	if (x) i++;
	while (x->next) {
		i++;
		x = x->next;
	}
	return i;
}

/*Dado uma lista e as coordenadas de um elemento,
ve se o elemtno pertence a lista*/
int pertenceLCords(LCords a, int x, int y) {
	while (a && (a->x != x) && (a->y != y)) {
		a = a->next;
	}
	if (a->x == x && a->y == y) return 1;
	return 0;
}


LCords lastLCords(LCords x) {
	while (x->next) {
		x = x->next;
	}
	return x;
}

/*retorna 1 caso tenham as coordenadas iguais*/
int cmpLCords(LCords x, LCords y) {
	return ((x->x == y->x) && (x->y == y->y));
}

/*retira da lista inic o lixo, retorna o inicio da lista*/
LCords removeLCords(LCords inic, LCords lixo) {
	LCords ant, this;
	if (cmpLCords(inic, lixo)) {
		if (inic->next) {
			return inic->next;
		}
		else return NULL;
	}
	else {
		ant = inic;
		this = inic->next;
		while (this) {
			if (cmpLCords(this, lixo)) {
				ant->next = this->next;
				break;
			}
			ant = this;
			this = this->next;
		}
	}
	return inic;
}


/*	retorna uma lista com dois elementos, os que sao mais proximos
	E nessa lista que deve começar a trabalhar.
	Elimina da lista que recebe esses dois pontos.

	TODO:	caso de o elemento a tirar ser o primeiro,

*/
LCords findShort(LCords inic) {
	LCords inica, inicb;
	double tmp, dist;
	LCords mina, minb;
	if (tamLCords(inic) < 2) {
		return inic;
	}
	inica = inic;
	inicb = inic->next;
	mina = inica;
	minb = inicb;
	dist = haversine(inica->x, inica->y, inicb->x, inicb->y);
	for (inica = inic; inica->next; inica = inica->next) {
		for (inicb = inica->next; inicb->next; inicb = inicb->next) {
			tmp = haversine(inica->x, inica->y, inicb->x, inicb->y);
			if (tmp < dist) {
				mina = inica;
				minb = inicb;
				dist = tmp;
			}
		}
	}
	inic = removeLCords(inic, mina);
	inic = removeLCords(inic, minb);
	mina->next = minb;
	minb->next = NULL;
	return mina;
}

/*retorna o elemento de init mais proximo da lista final */
LCords closestLCords(LCords init, LCords finala) {
	double distm, this;
	LCords min, mov, finalb;
	finalb = finala->next;
	min = mov = init;
	distm = haversine(finala->x, mov->x, finala->y, mov->y);

	while (mov) {
		this = haversine(finala->x, mov->x, finala->y, mov->y);
		if (this < distm ) {
			distm = this;
			min = mov;
		}
		this = haversine(finalb->x, mov->x, finalb->y, mov->y);
		if (this < distm ) {
			distm = this;
			min = mov;
		}
		mov = mov->next;
	}
	/*printf("%d,%d\n", min->x, min->y);*/
	return min;
}

/*Adiciona ao inicio ou fim de a o x*/
LCords adicionaLCords(LCords a, LCords x) {
	LCords last = lastLCords(a);
	if (haversine(a->x, x->x, a->y, x->y) < haversine(last->x, x->x, last->y, x->y)) {
		x->next = a;
		return x;
	}
	else {
		last->next = x;
		x->next = NULL;
		return a;
	}
}

/*Funçao que organiza o processamento do algoritmo do vizinho
mais proximo, isto e, começa com os dois mais juntos e vai
adicionando o que estiver mais perto. Quando estiverem todos
temos algo com algo entre 30% e 20% pior que a soluçao otima*/
LCords shortestNeig(LCords init) {
	LCords add, last = findShort(init);
	while (init) {
		add = closestLCords(init, last);
		init = removeLCords(init, add);
		last = adicionaLCords(last, add);
	}
	return last;
}


LDistPoints newLDP(int ax, int ay, int bx, int by) {
	LDistPoints r = (LDistPoints)malloc(sizeof(struct listDistPoints));
	r->ax = ax;
	r->ay = ay;
	r->bx = bx;
	r->by = by;
	r->dist = haversine(ax, ay, bx, by);
	r->next = NULL;
	return r;
}

/*adiciona o a na lista, por ordem crescente*/
LDistPoints insertLDP(LDistPoints lista, LDistPoints a) {
	LDistPoints orig = lista;
	if (!lista) {
		return a;
	}
	if (lista->dist > a->dist) {
		a->next = lista;
		return a;
	}
	while (lista->next && lista->next->dist < a->dist) {
		lista = lista->next;
	}
	a->next = lista->next;
	lista->next = a;
	return orig;
}

/*cria a lista de distancias*/
LDistPoints preencheDist(LCords init) {
	LDistPoints ret, m;
	ret = m = newLDP(0, 0, 0, 0);
	LCords i, j;
	i = init;
	while (i) {
		j = i->next;
		while (j) {
			m->next = newLDP(i->x, i->y, j->x, j->y);
			m = m->next;
			m->dist = haversine(i->x, i->y, j->x, j->y);
			j = j->next;
		}
		i = i->next;
	}
	m->next = NULL;
	m = ret;
	ret = ret->next;
	free (m);
	return ret;
}

void printDist(LDistPoints i) {
	int a = 0;
	while (i) {
		printf("%lf\n", i->dist);
		i = i->next;
		a++;
	}
	printf("%d\n", a);
}

LDistPoints ordenaLDP(LDistPoints init) {
	LDistPoints m = init->next, aux;
	init->next = NULL;
	while (m) {
		aux = m;
		m = m->next;
		aux->next = NULL;
		init = insertLDP(init, aux);
	}
	return init;
}

MCords addPoint(MCords m, int ax, int ay, int bx, int by) {
	LCords tmp;
	MCords n, ret, antn;
	if (!m) {
		ret = (MCords)malloc(sizeof(struct mcords))
		      ret->this = newLCords(ax, ay, bx, by);
		ret->next = NULL;
		return ret;
	}
	ret = m;
	while (m) {
		if (m->this->x == ax && m->this->y == ay) {
			n = ret;
			while (n) {
				tmp = lastLCords(n->this);
				if (tmp->x == bx && tmp->y == by) {
					if (n != m) {
						tmp->next = m->this;
						if(antn){
							antn->next=n->next;
							return ret;
						}
						else return n;
					}
				}
			}
		}
	}
}

/*Pega numa lista LDP, que tem as distancias entre todos os
pontos e cria uma lista que estara devidamente organizada*/
LCords makeLCordsfromLDP(LDistPoints lista, LCords init) {

}


/*Funcao que organiza o processamento do algoritmo do ******,
isto e, pega em todas as distancias entre todos os vertices e
coloca-as numa lista, depois vai pegando na mais pequena e
adiciona-a a soluçao caso nao crie ciclos. Quando estiverem
todos temos uma soluçao que deve estar dentro dos 10% pior que
a soluçao otima*/
LCords listAllShort(LCords init) {
	LDistPoints ldp = preencheDist(init);
	ldp = ordenaLDP(ldp);
	printDist(ldp);

	return init;
}



LCords carregaInput() {
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
	LCords init, last;
	LDistPoints distancias;
	init = carregaInput();
	/*	last = shortestNeig(init);
		printLCordsaux(last, 1);
	*/
	listAllShort(init);
	return 0;
}


