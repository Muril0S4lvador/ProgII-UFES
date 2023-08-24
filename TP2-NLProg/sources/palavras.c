#include "../headers/palavras.h"

struct palavra{
    char *nome;
    tDados_pt dados_documentos;
    int qtdAlloc; 
    int qtdDados; //qtd de documentos em que a palavra aparece
    int qtd_palavras;
    int qtd_pesquisa;
    int idx;
};


char* LeEAlocaString(FILE *arq, char *str){
    char c[2] = "\0\0";
    int qtd_caracteres = 0, qtd_caracteresAlloc = 0;

    while(1){
    
        if( qtd_caracteres == 0 ){
            str = (char*) calloc(QTD_ALLOC_INICIAL_CAR, sizeof( char ));
            qtd_caracteresAlloc = QTD_ALLOC_INICIAL_CAR;

        } else if( qtd_caracteres == qtd_caracteresAlloc - 1) {
            qtd_caracteresAlloc *= 2;
            str = (char*) realloc(str, qtd_caracteresAlloc * sizeof( char ));
        }

        c[0] = (char) fgetc(arq);

        if( feof(arq) || c[0] == '\n' || c[0] == ' '){ 
            break;
        }

        strcpy( &str[qtd_caracteres], c );
        qtd_caracteres++;
    }
 
    return str;
}


tPalavra_pt InicializaPalavra(tPalavra_pt pal, int controle, char *str){
    
    pal = AlocaERealocaPalavras(pal, controle);

    (pal + pal->qtd_palavras)->nome = calloc(strlen(str) + 1, sizeof(char));
    strcpy((pal + pal->qtd_palavras)->nome, str);

    (pal + pal->qtd_palavras)->qtdDados = 0;
    (pal + pal->qtd_palavras)->idx = pal->qtd_palavras;
        
    return pal;
}

tPalavra_pt AlocaERealocaPalavras(tPalavra_pt pal, int controle){

    if(!controle){
        pal = (tPalavra_pt) calloc(QTD_ALLOC_INICIAL_PAL, sizeof( tPalavra ));
        pal->qtdAlloc = QTD_ALLOC_INICIAL_PAL;

    } else if( pal->qtd_palavras == pal->qtdAlloc ){
        pal->qtdAlloc *= 2;
        pal = (tPalavra_pt) realloc (pal, pal->qtdAlloc * sizeof( tPalavra ));
        memset( pal+controle, 0, (pal->qtdAlloc-controle) * sizeof( tPalavra ) );
    }

    return pal;
}

int VerificaIndicePalavra(tPalavra_pt pal, char *str){
    tPalavra_pt PalavraProcurada = NULL;
    tPalavra PalavraDesejada;

    PalavraDesejada.nome = str;
    
    PalavraProcurada = bsearch(&PalavraDesejada, pal, pal->qtd_palavras, sizeof( tPalavra ), ComparaNomes);

    return ( PalavraProcurada != NULL ) ? PalavraProcurada->idx : -1 ;
}

void AtualizaQtdPalavrasLidas(tPalavra_pt palavras){
    palavras->qtd_palavras++;
}

int RetornaQtdDePalavrasLidas(tPalavra_pt palavra){
    return palavra->qtd_palavras;
}

void AtualizaDadosDocumentosEmPalavras(tPalavra_pt pal, int iP, int posicao, int frequencia, float TF_IDF){
    int iDado = 0;

    iDado = VerificaPosicaoJaDeclarada((pal+iP)->dados_documentos, (pal+iP)->qtdDados, posicao);

    if( iDado == -1 ){
        iDado = (pal+iP)->qtdDados;
        (pal+iP)->dados_documentos = AlocaERealocaDados((pal+iP)->dados_documentos, (pal+iP)->qtdDados);
        (pal+iP)->qtdDados++;
    }

    (pal+iP)->dados_documentos = InicializaDados((pal+iP)->dados_documentos, iDado, posicao, frequencia, TF_IDF);
}

void OrdenaOrdemAlfabetica(tPalavra_pt pal){

    int qtd = RetornaQtdDePalavrasLidas(pal), qtdAlloc = pal->qtdAlloc;

    qsort(pal, qtd, sizeof( tPalavra ), ComparaNomes);

    pal->qtd_palavras = qtd;
    pal->qtdAlloc = qtdAlloc;

    for(int i = 0; i < qtd; i++){
        (pal+i)->idx = i;
    }

}

int ComparaNomes(const void *pal1, const void *pal2){
    const struct palavra *p1 = pal1;
    const struct palavra *p2 = pal2;
    
    return strcmp(p1->nome, p2->nome);
}

/* FUNCOES DE RETORNO */

fptrRetorna operacoes_retorno[128] = {NULL};

void InicializaOperacoesRetorno() {
    operacoes_retorno['q'] = RetornaDadosDocumentos_Qtd; 
    operacoes_retorno['p'] = RetornaDadosDocumento_Posicao; 
    operacoes_retorno['f'] = RetornaDadosDocumento_Frequencia;
}

int RetornaDadosDocumentos(tPalavra_pt pal, int iP, int iDado, char opcao) {
    fptrRetorna operacao;

    operacao = operacoes_retorno[(int)opcao];
    return operacao(pal, iP, iDado, opcao);
}


int RetornaPalIdx(tPalavra_pt pal, int iP, int iDado, char opcao){
    return (pal+iP)->idx;
}

int RetornaDadosDocumentos_Qtd(tPalavra_pt pal, int iP, int iDado, char opcao){
    return (pal+iP)->qtdDados;
}

int RetornaDadosDocumento_Posicao(tPalavra_pt pal, int iP, int iDado, char opcao){
    return RetornaDados( (pal+iP)->dados_documentos, iDado, opcao );
}

int RetornaDadosDocumento_Frequencia(tPalavra_pt pal, int iP, int iDado, char opcao){
    return RetornaDados( (pal+iP)->dados_documentos, iDado, opcao );
}

double CalculaTF_IDF(tPalavra_pt pal, int iP, int tf, int qtd_documentos){
    
    /* fator de ponderacao */  
    int df = RetornaQtdDados(pal, iP);

    double idf = log( (double) (1 + qtd_documentos)/(1 + df) ) + 1;

    /* calculo do TF-IDF */  
    double TF_IDF = tf * idf;


    return TF_IDF;
}

void SalvaIndicePalavra(FILE *arq, tPalavra_pt pal, int qtd){
    int qtd_caracteres = 0;

    fwrite(&qtd, sizeof(int), 1, arq);

    for( int i = 0; i < qtd; i++){
        qtd_caracteres = strlen( (pal+i)->nome ) + 1;

        fwrite( &qtd_caracteres, sizeof(int), 1, arq);
        fwrite( (pal+i)->nome, sizeof(char), qtd_caracteres, arq);
        fwrite( &(pal+i)->idx, sizeof(int), 1, arq );

        fwrite( &(pal+i)->qtdDados, sizeof(int), 1, arq );
        SalvaIndiceDados( arq, (pal+i)->dados_documentos, (pal+i)->qtdDados );
    }
    printf("\n");
    
}

void LiberaMemoriaPalavra(tPalavra_pt pal){

    for(int i = 0; i < pal->qtd_palavras; i++){
        free((pal+i)->nome);
        free((pal+i)->dados_documentos);
    }

    free(pal);
    pal = NULL;
}

/* PROGRAMA 2 */

tPalavra_pt LeEArmazenaIndicePalavra(FILE *arq, tPalavra_pt pal){
    int qtd_pal = 0, qtd_caracteres = 0;

    fread( &qtd_pal, sizeof(int), 1, arq );

    pal = (tPalavra_pt) calloc( qtd_pal, sizeof(tPalavra) );

    pal->qtd_palavras = qtd_pal;
    pal->qtdAlloc = qtd_pal;

    for( int i = 0; i < qtd_pal; i++){
        fread( &qtd_caracteres, sizeof(int), 1, arq);
        (pal+i)->nome = (char*) calloc( qtd_caracteres, sizeof(char) );
        fread( (pal+i)->nome, sizeof(char), qtd_caracteres, arq);
        fread( &(pal+i)->idx, sizeof(int), 1, arq );


        fread( &((pal+i)->qtdDados), sizeof(int), 1, arq );
        (pal+i)->dados_documentos = LeEArmazenaIndiceDados( arq, (pal+i)->dados_documentos, (pal+i)->qtdDados );

    }
    printf("\nLeu Indice de Palavras\n");

    return pal;
}

char* LePesquisaUsuario(){
    int tam = 5000;
    char pesquisa[tam], *search = NULL;

    scanf("%*c");
    fgets(pesquisa, tam, stdin);

    search = calloc(strlen(pesquisa)+1, sizeof(char));

    strcpy(search, pesquisa);

    return search;
}

tPalavra_pt SeparaPalavrasPesquisa(tPalavra_pt palaPesq, char* pesquisa){

    char *token = NULL;
    int tam = strlen(pesquisa), controle = 0, i = -1, novaPal = 0;

    if( pesquisa[tam-1] == '\n') pesquisa[tam-1] = 0;

    token = strtok(pesquisa, " ");

    while( token ){

        novaPal = 0;

        if ( controle ) i = VerificaIndicePalavra(palaPesq, token);

        if( i < 0 ){
            palaPesq = InicializaPalavra(palaPesq, controle, token);
            AtualizaQtdPalavrasLidas(palaPesq);

            novaPal = 1;
            (palaPesq+controle)->qtd_pesquisa++;
            controle++;

        } else {
            (palaPesq+i)->qtd_pesquisa++;
        }

        if( controle && novaPal ) OrdenaOrdemAlfabetica(palaPesq);

        token = strtok(NULL, " ");
    }
    free(pesquisa);

    return palaPesq;
}

void AtualizaDadosPalavrasPesquisadas(tPalavra_pt palPesq, tPalavra_pt idPal){
    tPalavra_pt Resultado = NULL;
    int qtd = RetornaQtdDePalavrasLidas(palPesq), qtd_pesquisa = 0;

    for(int i = 0; i < qtd; i++){
        Resultado = bsearch( &(palPesq+i)->nome, idPal, idPal->qtd_palavras, sizeof(tPalavra), ComparaNomes );

        if( Resultado ){

            free( (palPesq+i)->nome );
            qtd_pesquisa = (palPesq+i)->qtd_pesquisa;

            memcpy((palPesq+i), Resultado, sizeof( tPalavra ));

            (palPesq+i)->qtd_pesquisa = qtd_pesquisa;             

        } else {
            (palPesq+i)->idx = -1;

        }
    }
    
    palPesq->qtd_palavras = qtd;
}

int RetornaIdxDePalavra(tPalavra_pt palavra, int indice){
    return (palavra+indice)->idx;
}

int RetornaQtdPesquisa(tPalavra_pt palavra, int indice){
    return (palavra+indice)->qtd_pesquisa;
}

int RetornaQtdDados(tPalavra_pt pal, int iP){
    return (pal+iP)->qtdDados;
}

tPalavra_pt AchaPalavraPesquisada(tPalavra_pt palPesq, tPalavra_pt idPal, char *str){
    tPalavra_pt Resultado = NULL;
    tPalavra Procurado;

    palPesq = malloc(sizeof(tPalavra));

    Procurado.nome = str;

    Resultado = bsearch(&Procurado, idPal, idPal->qtd_palavras, sizeof(tPalavra), ComparaNomes);

    if(Resultado){
        memcpy(palPesq, Resultado, sizeof(tPalavra));
        palPesq->qtd_palavras = 1;
        return palPesq;
    } 
    
    free(palPesq);
    return NULL;
}

void OrganizaDados(tPalavra_pt pal){
    OrdenaFrequencia(pal->dados_documentos, pal->qtdDados);
}

void ImprimeInicioRelatorioPalavras(tPalavra_pt pal){
    printf("A palavra '%s' aparece no total em %d documentos\n", pal->nome, pal->qtdDados);
}

void LiberaMemoriaPalPesq(tPalavra_pt palPesq){
    int qtd = palPesq->qtd_palavras;

    for(int i = 0; i < qtd; i++){
        if( (palPesq+i)->idx < 0 ){
            free((palPesq+i)->nome);
        }
    }
    free(palPesq);
}