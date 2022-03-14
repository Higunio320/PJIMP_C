#include "bfs.h"

typedef struct {
	int s;
	int n;
	int* a;
} kopiec;

void push(kopiec* kopiec, int w, double* odleglosci);

int pop(kopiec* kopiec, double* odleglosci);

void zmiana_odleglosci(kopiec *kopiec, int w, double* odleglosci);

void dijkstra(wierzcholek ** a, int rozmiar, int start, int koniec);
