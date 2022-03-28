#include <stdio.h>
#include <stdlib.h>
#include "bfs.h"

void wypisz_kolejke(int* kolejka, int p) {
	int i;
	printf("Kolejka : ");
	for(i = 0; i < p; i++)
		printf("%d ", kolejka[i]);
	printf("\n");
}

void double_size(int* kolejka, int* size) {
	printf("Zwiększam rozmiar kolejki z %d do %d\n", (*size), (*size)*2);
	kolejka = (int *) realloc(kolejka, (sizeof(int)*(*size)*2));
	(*size) *= 2;
}

int bfs(wierzcholek** a, int rozmiar) {
	int i;
	int x = 1;
	int p = 0;
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

