#include "Musicas.h"

struct musicas{
    char id[23];
    char nome[100];
    int popularidade;
    unsigned int duracao_ms;
    int explicit;
    tArtistas_pt artistasDaMusica;
    int qtd_artistas;
    char dataLancamento[20];
    double danceability;
    double energy;
    int key;
    double loudness;
    int mode;
    double speechiness;
    double acousticness;
    double instrumentalness;
    double liveness;
    double valence;
    double tempo_BPM;
    int time_signature;
    int tamAlloc;
    int vezesEmPlaylists;
};

FILE* AbreArquivoMusicas(FILE *musicasF, char argv[]){
    char endereco[100] = "\0";
    sprintf(endereco, "%s", argv);

    musicasF = fopen(endereco, "r");

    if( !musicasF ){
        printf("Não foi encontrado o arquivo de musicas\n");
        exit(1);
    }
    if( musicasF ){
        printf("Aberto o arquivo %s\n", endereco);
    }

    return musicasF;
}

tMusicas_pt AlocaERealocaMusicas(tMusicas_pt musicas, int qtd){

    if( qtd == 0 ){
        musicas = (tMusicas_pt) malloc(QTD_ALLOC_INICIAL * sizeof( struct musicas ));
        (musicas+qtd)->tamAlloc = QTD_ALLOC_INICIAL;

    } else if( qtd == musicas->tamAlloc ){
        musicas->tamAlloc *= 2;
        musicas =(tMusicas_pt) realloc(musicas, (musicas->tamAlloc)*sizeof( struct musicas ));

    }

    return musicas;
}

tMusicas_pt LeECriaMusicas(tMusicas_pt musicas, FILE *musicasF, int qtd, char id[]){
    int popularidade;
    int explicit;
    int key;
    int mode;
    int time_signature;
    unsigned int duracao_ms;
    double danceability;
    double energy;
    double loudness;
    double speechiness;
    double acousticness;
    double liveness;
    double valence;
    double tempo_BPM;

    musicas = AlocaERealocaMusicas(musicas, qtd);

    /* --> Leitura das musicas <-- */
    fscanf(musicasF, ";%[^;];", (musicas+qtd)->nome);
    fscanf(musicasF, "%d;", &popularidade);
    fscanf(musicasF, "%d;", &duracao_ms);
    fscanf(musicasF, "%d;", &explicit);
   
    musicas = LeArtistasEmMusicas(musicas, musicasF, qtd);

    fscanf(musicasF, "%[^;];", (musicas+qtd)->dataLancamento);
    fscanf(musicasF, "%lf;", &danceability);
    fscanf(musicasF, "%lf;", &energy);
    fscanf(musicasF, "%d;", &key);
    fscanf(musicasF, "%lf;", &loudness);
    fscanf(musicasF, "%d;", &mode);
    fscanf(musicasF, "%lf;", &speechiness);
    fscanf(musicasF, "%lf;", &acousticness);

    musicas = LeECalculaInstrumentalness(musicas, musicasF, qtd);

    fscanf(musicasF, ";%lf;", &liveness);
    fscanf(musicasF, "%lf;", &valence);
    fscanf(musicasF, "%lf;", &tempo_BPM);
    fscanf(musicasF, "%d", &time_signature);
    fscanf(musicasF, "%*c");



    /* Adicionando as Variaveis na struct */

    strcpy((musicas+qtd)->id, id);
    (musicas+qtd)->popularidade = popularidade;
    (musicas+qtd)->duracao_ms = duracao_ms;
    (musicas+qtd)->explicit = explicit;
    (musicas+qtd)->danceability = danceability;
    (musicas+qtd)->energy = energy;
    (musicas+qtd)->key = key;
    (musicas+qtd)->loudness = loudness;
    (musicas+qtd)->mode = mode;
    (musicas+qtd)->speechiness = speechiness;
    (musicas+qtd)->acousticness = acousticness;
    (musicas+qtd)->liveness = liveness;
    (musicas+qtd)->valence = valence;
    (musicas+qtd)->tempo_BPM = tempo_BPM;
    (musicas+qtd)->time_signature = time_signature;
    (musicas+qtd)->vezesEmPlaylists = 0;

    return musicas;
}

tMusicas_pt LeECalculaInstrumentalness(tMusicas_pt musicas, FILE *musicasF, int qtd){ //2.66e-05
    double mantissa;
    int i, expoente = 0;

    fscanf(musicasF, "%lf", &mantissa);

    if( fscanf(musicasF, "e-") == 1){
        fscanf(musicasF, "%d", &expoente);

        for(i = 0; i < expoente; i++){
                mantissa = mantissa/10;
        }
    }  

    else if( fscanf(musicasF, "e") == 1 || fscanf(musicasF, "e+") == 1 ){
        fscanf(musicasF, "%d", &expoente);

        for(i = 0; i < expoente; i++){
                mantissa = mantissa*10;
        }
    } 

    (musicas+qtd)->instrumentalness = mantissa;

    return musicas;
}

void ListarMusicaCompleto(tMusicas_pt musicas, tArtistas_pt artistas, int i, int qtdArtistas){

    printf("\n----\n");
    printf("Musica %d\n\n", i);

    printf("Nome : %s\n",               (musicas+i)->nome            );
    printf("Popularidade : %d%%\n",     (musicas+i)->popularidade    );
    printf("Duracao : %d ms\n",         (musicas+i)->duracao_ms      );
    printf("Explicit : %d\n",           (musicas+i)->explicit        );
    printf("Data de Lançamento : %s\n", (musicas+i)->dataLancamento  );
    printf("Danceability : %.3lf\n",    (musicas+i)->danceability    );
    printf("Energy : %.3lf\n",          (musicas+i)->energy          );
    printf("Key : %d\n",                (musicas+i)->key             );
    printf("Loudness : %.3lf\n",        (musicas+i)->loudness        );
    printf("Mode : %d\n",               (musicas+i)->mode            );
    printf("Speedchiness : %.3lf\n",    (musicas+i)->speechiness    );
    printf("Acousticness : %.3lf\n",    (musicas+i)->acousticness    );
    printf("Instrumentalness : %.3lf\n",(musicas+i)->instrumentalness);
    printf("Liveness : %.3lf\n",        (musicas+i)->liveness        );
    printf("Valence : %.3lf\n",         (musicas+i)->valence         );
    printf("Tempo : %.3lf BPM\n",       (musicas+i)->tempo_BPM       );
    printf("Time Signature : %d\n",     (musicas+i)->time_signature  );
    
    ListaArtistasCompleto((musicas+i)->artistasDaMusica, (musicas+i)->qtd_artistas, artistas, qtdArtistas);
    
    printf("----\n");
    
}

tMusicas_pt LeArtistasEmMusicas(tMusicas_pt musica, FILE *musicasF, int qtd){
    char listaDeNomes[1000] = "\0", *nome = NULL;
    (musica+qtd)->qtd_artistas = 0;

    fscanf(musicasF, "%[^;];", listaDeNomes);

    /* Se tem mais de um artista em uma musica, leva para outra funcao de definir artistas */
    int maisDeUmArtista = MaisDeUmArtista(listaDeNomes, strlen(listaDeNomes));

    if( maisDeUmArtista ){

        nome = strtok(listaDeNomes, "|");

        while( nome ){
            (musica+qtd)->artistasDaMusica = DefineNome((musica+qtd)->artistasDaMusica, nome, (musica+qtd)->qtd_artistas);
            (musica+qtd)->qtd_artistas++;

            nome = strtok(NULL, "|");
        }

    } else {
        (musica+qtd)->artistasDaMusica = DefineNome((musica+qtd)->artistasDaMusica, listaDeNomes, (musica+qtd)->qtd_artistas);
        (musica+qtd)->qtd_artistas++;
    }

    (musica+qtd)->artistasDaMusica = LeIdsArtistas((musica+qtd)->artistasDaMusica, musicasF, (musica+qtd)->qtd_artistas);

    return musica;
}

int MaisDeUmArtista(char *lista, int tam){
    int i;

    /* Se houver algum | na string, entao tem mais de 1 artista */
    for(i = 0; i < tam; i++){
        if( lista[i] == '|' )
            return 1;
    }

    return 0;
}


/* FUNCOES PRESENTES NO TPLAYLISTS */

void ImprimeNomeMusica(tMusicas_pt musica, int i){
    printf("%s\n", (musica+i)->nome);
}

tMusicas_pt CriaPonteiroMusicas(tMusicas_pt musicas_playlist, int *indices, int qtd_musicasPlaylist, tMusicas_pt musicas, int qtdMusicasTotal){
    int i, iM;

    /* Quando o indice da musica presente na playlist coincidir com o da musica no arquivo, 
       armazena o struct da respectiva musica no ponteiro musicas_playlist */
    for(i = 0; i < qtd_musicasPlaylist; i++){
        for(iM = 0; iM < qtdMusicasTotal-1; iM++){
          
            if( indices[i] == iM ){
                musicas_playlist[i] = musicas[iM];
            }

        }
    }

    return musicas_playlist;
}

double CalculaMedia(tMusicas_pt musicas, int qtd, int iC){
    int i;
    double media = 0;

    /* Calcula a soma total de um determinado atributo e divide pela quantidade de musicas presentes na playlist
       A media de cada atributo ficara armazenada no espaco do vetor de mesmo indice -> iC=1, atributo 1(energy) armazenado em mediaCaracteristicas[1] */

    switch (iC){
        case 0:
            for(i = 0; i < qtd; i++){
                media += (musicas+i)->danceability;
            }
            break;

        case 1:
            for(i = 0; i < qtd; i++){
                media += (musicas+i)->energy;  
            }
            break;

        case 2:
            for(i = 0; i < qtd; i++){
                media += (musicas+i)->mode;
            }
            break;

        case 3:
            for(i = 0; i < qtd; i++){
                media += (musicas+i)->speechiness;
            }
            break;

        case 4:
            for(i = 0; i < qtd; i++){
                media += (musicas+i)->acousticness;
            }
            break;

        case 5:
            for(i = 0; i < qtd; i++){
                media += (musicas+i)->instrumentalness;
            }
            break;

        case 6:
            for(i = 0; i < qtd; i++){
                media += (musicas+i)->liveness;
            }
            break;

        case 7:
            for(i = 0; i < qtd; i++){
                media += (musicas+i)->valence;    
            }
            break;
    }

    media = media/qtd;

    return media;
}

double RetornaCaracteristicaMusica(tMusicas_pt musicas, int i, int iC){

    /* Cada atributo ficara armazenado no espaco do vetor de mesmo indice */

    switch (iC){
        case 0:
            return (musicas+i)->danceability;

        case 1:
            return (musicas+i)->energy;

        case 2:
            return (musicas+i)->mode;

        case 3:
            return (musicas+i)->speechiness;

        case 4:
            return (musicas+i)->acousticness;

        case 5:
            return (musicas+i)->instrumentalness;

        case 6:
            return (musicas+i)->liveness;

        case 7:
            return (musicas+i)->valence;
    }

    return 0;
}


/* FUNCOES PRESENTES NO SWITCH */

tMusicas_pt IncrementaVezesMusicaEmPlaylist(tMusicas_pt musicas, int i){
    (musicas+i)->vezesEmPlaylists++;
    return musicas;
}

tArtistas_pt IncrementaVezesArtistaEmPlaylist(tMusicas_pt musica, int indice, tArtistas_pt artistas, int qtd){
    
    artistas = BuscaArtistaEIncrementa((musica+indice)->artistasDaMusica, artistas, qtd, (musica+indice)->qtd_artistas);
    return artistas;
}

void BuscarMusicas(char texto[], tMusicas_pt musicas, int qtdMusicas){
    int i, count=0;

    for(i = 0; i < qtdMusicas-1; i++){

        if(strstr((musicas+i)->nome, texto) != NULL){
            ListarMusica((musicas+i), i);
            count++;
        }
    } 

    if(count == 0)
        printf("Nao ha musicas com esse texto no titulo!\n\n");
}

int ExibeERetornaIndices(int qtd){
    int i;

    if(qtd == 1)
        printf("OBS.: Apenas o indice 0 esta disponivel\n");
    else
        printf("OBS.: Indices de 0 a %d\n\n", qtd-1);

    scanf("%d", &i);

    return i;
}

void ListarMusica(tMusicas_pt musica, int indice){
    printf("\n----\n");

    printf("%s\n", musica->nome);
    printf("Indice: %d -- ID: %s\n", indice, musica->id);

    ListaNomesArtistasMusica(musica->artistasDaMusica, musica->qtd_artistas);
    
    printf("----\n");

}

void EscutarMusica(int i, tMusicas_pt musica){
    int ordem;
    
    printf("\nGostaria de escuta-la?\n");
    printf("0 - Nao\n1 - Sim\n");
    scanf("%d", &ordem);

    if( ordem ){
        printf("\nfirefox https://open.spotify.com/track/%s\n", (musica+i)->id);
    }
}

void GerarRelatorioMusicas(tMusicas_pt musicas, int qtdMusicasTotal){
    int i = 0, j = 0, qtdMusicasCitadas = 0;
    char endereco[50] = ARQUIVORELATORIOMUSICA;
    FILE *musicasF = fopen(endereco, "w");

    /* Varre o vetor de musicas buscando quantas foram adicionadas em alguma playlist */
    for(i = 0; i < qtdMusicasTotal; i++){
        if( (musicas+i)->vezesEmPlaylists > 0 )
            qtdMusicasCitadas++;
    }

    /* Cria vetores de inteiros do exato tamanho de musicas necessarias */
    int indices[qtdMusicasCitadas], vezesEmPL[qtdMusicasCitadas];

    for(i = 0; i < qtdMusicasTotal; i++){
        if( (musicas+i)->vezesEmPlaylists > 0 ){
            indices[j] = i;
            vezesEmPL[j] = (musicas+i)->vezesEmPlaylists;
            j++;
        }
        if( j == qtdMusicasCitadas )
            break;

    }

    /* Organiza o vetor de forma decrescente, juntamente om os seus indices */
    int aux;
    for(i = 0; i < qtdMusicasCitadas; i++){
        for( j = i+1; j < qtdMusicasCitadas; j++){
            if(vezesEmPL[i] < vezesEmPL[j]){
                aux = vezesEmPL[i];
                vezesEmPL[i] = vezesEmPL[j];
                vezesEmPL[j] = aux;
                
                aux = indices[i];
                indices[i] = indices[j];
                indices[j] = aux;
            }
        }
    }

    for(i = 0; i < qtdMusicasCitadas; i++){
            fprintf(musicasF, "%s - %d vezes em playlists\n", (musicas+indices[i])->nome, (musicas+indices[i])->vezesEmPlaylists);
    }

    fclose(musicasF);
}

void LiberarMusicas(tMusicas_pt musicas, int qtd){
    int i;

    for(i = 0; i < qtd; i++){
        free((musicas+i)->artistasDaMusica);
    }
    free(musicas);
}