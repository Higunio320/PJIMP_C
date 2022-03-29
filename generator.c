#include "bfs.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
												/* wariant = 0 - wagi krawedzi musza byc takie same z obu wierzcholkow */
void wpisz_dlugosci(wierzcholek** wierzcholek, int numer, int liczba_drog, double min, double max, int wariant) {	/* funkcja wpisujaca dlugosci krawedzi */
	int i, j, tmp;													/* wychodzacych z danego wierzcholka */
	wierzcholek[numer]->drogi = (double *) malloc (sizeof(double) * liczba_drog);
	for(i = 0; i < liczba_drog; i++) {
		if ((wierzcholek[numer]->w[i] < numer) && (wariant == 0)) {				/* jesli wariant = 0, to wagi krawedzi miedzy danymi wierzcholkami */
			for(j = 0; j < wierzcholek[wierzcholek[numer]->w[i]]->n; j++) {			/* np 0-1 i 1-0 musza byc takie same i wtedy nalezy przepisac */
				if(wierzcholek[wierzcholek[numer]->w[i]]->w[j] == numer) {		/* wagi z istniejacych juz wierzcholkow (o nizszych indeksach) */
					tmp = j;
					break;
				}
			}
			wierzcholek[numer]->drogi[i] = wierzcholek[wierzcholek[numer]->w[i]]->drogi[tmp];
		} else {										/* gdy moga byc rozne lub dane polaczenie jeszcze nie istnieje */
			wierzcholek[numer]->drogi[i] = min + (max - min)*((double) rand()/RAND_MAX);	/* nalezy dana wage krawedzi wygenerowac */
		}
	}
}

void generator (wierzcholek** wierzcholek, int wysokosc, int szerokosc, double min, double max, int wariant) {
	int i, j;
	srand(time(NULL));
	int przypadek;											/* Rozklad przypadkow */
												      /* --------------------- */
	for (i = 0; i < wysokosc*szerokosc; i++) {						      /* " 0 - - - 4 - - - 1 " */
		wierzcholek[i]->x = i;								      /* " | - - - | - - - | " */
		if (i == 0) {									      /* " 6 - - - 8 - - - 7 " */				
			przypadek = 0;								      /* " | - - - | - - - | " */
		} else if (i == (szerokosc - 1)) {						      /* " 2 - - - 5 - - - 3 " */
			przypadek = 1;								      /* --------------------- */
		} else if (i == (szerokosc * (wysokosc - 1))) {					    /* "0, 1, 2, 3" - odpowiednie "rogi" grafu */
			przypadek = 2;								    /* "4, 5, 6, 7" - odpowiednie "bogi" grafu */
		} else if (i == (szerokosc * wysokosc - 1)) {					    /* "8" - jakikolwiek wierzcholek wewnatrz */
			przypadek = 3;
		} else if (i < szerokosc) {
			przypadek = 4;
		} else if (i > (szerokosc * (wysokosc - 1))) {
			przypadek = 5;
		} else if ((i % szerokosc) == 0) {
			przypadek = 6;
		} else if (((i + 1) % szerokosc) == 0) {
			przypadek = 7;
		} else {
			przypadek = 8;
		}
		switch(przypadek) {
			case 0: case 1: case 2: case 3:					/* dla przypadkow w rogach grafu sytuacja wyglada podobnie, lecz */
				wierzcholek[i]->n = 2;					/* roznia sie one indeksami polaczonych wierzcholkow */
				wierzcholek[i]->w = (int *) malloc (sizeof(int)*2);
				if (przypadek == 0 || przypadek == 1) {
					wierzcholek[i]->w[0] = i + szerokosc;
				} else {
					wierzcholek[i]->w[0] = i - szerokosc;
				}
				if (przypadek == 0 || przypadek == 2) {
					wierzcholek[i]->w[1] = i + 1;
				} else {
					wierzcholek[i]->w[1] = i - 1;
				}
				wpisz_dlugosci(wierzcholek, i, 2, min, max, wariant);
				break;
			case 4: case 5: case 6: case 7:					/* podobnie jak wyzej, dla wierzcholkow na scianach grafu sytuacja */
				wierzcholek[i]->n = 3;					/* jest podobna */
				wierzcholek[i]->w = (int *) malloc (sizeof(int)*3);
				if (przypadek == 4 || przypadek == 5) {
					wierzcholek[i]->w[0] = i - 1;
					wierzcholek[i]->w[1] = i + 1;
				} else {
					wierzcholek[i]->w[0] = i - szerokosc;
					wierzcholek[i]->w[1] = i + szerokosc;
				}
				switch(przypadek) {
					case 4:
						wierzcholek[i]->w[2] = i + szerokosc;
						break;
					case 5:
						wierzcholek[i]->w[2] = i - szerokosc;
						break;
					case 6:
						wierzcholek[i]->w[2] = i + 1;
						break;
					case 7:
						wierzcholek[i]->w[2] = i - 1;
					default:
						break;
				}
				wpisz_dlugosci(wierzcholek, i , 3, min, max, wariant);
				break;
			case 8:								/* dla kazdego wierzcholka "wewnatrz" grafu indeksy wierzcholkow */
				wierzcholek[i]->n = 4;					/* polaczonych mozna ustalic w ten sam sposob */
				wierzcholek[i]->w = (int *) malloc (sizeof(int)*4);
				wierzcholek[i]->w[0] = i - 1;
				wierzcholek[i]->w[1] = i - szerokosc;
				wierzcholek[i]->w[2] = i + 1;
				wierzcholek[i]->w[3] = i + szerokosc;
				wpisz_dlugosci(wierzcholek, i, 4, min, max, wariant);
				break;
			default:
				printf("Nie powinno sie tak stanac");
				break;
		}
		wierzcholek[i]->stan = 0;
	}
}
