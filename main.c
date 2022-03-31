#include <stdio.h>
#include <stdlib.h>
#include "dijkstra.h"
#include "generator.h"
#include "reader.h"
#include "writer.h"
#include "string.h"

void free_graf(wierzcholek** graf, int rozmiar) {
	int i, j;
	for(i = rozmiar-1; i > -1; i--) { 
		free(graf[i]->w);
		free(graf[i]->drogi);
		free(graf[i]);
	}
	free(graf);
}

int czy_liczba(char *a) {
	char *p;
	p = &a[0];
	while(*p) {
		if(*p < '0' || *p > '9')
			return 1;
		p++;
	}
	return 0;
}

int czy_liczba_f(char *a) {
	char *p;
	p = &a[0];
	while(*p) {
		if((*p < '0' || *p > '9') && *p != '.')
		       return 1;
		p++;
	}
	return 0;
}

void wypisz_blad (int kod) {
	switch(kod) {
		case 0:
			printf("Zbyt mala ilosc argumentow\n");
			break;
		case 1:
			printf("Niepoprawna wielkosc grafu\n");
			break;
		case 2:
			printf("Pierwszy argument musi okreslac generacje lub czytanie grafu\n");
			break;
		case 3:
			printf("Niepoprawny przedzial losowanych drog\n");
			break;
		default:
			break;
	}
	printf("\n\n\tUzycie z generacja grafu: ./graf -g wysokosc szerokosc min max wariant [-s nazwa_pliku] [-b] [-d poczatek koniec]\n\n");
	printf("\t\t\tGeneracja grafu o podanej wysokosci, szerokosci, z krawedziami o wagach z danego przedzialu liczb double,\n");
	printf("\t\t\tz mozliwoscia wariantu 0 (krawedz ma tylko jedna wage) lub 1 (krawedz moze miec rozne wagi w dwie strony\n\n");
	printf("\t\t\t-s nazwa_pliku    \topcjonalna flaga pozwalajaca zapisac wygenerowany graf do pliku nazwa_pliku,\n");
	printf("\t\t\t                  \tktora nalezy podac przed pozostalymi flagami\n\n");
	printf("\tUzycie z czytaniem grafu z pliku: ./graf -r nazwa_pliku [-b] [-d poczatek koniec]\n\n");
	printf("\t\t\tPrzeczytanie grafu z pliku nazwa_pliku\n\n");
	printf("\t\t\tOpcjonalne flagi w obu przypadkach:\n");
	printf("\t\t\t-b                \tsprawdzenie spojnosci grafu\n");
	printf("\t\t\t-d poczatek koniec\tznalezienie najkrotszej sciezki pomiedzy wierzcholkami poczatek i koniec\n\n\n");
}





int main(int argc, char **argv) {
	int i, x;
	int szerokosc, wysokosc, min, max, wariant;
	char *nazwa_pliku;
	if(argc == 1) {
		wypisz_blad(0);
		return 1;
	}
	wierzcholek** graf;
	if(!strcmp(argv[1], "-g")) {
		if(argc > 5) {
			if(czy_liczba(argv[2]) == 0) {
				wysokosc = atoi(argv[2]);
			} else {
				wypisz_blad(1);
				return 1;
			}
			if(czy_liczba(argv[3]) == 0) {
				szerokosc = atoi(argv[3]);
			} else {
				wypisz_blad(1);
				return 1;
			}
			if(czy_liczba_f(argv[4]) == 0) {
				min = atof(argv[4]);
			} else {
				wypisz_blad(3);
				return 1;
			}
			if(czy_liczba_f(argv[5]) == 0) {
				max = atof(argv[5]);
			} else {
				wypisz_blad(3);
				return 1;
			}
			if(!strcmp(argv[6], "0")|| !strcmp(argv[6], "1")) {
				wariant = atoi(argv[6]);
			} else {
				printf("Zly wariant\n");
				return 1;
			}
			if(min > max) {
				wypisz_blad(3);
				return 1;
			}
			graf = (wierzcholek **) malloc (sizeof(wierzcholek*)*wysokosc*szerokosc);
			for(i = 0; i < szerokosc*wysokosc; i++)
				graf[i] = (wierzcholek *) malloc (sizeof(wierzcholek));
			generator(graf, wysokosc, szerokosc, min, max, wariant);
			i = 7;
			if(argc > 7) {
				if(!strcmp(argv[7], "-s")) {
					if(zapisz_graf(argv[8], graf, wysokosc, szerokosc) == 1) {
						printf("Nie udalo sie otworzyc pliku %s\n", argv[8]);
						free_graf(graf, wysokosc*szerokosc);
						return 1;
					} else {
						i += 2;
					}
				}
			}
		} else {
			wypisz_blad(0);
			return 1;
		}
	} else if (!strcmp(argv[1], "-r")) {
		if(argc > 2) {
			nazwa_pliku = argv[2];
		} else {
			wypisz_blad(0);
			return 1;
		}
		x = czytaj_wielkosc(nazwa_pliku, graf, &wysokosc, &szerokosc);
		switch(x) {
			case 0:
				break;
			case 1:
				printf("Bledny format pliku\n");
				return 1;
			case 2:
				printf("Nie udalo sie otworzyc pliku %s\n", nazwa_pliku);
				return 1;
			default:
				break;
		}
		graf = (wierzcholek **) malloc (sizeof(wierzcholek*)*wysokosc*szerokosc);
		for(x = 0; x < wysokosc*szerokosc; x++)
			graf[x] = (wierzcholek *) malloc (sizeof(wierzcholek));
		x = czytaj_graf(nazwa_pliku, graf, wysokosc, szerokosc);
		switch(x) {
			case 0:
				break;
			case 1:
				printf("Bledny format pliku\n");
				free_graf(graf, wysokosc*szerokosc);
				return 1;
			case 2:
				printf("Nie udalo sie otworzyc pliku %s\n", nazwa_pliku);
				free_graf(graf, wysokosc*szerokosc);
				return 1;
			default:
				break;
		}
		i = 3;
	} else {
		wypisz_blad(2);
		return 1;
	}


	while(i < argc) {
		if (!strcmp(argv[i], "-b")) {
			bfs(graf, szerokosc*wysokosc);
			i++;
		} else if (!strcmp(argv[i], "-d")) {
			if(argc > i + 2) {
				if((czy_liczba(argv[i+1]) == 0) && (czy_liczba(argv[i+2]) == 0)) {
					dijkstra(graf, szerokosc*wysokosc, atoi(argv[i+1]), atoi(argv[i+2]));
					i += 3;
				} else {
					printf("Bledne argumenty wierzcholkow, dla ktorych ma zostac obliczona najkrotsza sciezka\n");
					free_graf(graf, szerokosc*wysokosc);
					return 1;
				}
			} else {
				wypisz_blad(0);
				free_graf(graf, szerokosc*wysokosc);
				return 1;
			}
		} else {
			printf("Niepoprawny argument: %s\n", argv[i]);
			free_graf(graf, szerokosc*wysokosc);
			return 1;
		}

	}
	free_graf(graf, szerokosc*wysokosc);
	return 0;
}



