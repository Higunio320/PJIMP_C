#include <stdio.h>
#include <stdlib.h>
#include "dijkstra.h"


void push (kopiec* kopiec, int wierzcholek, double* odleglosci) {					/* funkcja wczytujaca wierzcholek do kopca*/
	int i, j;
	if (kopiec->n == kopiec->s) {
		kopiec->a = (int *) realloc(kopiec->a, sizeof(int)*(kopiec->s * 2));	/* powiekszenie rozmiaru kopca jesli zajdzie taka potrzeba */
		kopiec->s *= 2;
	}
	kopiec->a[kopiec->n] = wierzcholek;
	kopiec->n++;
	i = kopiec->n - 1;
	j = (i - 1)/2;
	while(i > 0 && (odleglosci[kopiec->a[j]] > odleglosci[wierzcholek])) {
		kopiec->a[i] = kopiec->a[j];
		i = j;
		j = (i - 1)/2;
		kopiec->a[i] = wierzcholek;
	}
}

int pop (kopiec* kopiec, double* odleglosci) {						/* funkcja "zabierajaca" wierzcholek z kopca, ktora zwraca */
	if(kopiec->n == 0)								/* jego numer */
		return -1;
	int v, i, j, ret;
	ret = kopiec->a[0];
	v = kopiec->a[kopiec->n-1];
	kopiec->n--;
	i = 0;
	j = 1;
	while(j < kopiec->n) {
		if((j + 1 < kopiec->n) && odleglosci[kopiec->a[j+1]] < odleglosci[kopiec->a[j]])
			j++;
		if(odleglosci[v] <= odleglosci[kopiec->a[j]])
			break;
		kopiec->a[i] = kopiec->a[j];
		i = j;
		j = 2*i + 1;
	}
	kopiec->a[i] = v;
	return ret;
}

void zmiana_odleglosci(kopiec *kopiec, int wierzcholek, double* odleglosci) {			/* funkcja zmieniajaca polozenie danego wierzcholka w kopcu, gdy */
	int i, tmp;									/* zostanie zmieniona droga do niego (gdy znaleziona zostanie krotsza */
	for(i = (kopiec->n - 1); i >= 0; i--) {						/* od juz zapisanej */
		if (kopiec->a[i] == wierzcholek) {
			tmp = i;
			break;
		}
		if(i == 0)
			printf("Cos poszlo nie tak\n");
	}
	i = (tmp - 1)/2;
	while(tmp > 0 && (odleglosci[kopiec->a[i]] > odleglosci[kopiec->a[tmp]])) {
		kopiec->a[tmp] = kopiec->a[i];
		tmp = i;
		i = (tmp - 1)/2;
		kopiec->a[tmp] = wierzcholek;
	}
}



void dijkstra(wierzcholek** a, int rozmiar, int start, int koniec) {			/* funkcja ktora steruje caloscia, a nastepnie drukuje dlugosc najkrotszej */
	if (koniec > (rozmiar - 1)) {
		printf("Wierzcholek %d nie miesci sie w grafie\n", koniec);
		return;
	}
	int i, tmp;									/* sciezki oraz wierzcholki sie w niej zawierajace */
	for(i = 0; i < rozmiar; i++) {
		a[i]->p = 0;
		a[i]->stan = 1;
	}
	double *odleglosci;
	odleglosci = (double *) malloc(sizeof(double)*rozmiar);
	kopiec *tabela;
	tabela = (kopiec *) malloc(sizeof(kopiec));
	tabela->a = (int *) malloc(sizeof(int)*2);
	tabela->n = 0;
	tabela->s = 2;
	a[start]->p = -1;
	odleglosci[start] = 0;
	a[start]->stan = 3;
	push(tabela, start, odleglosci);

	while(a[koniec]->stan != 3) { 			/* petla wykonuje sie az do momentu, gdy do wierzcholka koncowego zostanie znaleziona najkrotsza droga */
		tmp = pop(tabela, odleglosci);		/* tmp przechowuje aktualnie odebrany wierzcholek ze szczytu kopca */
		if(tmp == koniec)
			break;
		if(tmp == -1) {										/* funkcja "pop" zwraca -1, jesli nie ma juz zadnych elementow w kopcu, */
			printf("Nie istnieje droga pomiedzy wierzcholkami %d i %d\n", start, koniec);	/* co oznacza, ze do danego wierzcholka nie istnieje droga */
			free(tabela->a);
			free(tabela);
			free(odleglosci);
			return;
		}
		a[tmp]->stan = 3;
		for(i = 0; i < a[tmp]->n; i++) {		/* iteracja po kazdym wierzcholku polaczonym z wyciagnietym z kopca */
			if(a[a[tmp]->w[i]]->stan < 2) {		/* jesli nie byl w kopcu, to nalezy go dodac */
				odleglosci[a[tmp]->w[i]] = odleglosci[tmp] + a[tmp]->drogi[i];
				push(tabela, a[tmp]->w[i], odleglosci);
				a[a[tmp]->w[i]]->stan = 2;
				a[a[tmp]->w[i]]->p = tmp;
			} else {
				if (odleglosci[a[tmp]->w[i]] > odleglosci[tmp] + a[tmp]->drogi[i]) {	/* jesli juz jest w kopcu, nalezy sprawdzic, czy droga przez */
					odleglosci[a[tmp]->w[i]] = odleglosci[tmp] + a[tmp]->drogi[i];	/* wierzcholek przechowywany w "tmp" nie jest krotsza od juz */
					a[a[tmp]->w[i]]->p = tmp;					/* w nim zapisanej */
					zmiana_odleglosci(tabela, a[tmp]->w[i], odleglosci);
				}
			}
		}
	}
	i = koniec;						/* wydrukowanie dlugosci sciezki oraz wierzcholkow po kolei */
	printf("Dlugosc sciezki: %f\n", odleglosci[koniec]);
	while(i != start) {
		printf("%d -> %d\n", a[i]->p, i);
		i = a[i]->p;
	}
	free(tabela->a);
	free(tabela);
	free(odleglosci);
}
