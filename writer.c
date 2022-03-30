#include<stdio.h>
#include"bfs.h"
#include"writer.h"

int zapisz_graf(char* file_name, wierzcholek** wierzcholek, int wysokosc, int szerokosc) {

	int i,j;
	FILE *out = fopen(file_name, "w"); // otwieram plik

	if(out == NULL) {
		fprintf(out, "Nie moge otworzyc pliku!");
		return 5;
	} else { 

	fprintf(out, "%d %d\n", wysokosc, szerokosc); // wypiosuje kulumne i wiersz
	for(i = 0; i < wysokosc * szerokosc; i++) { // wypisuje tyle wierzcholkow ile rozmiar grafu
		for(j = 0; j < wierzcholek[i]->n; j++) {
			fprintf(out, "\t%d :%f", wierzcholek[i]->w[j], wierzcholek[i]->drogi[j]);
		}
		fprintf(out, "\n");
	}
	fclose(out);
	}
}
		

