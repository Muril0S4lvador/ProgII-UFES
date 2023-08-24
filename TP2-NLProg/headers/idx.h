#ifndef idx_H
#define idx_H

#include <stdio.h>
#include <stdlib.h>
#include <search.h>
#include <string.h>

#include "palavras.h"

#define ALLOC_INICIAL_IDX 250

typedef struct idx tIndices;
typedef tIndices* tIndices_pt;

/**
 * @brief Aloca ou realoca Vetor de struct tDados
 * 
 * @param idx Vetor de tIndices
 * @param controle Inteiro para controlar se o vetor ja foi alocado ou nao
 * @return Vetor de indices alocado/realocado corretamente 
 */
tIndices_pt AlocaERealocaIndices(tIndices_pt idx, int controle);

/**
 * @brief Aloca um vetor de tIndices e o preenche com os dados dos documentos analizados
 * 
 * @param pal Indice de palavras 
 * @return Vetor tIndices
 */
tIndices_pt PreencheEAlocaIndicesDeDoc(tPalavra_pt pal);

/**
 * @brief Verifica se um "idx" esta presente no indice e o retorna
 * 
 * @param indices Vetor de tIndices
 * @param idx Indice procurado no vetor
 * @return Idx
 */
int VerificaIdxIndice(tIndices_pt indices, int idx);

/**
 * @brief Compara idx entre dois ponteiros de tIndices
 * 
 * @param v1 Ponteiro void generico
 * @param v2 Ponteiro void generico
 * @return 
 */
int ComparaIndicesIdx(const void *v1, const void *v2);

/**
* @brief Retorna a quantidade de itens do vetor de tIndices
*
* @param indices Vetor de tIndices
* @return 
*/
int RetornaQtdIdx(tIndices_pt indices);

/**
* @brief Retorna o idx desejado do vetor de tIndices
*
* @param indices Vetor de tIndices
* @param i Indice desejado do vetor de tIndices
* @return 
*/
int RetornaIndiceIdx(tIndices_pt indices, int i);

/**
 * @brief Calcula o cosseno e preenche "simi" de um tIndice com esse valor
 * 
 * @param indices Vetor tIndices
 * @param i Indice o vetor
 * @param num Numerador
 * @param den1 Denominador 1
 * @param den2 Denominador 2
 * @return tIndices_pt 
 */
tIndices_pt AtualizaSimiIdx(tIndices_pt indices, int i, double num, double den1, double den2);

/**
 * @brief Ordena o vetor de indices de acordo com a similaridade
 * 
 * @param indices Vetor de tIndices
 * @return 
 */
tIndices_pt OrdenaPorSimilaridade(tIndices_pt indices);

/**
 * @brief Compara similaridade entre dois ponteiros
 * 
 * @param v1 Ponteiro void generico
 * @param v2 Ponteiro void generico
 * @return 
 */
int ComparaSimilaridade(const void *v1, const void *v2);

/**
 * @brief Libera a memoria alocada para os ponteiros de tIndices
 * 
 * @param indices Vetor de tIndices
 */
void LiberaMemoriaIdx(tIndices_pt indices);

void ImprimeIndices(tIndices_pt indices);

#endif