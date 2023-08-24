#ifndef _PLAYLISTS_H_
#define _PLAYLISTS_H_

#include "Musicas.h"

typedef struct playlists tPlaylists;
typedef tPlaylists* tPlaylists_pt;


void ImprimeMenu(void);


tPlaylists_pt AlocaERealocaPlaylists(tPlaylists_pt playlists, int qtd);

tPlaylists_pt AlocaERealocaIndice(tPlaylists_pt playlist, int qtd, int iP);

tPlaylists_pt CriaPlaylist(tPlaylists_pt playlist, char nome[], int qtd);

tPlaylists_pt IncrementaPlaylist(tPlaylists_pt playlist, int iP, tMusicas_pt musicas, int iM);

int VerificaPlaylist(tPlaylists_pt playlists, int iP, tMusicas_pt musicas, int iM);

void ListarPlaylistCompleta(tPlaylists_pt playlist, int indice, tMusicas_pt musicas);

void ListarPlaylists(tPlaylists_pt playlist, int qtd);


/* RECOMENDACAO DE MUSICAS */

void RecomendaMusicas(tPlaylists_pt playlists, int iP, tMusicas_pt musicas, int k, int qtdMusicas);

double* AlocaERealocaDouble(double *distancia, int qtdMusicas);

double CalculaDistanciaEuclidiana(double mediaCaracteristicas[], double caracteristicas[]);

void ImprimeDistanciasOrdemCrescente(double *distancia, tMusicas_pt musicas, int qtdMusicas, int k, tPlaylists_pt playlists, int iP);


/* MANIPULACAO DOS ARQUIVOS DE PLAYLISTS */

void SalvaPlaylists(tPlaylists_pt playlists, int qtd);

FILE* AbreArquivoPlaylists();

tPlaylists_pt LeArquivoPlaylists(tPlaylists_pt playlists, FILE *playlistsF, int qtd);


/* FUNCAO PARA LIBERAR MEMORIA DE TODOS OS PONTEIROS, MANTEM NO FUNDO DO CODIGO */

void LiberaMemoria(tArtistas_pt artistas, tMusicas_pt musicas, int qtdMusicas, tPlaylists_pt playlists, int qtdPlaylists);


#endif