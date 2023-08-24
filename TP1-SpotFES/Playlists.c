#include "Playlists.h"

struct playlists{
    char nome[100];
    int *indices;
    int qtd_musicas;
    int tamAlloc;
    int tamAllocMusicas;
    int qtdPlaylists;
};


void ImprimeMenu(void){

    printf("\n\nDigite o que deseja:\n\n");
    printf("0 - Sair\n1 - Buscar musicas\n2 - Listar uma musica\n3 - Criar uma playlist\n4 - Listar playlists\n5 - Listar uma playlist\n");
    printf("6 - Adicionar uma musica na playlist\n7 - Recomendar musicas parecidas com uma playlist\n8 - Gerar relatorio\n\n");
}

tPlaylists_pt AlocaERealocaPlaylists(tPlaylists_pt playlists, int qtd){

    if(qtd == 0){
        playlists = (tPlaylists_pt) malloc(QTD_ALLOC_INICIAL * sizeof( struct playlists ));
        (playlists+qtd)->tamAlloc = QTD_ALLOC_INICIAL;

    } else if( qtd == playlists->tamAlloc ){
        playlists->tamAlloc *= 2;
        playlists = (tPlaylists_pt) realloc (playlists, playlists->tamAlloc * sizeof( struct playlists ));

    }
    return playlists;
}

tPlaylists_pt AlocaERealocaIndices(tPlaylists_pt playlist, int qtd, int iP){

    if(qtd == 0){
        (playlist+iP)->indices = (int*) malloc(QTD_ALLOC_INICIAL * sizeof( int ));
        (playlist+iP)->tamAllocMusicas = QTD_ALLOC_INICIAL;

    } else if( qtd == (playlist+iP)->tamAllocMusicas ){
        (playlist+iP)->tamAllocMusicas *= 2;
        (playlist+iP)->indices = (int*) realloc ((playlist+iP)->indices, (playlist+iP)->tamAllocMusicas * sizeof( int ));

    }
    return playlist;
}

tPlaylists_pt CriaPlaylist(tPlaylists_pt playlist, char nome[], int qtd){

    playlist = AlocaERealocaPlaylists(playlist, qtd);
    
    strcpy((playlist+qtd)->nome, nome);   
    (playlist+qtd)->qtd_musicas = 0;

    printf("\nPlaylist Criada!\n");

    return playlist;
}

tPlaylists_pt IncrementaPlaylist(tPlaylists_pt playlist, int iP, tMusicas_pt musicas, int iM){

    playlist = AlocaERealocaIndices(playlist, (playlist+iP)->qtd_musicas, iP);

    (playlist+iP)->indices[(playlist+iP)->qtd_musicas] = iM;
    (playlist+iP)->qtd_musicas++;
    
    return playlist;
}

int VerificaPlaylist(tPlaylists_pt playlists, int iP, tMusicas_pt musicas, int iM){
    int i;

    /* Verifica se em uma playlist ja tem a musica que se quer adicionar */
    for(i = 0; i < (playlists+iP)->qtd_musicas; i++){
        if( (playlists+iP)->indices[i] == iM )
            return 0;
    }
    return 1;
}

void ListarPlaylistCompleta(tPlaylists_pt playlist, int indice, tMusicas_pt musicas){
    int i;

    printf("\nNome da playlist: %s\n\n", (playlist+indice)->nome);

    if( (playlist+indice)->qtd_musicas == 0 ){
        printf("Nao ha musicas nessa playlist!\n");

    } else {
        printf("Musica(s):\n");

        for(i = 0; i < (playlist+indice)->qtd_musicas; i++){
            printf("%d - ", i);
            ImprimeNomeMusica(musicas, (playlist+indice)->indices[i]);
        }

    }
    
}

void ListarPlaylists(tPlaylists_pt playlist, int qtd){
    int i;

    for(i = 0; i < qtd; i++){
        printf("Playlist %d: %s - %d musica(s)\n", i, (playlist+i)->nome, (playlist+i)->qtd_musicas);
    }
    
}

/*  RECOMENDACAO DE MUSICAS */

void RecomendaMusicas(tPlaylists_pt playlists, int iP, tMusicas_pt musicas, int qtdRecomendacoes, int qtdMusicas){
    double mediaCaracteristicas[8], caracteristicasMusica[8]; 
    tMusicas_pt musicas_playlist = NULL;
    double *distancia = NULL;
    int i, iC;


    int qtdMusicasPossiveis = (qtdMusicas-1)-(playlists+iP)->qtd_musicas;

    if( (playlists+iP)->qtd_musicas == 0 ){
        printf("\nNao ha musicas nessa playlist!\n"); 

    } else if( qtdRecomendacoes > qtdMusicasPossiveis ) {
        printf("\nSo existem %d musicas possiveis, escolha um numero menor!\n", qtdMusicasPossiveis);

    } else {
        /* Cria um ponteiro de Musicas para armazenar as musicas presentes na playlist */
        for(i = 0; i < (playlists+iP)->qtd_musicas; i++){
            musicas_playlist = AlocaERealocaMusicas(musicas_playlist, i);
        }
        musicas_playlist = CriaPonteiroMusicas(musicas_playlist, (playlists+iP)->indices, (playlists+iP)->qtd_musicas, musicas, qtdMusicas);


        /* Inicializa cada indice do vetor como a media de uma caracteristica */
        for(iC = 0; iC < 8; iC++){
            mediaCaracteristicas[iC] = CalculaMedia(musicas_playlist, (playlists+iP)->qtd_musicas, iC);
        }


        /* Aloca o vetor de distancia de acordo com a qtd de musicas lidas pelo programa */
        distancia = (double*) malloc( (qtdMusicas-1) * sizeof(double) );

        /* Calcula a distancia euclidiana para todas as musicas */
        for(i = 0; i < qtdMusicas-1; i++){

            /* Preenche o vetor com os valores das caracteristicas de uma musica */
            for(iC = 0; iC < 8; iC++){
                caracteristicasMusica[iC] = RetornaCaracteristicaMusica(musicas, i, iC);
            }

            distancia[i] = CalculaDistanciaEuclidiana(mediaCaracteristicas, caracteristicasMusica);
        }


        /* Imprime as K primeiras musicas com distancia em ordem crescente */
        ImprimeDistanciasOrdemCrescente(distancia, musicas, qtdMusicas, qtdRecomendacoes, playlists, iP);
    }
    
    free(distancia);
    free(musicas_playlist);
}

double CalculaDistanciaEuclidiana(double mediaCaracteristicas[], double caracteristicas[]){
    int i;
    double d = 0.0;

    for(i = 0; i < 8; i++){
        d += pow(caracteristicas[i] - mediaCaracteristicas[i], 2);
    }
    d = sqrt(d);

    return d;
}

void ImprimeDistanciasOrdemCrescente(double *distancia, tMusicas_pt musicas, int qtdMusicas, int qtdRecomendacoes, tPlaylists_pt playlists, int iP){
    int i, j, confirma = 1;
    int i_maiorDistancia, i_menorDistancia; //indices
    double menor_distancia, maior_distancia;
    
    
    maior_distancia = distancia[0];

    /* Acha o indice do vetor que possui a maior distancia */
    for(i = 0; i < qtdMusicas-1; i++){
        if( distancia[i] > maior_distancia ){
            maior_distancia = distancia[i];
            i_maiorDistancia = i;
        }
    }

    /* acha o indice do vetor que possui a maior distancia e imprime a musica relacionada a ele */
    for(i = 0; i < qtdRecomendacoes; i++){
        menor_distancia = maior_distancia;
        i_menorDistancia = i_maiorDistancia;

        /* Procura, dentre as musicas, aquela que possui menor distancia e a imprime
           Cada distancia corresponde a musica que possui mesmo indice */
        for(j = 0; j < qtdMusicas-1; j++){

            if( (distancia[j] < menor_distancia)){
                menor_distancia = distancia[j];
                i_menorDistancia = j;
            }

        }

        /* Se a musica ja pertencer a playlist base, ela nao é recomendada */
        confirma = VerificaPlaylist(playlists, iP, musicas, i_menorDistancia);

        if( confirma ){
            printf("- Indice %d - ", i_menorDistancia);
            ImprimeNomeMusica(musicas, i_menorDistancia);

        }else{
            i -= 1;
        }

        /* A menor distancia recebe o valor da maior, para que nao seja repetida nas proximas vezes */
        distancia[i_menorDistancia] = maior_distancia;
    }

}

/* MANIPULACAO DOS ARQUIVOS DE PLAYLISTS */

void SalvaPlaylists(tPlaylists_pt playlists, int qtd){
    int i;
    char endereco[30] = ARQUIVOPLAYLISTS;
    FILE *arq = fopen(endereco, "wb");

    if( arq == NULL){
        printf("Erro ao abrir arquivo %s.\n", endereco);
        
    } else if ( qtd > 0){

        fwrite(&qtd, sizeof(int), 1, arq);
        fwrite( &(playlists)->tamAlloc, sizeof(int), 1, arq );

        for(i = 0; i < qtd; i++){

            fwrite( (playlists+i)->nome, sizeof(char), 100, arq);
            fwrite( &(playlists+i)->qtd_musicas, sizeof(int), 1, arq );
            fwrite( &(playlists+i)->tamAllocMusicas, sizeof(int), 1, arq );
            fwrite( (playlists+i)->indices, sizeof(int), (playlists+i)->qtd_musicas, arq );

        }
    }

    fclose(arq);
}

FILE* AbreArquivoPlaylists(){
    char endereco[30] = ARQUIVOPLAYLISTS;
    FILE *arq = fopen(endereco, "rb");

    return arq;
}

tPlaylists_pt LeArquivoPlaylists(tPlaylists_pt playlists, FILE *playlistsF, int qtd){
    int i, tamAlloc = 0;

    fread( &tamAlloc, sizeof(int), 1, playlistsF );
    playlists =(tPlaylists_pt) malloc( tamAlloc * sizeof(struct playlists) );
    playlists->tamAlloc = tamAlloc;

    for(i = 0; i < qtd; i++){

        fread( (playlists+i)->nome, sizeof(char), 100, playlistsF );
        fread( &(playlists+i)->qtd_musicas, sizeof(int), 1, playlistsF );
        fread( &(playlists+i)->tamAllocMusicas, sizeof(int), 1, playlistsF );

        (playlists+i)->indices =(int*) malloc( (playlists+i)->tamAllocMusicas * sizeof(int) );
        fread( (playlists+i)->indices, sizeof(int), (playlists+i)->qtd_musicas, playlistsF );


    }
    return playlists;
}

/* FUNCAO PARA LIBERAR MEMORIA DE TODOS OS PONTEIROS */

void LiberaMemoria(tArtistas_pt artistas, tMusicas_pt musicas, int qtdMusicas, tPlaylists_pt playlists, int qtdPlaylists){
    int i;

    for( i = 0; i < qtdPlaylists; i++){
        free((playlists+i)->indices);
    }
    free(playlists);
    
    LiberarMusicas(musicas, qtdMusicas);
    free(artistas);
}