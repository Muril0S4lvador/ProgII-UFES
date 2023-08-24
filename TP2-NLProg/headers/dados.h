#ifndef DADOS_H
#define DADOS_H

#include <stdio.h>
#include <stdlib.h>
#include <search.h>
#include <string.h>


#define QTD_ALLOC_INICIAL_DADOS 600

typedef struct dados tDados;
typedef tDados* tDados_pt;

/**
 * @brief Aloca ou realoca Vetor de struct tDados
 * 
 * @param dados Vetor de Dados
 * @param qtd Quantidade de dados de uma struct
 * @return Vetor de dados alocado/realocado corretamente 
 */
tDados_pt AlocaERealocaDados(tDados_pt dados, int qtd);

/**
 * @brief Preenche o struct tDados com as informacoes passadas
 * 
 * @param dados Vetor de tDados
 * @param iDado indice do dado especifico
 * @param posicao posicao da palavra
 * @param frequencia frequencia da palavra
 * @param TF_IDF TF-IDF da palavra
 * @return Vetor de dados alocado e preenchido
*/
tDados_pt InicializaDados(tDados_pt dados, int iDado, int posicao, int frequencia, float TF_IDF);

/**
 * @brief Procura qual palavra faz referencia a um documento em tDocumentos
 * 
 * @param dados Vetor de tDados
 * @param qtd Quantidade de dados
 * @param iD Indice do documento desejado
 * @return Retorna o indice do Vetor tDados que faz referencia a um documento em tDocumentos
 */
int VerificaPosicaoJaDeclarada(tDados_pt dados, int qtd, int idx);

/**
 * @brief Retorna o valor da posicao ou da frequencia de determinado elemento de tDados
 * 
 * @param dados Vetor de Dados
 * @param iDado Indice desejado do Vetor tDados
 * @param opcao Opcao desejada de retorno, ou frequencia ou posicao
 * @return Dependendo da opcao, retorna a frequencia ou a posicao do Vetor tDados
 */
int RetornaDados(tDados_pt dados, int iDado, char opcao);

/**
 * @brief retorna o valor de TF-IDF de um determinado elemento do Vetor
 * 
 * @param dados Vetor de dados
 * @param iDado indice do Vetor de dados desejado
 * @return valor float de TF-IDF
 */
double RetornaTF_IDF(tDados_pt dados, int iDado);

/**
 * @brief Salva um Vetor de tDados em um arquivo binario
 * 
 * @param arq Arquivo binario aberto
 * @param dados Vetor de tDados
 * @param qtd quantidade de dados a serem salvos
 */
void SalvaIndiceDados(FILE *arq, tDados_pt dados, int qtd);

/**
 * @brief Le e armazena o ponteiro de tDados de dentro dos indices
 * 
 * @param arq Arquivo de saida binario do programa 1
 * @param dados Ponteiro de tDados do indice
 * @param qtd quantidade de dados guardada 
 * @return Vetor de tDados_pt alocado e preenchido
 */
tDados_pt LeEArmazenaIndiceDados(FILE *arq, tDados_pt dados, int qtd);

/**
 * @brief Compara posicao entre dois ponteiros de tDados
 * 
 * @param v1 Ponteiro void generico
 * @param v2 Ponteiro void generico
 * @return 
 */
int ComparaPos(const void *v1, const void *v2);

/**
 * @brief 
 * 
 * @param dados 
 * @param tam 
 * @param id 
 * @return 
 */
float ProcuraTFIDFEmDados(tDados_pt dados, int tam, int id);

/**
 * @brief 
 * 
 * @param dados_docs 
 * @param resultado 
 * @return 
 */
tDados_pt CopiaDados(tDados_pt dados_docs, tDados_pt resultado);

/**
 * @brief Compara frequencia entre dois ponteiros de tDados
 * 
 * @param v1 Ponteiro void generico
 * @param v2 Ponteiro void generico
 * @return 
 */
int ComparaFre(const void *v1, const void *v2);

/**
 * @brief Ordena decrescente o vetor pela frequencia
 * 
 * @param dados Ponteiro de tDados
 * @param size tamanho do ponteiro de tDados
 */
void OrdenaFrequencia(tDados_pt dados, int size);


/* EXCLUIR DEPOIS */
void ImprimeDados(tDados_pt dados, int qtd); //teste
void ImprimeDadosArq(tDados_pt dados, int qtd, FILE *arq);

#endif