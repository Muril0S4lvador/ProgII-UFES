#ifndef DOCUMENTOS_H
#define DOCUMENTOS_H

#include <stdio.h>
#include <stdlib.h>
#include <search.h>
#include <string.h>

//#include "palavras.h"
#include "idx.h"

#define QTD_ALLOC_INICIAL_DOC 500
#define QTD_NOTICIAS 10 
#define QTD_RELATORIO 10

typedef struct documento tDocumento;
typedef tDocumento* tDocumento_pt;


/**
 * @brief Encontra o endereço completo do arquivo de noticias
 * 
 * @param doc Indice de documentos
 * @param iD Indice desejado no vetor
 * @param caminho_inicial Endereco do arquivo de entrada inicial recebido pelos argumentos
 * @param endereco Vetor de char onde será armazenado o endereço completo do arquivo de notícias
 * @return Endereco completo do arquivo desejado
 */
char* RetornaEnderecoDocumento(tDocumento_pt doc, int iD, char* caminho_inicial, char* endereco);

/**
 * @brief Aloca e/ou realoca vetor de documentos
 * 
 * @param doc indice de documentos
 * @param qtd Quantidade de documentos lidos
 * @return Indice de documentos alocado corretamente 
 */
tDocumento_pt AlocaERealocaIndiceDocumentos(tDocumento_pt doc, int controle);

/**
 * @brief Retorna a quantidade total de documentos lidos 
 * 
 * @param pal Indice de documentos
 * @return Quantidade de documentos lidos pelo programa
 */
int RetornaQtdDeDocLidos(tDocumento_pt doc);

/**
 * @brief Aumenta a quantidade total de documentos lidos pelo programa
 * 
 * @param doc Indice de documentos
 */
void AumentaQtdDeDocLidos(tDocumento_pt doc);

/**
 * @brief Retorna quantidade de dados (palavras) presentes no documentos
 * 
 * @param doc Vetor de documentos
 * @param i Indice do documento procurado
 * @return Quantidade de dados 
 */
int RetornaQtdDadosDoDoc(tDocumento_pt doc, int i);

/**
 * @brief Retorna classe do documento
 * 
 * @param doc Vetor de documentos
 * @param i Indice do d
 * @return Classe 
 */
char* RetornaClasseDoDoc(tDocumento_pt doc, int i);

/**
 * @brief Retorna o nome do documento de indice i
 * 
 * @param doc Vetor de documentos
 * @param i Idx do documento no vetor
 * @return Nome do documento 
 */
char* RetornaNomeDoDoc(tDocumento_pt doc, int i);

/**
 * @brief Retorna o idx do documento
 * 
 * @param doc Vetor de documentos
 * @param i Idx do documento no vetor
 * @return Idx do documento
 */
int RetornaIdxDoDoc(tDocumento_pt doc, int i);

/**
 * @brief Lê o nome e a classe de um documento
 * 
 * @param arq Arquivo inicial de entrada
 * @param doc Indice de documentos
 * @return Se for o final do arquivo retorna 1, se nao, 0
 */
int LeEInicializaDocumento(FILE *arq, tDocumento_pt doc);

/**
 * @brief Calcula o TF-IDF e armazena nos vetores dados_documentos e dados_palavras 
 * 
 * @param doc Indice de documentos
 * @param pal Indice de palavras
 */
void AtualizaDadosNosIndices(tDocumento_pt doc, tPalavra_pt pal);

/**
 * @brief Atualiza o vetor tDados de um documento sobre as palavras contidas nele
 * 
 * @param doc Indice de documentos
 * @param iD Indice desejado do indice de documentos
 * @param iP Indice desejado do indice de palavras
 * @param frequencia Frequencia da palavra no indice de documentos
 */
tDocumento_pt AtualizaDadosPalavrasEmDocumentos(tDocumento_pt doc, int iD, int posicao, int frequencia, float TF_IDF);

/**
 * @brief Salva o indice de documentos em um arquivo binario
 * 
 * @param arq Arquivo binario aberto
 * @param doc Indice de documentos
 * @param qtd Quantidade de documentos salvos no vetor
 */
void SalvaIndiceDocumento(FILE *arq, tDocumento_pt doc, int qtd);

/**
 * @brief Libera a memoria alocada para o indice de documentos
 * 
 * @param doc Indice de documentos
 */
void LiberaMemoriaDocumento(tDocumento_pt doc);

/**
 * @brief Le e preenche o indice de documentos no programa 2
 * 
 * @param arq Arquivo binário com o indice
 * @param doc Indice de documentos vazio e não alocado
 * @return Indice de documentos alocado e preenchido
 */
tDocumento_pt LeEArmazenaIndiceDocumento(FILE *arq, tDocumento_pt doc);

/**
 * @brief Procura determinado documento dentro do indice e o retorna
 * 
 * @param doc Vetor de documentos
 * @param iD Indice
 * @return Documento procurado
 */
tDocumento_pt VerificaIndiceDocumento(tDocumento_pt doc, int iD);

/**
 * @brief Compara dois documentos a partir de seus idx
 * 
 * @param v1 Ponteiro void generico
 * @param v2 Ponteiro void generico
 * @return Resultado da comparacao (diferenca entre os valores)
 */
int ComparaIdx(const void *v1, const void *v2);

/**
 * @brief Ordena o vetor de documentos a partir de seus indices
 * 
 * @param doc Indice documentos
 */
void OrdenaDocsPorIdx(tDocumento_pt doc);

/**
 * @brief Atualiza a variavel Valor no indice de documentos
 * 
 * @param indiceDoc Indice de documentos
 * @param docsAnalise vetor com os documentos analizados
 * @param palPesq Vetor com as palavras pesquisadas
 * @param indicePal Indice de palavras
 */
void AtualizaValorDoc(tDocumento_pt indiceDoc, tIndices_pt docsAnalise, tPalavra_pt palPesq, tPalavra_pt indicePal);

/**
 * @brief Compara dois documentos a partir da variavel "Valor"
 * 
 * @param v1 Ponteiro void generico
 * @param v2 Ponteiro void generico
 * @return Diferenca entre os valores
 */
int ComparaValor(const void *v1, const void *v2);

/**
 * @brief Ordena vetor tDocumento_pt a partir da variavel "Valor"
 * 
 * @param idDoc Indice de documentos
 */
void OrdenaValorTF_IDF(tDocumento_pt idDoc);

/**
 * @brief Imprime o resultado do buscador de noticias
 * 
 * @param indiceDoc Indice de documentos
 * @param docsAnalise Vetor tIndices_pt com os documentos analizados
 */
void ImprimeBusca(tDocumento_pt indiceDoc, tIndices_pt docsAnalise);

/**
 * @brief Calcula a similaridade (cosseno) de cada documento presente em docsAnalise
 * 
 * @param docsAnalise Vetor tIndices_pt com os documentos que devem ser analisados 
 * @param indiceDoc Indice de documentos
 * @param consulta Ponteiro com o documento formado pelas palavras pesquisadas
 */
void CalculoSimilaridade(tIndices_pt docsAnalise, tDocumento_pt indiceDoc, tDocumento_pt consulta);

/**
 * @brief Calcula a norma das palavras de um documento
 * 
 * @param indiceDoc Vetor de documentos
 * @param iD Idx do documento no vetor
 * @return Valor da norma
 */
float CalculoNorma(tDocumento_pt indiceDoc,  int iD);

/**
 * @brief Compara dois documentos de acordo com a quantidade de dados de cada um
 * 
 * @param v1 Ponteiro void generico
 * @param v2 Ponteiro void generico
 * @return Resultado da comparacao
 */
int ComparaQtdDados(const void *v1, const void *v2);

/**
 * @brief Aloca um ponteiro de tDocumento e copia o indice de documentos para ele, a fim de nao alterar o original
 * 
 * @param doc Indice de documentos
 * @param docCopy Copia do indice de documentos 
 * @return O indice ordenado pela quantidade de dados 
 */
tDocumento_pt DuplicaIndiceDoc(tDocumento_pt doc, tDocumento_pt docCopy);

/**
 * @brief Imprime o relatorio de documentos
 * 
 * @param doc Indice de documentos
 */
void ImprimeRelatorioDoc(tDocumento_pt doc);

/**
 * @brief Imprime informacoes do documento no relatorio de palavras
 * 
 * @param idDoc Vetor de documentos
 * @param pos Idx do documento desejado
 * @param freq Frequencia da palavra no documento
 */
void ImprimeDocsRelatorioPalavra(tDocumento_pt idDoc, int pos, int freq);

#endif