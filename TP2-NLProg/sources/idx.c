#include "../headers/idx.h"

struct idx{
    int idx;
    double simi;
    int qtd;
    int qtdAlloc;
};

tIndices_pt AlocaERealocaIndices(tIndices_pt idx, int controle){

    if( !controle ){
        idx = (tIndices_pt) calloc( ALLOC_INICIAL_IDX, sizeof( tIndices ) );
        idx->qtdAlloc = ALLOC_INICIAL_IDX;

    } else if( idx->qtd == idx->qtdAlloc ){
        idx->qtdAlloc *= 2;
        idx = (tIndices_pt) realloc ( idx, idx->qtdAlloc * sizeof( tIndices ) );
        memset( (idx+controle), 0, (idx->qtdAlloc-controle) * sizeof( tIndices ) );
    }

    return idx;
}

tIndices_pt PreencheEAlocaIndicesDeDoc(tPalavra_pt pal){
    tIndices_pt indices = NULL;
    int controle = 0, qtdPalavras = RetornaQtdDePalavrasLidas(pal), qtdDados = 0, idxPal = -1, idxDoc = 0, verifica = 0, aux = 0;
    
    for(int i = 0; i < qtdPalavras; i++){
        qtdDados = RetornaQtdDados(pal, i);
        idxPal = RetornaIdxDePalavra(pal, i);

        if( idxPal >= 0 ){
            for(int j = 0; j < qtdDados; j++){
                idxDoc = RetornaDadosDocumento_Posicao(pal, i, j, 'p');

                verifica = (controle == 0) ? -1 : VerificaIdxIndice(indices, idxDoc);
                
                if( verifica < 0 ){

                    indices = AlocaERealocaIndices(indices, controle);

                    (indices+indices->qtd)->idx = idxDoc;
                    controle++;

                    indices->qtd++;

                    if( indices->qtd > 0 ){

                        aux = indices->qtd;
                        qsort(indices, indices->qtd, sizeof(tIndices), ComparaIndicesIdx);
                        indices->qtd = aux;

                    }
                }
            }
        }
    }
    
    return indices;
}

int VerificaIdxIndice(tIndices_pt indices, int idx){
    tIndices_pt Resultado = NULL;
    tIndices Procurado;

    Procurado.idx = idx;

    Resultado = bsearch(&Procurado, indices, indices->qtd, sizeof(tIndices), ComparaIndicesIdx);

    return (Resultado) ? Resultado->idx : -1 ;
}

int ComparaIndicesIdx(const void *v1, const void *v2){
    const struct idx *d1 = v1;
    const struct idx *d2 = v2;
    return d1->idx - d2->idx;
}

int RetornaQtdIdx(tIndices_pt indices){
    return indices->qtd;
}

int RetornaIndiceIdx(tIndices_pt indices, int i){
    return (indices+i)->idx;
}

tIndices_pt AtualizaSimiIdx(tIndices_pt indices, int i, double num, double den1, double den2){
    (indices+i)->simi = num / (den1 * den2);

    return indices;
}

tIndices_pt OrdenaPorSimilaridade(tIndices_pt indices){
    int qtd = indices->qtd;
    qsort( indices, indices->qtd, sizeof( tIndices ), ComparaSimilaridade);

    indices->qtd = qtd;

    return indices;
}

int ComparaSimilaridade(const void *v1, const void *v2){
    const struct idx *d1 = v1;
    const struct idx *d2 = v2;
    return (d1->simi - d2->simi)*(-10000);
}

void LiberaMemoriaIdx(tIndices_pt indices){
    free( indices );
}

void ImprimeIndices(tIndices_pt indices){
    FILE *arq = fopen("zIndicesDoc.txt", "w");
    fprintf(arq, "Total de Indices no vetor: %d\n\n", indices->qtd);
    for(int i = 0; i < indices->qtd; i++){
        fprintf(arq, "Indice: %d - %.4lf\n", (indices+i)->idx, (indices+i)->simi);
    }
    fclose(arq);
}