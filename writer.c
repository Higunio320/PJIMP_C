#include<stdio.h>
#include"bfs.h"
#include"reader.h"
#include<stdio.h>
void zapisz_graf( char* file_name,wierzcholek** wierzcholek, rozmiar* graf) {

int k;
	if( graf!= NULL) {
		FILE *out = fopen(file_name, "w"); // otwieram plik

	fprintf(out, "%d %d\n", graf->col, graf->row); // wypiosuje kulumne i wiersz
	for(k = 0; k < (graf->col) * (graf->row); k++) { // wypisuje tyle wierzcholkow ile rozmiar grafu
		fprintf(out,"\t");		//znak tabulatora
		while( wierzcholek[k]->x != NULL) {	// wypisuje dopoki sa wierzcholki
			fprintf(out, " %d :%.16g ", wierzcholek[k]->x, wierzcholek[k]->drogi[k]);
		}
		fprintf(out, "\n");
	}
	fclose(out);
	}
}
		

