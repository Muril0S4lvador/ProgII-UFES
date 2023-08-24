#include "headers/menu.h"


int main( int argc, char *argv[] ){
    tDocumento_pt indiceDoc = NULL;
    tPalavra_pt indicePal = NULL;
    char *caminho_arqBinario = NULL;
    char opcao = '\0';
    int K = 0;

    ConfereArgumentos(argc, 2);

    if( RetornaCaminhoArqBinario(argv) ){
        caminho_arqBinario = argv[1];
        K = atoi( argv[2] );
    } else {
        caminho_arqBinario = argv[2];
        K = atoi( argv[1] );
    }

    FILE *arq = AbreArquivoBinario(caminho_arqBinario, 'r');

    indicePal = LeEArmazenaIndicePalavra(arq, indicePal);
    indiceDoc = LeEArmazenaIndiceDocumento(arq, indiceDoc);

    InicializaFuncoesMenu();

    BemVindo();

    while( 1 ){
        ImprimeMenu();
        scanf("\n%c", &opcao);

        if( opcao >= '0' && opcao <= '4' ) 
            PesquisaFuncaoMenu(opcao, indicePal, indiceDoc, K);
        
        else printf("Opcao invalida!\n");
    }
 
    return 0;
}