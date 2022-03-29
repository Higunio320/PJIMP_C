#include<stdio.h>
#include"bfs.h"
#include"reader.h"
#include<stdio.h>
void zapisz_graf( char* file_name, wierzcholek** g, rozmiar* graf) {

int i,j;
	if( graf!= NULL) {
		FILE *out = fopen(file_name, "w"); // otwieram plik

	fprintf(out, "%d %d\n", graf->col, graf->row); // wypiosuje kulumne i wiersz
	for(i = 0; i < ((graf->col) * (graf->row)) - 1; i++) { // wypisuje tyle wierzcholkow ile rozmiar grafu
		for(j = 0; j < g[i]->n; j++) {
			fprintf(out, "\t%d :%f", g[i]->w[j], g[i]->drogi[j]);
		}
		fprintf(out, "\n");
	}
	fclose(out);
	}
}
		

