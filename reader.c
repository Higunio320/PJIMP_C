#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include"bfs.h"
#include"reader.h"

void reset_temp(char* tmp, int* k){

	while((*k)--){
		tmp[(*k)] = '\0';
        }
        (*k)++;	
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

int czytaj_graf(char* file_name, wierzcholek** wierzcholek, int wysokosc, int szerokosc){
    
    FILE *in = fopen(file_name, "r");
    if (in == NULL){
        return 4;
    }
    char* tmp = (char*) malloc(4096 * sizeof(char));
    int c, j = 0;
    int k;
    int linia = 0;
    int i = 0;
     
    /*wczytywanie liczby kolumn i wierszy*/
    int licznik = 0;
    c = fgetc(in);
    if (c == EOF){
	free(tmp);
        return 4;
    }
    while(linia == 0){
        if (c != ' ' && c != '\n'){
            tmp[i++] = c;
        }
        else{
            if (licznik == 0 || licznik == 1){
            if (licznik == 0){
                    	wysokosc = atoi(tmp);
                    }
                    else{
                        szerokosc = atoi(tmp);
                    }
                    reset_temp(tmp, &k);
                   	licznik++;
            }
            else{
                free(tmp);
                fclose(in);
                return 3;
            }
        }
        if(c == '\n'){
            linia++;
        }
        c = fgetc(in);
    }
    				/*wczytujemy krawedzie*/
c = fgetc(in);

    while (c != EOF){
        if (linia > wysokosc*szerokosc){
            free(tmp);
            return 3;
        }
        if (c == '\n'){
            linia++;
            j = 0;	/*numer wezla*/
        }
       
            while (isdigit(c)){
                tmp[i++] = c;
                c = fgetc(in);
            }
		if(j == 0) {
			wierzcholek[linia]->n = 1;
			wierzcholek[linia]->w = (int*) malloc(sizeof(int));
			wierzcholek[linia]->drogi = (double*) malloc(sizeof(double));
		} 
		else {
			wierzcholek[linia]->n++;
			wierzcholek[linia]->w = (int*)realloc(wierzcholek[linia]->w, sizeof(int) * wierzcholek[linia]->n);
			wierzcholek[linia]->drogi = (double*)realloc(wierzcholek[linia]->drogi, sizeof(double) * wierzcholek[linia]->n);
		}	
 
            c = fgetc(in);
            if (c == ':'){
                /*po liczbie wystepuje : wiec jest to droga od danego wezla
               mozna jeszcze  sprawdzac czy takie polaczenie moze istniec*/
                    wierzcholek[j]->w[j] = atoi(tmp); 
                    reset_temp(tmp, &k);
                  	  /*odczytujemy wage*/
                    c = fgetc(in);
                    while (c != ' ' && c != '\n'){
                        tmp[i++] = c;
                        c = fgetc(in);
                    }
		    
                    if(czy_liczba_dodatnia(tmp)){
                       	wierzcholek[linia]->drogi[j] = atof(tmp);
			j++;	
                        reset_temp(tmp, &k);
                        continue;
                    }
                    else{
                        free(tmp);
                        fclose(in);
                        return 4;
                    }
            }
            else{
                /*gdy brak : skladnia niepoprawna - blad*/
                free(tmp);
		fclose(in);
                return 4;
            }
        
        c = fgetc(in);
    }
    free(tmp);
    fclose(in);
    return 0;
}
