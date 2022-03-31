#include "bfs.h"

typedef struct {	/* struktura kopca */
	int s;		/* aktualna wielkosc kopca (ile moze przechowywac danych) */
	int n;		/* liczba przechochywanych wierzcholkow */
	int* a;		/* kopiec */
} kopiec;

void push(kopiec* kopiec, int w, double* odleglosci);

int pop(kopiec* kopiec, double* odleglosci);

void zmiana_odleglosci(kopiec *kopiec, int w, double* odleglosci);

void dijkstra(wierzcholek ** a, int rozmiar, int start, int koniec);
