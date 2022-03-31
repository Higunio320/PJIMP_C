all:
	cc -ggdb -c main.c
	cc -ggdb -c dijkstra.c
	cc -ggdb -c bfs.c
	cc -ggdb -c generator.c
	cc -ggdb -c writer.c
	cc -ggdb -c reader.c
	cc -ggdb bfs.o main.o dijkstra.o generator.o writer.o reader.o -o graf
	rm *.o
