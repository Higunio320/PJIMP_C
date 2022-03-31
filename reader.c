#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include"bfs.h"
#include"reader.h"

void reset_temp(char* tmp){
	int i = 0;
	while(tmp[i] != '\0' ) {
		tmp[i] = '\0';
		i++;
        }
}

/*bledy ustawione tak jak w sf*/

int czy_liczba_dodatnia(char* tmp){

	int i = 0;
	while (tmp[i] != '\0' ) {
		if((tmp[i] < '0' || tmp[i] > '9') && tmp[i] != '.') {
			return 0;
		}
	i++;
	}
	return 1;
}

int czytaj_wielkosc(char* file_name, wierzcholek** graf, int* wysokosc, int* szerokosc) {
    FILE* in = fopen(file_name, "r");
    if (in == NULL) {
        return 2;
    }
    int i = 0;
    char c;
    int linia = 0;
    char* tmp = (char*)malloc(4096 * sizeof(char));
    while(tmp[i] != 0) {
	tmp[i] = '\0';
 	i++;
    }
   

    /*wczytywanie liczby kolumn i wierszy*/
    int licznik = 0;
    c = fgetc(in);
    if (c == EOF) {
        free(tmp);
        fclose(in);
        return 1;
    }
    while (linia == 0) {
        if (c != ' ' && c != '\n' && c != '\t') {
            if (isdigit(c)) {
                tmp[i++] = c;
            }
            else {
                free(tmp);
                fclose(in);
                return 1;
            }
        }
        else {
            if (licznik == 0 || licznik == 1) {
                if (licznik == 0) {
                    *wysokosc = atoi(tmp);
                }
                else {
                    *szerokosc = atoi(tmp);
                }
                reset_temp(tmp);
                licznik++;
                i = 0;
            }
            else {
                free(tmp);
                fclose(in);
                return 1;
            }
        }
        if (c == '\n') {
            if (licznik == 0) {
                free(tmp);
                fclose(in);
                return 1;
            }
            linia++;
        }
        c = fgetc(in);
    }
    free(tmp);
    fclose(in);
    return 0;
}

int czytaj_graf(char* file_name, wierzcholek** graf, int wysokosc, int szerokosc){
    
    FILE *in = fopen(file_name, "r");
    if (in == NULL){
        return 2;
    }
    char* tmp = (char*) malloc(4096 * sizeof(char));
    char c;
    int j = 0;
    int k;
    int linia = 0;
    int i = 0;
     
    /*wczytywanie liczby kolumn i wierszy*/
    int licznik = 0;
    c = fgetc(in);
    if (c == EOF){
	free(tmp);
	fclose(in);
        return 1;
    }
    while(c != '\n')
	    c = fgetc(in);
    c = fgetc(in);

    				/*wczytujemy krawedzie*/
linia = 0;

    while (c != EOF){
	while(c == ' ' || c == '\t')
		c = fgetc(in);
        if (c == '\n'){
		if(j == 0) {
			free(tmp);
			fclose(in);
			return 1;
		}
            linia++;
            j = 0;	/*numer wezla*/
	    c = fgetc(in);
	    continue;
        }
	if(linia > wysokosc*szerokosc - 1) {
		free(tmp);
		fclose(in);
		return 1;
	}
       
            while (isdigit(c)){
                tmp[i++] = c;
                c = fgetc(in);
            }
		if(j == 0) {
			graf[linia]->n = 1;
			graf[linia]->w = (int*) malloc(sizeof(int));
			graf[linia]->drogi = (double*) malloc(sizeof(double));
		} 
		else {
			graf[linia]->n++;
			graf[linia]->w = (int*)realloc(graf[linia]->w, sizeof(int) * graf[linia]->n);
			graf[linia]->drogi = (double*)realloc(graf[linia]->drogi, sizeof(double) * graf[linia]->n);
		}
	    if(c != ' ') {
		    free(tmp);
		    fclose(in);
		    return 1;
	    }
            c = fgetc(in);
            if (c == ':'){
                /*po liczbie wystepuje : wiec jest to droga od danego wezla
               mozna jeszcze  sprawdzac czy takie polaczenie moze istniec*/
                    graf[linia]->w[j] = atoi(tmp); 
                    reset_temp(tmp);
		    i = 0;
                  	  /*odczytujemy wage*/
                    c = fgetc(in);
		    if(!isdigit(c)) {
			    free(tmp);
			    fclose(in);
			    return 1;
		    }
                    while (c != ' ' && c != '\n' && c != '\t'){
                        tmp[i++] = c;
                        c = fgetc(in);
                    }
		    
                    if(czy_liczba_dodatnia(tmp)){
                       	graf[linia]->drogi[j] = atof(tmp);
			j++;	
                        reset_temp(tmp);
			i = 0;
                        continue;
                    }
                    else{
                        free(tmp);
                        fclose(in);
                        return 1;
                    }
            }
            else{
                /*gdy brak : skladnia niepoprawna - blad*/
                free(tmp);
		fclose(in);
                return 1;
            }
        
        c = fgetc(in);
    }
    if(linia < szerokosc*wysokosc) {
	    return 1;
    }
    free(tmp);
    fclose(in);
    return 0;
}
