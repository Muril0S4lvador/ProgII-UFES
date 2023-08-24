#include "../headers/menu.h"

void BemVindo(){
    printf("\n---------------\n Bem-vindo! :) \n---------------\n\n");

}

void ImprimeMenu(void){
    printf("\n\nDigite o que deseja:\n\n");
    printf("0 - Sair\n1 - Buscar noticias\n2 - Classificar noticias\n3 - Relatorio de palavras\n4 - Relatorio de documentos\n");
}

/* DISPATCH TABLE */

fptrMenu funcoes_menu[5] = {NULL};

void InicializaFuncoesMenu() {
    funcoes_menu['0'] = FinalizaPrograma2; 
    funcoes_menu['1'] = Funcionalidade1; 
    funcoes_menu['2'] = Funcionalidade2;
    funcoes_menu['3'] = RelatorioPalavra;
    funcoes_menu['4'] = RelatorioDocumentos;

}

void PesquisaFuncaoMenu(char opcao, tPalavra_pt indicePal, tDocumento_pt indiceDoc, int K) {
    fptrMenu funcao;

    funcao = funcoes_menu[(int)opcao];
    return funcao(indicePal, indiceDoc, K);
}

/* FUNCIONALIDADES */

void FinalizaPrograma2(tPalavra_pt indicePal, tDocumento_pt indiceDoc, int K){
    LiberaMemoriaPalavra(indicePal);
    LiberaMemoriaDocumento(indiceDoc);
    exit(0);
}

tPalavra_pt ArmazenaPalavrasPesquisa(tPalavra_pt indicePal, tPalavra_pt palPesq){
    char *pesquisa = NULL;

    printf("O que busca?\n-> ");
    pesquisa = LePesquisaUsuario();

    palPesq = SeparaPalavrasPesquisa(palPesq, pesquisa);
    AtualizaDadosPalavrasPesquisadas(palPesq, indicePal);

    return palPesq;
}


void Funcionalidade1(tPalavra_pt indicePal, tDocumento_pt indiceDoc, int K){
    tPalavra_pt palPesq = NULL; 
    palPesq = ArmazenaPalavrasPesquisa(indicePal, palPesq);

    tIndices_pt docsAnalise = NULL;
    docsAnalise = PreencheEAlocaIndicesDeDoc(palPesq);

    if( docsAnalise ){

        AtualizaValorDoc(indiceDoc, docsAnalise, palPesq, indicePal);

        OrdenaValorTF_IDF(indiceDoc);

        ImprimeBusca(indiceDoc, docsAnalise);

    } else{
        printf("Não existem noticias com o texto digitado\n");
    }

    LiberaMemoriaPalPesq(palPesq);
    LiberaMemoriaIdx(docsAnalise);
}


void Funcionalidade2(tPalavra_pt indicePal, tDocumento_pt indiceDoc, int K){
    tDocumento_pt consulta = NULL;

    tPalavra_pt palPesq = NULL; 
    palPesq = ArmazenaPalavrasPesquisa(indicePal, palPesq);

    tIndices_pt docsAnalise = NULL;
    docsAnalise = PreencheEAlocaIndicesDeDoc(palPesq);

    if( docsAnalise ){

        consulta = AlocaERealocaIndiceDocumentos(consulta, 0);
        AumentaQtdDeDocLidos(consulta);

        int qtd_palPesq = RetornaQtdDePalavrasLidas(palPesq), qtd_docTotal = RetornaQtdDeDocLidos(indiceDoc);
        int tf = 0, iD = 0, posicao = 0;
        float TF_IDF = 0;

        /* atualiza o ponteiro "consulta" com as palavras da pesquisa */ 
        for( int iP = 0; iP < qtd_palPesq; iP++){
            
            tf = RetornaQtdPesquisa(palPesq, iP);
            TF_IDF = CalculaTF_IDF(palPesq, iP, tf, qtd_docTotal);

            posicao = RetornaIdxDePalavra(palPesq, iP);

            if( posicao >= 0 ) consulta = AtualizaDadosPalavrasEmDocumentos(consulta, iD, posicao, tf, TF_IDF);
        }

        CalculoSimilaridade(docsAnalise, indiceDoc, consulta);
        BuscaEImprimeClasseComum(docsAnalise, indiceDoc, K); 

        LiberaMemoriaDocumento(consulta);

        ImprimeIndices(docsAnalise);

        LiberaMemoriaPalPesq(palPesq);
        LiberaMemoriaIdx(docsAnalise);

    } else {
        printf("\nNao foi possivel calcular a classe comum, pois as palavras pesquisadas nao aparecem em nenhum documento.\n");

    }

}

void RelatorioPalavra(tPalavra_pt indicePal, tDocumento_pt indiceDoc, int K){
    tPalavra_pt palavraPesq = NULL;
    tClasse_pt classes = NULL;
    char str[500] = "\0";

    printf("Digite a palavra desejada (apenas uma):\n");
    scanf("%s", str);

    palavraPesq = AchaPalavraPesquisada(palavraPesq, indicePal, str);

    if( palavraPesq ){
        OrganizaDados(palavraPesq);
        classes = PreencheVetorClasse(palavraPesq, indiceDoc);
        
        ImprimeRelatorioPal(palavraPesq, classes, indiceDoc);

        LiberaMemoriaClasse(classes);
        free(palavraPesq);
        palavraPesq = NULL;

    } else{
        printf("Palavra não existente no vetor!\n");

    }
}

void RelatorioDocumentos(tPalavra_pt indicePal, tDocumento_pt indiceDoc, int K){
    tDocumento_pt docCopy = NULL;
    
    docCopy = DuplicaIndiceDoc(indiceDoc, docCopy);

    ImprimeRelatorioDoc(docCopy);

    free(docCopy);
    docCopy = NULL;
}