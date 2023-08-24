all: clean main

main: main.o Artistas.o Musicas.o Playlists.o
	gcc -o main main.o Artistas.o Musicas.o Playlists.o -lm

main.o: main.c Artistas.h Musicas.h Playlists.h
	gcc -o main.o main.c -c -Wall

Artistas.o: Artistas.c Artistas.h
	gcc -o Artistas.o Artistas.c -c -Wall

Musicas.o: Musicas.c Musicas.h
	gcc -o Musicas.o Musicas.c -c -Wall

Playlists.o: Playlists.c Playlists.h
	gcc -o Playlists.o Playlists.c -c -Wall

clean:
	rm -rf *.o *~ main
