#include "../headers/documentos.h"


struct documento{
    char *nome;
    char *classe;
    tDados_pt dados_palavras;
    int qtdAlloc;
    int qtdDados; //qtd de palavras presentes no documento
    int qtd_documentos;
    int idx;
    double Valor;
    double simi;
};

tDocumento_pt AlocaERealocaIndiceDocumentos(tDocumento_pt doc, int controle){

    if( !controle ) {
        doc = (tDocumento_pt) calloc(QTD_ALLOC_INICIAL_DOC, sizeof( tDocumento ));
        doc->qtdAlloc = QTD_ALLOC_INICIAL_DOC;

    } else if( doc->qtd_documentos == doc->qtdAlloc) {
        doc->qtdAlloc *= 2;
        doc = (tDocumento_pt) realloc(doc, doc->qtdAlloc * sizeof( tDocumento ));
        memset( doc+controle, 0, (doc->qtdAlloc-controle) * sizeof( tDocumento ) );
    }

    return doc;
}

int RetornaQtdDeDocLidos(tDocumento_pt doc){
    return doc->qtd_documentos;
}

void AumentaQtdDeDocLidos(tDocumento_pt doc){
    doc->qtd_documentos++;
}

int RetornaQtdDadosDoDoc(tDocumento_pt doc, int i){
    return (doc+i)->qtdDados;
}

char* RetornaClasseDoDoc(tDocumento_pt doc, int i){
    return (doc+i)->classe;
}

char* RetornaNomeDoDoc(tDocumento_pt doc, int i){
    return (doc+i)->nome;
}

int RetornaIdxDoDoc(tDocumento_pt doc, int i){
    return (doc+i)->idx;
}

int LeEInicializaDocumento(FILE *arq, tDocumento_pt doc){

    int qtd = RetornaQtdDeDocLidos(doc);

    (doc+qtd)->nome = LeEAlocaString(arq, (doc+qtd)->nome);

    if( feof(arq) ){
        free((doc+qtd)->nome);
        return 1;
    }
    
    char *classe = NULL;
    classe = LeEAlocaString(arq, classe);
    int TamClasse = strlen(classe);

    (doc+qtd)->classe = calloc(TamClasse, sizeof( char ));
    strncpy((doc+qtd)->classe, classe, TamClasse);
    free(classe);

    (doc+qtd)->qtdDados = 0;
    (doc+qtd)->idx = qtd;
            
    return 0;
}

char* RetornaEnderecoDocumento(tDocumento_pt doc, int iD, char* caminho_inicial, char *endereco){
    int qtd_caracteres = 0;

    if( strstr(caminho_inicial,"test") != NULL){
        qtd_caracteres = strlen(caminho_inicial) - 8;
    } else {
        qtd_caracteres = strlen(caminho_inicial) - 9;
    }

    endereco = (char*) calloc( (qtd_caracteres + 1 + strlen((doc+iD)->nome)), sizeof(char) );

    strncpy(endereco, caminho_inicial, qtd_caracteres);

    strcat(endereco, (doc+iD)->nome);
    
    return endereco;
}

void AtualizaDadosNosIndices(tDocumento_pt doc, tPalavra_pt pal){

    int qtd_palavras = RetornaQtdDePalavrasLidas(pal), qtd_documentos = RetornaQtdDeDocLidos(doc);
    int iP = 0, iD = 0, iDado = 0, qtd_dados = 0, frequencia = 0, posicao = 0, tf = 0;
    double TF_IDF = 0;

    for( iP = 0; iP < qtd_palavras; iP++){
        qtd_dados = RetornaDadosDocumentos( pal, iP, iDado, 'q' ); //representa a quantidade de dados (documentos) de uma palavra

        for( iDado = 0; iDado < qtd_dados; iDado++){
            
            tf = RetornaDadosDocumentos( pal, iP, iDado, 'f' );
            TF_IDF = CalculaTF_IDF(pal, iP, tf, qtd_documentos);
            
            frequencia = 0;
            posicao = RetornaDadosDocumentos( pal, iP, iDado, 'p' );

            AtualizaDadosDocumentosEmPalavras(pal, iP, posicao, frequencia, TF_IDF);


            frequencia = RetornaDadosDocumentos( pal, iP, iDado, 'f' );
            iD = posicao;
            posicao = iP;
            doc = AtualizaDadosPalavrasEmDocumentos(doc, iD, posicao, frequencia, TF_IDF);
        }   
    }
}

tDocumento_pt AtualizaDadosPalavrasEmDocumentos(tDocumento_pt doc, int iD, int posicao, int frequencia, float TF_IDF){
    int iDado = 0;

    iDado = VerificaPosicaoJaDeclarada((doc+iD)->dados_palavras, (doc+iD)->qtdDados, posicao);


    if( iDado == -1 ){
        iDado = (doc+iD)->qtdDados;
        (doc+iD)->dados_palavras = AlocaERealocaDados((doc+iD)->dados_palavras, (doc+iD)->qtdDados);
        (doc+iD)->qtdDados++;
    }
   // printf("iDado = %d\n\n", (doc+iD)->qtdDados);


    (doc+iD)->dados_palavras = InicializaDados((doc+iD)->dados_palavras, iDado, posicao, frequencia, TF_IDF);

    return doc;
}

void SalvaIndiceDocumento(FILE *arq, tDocumento_pt doc, int qtd){
    int qtd_caracteres = 0;

    fwrite(&qtd, sizeof(int), 1, arq);

    for( int i = 0; i < qtd; i++){
        qtd_caracteres = strlen( (doc+i)->nome )+1;
        fwrite( &qtd_caracteres, sizeof(int), 1, arq);
        fwrite( (doc+i)->nome, sizeof(char), qtd_caracteres, arq);

        qtd_caracteres = strlen( (doc+i)->classe )+1;
        fwrite( &qtd_caracteres, sizeof(int), 1, arq);
        fwrite( (doc+i)->classe, sizeof(char), qtd_caracteres, arq);

        fwrite( &(doc+i)->qtdDados, sizeof(int), 1, arq );
        fwrite( &(doc+i)->idx, sizeof(int), 1, arq );
        SalvaIndiceDados( arq, (doc+i)->dados_palavras, (doc+i)->qtdDados );
    }
} 

void LiberaMemoriaDocumento(tDocumento_pt doc){

    for(int i = 0; i< doc->qtd_documentos; i++){
        free((doc+i)->nome);
        free((doc+i)->classe);
        free((doc+i)->dados_palavras);
    }

    free(doc);
    doc=NULL;
}

/* PROGRAMA 2 */


tDocumento_pt LeEArmazenaIndiceDocumento(FILE *arq, tDocumento_pt doc){
    int qtd_doc = 0, qtd_caracteres = 0;

    fread( &qtd_doc, sizeof(int), 1, arq );
    doc = (tDocumento_pt) calloc( qtd_doc, sizeof(tDocumento) );

    doc->qtd_documentos = qtd_doc;
    doc->qtdAlloc = qtd_doc;

    for( int i = 0; i < qtd_doc; i++){
        fread( &qtd_caracteres, sizeof(int), 1, arq);
        (doc+i)->nome = (char*) calloc( qtd_caracteres, sizeof(char) );
        fread( (doc+i)->nome, sizeof(char), qtd_caracteres, arq);

        fread( &qtd_caracteres, sizeof(int), 1, arq);
        (doc+i)->classe = (char*) calloc( qtd_caracteres, sizeof(char) );
        fread( (doc+i)->classe, sizeof(char), qtd_caracteres, arq);

        fread( &((doc+i)->qtdDados), sizeof(int), 1, arq );
        fread( &((doc+i)->idx), sizeof(int), 1, arq );
        (doc+i)->dados_palavras = LeEArmazenaIndiceDados( arq, (doc+i)->dados_palavras, (doc+i)->qtdDados );
    }
    printf("\nLeu Indice de Documentos\n");

    fclose(arq);
    return doc;
}

tDocumento_pt VerificaIndiceDocumento(tDocumento_pt doc, int iD){
    tDocumento_pt DocumentoProcurado = NULL;
    tDocumento DocumentoDesejado;

    DocumentoDesejado.idx = iD;
    
    DocumentoProcurado = bsearch(&DocumentoDesejado, doc, doc->qtd_documentos, sizeof( tDocumento ), ComparaIdx);

    return DocumentoProcurado;
}

int ComparaIdx(const void *v1, const void *v2){
    const struct documento *d1 = v1;
    const struct documento *d2 = v2;

    int d = d1->idx - d2->idx;
    return d;
}

void OrdenaDocsPorIdx(tDocumento_pt doc){

    int qtd = RetornaQtdDeDocLidos(doc), qtdAlloc = doc->qtdAlloc;

    qsort(doc, qtd, sizeof( tDocumento ), ComparaIdx);

    doc->qtd_documentos = qtd;
    doc->qtdAlloc = qtdAlloc;

}

void AtualizaValorDoc(tDocumento_pt indiceDoc, tIndices_pt docsAnalise, tPalavra_pt palPesq, tPalavra_pt indicePal){
    int qtdDoc = RetornaQtdIdx(docsAnalise), qtdPesq = RetornaQtdDePalavrasLidas(palPesq);
    int idxPal = 0, idxDoc = 0;

    for(int i = 0; i < qtdPesq; i++){
        idxPal = RetornaIdxDePalavra(palPesq, i);

        if( idxPal >= 0){
            for(int j = 0; j < qtdDoc; j++){
                idxDoc = RetornaIndiceIdx(docsAnalise, j);

                (indiceDoc+idxDoc)->Valor += ProcuraTFIDFEmDados((indiceDoc+idxDoc)->dados_palavras, (indiceDoc+idxDoc)->qtdDados, idxPal);
            }
        }
    }

}

void OrdenaValorTF_IDF(tDocumento_pt idDoc){
    int qtd = idDoc->qtd_documentos;

    qsort(idDoc, qtd, sizeof(tDocumento), ComparaValor);
    idDoc->qtd_documentos = qtd;

}

int ComparaValor(const void *v1, const void *v2){
    const struct documento *d1 = v1;
    const struct documento *d2 = v2;
    return (d1->Valor - d2->Valor)*(-10000);
}

void ImprimeBusca(tDocumento_pt indiceDoc, tIndices_pt docsAnalise){
    int qtd = RetornaQtdIdx(docsAnalise), i = 0, idx = 0;

    printf("\nRESULTADO DA BUSCA:\n");

    for( i = 0; i < qtd ; i++){
        if( i >= QTD_NOTICIAS) break;

        idx = RetornaIndiceIdx(docsAnalise, i);

        printf("[%d]%s -> %.4f\n", i, (indiceDoc+idx)->nome, (indiceDoc+idx)->Valor);
    }

    if( i < QTD_NOTICIAS ) printf("Só foi possível encontrar %d noticias.\n", i);
        
}


void CalculoSimilaridade(tIndices_pt docsAnalise, tDocumento_pt indiceDoc, tDocumento_pt consulta){
    int qtd_palPesq = RetornaQtdDadosDoDoc(consulta, 0), qtd_docsAnalise = RetornaQtdIdx(docsAnalise);
    int iD = 0, iDado = 0, idxPal = 0, idxDoc = 0;
    double fConsulta = 0, fAnalise = 0;
    double num = 0, den1 = 0, den2 = 0;

    /* calculo denominador1 (corresponde ao ponteiro "consulta") */ 
    den1 = CalculoNorma(consulta, iD);

    for( iD = 0; iD < qtd_docsAnalise; iD++ ){
        idxDoc = RetornaIndiceIdx(docsAnalise, iD);
        num = 0;

        /* calculo do numerador */  
        for( int iP = 0; iP < qtd_palPesq; iP++){
            idxPal = RetornaDados( consulta->dados_palavras, iP, 'p' );


            iDado = VerificaPosicaoJaDeclarada( (indiceDoc+idxDoc)->dados_palavras, (indiceDoc+idxDoc)->qtdDados, idxPal );

            if( iDado >= 0 ){
                fAnalise = RetornaTF_IDF( (indiceDoc+idxDoc)->dados_palavras, iDado );
                fConsulta = RetornaTF_IDF( consulta->dados_palavras, iP );

                num += fAnalise * fConsulta;
            }
        }

        /* calculo do denominador2 */ 
        den2 = CalculoNorma(indiceDoc, idxDoc);

        /* calculo cosseno (simi) */ 
        docsAnalise = AtualizaSimiIdx(docsAnalise, iD, num, den1, den2);
    }

    docsAnalise = OrdenaPorSimilaridade(docsAnalise);
}



float CalculoNorma(tDocumento_pt doc, int iD){
    float norma = 0, TF_IDF = 0;
    int qtd_dados = RetornaQtdDadosDoDoc(doc, iD);

    for( int i = 0; i < qtd_dados; i++){
        TF_IDF = RetornaTF_IDF( (doc+iD)->dados_palavras, i );
        norma += pow( TF_IDF, 2 );
    }

    norma = sqrt(norma);

    return norma;
}



int ComparaQtdDados(const void *v1, const void *v2){
    const struct documento *d1 = v1;
    const struct documento *d2 = v2;
    return ( d1->qtdDados - d2->qtdDados );
}


tDocumento_pt DuplicaIndiceDoc(tDocumento_pt doc, tDocumento_pt docCopy){
    int qtd = RetornaQtdDeDocLidos(doc);
    docCopy = malloc(qtd * sizeof(tDocumento));

    for(int i = 0; i < qtd; i++){
        memcpy((docCopy+i), (doc+i), sizeof(tDocumento));
    }
    
    qsort(docCopy, qtd, sizeof( tDocumento ), ComparaQtdDados);
    docCopy->qtd_documentos = qtd;

    return docCopy;
}

void ImprimeRelatorioDoc(tDocumento_pt doc){

    int qtd = RetornaQtdDeDocLidos(doc);

    printf("|============= 10 mais longos: =============|\n");
    for(int i = qtd - 1; i >= (qtd - QTD_RELATORIO); i--){
        printf("\nNome: %s | Classe: %s | Total de palavras: %d\n", (doc+i)->nome, (doc+i)->classe, (doc+i)->qtdDados);
    }

    printf("\n\n|============= 10 mais curtos: =============|\n");
    for(int i = 0; i < QTD_RELATORIO; i++){
        printf("\nNome: %s | Classe: %s | Total de palavras: %d\n", (doc+i)->nome, (doc+i)->classe, (doc+i)->qtdDados);
    }
}

void ImprimeDocsRelatorioPalavra(tDocumento_pt idDoc, int pos, int freq){
    printf("%s | %s | %d\n", (idDoc+pos)->nome, (idDoc+pos)->classe, freq);
}