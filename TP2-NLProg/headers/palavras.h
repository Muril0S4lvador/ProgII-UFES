#ifndef PALAVRAS_H
#define PALAVRAS_H

#include <stdio.h>
#include <stdlib.h>
#include <search.h>
#include <string.h>
#include <math.h>

#include "dados.h"

#define QTD_ALLOC_INICIAL_PAL 1000
#define QTD_ALLOC_INICIAL_CAR 10

typedef struct palavra tPalavra;
typedef tPalavra* tPalavra_pt;
typedef int (*fptrRetorna)(tPalavra_pt, int, int, char);


/**
 * @brief Aloca e/ou realoca vetor de struct tPalavra
 * 
 * @param pal Indice de palavras
 * @param controle Inteiro para controlar se o vetor já foi alocado ou não
 * @return Indice de palavras alocado corretamente
 */
tPalavra_pt AlocaERealocaPalavras(tPalavra_pt pal, int controle);

/**
 * @brief Aloca e/ou realoca espaco para uma string enquanto a lê
 * 
 * @param arq Arquivo aberto de texto
 * @param str Vetor de char que deseja ser alocado e lido
 * @return String lida e bem alocada
 */
char* LeEAlocaString(FILE *arq, char *str);

/**
 * @brief Inicializa a palavra
 * 
 * @param pal Indice de palavras
 * @param controle Inteiro para controlar se o vetor já foi alocado ou não
 * @param str Vetor de char contendo a palavra a ser armazenada
 * @return Indice de palavras alocado e atualizado
 */
tPalavra_pt InicializaPalavra(tPalavra_pt pal, int controle, char *str);

/**
 * @brief Retorna a quantidade total de palavras lidas 
 * 
 * @param pal Indice de palavras
 * @return Quantidade total de palavras dentro do indice de palavras
 */
int RetornaQtdDePalavrasLidas(tPalavra_pt palavra);

/**
 * @brief Aumenta em 1 a quantidade total de palavras no indice de palavras 
 * 
 * @param pal Indice de palavras
 */
void AtualizaQtdPalavrasLidas(tPalavra_pt palavras);

/**
 * @brief Procura determinada palavra dentro do indice de palavras e retorna seu indice
 * 
 * @param pal Indice de palavras
 * @param str Palavra a ser procurada no indice
 * @return Indice da palavra procurada dentro do vetor de palavras ou, caso ela não esteja ainda no vetor, -1
 */
int VerificaIndicePalavra(tPalavra_pt pal, char *str);

/**
 * @brief Atualiza o vetor tDados de determinada palavra
 * 
 * @param pal Indice de palavras
 * @param iP Indice do vetor de tPalavras
 * @param posicao Documento em que a palavra aparece
 * @param frequencia Frequencia da palavra no documento
 * @param TF_IDF TF-IDF da poalavra no documento
 */
void AtualizaDadosDocumentosEmPalavras(tPalavra_pt pal, int iP, int posicao, int frequencia, float TF_IDF);

/**
 * @brief Ordena o indice de palavras em ordem alfabetica
 * 
 * @param pal Indice de palavras
 */
void OrdenaOrdemAlfabetica(tPalavra_pt pal);

/**
 * @brief Compara duas palavras por meio do strcmp
 * 
 * @param pal1 Ponteiro void generico
 * @param pal2 Ponteiro void generico
 * @return Valor de strcmp
 */
int ComparaNomes(const void *pal1, const void *pal2);

/**
 * @brief Inicializa o vetor operacoes_retorno com as funcoes de retorno
 * 
 */
void InicializaOperacoesRetorno();

/**
 * @brief Pesquisa a funcao na tabela de dispersao e a retorna
 * 
 * @param pal Indice de palavras
 * @param iP Indice desejado do vetor
 * @param iDado Indice desejado do vetor de tDados, dentro do indice de palavras
 * @param opcao Indice da tabela de dispersao desejado
 * @return Retorna valor dependendo da operacao desejada
 */
int RetornaDadosDocumentos(tPalavra_pt pal, int iP, int iDado, char opcao);

/**
 * @brief Retorna a quantidade de dados de determinada palavra em um documento
 * 
 * @param pal Indice de palavras
 * @param iP Indice desejado do vetor
 * @param iDado Indice desejado do vetor de tDados_pt
 * @param opcao Indice da tabela de dispersao desejado
 * @return Quandidade de dados da palavra 
 */
int RetornaDadosDocumentos_Qtd(tPalavra_pt pal, int iP, int iDado, char opcao);

/**
 * @brief Retorna o valor da posicao de determianda palavra em um documento
 * 
 * @param pal Indice de palavras
 * @param iP Indice desejado do vetor
 * @param iDado Indice desejado do vetor de tDados_pt
 * @param opcao Indice da tabela de dispersao desejado
 * @return Indice do documento em que aquela palavra aparece
 */
int RetornaDadosDocumento_Posicao(tPalavra_pt pal, int iP, int iDado, char opcao);

/**
 * @brief retorna o valor da frequencia de determinada palavra em um documento
 * 
 * @param pal Indice de palavras
 * @param iP Indice desejado do vetor
 * @param iDado Indice desejado do vetor de tDados_pt
 * @param opcao Indice da tabela de dispersao desejado
 * @return Frequencia da palavra no documento 
 */
int RetornaDadosDocumento_Frequencia(tPalavra_pt pal, int iP, int iDado, char opcao);

/**
 * @brief retorna o valor do TF-IDF de determinada palavra em um documento
 * 
 * @param pal Indice de palavras
 * @param iP Indice desejado do vetor
 * @param iDado Indice desejado do vetor de tDados_pt
 * @param opcao Indice da tabela de dispersao desejado
 * @return Valor de TF-IDF 
 */
float RetornaDadosDocumento_TF_IDF(tPalavra_pt pal, int iP, int iDado);

/**
 * @brief calcula o valor TF-IDF de determinada palavra
 * 
 * @param pal Indice de palavras
 * @param iP Indice da palavra no vetor
 * @param iDado Indice desejado no vetor de tDados_pt
 * @param qtd_documentos Quantidade de documentos em que a palavra aparece
 * @return Valor de TF-IDF
 */
double CalculaTF_IDF(tPalavra_pt pal, int iP, int tf, int qtd_documentos);

/**
 * @brief Salva o indice de palavras no arquivo binario
 * 
 * @param arq Arquivo binario aberto
 * @param pal Indice de palavras
 * @param qtd Quantidade de palavras no indice
 */
void SalvaIndicePalavra(FILE *arq, tPalavra_pt pal, int qtd);

/**
 * @brief Libera a memoria alocada para o indice de palavras
 * 
 * @param pal Indice de palavras
 */
void LiberaMemoriaPalavra(tPalavra_pt pal);

/**
 * @brief Libera memoria das palavras pesquisadas que nao estao presentes no indice
 * 
 * @param palPesq Vetor com as palavras pesquisadas
 */
void LiberaMemoriaPalPesq(tPalavra_pt palPesq);

/**
 * @brief Le e preenche o indice de palavras no programa 2
 * 
 * @param arq Arquivo binário com o indice
 * @param pal Indice de palavras vazio e não alocado
 * @return Indice de palavras alocado e preenchido 
 */
tPalavra_pt LeEArmazenaIndicePalavra(FILE *arq, tPalavra_pt pal);

/**
 * @brief Le a pesquisa 
 * 
 * @return Ponteiro com a pesquisa 
 */
char* LePesquisaUsuario();

/**
 * @brief Separa as palavras da pesquisa e as armazena em um vetor tPalavra_pt
 * 
 * @param palaPesq Vetor que ira armazenar as palavras
 * @param pesquisa String com a pesquisa
 * @return Vetor com as palavras pesquisadas  
 */
tPalavra_pt SeparaPalavrasPesquisa(tPalavra_pt palaPesq, char* pesquisa);

/**
 * @brief Verifica se a palavra existe no indice de palavras; se sim, copia as copia suas informacoes para palPesq
 * 
 * @param palPesq Vetor com as palavras pesquisadas
 * @param idPal Indice com todas as palavras
 */
void AtualizaDadosPalavrasPesquisadas(tPalavra_pt palPesq, tPalavra_pt idPal);

/**
 * @brief Retorna idx da palavra 
 * 
 * @param palavra Vetor com as palavras pesquisadas
 * @param indice Indice da palavra buscada
 * @return Valor do idx 
 */
int RetornaIdxDePalavra(tPalavra_pt palavra, int indice);

/**
 * @brief Retorna a quantidade de vezes que a palavra apareceu na pesquisa
 * 
 * @param palavra Vetor com as palavras pesquisadas
 * @param indice Indice da palavra buscada
 * @return Quantidade 
 */
int RetornaQtdPesquisa(tPalavra_pt palavra, int indice);

/**
 * @brief Retorna a quantidade de dados de uma palavra
 * 
 * @param pal Vetor com as palavras pesquisadas
 * @param iP Indice da palavra buscada
 * @return Valor do indice 
 */
int RetornaQtdDados(tPalavra_pt pal, int iP);

/**
 * @brief Procura uma palavra no indice e a copia para tPalavra_pt palPesq
 * 
 * @param palPesq Vetor com as palavras pesquisadas
 * @param idPal Indice com todas as palavras
 * @param str Nome da palavra procurada
 * @return Vetor com as palavras pesquisadas 
 */
tPalavra_pt AchaPalavraPesquisada(tPalavra_pt palPesq, tPalavra_pt idPal, char *str);

/**
 * @brief Ordena os dados_documentos de uma palavra de indice 0 a partir das frequencias 
 * 
 * @param pal tPalavra_pt com a palavra escolhida no relatorio
 */
void OrganizaDados(tPalavra_pt pal);

/**
 * @brief Imprime a parte inicial do relatorio de palavras
 * 
 * @param pal tPalavra_pt com a palavra do relatorio
 */
void ImprimeInicioRelatorioPalavras(tPalavra_pt pal);

#endif