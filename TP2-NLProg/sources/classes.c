#include "../headers/classes.h"

struct classe{
    char *nome;
    int frequencia;
    int idx;
    int qtd_classes;
    int qtdAlloc;
};


tClasse_pt AlocaERealocaClasses(tClasse_pt classe, int controle){

    if( !controle ){
        classe = (tClasse_pt) calloc( QTD_ALLOC_INICIAL_CLASSE, sizeof( tClasse ) );
        classe->qtdAlloc = QTD_ALLOC_INICIAL_CLASSE;

    } else if( classe->qtd_classes == classe->qtdAlloc ) {
        classe->qtdAlloc *= 2;
        classe = (tClasse_pt) realloc ( classe, classe->qtdAlloc * sizeof( tClasse ) );
        memset( (classe+controle), 0, (classe->qtdAlloc-controle) * sizeof( tClasse ) );
    }

    return classe;
}

int VerificaIndiceClasse(tClasse_pt classes, char *str){
    tClasse_pt ClasseProcurada = NULL;
    tClasse ClasseDesejada;

    ClasseDesejada.nome = str;
    
    ClasseProcurada = bsearch(&ClasseDesejada, classes, classes->qtd_classes, sizeof( tClasse ), ComparaClasses);

    return ( ClasseProcurada != NULL ) ? ClasseProcurada->idx : -1 ;
}

void OrdenaOrdemAlfabeticaClasses(tClasse_pt classes){

    int qtd = RetornaQtdClasses(classes), qtdAlloc = classes->qtdAlloc;

    qsort(classes, qtd, sizeof( tClasse ), ComparaClasses);

    classes->qtd_classes = qtd;
    classes->qtdAlloc = qtdAlloc;

    for(int i = 0; i < qtd; i++){
        (classes+i)->idx = i;
    }
}

int ComparaClasses(const void *cl1, const void *cl2){
   
    const struct classe *c1 = cl1;
    const struct classe *c2 = cl2;
    return strcmp(c1->nome, c2->nome);
}

tClasse_pt AtualizaClasses(tClasse_pt classes, char *str, int fre){
    int novaClasse = 0;
    int controle = ( classes == NULL ) ? 0 : classes->qtd_classes;

    int iC = ( !controle ) ? -1 : VerificaIndiceClasse(classes, str);

    if( iC < 0 ){
        classes = InicializaClasse(classes, str, controle);

        iC = controle;
        novaClasse = 1;
    }
    
    AumentaFrequenciaClasse(classes, iC, fre);

    if( iC > 0 && novaClasse ) OrdenaOrdemAlfabeticaClasses(classes);

    return classes;
}

tClasse_pt InicializaClasse(tClasse_pt classes, char *str, int controle){

    classes = AlocaERealocaClasses(classes, controle);

    int i = RetornaQtdClasses(classes);

    (classes+i)->nome = calloc( strlen(str) + 1, sizeof(char) );
    strcpy( (classes+i)->nome, str );

    (classes+i)->idx = controle;

    AumentaQtdClasses(classes);

    return classes;
}

void BuscaEImprimeClasseComum(tIndices_pt docsAnalise, tDocumento_pt indiceDoc, int K){
    tClasse_pt classes = NULL;
    int iMax = 0, max = 0, frequencia = 0, idxDoc = -1;
    int qtd_docs = RetornaQtdIdx(docsAnalise);

    char *classeDoc = NULL;

    for( int iD = 0; iD < K; iD++){
        if( iD == qtd_docs ) break;

        idxDoc = RetornaIndiceIdx(docsAnalise, iD);

        classeDoc = RetornaClasseDoDoc(indiceDoc, idxDoc);
        frequencia = 1;

        classes = AtualizaClasses(classes, classeDoc, frequencia);
    }

    int qtd_classes = RetornaQtdClasses(classes);

    for( int iC = 0; iC < qtd_classes; iC++ ){
        frequencia = RetornaFrequenciaClasse(classes, iC);

        if( max < frequencia ){
            max = frequencia;
            iMax = iC;
        }
    }

    printf("\nAs palavras pesquisadas pertencem a clase '%s'!\n", RetornaNomeClasse(classes, iMax));

    LiberaMemoriaClasse(classes);
}

void LiberaMemoriaClasse(tClasse_pt classe){
    int qtd = classe->qtd_classes;

    for(int i = 0; i < qtd; i++){
        free((classe+i)->nome);
    }
    free(classe);
    classe = NULL;
}

int RetornaQtdClasses(tClasse_pt classes){
    return classes->qtd_classes;
}

void AumentaQtdClasses(tClasse_pt classes){
    classes->qtd_classes++;
}

void AumentaFrequenciaClasse(tClasse_pt classes, int i, int fre){
    (classes+i)->frequencia += fre;
}

int RetornaFrequenciaClasse(tClasse_pt classes, int i){
    return (classes+i)->frequencia;
}

char* RetornaNomeClasse(tClasse_pt classes, int i){
    return (classes+i)->nome;
}

tClasse_pt PreencheVetorClasse(tPalavra_pt palPesq, tDocumento_pt idDoc){
    int qtdDados = RetornaDadosDocumentos_Qtd(palPesq, 0, 0, 'q'), idx = 0, fre = 0;
    char *str = NULL;
    tClasse_pt classes = NULL;

    for(int i = 0; i < qtdDados; i++){
        idx =  RetornaDadosDocumento_Posicao(palPesq, 0, i, 'p');
        fre = RetornaDadosDocumento_Frequencia(palPesq, 0, i, 'f');
        str = RetornaClasseDoDoc(idDoc, idx);

        classes = AtualizaClasses(classes, str, fre);
    }
    int qtd = classes->qtd_classes;
    qsort(classes, classes->qtd_classes, sizeof(tClasse), ComparaFreClasse);
    classes->qtd_classes = qtd;

    return classes;
}

int ComparaFreClasse(const void *v1, const void *v2){
    const struct classe *d1 = v1;
    const struct classe *d2 = v2;
    return d2->frequencia - d1->frequencia;
}

void ImprimeRelatorioPal(tPalavra_pt pal, tClasse_pt classes, tDocumento_pt idDoc){
    int qtd = RetornaDadosDocumentos_Qtd(pal, 0, 0, 'q'), pos = -1, freq = -1, i = 0;

    printf("|============= Relatorio de Palavras: =============|\n");

    ImprimeInicioRelatorioPalavras(pal);

    printf("\n|============= Frequencia por Documento: =============|");

    printf("\nNome do Arquivo | Classe | Frequencia\n");

    for( i = 0; i < qtd; i++){

        if( i >= QTD_RELATORIO ) break;

        pos = RetornaDadosDocumento_Posicao(pal, 0, i, 'p');
        freq = RetornaDadosDocumento_Frequencia(pal, 0, i, 'f');
        ImprimeDocsRelatorioPalavra(idDoc, pos, freq);

    }

    if( i < QTD_NOTICIAS ) printf("\nSó foi possível encontrar %d noticias.\n", i);

    ImprimeClasses(classes);
}

void ImprimeClasses(tClasse_pt classe){
    int qtd = classe->qtd_classes;

    printf("\n|============= Frequencia por Classe: =============|\n");

    for(int i = 0; i < qtd; i++){
        printf("Classe: %s | Frequencia: %d\n", (classe+i)->nome, (classe+i)->frequencia);
    }
}