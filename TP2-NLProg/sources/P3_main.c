#include "headers/menu.h"

int main( int argc, char *argv[] ){
    char *caminho_noticias = NULL, *caminho_arqSaida = NULL, *caminho_arqBinario = NULL;
    int K = 0;

    ConfereArgumentos(argc, 3);

    caminho_arqBinario = argv[ RetornaCaminhoArqBinario(argv) ];
    printf("Arq binario: %s\n", caminho_arqBinario);

    caminho_noticias = argv[ RetornaCaminhoTesteTXT(argv) ];
    printf("Caminho not: %s\n", caminho_noticias);

    caminho_arqSaida = argv[ EncontraArqSaidaProg3(argc, argv) ];
    printf("Caminho out: %s\n", caminho_noticias);

    K = EncontraKEmArgumentos(argc, argv);
    printf("K = %d\n", K);

    exit(0);



    /*
        # ARGUMENTOS DO PROGRAMA #
        o programa deve receber arq binario de prog1
        entrada de um teste.txt
        k usado no prog2
        nome para um arquivo de saida
    */

    /*
        # O QUE ELE VAI FAZER #
        pela tecnica de classificação de noticias(usado no prog2), classificar todas as noticias do conjunto de teste.txt
        salvar em um arquivo .txt via linha de comando a acurácia do metodo e a matriz de confusão

    */

   /*
        # MATRIZ DE CONFUSAO #
        na matriz, as linhas representam a classe verdadeira das noticias, e as colunas a classe estimada pelo sistema

        ** OU SEJA, é uma matriz quadrada cuja largura e altura sao iguais ao numero de classes **

        a celula(i, j) da matriz contém o NÚMERO de noticias que são da classe i(arquivo), mas foram classificados pela como classe j(sistema)

        Além da matriz de confusao e de acuracia, dve ser salvo uma sequencia de linhas indicando a qual classe as linhas/colunas da matriz se referem

        o classificador tende a atribuir a classe ECO a maioria das noticias

        (VER IMAGEM NA ESPECIFICAÇÃO)
   */

}