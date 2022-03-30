#include <stdio.h>
#include <stdlib.h>
#include "bfs.h"

void wypisz_kolejke(int* kolejka, int p) {					/* funkcja wypisujaca kolejke - przydatne w naprawianiu bledow */
	int i;									/* "do usuniecia w ostatecznej wersji" */
	printf("Kolejka : ");
	for(i = 0; i < p; i++)
		printf("%d ", kolejka[i]);
	printf("\n");
}

void double_size(int* kolejka, int* size) {					/* funkcja podwajajaca wielkosc kolejki, gdy zajdzie taka potrzeba */
	printf("Zwiększam rozmiar kolejki z %d do %d\n", (*size), (*size)*2);	/* z jakiegos poowodu nie dziala */
	kolejka = (int *) realloc(kolejka, (sizeof(int)*(*size)*2));
	(*size) *= 2;
}

void bfs(wierzcholek** a, int rozmiar) {
	int i;
	int odwiedzone = 1;		/* liczba odwiedzonych wierzcholkow (1, poniewaz pomijamy juz wierzcholek nr. 0) */
	int przechowywane = 0;		/* liczba przechowywanych wierzcholkow w kolejce */
	int *kolejka;
	kolejka = (int *) malloc (sizeof(int)*rozmiar);
	for(i = 0; i < a[0]->n; i++) {
		kolejka[i] = a[0]->w[i];
		a[a[0]->w[i]]->stan = 1;
		odwiedzone++;
		przechowywane++;
	}
	a[0]->stan = 1;
	while(odwiedzone != rozmiar) {		/* petla wykonuje sie poki nie zostana odwiedzone wszystkie wierzcholki   */
		if(przechowywane == 0) {	/* jesli przechowywane jest 0 wierzcholkow i petla sie nie zakonczyla, to */
			free(kolejka);		/* do minimum jednego nie istnieje droga - graf niespojny */
			printf("\n\n\t\t\tGraf niespoj\n\n");
			return;
		}
		for(i = 0; i < a[kolejka[0]]->n; i++) {				/* dodanie do kolejki kazdego wierzcholka, ktory */
			if(a[a[kolejka[0]]->w[i]]->stan == 0) {			/* jest polaczony z tym z poczatku kolejki, oraz */
				kolejka[przechowywane] = a[kolejka[0]]->w[i];   /* jeszcze w niej nie jest */
				a[a[kolejka[0]]->w[i]]->stan = 1;
				odwiedzone++;
				przechowywane++;
			}
		}
		kolejka[0] = kolejka[przechowywane-1];	/* przepisanie wierzcholka z konca tabeli na poczatek */
		przechowywane--;
	}
	free(kolejka);
	printf("\n\n\t\t\tGraf spojny\n\n\n");
	return;
}

