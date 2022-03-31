#include<stdio.h>
#include "bfs.h"
#include<stdio.h>
int zapisz_graf( char* file_name,wierzcholek** wierzcholek, int wysokosc, int szerokosc) {

	int k, i;
	FILE *out = fopen(file_name, "w"); // otwieram plik
	if(out == NULL){
		return 1;
	}

	fprintf(out, "%d %d\n", wysokosc, szerokosc); // wypiosuje kulumne i wiersz
	for(k = 0; k < wysokosc * szerokosc; k++) { // wypisuje tyle wierzcholkow ile rozmiar grafu
		fprintf(out,"\t");		//znak tabulatora
		for(i = 0; i < wierzcholek[k]->n; i++) {	// wypisuje dopoki sa wierzcholki
			fprintf(out, " %d :%.16g ", wierzcholek[k]->w[i], wierzcholek[k]->drogi[i]);
		}
		fprintf(out, "\n");
	}
	fclose(out);
	return 0;
}
