#ifndef _ARTISTAS_H_
#define _ARTISTAS_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define ARQUIVOENTRADAARTISTAS "artists_3480.csv"
#define ARQUIVOENTRADAMUSICAS "tracks_full.csv"
#define CAMINHOENTRADA "data_tests/"
#define QTD_ALLOC_INICIAL 100
#define ARQUIVORELATORIOARTISTA "Relatorio_Artista.txt"
#define ARQUIVORELATORIOMUSICA "Relatorio_Musica.txt"
#define ARQUIVOPLAYLISTS "Playlists.dat"

typedef struct artistas tArtistas;
typedef tArtistas* tArtistas_pt;


FILE *AbreArquivoArtistas(FILE *artistasF, char argv[]);

tArtistas_pt AlocaERealocaArtistas(tArtistas_pt artistas, int qtd);

tArtistas_pt LeECriaArtistas(tArtistas_pt artista, FILE *artistasF, int qtd, char id[]);

void ListaArtistasCompleto(tArtistas_pt artistas, int qtdDentroMusica, tArtistas_pt TodosArtistas, int qtdGeral);

tArtistas_pt BuscaArtistaEIncrementa(tArtistas_pt artistaDaMusica, tArtistas_pt artistas, int qtdGeral, int qtdArtistas);

void GerarRelatorioArtistas(tArtistas_pt artistas, int qtdArtistasTotal);


/* FUNÇÕES VISTAS EM TMUSICAS */

tArtistas_pt DefineNome(tArtistas_pt artista, char* nome,  int qtd);

tArtistas_pt LeIdsArtistas(tArtistas_pt artistas, FILE *musicasF, int qtd);

void ListaNomesArtistasMusica(tArtistas_pt artista, int indice);


#endif