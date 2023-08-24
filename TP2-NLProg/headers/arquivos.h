#ifndef ARQUIVOS_H
#define ARQUIVOS_H

#include <stdio.h>
#include <stdlib.h>
#include <search.h>
#include <string.h>

#include "documentos.h"

/**
 * @brief Verifica se o numero de argumentos recebidos pelo terminal coincide com a qtd necessaria do programa
 * 
 * @param argc Quantidade de argumentos
 * @param num_programa numero referente ao programa aberto (ex.: 1 -> programa 1)
 */
void ConfereArgumentos(int argc, int num_programa);

/**
 * @brief Verifica o argv[1] se tem o endereco do arquivo necessario, se nao tiver retorna 0
 * 
 * @param argv O argumento de indice 1, para testar se tem ou nao a terminacao .txt
 * @return int que informa se é falso ou verdadeiro que argv[1] é o endereço do arquivo de entrada
 */
int RetornaCaminhoInicial(char *argv[]);

/**
 * @brief Verifica o argv[1] se tem o endereco do arquivo necessario, se nao tiver retorna 0
 * 
 * @param argv O argumento de indice 1, para testar se tem ou nao a terminacao .bin
 * @return int que informa se é falso ou verdadeiro que argv[1] é o endereço do arquivo de entrada
 */
int RetornaCaminhoArqBinario(char *argv[]);

/**
 * @brief Verifica se o arquivo abriu corretamente, caso contrário, encerra o programa
 * 
 * @param caminho Endereco do arquivo aberto
 * @param arq Arquivo desejado
 */
void ConfereAberturaAquivo(char *caminho, FILE *arq);

/**
 * @brief Abre um arquivo em formato .txt
 * 
 * @param caminho Endereco do arquivo desejado
 * @param opcao Opcao de abertura (ler ou escrever um arquivo)
 * @return Arquivo de texto aberto 
 */
FILE *AbreArquivoTexto(char *caminho, char opcao);

/**
 * @brief Abre um arquivo em formato .bin
 * 
 * @param caminho Endereço do arquivo desejado
 * @param opcao Opção de abertura (ler ou escrever um arquivo)
 * @return Arquivo binário aberto 
 */
FILE *AbreArquivoBinario(char *caminho, char opcao);

/**
 * @brief Le o arquivo inicial e inicializa o vetor tDocumento_pt com os nomes e as classes de cada noticia
 * 
 * @param arq Arquivo com os nomes dos arquivos que possuem o texto de cada noticia
 * @return Indice de documentos alocado e atualizado 
 */
tDocumento_pt LeArquivoInicial(FILE *arq, tDocumento_pt documentos);

/**
 * @brief Le o conteúdo de todos os arquivos de noticias recebidos pela função 'LeArquivoInicial'
 * 
 * @param doc Indice de documentos, contendo o nome dos arquivos de noticias a serem lidos
 * @param caminho Caminho inicial recebido pelos argumentos, por ele será obtido o caminho da pasta dos arquivos de noticias
 * @param palavras Indice de palavras não alocado
 * @return Indice de palavras alocado corretamente e atualizado
 */
tPalavra_pt LeTodosOsArquivos(tDocumento_pt doc, char *caminho, tPalavra_pt palavras);

/**
 * @brief Salva o indice de palavras e de documentos em um arquivo binário
 * 
 * @param caminho_arq Endereço para a criação do arquivo de saída binário, recebido como arqgumento
 * @param pal Indice de palavras
 * @param doc Indice de documentos
 */
void SalvaIndices(char *caminho_arq, tPalavra_pt pal, tDocumento_pt doc);

/**
 * @brief Informa quantos documentos e palavras foram lidas no primeiro programa, e informa qual o arquivo de saída binário
 * 
 * @param pal Indice de palavras
 * @param doc Indice de documentos
 * @param arq Endereço do arquivo de saída
 */
void FinalizaMain1(tPalavra_pt pal, tDocumento_pt doc, char* arq);




#endif