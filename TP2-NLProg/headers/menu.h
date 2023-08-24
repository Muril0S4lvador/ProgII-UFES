#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <search.h>
#include <string.h>

#include "arquivos.h"
#include "classes.h"
#include "idx.h"

typedef void (*fptrMenu)(tPalavra_pt, tDocumento_pt, int);


/**
 * @brief Imprime mensagem de boas vindas
 * 
 */
void BemVindo();

/**
 * @brief Imprime menu
 * 
 */
void ImprimeMenu(void);

/**
 * @brief Inicializa o vetor funcoes_menu com as funcoes de cada opcao do menu
 * 
 */
void InicializaFuncoesMenu();

/**
 * @brief Pesquisa a funcao na tabela de dispersao e a retorna
 * 
 * @param opcao Indice da tabela de dispersao desejado
 * @param indicePal Indice de todas as palavras
 * @param indiceDoc Indice de todos os documentos
 * @param K Inteiro passado pela linha de comando
 */
void PesquisaFuncaoMenu(char opcao, tPalavra_pt indicePal, tDocumento_pt indiceDoc, int K);

/**
 * @brief Libera a memoria utilizada no programa 2
 * 
 * @param indicePal Indice de todas as palavras
 * @param indiceDoc Indice de todos os documentos
 * @param K Inteiro passado pela linha de comando
 */
void FinalizaPrograma2(tPalavra_pt indicePal, tDocumento_pt indiceDoc, int K);

/**
 * @brief Le a pesquisa e armazena as palavras no vetor (tPalavra_pt) palPesq
 * 
 * @param indicePal Indice de todas as palavras
 * @param palPesq Vetor tPalavra_pt com as palavras presentes na pesquisa
 * @return Indice de palavras alocado e preenchido 
 */
tPalavra_pt ArmazenaPalavrasPesquisa(tPalavra_pt indicePal, tPalavra_pt palPesq);

/**
 * @brief Buscador de noticias
 * 
 * @param indicePal Indice de todas as palavras
 * @param indiceDoc Indice de todos os documentos
 * @param K Inteiro passado pela linha de comando
 */
void Funcionalidade1(tPalavra_pt indicePal, tDocumento_pt indiceDoc, int K);

/**
 * @brief Classificador de noticias
 * 
 * @param indicePal Indice de todas as palavras
 * @param indiceDoc Indice de todos os documentos
 * @param K Inteiro passado pela linha de comando
 */
void Funcionalidade2(tPalavra_pt indicePal, tDocumento_pt indiceDoc, int K);

/**
 * @brief 
 * 
 * @param indicePal Indice de todas as palavras
 * @param indiceDoc Indice de todos os documentos
 * @param K Inteiro passado pela linha de comando
 */
void RelatorioPalavra(tPalavra_pt idPal, tDocumento_pt idDoc, int K);

/**
 * @brief 
 * 
 * @param indicePal Indice de todas as palavras
 * @param indiceDoc Indice de todos os documentos
 * @param K Inteiro passado pela linha de comando 
 */
void RelatorioDocumentos(tPalavra_pt idPal, tDocumento_pt idDoc, int K);


#endif