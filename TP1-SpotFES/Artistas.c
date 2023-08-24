#include "Artistas.h"

struct artistas{
    char id[23];
    double seguidores;
    char generos[1000];
    char nome[100];
    int popularidade;
    int tamAlloc;
    int musicasEmPlaylists;
};


FILE *AbreArquivoArtistas(FILE *artistasF, char argv[]){
    char endereco[100] = "\0";
    sprintf(endereco, "%s", argv);
    
    artistasF = fopen(endereco, "r");

    if( !artistasF ){
        printf("Não foi encontrado o arquivo de artistas\n");
        exit(1);
    }

    if( artistasF ){
        printf("Aberto o arquivo %s\n", endereco);
    }

    return artistasF;
}

tArtistas_pt AlocaERealocaArtistas(tArtistas_pt artistas, int qtd){

    if( qtd == 0 ){
        artistas = (tArtistas_pt) malloc(QTD_ALLOC_INICIAL * sizeof( struct artistas ));
        (artistas+qtd)->tamAlloc = QTD_ALLOC_INICIAL;

    } else if( qtd == artistas->tamAlloc ){
        artistas->tamAlloc *= 2;
        artistas =(tArtistas_pt) realloc(artistas, (artistas->tamAlloc)*sizeof( struct artistas ));

    }

    return artistas;
}

tArtistas_pt LeECriaArtistas(tArtistas_pt artista, FILE *artistasF, int qtd, char id[]){
    int popularidade;
    double seguidores;


    artista = AlocaERealocaArtistas(artista, qtd);

    strcpy((artista+qtd)->id, id);
    fscanf(artistasF,";%lf;", &seguidores);
    fscanf(artistasF, "%[^;];", (artista+qtd)->generos);
    fscanf(artistasF, "%[^;];", (artista+qtd)->nome);
    fscanf(artistasF, "%d", &popularidade);
    fscanf(artistasF, "%*c");

    (artista+qtd)->seguidores = seguidores;
    (artista+qtd)->popularidade = popularidade;
    (artista+qtd)->musicasEmPlaylists = 0;

    return artista;
}

void ListaArtistasCompleto(tArtistas_pt artistas, int qtdDentroMusica, tArtistas_pt TodosArtistas, int qtdGeral){
    int i, j, cont;

    printf("\n\nArtista(s):\n");

    for(i = 0; i<qtdDentroMusica; i++){
        cont = 0;
        for(j = 0; j < qtdGeral-1; j++){
            if( strstr((artistas+i)->id, (TodosArtistas+j)->id) != NULL ){

                printf("\n%s\nID : %s --- Popularidade : %d%% --- Seguidores : %.1lf\nGeneros : %s\n",
                (TodosArtistas+j)->nome, (TodosArtistas+j)->id, (TodosArtistas+j)->popularidade, (TodosArtistas+j)->seguidores, (TodosArtistas+j)->generos);
                cont++;
            }
        }
        if( cont == 0 ){
            printf("\n%s\nID : %s\n", (artistas+i)->nome, (artistas+i)->id);
        }
    }
}

tArtistas_pt BuscaArtistaEIncrementa(tArtistas_pt artistaDaMusica, tArtistas_pt artistas, int qtdGeral, int qtdArtistas){
    int i, j;

    for( i = 0; i < qtdArtistas; i++ ){
        for(j = 0; j < qtdGeral-1; j++){
            if( strstr((artistaDaMusica+i)->id, (artistas+j)->id) != NULL ){
                (artistas+j)->musicasEmPlaylists++;
            
            }
        }
    }
    return artistas;
}

void GerarRelatorioArtistas(tArtistas_pt artistas, int qtdArtistasTotal){
    int i = 0, j = 0, qtdArtistasCitados = 0;
    char endereco[50] = ARQUIVORELATORIOARTISTA;
    FILE *artistasF = fopen(endereco, "w");
    
    /* Varre o vetor de artistas buscando quantos tem mais de 0 musicas adicionadas em playlists */
    for(i = 0; i < qtdArtistasTotal; i++){

        if( (artistas+i)->musicasEmPlaylists > 0 ){
            qtdArtistasCitados++;

        }
    }

    /* Cria vetores de inteiros do exato tamanho de artistas necessarios */
    int indices[qtdArtistasCitados], vezesMusicasEmPL[qtdArtistasCitados];

    /* Varre novamente todos os artistas com alguma musica em playlists, mas, dessa vez, 
       adiciona os indices e a quantidade de vezes de musicas dos artistas em playlists nos vetores */
    for(i = 0; i < qtdArtistasTotal; i++){
        if( (artistas+i)->musicasEmPlaylists > 0 ){
            indices[j] = i;
            vezesMusicasEmPL[j] = (artistas+i)->musicasEmPlaylists;
            j++;

        }

        if( j == qtdArtistasCitados )
            break;
    }
    
    /* Nesse for, ordena de forma decrescente as quantidades de vezes que cada artista teve sua musica adicionada em playlist
       e ordena o vetor indices paralelamente */
    int aux;
    for(i = 0; i < qtdArtistasCitados-1; i++){
        for( j = i+1; j < qtdArtistasCitados; j++){

            if(vezesMusicasEmPL[i] < vezesMusicasEmPL[j]){
                aux = vezesMusicasEmPL[i];
                vezesMusicasEmPL[i] = vezesMusicasEmPL[j];
                vezesMusicasEmPL[j] = aux;
                
                aux = indices[i];
                indices[i] = indices[j];
                indices[j] = aux;
            }
        }
    }

    for(i = 0; i < qtdArtistasCitados; i++){
            fprintf(artistasF, "%s - %d vezes em playlists\n", (artistas+indices[i])->nome, (artistas+indices[i])->musicasEmPlaylists);
    }

    fclose(artistasF);
}


/* FUNÇÕES VISTAS EM TMUSICAS */

tArtistas_pt DefineNome(tArtistas_pt artista, char* nome,  int qtd){
    artista = AlocaERealocaArtistas(artista, qtd);

    strcpy((artista+qtd)->nome, nome);
    return artista;
}

void ListaNomesArtistasMusica(tArtistas_pt artista, int qtd){
    int i;

    printf("\nArtistas:\n");
    for(i = 0; i < qtd; i++){
        printf("%s\n", (artista+i)->nome);

    }
}

tArtistas_pt LeIdsArtistas(tArtistas_pt artistas, FILE *musicasF, int qtd){
    char id[23] = "\0";
    int i;

    for(i = 0; i < qtd; i++){
        fscanf(musicasF, "%22s", id);
        fscanf(musicasF, "%*c");

        strcpy((artistas+i)->id, id);
    }

    return artistas;
}
