#ifndef _MUSICAS_H_
#define _MUSICAS_H_

#include "Artistas.h"

typedef struct musicas tMusicas;
typedef tMusicas* tMusicas_pt;


FILE* AbreArquivoMusicas(FILE *musicasF, char argv[]);

tMusicas_pt AlocaERealocaMusicas(tMusicas_pt musicas, int qtd);

tMusicas_pt LeECriaMusicas(tMusicas_pt musicas, FILE *musicasF, int qtd, char id[]);

tMusicas_pt IdentificaArtistasMusica(tMusicas_pt musicas, tArtistas_pt artistas, FILE *musicasF, char lista_ids[], int qtd, int qtdArtistas);

tMusicas_pt LeECalculaInstrumentalness(tMusicas_pt musicas, FILE *musicasF, int qtd);

void ListarMusicaCompleto(tMusicas_pt musicas, tArtistas_pt artistas, int i, int qtdArtistas);

tMusicas_pt LeArtistasEmMusicas(tMusicas_pt musica, FILE *musicasF, int qtd);

int MaisDeUmArtista(char *lista, int tam);


/* FUNCOES PRESENTES NO TPLAYLISTS */

void ImprimeNomeMusica(tMusicas_pt musica, int i);

tMusicas_pt CriaPonteiroMusicas(tMusicas_pt musicas_playlist, int *indices, int qtd_musicasPlaylist, tMusicas_pt musicas, int qtdMusicas);

double CalculaMedia(tMusicas_pt musicas, int qtd, int iC);

double RetornaCaracteristicaMusica(tMusicas_pt musicas, int i, int iC);


/* FUNCOES PRESENTES NO SWITCH */

tMusicas_pt IncrementaVezesMusicaEmPlaylist(tMusicas_pt musicas, int i);

tArtistas_pt IncrementaVezesArtistaEmPlaylist(tMusicas_pt musica, int indice, tArtistas_pt artistas, int qtd);

void BuscarMusicas(char texto[], tMusicas_pt musicas, int qtdMusicas);

int ExibeERetornaIndices(int qtd);

void ListarMusica(tMusicas_pt musica, int indice);

void EscutarMusica(int i, tMusicas_pt musica);

void GerarRelatorioMusicas(tMusicas_pt musicas, int qtdMusicasTotal);

void LiberarMusicas(tMusicas_pt musicas, int qtd);


#endif