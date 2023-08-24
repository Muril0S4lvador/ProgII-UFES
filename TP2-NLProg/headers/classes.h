#ifndef CLASSE_H
#define CLASSE_H

#include <stdio.h>
#include <stdlib.h>
#include <search.h>
#include <string.h>

#include "documentos.h"

#define QTD_ALLOC_INICIAL_CLASSE 20

typedef struct classe tClasse;
typedef tClasse* tClasse_pt;


/**
 * @brief Aloca e realoca vetor tClasse_pt
 * 
 * @param classe Vetor tClasse_pt 
 * @param controle Qunatidade de classes presentes no vetor
 * @return tClasse_pt 
 */
tClasse_pt AlocaERealocaClasses(tClasse_pt classe, int controle);

/**
 * @brief Procura uma classe no vetor e retorna seu indice; se nao existir, retorna -1
 * 
 * @param classes Vetor com as classes
 * @param str String com o nome que deseja-se procurar dentre as classes
 * @return indice da classe procurada 
 */
int VerificaIndiceClasse(tClasse_pt classes, char *str);

/**
 * @brief Ordena as classes a partir da ordem alfabetica dos nomes 
 * 
 * @param classes Vetor tClasses_pt
 */
void OrdenaOrdemAlfabeticaClasses(tClasse_pt classes);

/**
 * @brief Compara os nomes de duas classes
 * 
 * @param cl1 Ponteiro void generico
 * @param cl2 Ponteiro void generico
 * @return Resultado da comparacao 
 */
int ComparaClasses(const void *cl1, const void *cl2);

/**
 * @brief Atualiza as informacoes de uma classe
 * 
 * @param classes Vetor tClasses_pt
 * @param str String com o nome da classe que deseja-se atualizar
 * @param fre Frequencia da classe 
 * @return Vetor tClasses_pt
 */
tClasse_pt AtualizaClasses(tClasse_pt classes, char *str, int fre);

/**
 * @brief Inicializa a classe e armazena suas informacoes
 * 
 * @param classes Vetor tClasses_pt
 * @param str String com o nome da classe que deseja-se atualizar
 * @param controle 
 * @return Vetor tClasses_pt 
 */
tClasse_pt InicializaClasse(tClasse_pt classes, char *str, int controle);

/**
 * @brief Preenche vetor tClasses com base nos K primeiros documentos e procura a que possui maior frequencia
 * 
 * @param docsAnalise Vetor tIndices_pt com os indices dos documentos que serao analisados
 * @param indiceDoc Vetor tDocumento_pt com todos os documentos
 * @param K Quantidade de documentos que devem ser analisados
 */
void BuscaEImprimeClasseComum(tIndices_pt docsAnalise, tDocumento_pt indiceDoc, int K);

/**
 * @brief Libera memoria de todas as classes do vetor
 * 
 * @param classe Vetor de tClasse_pt
 */
void LiberaMemoriaClasse(tClasse_pt classe);

/**
 * @brief Retorna quantidade de classes no vetor
 * 
 * @param classes Vetor de tClasse_pt
 * @return Quantidade de classes
 */
int RetornaQtdClasses(tClasse_pt classes);

/**
 * @brief Aumenta em 1 a quantidade de classes
 * 
 * @param classes Vetor de tClasse_pt
 */
void AumentaQtdClasses(tClasse_pt classes);

/**
 * @brief Aumenta o valor da frequencia da classe de indice i
 * 
 * @param classes Vetor de tClasse_pt
 * @param i Indice no vetor
 * @param fre Valor da frequencia que deseja ser somado
 */
void AumentaFrequenciaClasse(tClasse_pt classes, int i, int fre);

/**
 * @brief Retorna a frequencia da classe de indice i
 * 
 * @param classes Vetor de tClasse_pt
 * @param i Indice 
 * @return Frequencia da classe
 */
int RetornaFrequenciaClasse(tClasse_pt classes, int i);

/**
 * @brief Retorna o nome da classe de indice i
 * 
 * @param classes Vetor de tClasse_pt
 * @param i Indice
 * @return Nome da classe
 */
char* RetornaNomeClasse(tClasse_pt classes, int i);

/**
 * @brief Preenche vetor tClasse com os dados da palavra escolhida no relatorio 
 * 
 * @param palPesq tPalavra_pt com a palavra pesquisada
 * @param idDoc Indice com todos os documentos
 * @return Vetor de tClasse_pt 
 */
tClasse_pt PreencheVetorClasse(tPalavra_pt palPesq, tDocumento_pt idDoc);

/**
 * @brief Compara as frequencias de duas classes
 * 
 * @param v1 Ponteiro void generico
 * @param v2 Ponteiro void generico
 * @return Resultado da comparacao 
 */
int ComparaFreClasse(const void *v1, const void *v2);

/**
 * @brief Imprime relatorio de palavras
 * 
 * @param pal tPalavra_pt com a palavra pesquisada
 * @param classes Vetor tClasses_pt
 * @param idDoc Vetor com todos os documentos
 */
void ImprimeRelatorioPal(tPalavra_pt pal, tClasse_pt classes, tDocumento_pt idDoc);

/**
 * @brief Imprime as classes e suas frequencias
 * 
 * @param classe Vetor tClasses_pt
 */
void ImprimeClasses(tClasse_pt classe);



#endif