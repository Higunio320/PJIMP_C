
typedef struct {
	int x; 		/* numer wierzcholka - moze byc do zmiany bo po co on*/
	int n;		/*ilosc polaczen z tego wierzcholka*/
	int *w;		/*numery wierzcholkow polaczonych*/	
	double *drogi;	/*drogi do wierzcholkow polaczonych zgodnie z kolejnoscia wyzej*/
	int p;		/*numer poprzednika w najkrotszej drodze (Dijkstra) */
	int stan;	/*stan potrzebny do BFS (by ustalic czy juz sie przeszlo przez ten wierzcholek*/
} wierzcholek;

void double_size(int* a, int* n);

int bfs(wierzcholek** a, int rozmiar);

