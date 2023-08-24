#include "headers/arquivos.h"

int main( int argc, char *argv[] ){

    char *caminho_inicial = NULL, *caminho_arqSaida = NULL;
    tPalavra_pt palavras = NULL;
    tDocumento_pt documentos = NULL;

    ConfereArgumentos(argc, 1);

    if( RetornaCaminhoInicial(argv) ){
        caminho_inicial = argv[1];
        caminho_arqSaida = argv[2];
    } else {
        caminho_inicial = argv[2];
        caminho_arqSaida = argv[1];
    }

    FILE *arq = AbreArquivoTexto(caminho_inicial, 'r');

    documentos = LeArquivoInicial(arq, documentos);

    palavras = LeTodosOsArquivos(documentos, caminho_inicial, palavras);

    InicializaOperacoesRetorno();

    AtualizaDadosNosIndices( documentos, palavras );

    SalvaIndices(caminho_arqSaida, palavras, documentos);

    FinalizaMain1(palavras, documentos, caminho_arqSaida);

    return 0;
}