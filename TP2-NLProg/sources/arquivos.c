#include "../headers/arquivos.h"

void ConfereArgumentos(int argc, int num_programa){
    if( argc <= 2 ){

        switch ( num_programa )
        {
        case 1:
            printf("ERRO\nAdicione o caminho para o arquivo de entrada e o nome do programa de saida como argumentos!\n");
            exit(1);

        case 2:
            printf("ERRO\nAdicione o caminho para o arquivo de entrada e um numero inteiro como argumentos!\n");
            exit(1);

        }
    }
}

int RetornaCaminhoInicial(char *argv[]){

    if( strstr(argv[1],"txt") != NULL){
        return 1;
    } else {
        return 0;
    }

}

void ConfereAberturaAquivo(char *caminho, FILE *arq){
    if( !arq ){
        printf("\nErro no arquivo %s\n", caminho);
        exit(1);
    }

    printf("\nArquivo %s aberto!\n", caminho);
}

FILE* AbreArquivoTexto(char *caminho, char opcao){
    FILE *arq = NULL;

    switch( opcao ){
        case 'r':
            arq = fopen(caminho, "r");
            break;
        
        case 'w':
            arq = fopen(caminho, "w");
            break;
    }

    ConfereAberturaAquivo(caminho, arq);

    return arq;    
}

FILE* AbreArquivoBinario(char *caminho, char opcao){
    FILE *arq = NULL;

    switch( opcao ){
        case 'r':
            arq = fopen(caminho, "rb");
            break;
        
        case 'w':
            arq = fopen(caminho, "wb");
            break;
    }
    
    ConfereAberturaAquivo(caminho, arq);
    
    return arq;    
}

tDocumento_pt LeArquivoInicial(FILE *arq, tDocumento_pt documentos){
    int controle = 0;

    while( !feof(arq) ){

        documentos = AlocaERealocaIndiceDocumentos(documentos, controle);

        if( !LeEInicializaDocumento(arq, documentos) ) 
            AumentaQtdDeDocLidos(documentos);
        
        controle++;
    }
    fclose(arq);

    return documentos;
}

tPalavra_pt LeTodosOsArquivos(tDocumento_pt doc, char *caminho, tPalavra_pt palavras){

    int qtd = RetornaQtdDeDocLidos(doc), iP = 0, frequencia = 0, posicao = 0, controle = 0, novapal = 0;
    float TF_IDF = 0;
    char *endereco = "\0", *palavra = "\0";
    FILE *arq_noticia = NULL;

    for( int iD = 0; iD < qtd; iD++ ){

        endereco = RetornaEnderecoDocumento(doc, iD, caminho, endereco);

        arq_noticia = AbreArquivoTexto(endereco, 'r');

        free(endereco);
        
        while ( !feof(arq_noticia) ){

            novapal = 0;

            palavra = LeEAlocaString(arq_noticia, palavra);

            iP = ( !controle ) ? -1 : VerificaIndicePalavra(palavras, palavra);

            if( iP < 0 ){
                palavras = InicializaPalavra(palavras, controle, palavra);
                controle++;

                iP = RetornaQtdDePalavrasLidas(palavras);
                AtualizaQtdPalavrasLidas(palavras);
                novapal = 1;

            }

            free(palavra);
            palavra = NULL;

            frequencia = 1;
            posicao = iD;
            AtualizaDadosDocumentosEmPalavras(palavras, iP, posicao, frequencia, TF_IDF);

            if( controle > 1 && novapal ) OrdenaOrdemAlfabetica(palavras);
        }

        printf("Leu todo o documento!\n");
        fclose(arq_noticia); 
    }

    return palavras;
}

void SalvaIndices(char *caminho_arq, tPalavra_pt pal, tDocumento_pt doc){
    FILE *arq_saida = AbreArquivoBinario(caminho_arq, 'w');

    int qtd_pal = RetornaQtdDePalavrasLidas(pal),
        qtd_doc = RetornaQtdDeDocLidos(doc);

    SalvaIndicePalavra(arq_saida, pal, qtd_pal);
    SalvaIndiceDocumento(arq_saida, doc, qtd_doc);

    printf("Os indices foram salvos no arquivo %s!\n", caminho_arq);

    fclose(arq_saida);
}

void FinalizaMain1(tPalavra_pt pal, tDocumento_pt doc, char* arq){
    
    printf("\n- Ao todo foram lidos %d documento(s) e %d palavra(s) diferentes.\n", 
    RetornaQtdDeDocLidos(doc), RetornaQtdDePalavrasLidas(pal));
    printf("- Nome arquivo de saida: %s\n", arq);

    LiberaMemoriaDocumento(doc);
    LiberaMemoriaPalavra(pal);
}

/* PROGRAMA 2 */

int RetornaCaminhoArqBinario(char *argv[]){

    if( strstr(argv[1],"bin") != NULL){
        return 1;
    } else {
        return 0;
    }

}