#include <stdio.h>
#include <stdlib.h>
#include "bfs.h"

void double_size(int* a, int* n) {
	a = realloc(a, 2*(*n)*sizeof(a));
	(*n) *= 2;
}

int bfs(wierzcholek** a, int rozmiar) {
	int i;
	int x = 1;
	int n = 2;
	int p = 0;
	int tmp = 0;
	int *kolejka;
	kolejka = (int *) malloc (sizeof(int)*rozmiar);
	for(i = 0; i < a[0]->n; i++) {
		kolejka[i] = a[0]->w[i];
		a[a[0]->w[i]]->stan = 1;
		x++;
		p++;
	}
	a[0]->stan = 1;
	while(x != rozmiar) {
		if(p == 0) {
			free(kolejka);
			printf("**********\nGraf niespojny\n**********\n");
			return -1;
		}
		tmp = p-1;
		for(i = 0; i < a[kolejka[0]]->n; i++) {
			if(a[a[kolejka[0]]->w[i]]->stan == 0) {
				kolejka[p] = a[kolejka[0]]->w[i];
				a[a[kolejka[0]]->w[i]]->stan = 1;
				x++;
				p++;
			}
		}
		kolejka[0] = kolejka[p-1];
		p--;
	}
	free(kolejka);
	printf("**********\nGraf spojny\n**********\n");
	return 0;
}

