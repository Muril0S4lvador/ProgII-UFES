#include "../headers/dados.h"

struct dados{
    int posicao;
    int frequencia;
    double TF_IDF;
    int qtdAlloc;
};

tDados_pt AlocaERealocaDados(tDados_pt dados, int qtd){

    if(qtd == 0){
        dados = (tDados_pt) calloc(QTD_ALLOC_INICIAL_DADOS, sizeof( tDados ));
        dados->qtdAlloc = QTD_ALLOC_INICIAL_DADOS;

    } else if( qtd == dados->qtdAlloc ){
        dados->qtdAlloc *= 2;
        dados = (tDados_pt) realloc (dados, dados->qtdAlloc * sizeof( tDados ));
        memset( dados+qtd, 0, (dados->qtdAlloc-qtd) * sizeof( tDados ) );
    }

    return dados;
}

tDados_pt InicializaDados(tDados_pt dados, int iDado, int posicao, int frequencia, float TF_IDF){
    
    (dados+iDado)->posicao = posicao;
    (dados+iDado)->frequencia += frequencia;
    (dados+iDado)->TF_IDF = TF_IDF;

    return dados;
}

int VerificaPosicaoJaDeclarada(tDados_pt dados, int qtd, int idx){

    for( int i = 0; i < qtd; i++){
        if( (dados+i)->posicao == idx )
            return i;
    }

    return -1;
}

void ImprimeDados(tDados_pt dados, int qtd){

    for( int i = 0; i < qtd; i++){
        printf("|%d - %d - %.2f| ", (dados+i)->posicao, (dados+i)->frequencia, (dados+i)->TF_IDF);
    }
}

int RetornaDados(tDados_pt dados, int iDado, char opcao){

    if( opcao == 'p')
        return (dados+iDado)->posicao;

    if( opcao == 'f')
        return (dados+iDado)->frequencia;
    
    return 0;
}

double RetornaTF_IDF(tDados_pt dados, int iDado){
    return (dados+iDado)->TF_IDF;
}

void SalvaIndiceDados(FILE *arq, tDados_pt dados, int qtd){

    for( int i = 0; i < qtd; i++){
        fwrite( &((dados+i)->posicao), sizeof(int), 1, arq);
        fwrite( &((dados+i)->frequencia), sizeof(int), 1, arq);
        fwrite( &((dados+i)->TF_IDF), sizeof(double), 1, arq);
    }
}

tDados_pt LeEArmazenaIndiceDados(FILE *arq, tDados_pt dados, int qtd){

    dados = (tDados_pt) calloc( qtd, sizeof(tDados) );
    dados->qtdAlloc = qtd;

    for( int i = 0; i < qtd; i++){
        fread( &((dados+i)->posicao), sizeof(int), 1, arq);
        fread( &((dados+i)->frequencia), sizeof(int), 1, arq);
        fread( &((dados+i)->TF_IDF), sizeof(double), 1, arq);
    }

    return dados;
}

int ComparaPos(const void *v1, const void *v2){
    const struct dados *d1 = v1;
    const struct dados *d2 = v2;
    int d = d1->posicao - d2->posicao;
    return d;
}

tDados_pt CriaDadoProcurado(tDados_pt dado, int pos){
    dado = calloc( 1, sizeof(tDados_pt) );

    dado->posicao = pos;
    return dado;
}


float ProcuraTFIDFEmDados(tDados_pt dados, int tam, int id){
    tDados_pt dadoAchado = NULL;
    tDados dadoProcurado;

    dadoProcurado.posicao = id;

    dadoAchado = bsearch(&dadoProcurado, dados, tam, sizeof( tDados ), ComparaPos);

    return ( dadoAchado ) ? dadoAchado->TF_IDF : 0;
}

tDados_pt CopiaDados(tDados_pt dados_docs, tDados_pt resultado){
    memcpy(dados_docs, resultado, sizeof( tDados ));
    return dados_docs;
}

int ComparaFre(const void *v1, const void *v2){
    const struct dados *d1 = v1;
    const struct dados *d2 = v2;
    int d = d2->frequencia - d1->frequencia;
    return d;
}

void OrdenaFrequencia(tDados_pt dados, int size){
    qsort(dados, size, sizeof(tDados), ComparaFre);
}

void ImprimeDadosArq(tDados_pt dados, int qtd, FILE *arq){

    for( int i = 0; i < qtd; i++){
        fprintf(arq, "|%d - %d - %.2lf| ", (dados+i)->posicao, (dados+i)->frequencia, (dados+i)->TF_IDF);
    }
    fprintf(arq, "\n\n");
}