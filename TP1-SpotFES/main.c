#include "Playlists.h"

int main( int argc, char *argv[] ){
    int i, qtdArtistas = 0, qtdMusicas = 0, qtdPlaylists = 0;
    char id[23] = "\0";
    tArtistas_pt artistas = NULL;
    tMusicas_pt musicas = NULL;
    tPlaylists_pt playlists = NULL;

    /* --> Le os Artistas <-- */
    FILE *artistasF = AbreArquivoArtistas(artistasF, argv[1]);
    while ( !feof(artistasF) ){
        
        fscanf(artistasF, "%22s", id);

        artistas = LeECriaArtistas(artistas, artistasF, qtdArtistas, id);
        qtdArtistas++;

    }
    printf("Finalizou a leitura de %d artista(s)\n\n", qtdArtistas-1);
    fclose(artistasF);


    /* --> Le as Musicas <-- */
    FILE *musicasF = AbreArquivoMusicas(musicasF, argv[2]);
    while ( !feof(musicasF) ){
        fscanf(musicasF, "%22s", id);

        musicas = LeECriaMusicas(musicas, musicasF, qtdMusicas, id);
        qtdMusicas++;
    }
    printf("Finalizou a leitura de %d musica(s)\n\n", qtdMusicas-1);
    fclose(musicasF);


    /* --> Le as Playlists <-- */
    FILE *playlistsF = AbreArquivoPlaylists();
    if( playlistsF != NULL){

        fread(&qtdPlaylists, sizeof(int), 1, playlistsF);

        playlists = LeArquivoPlaylists(playlists, playlistsF, qtdPlaylists);
        
        fclose(playlistsF);
    }

    printf("---------------\n Bem-vindo! :) \n---------------\n");

    while(1){
        char c;

        ImprimeMenu();

        scanf("\n%c", &c);

        switch (c){
            case '0':
                SalvaPlaylists(playlists, qtdPlaylists);
                LiberaMemoria(artistas, musicas, qtdMusicas, playlists, qtdPlaylists);
                exit(0);
                break;

            case '1': /* Buscar Musicas */ 
                if(qtdMusicas == 0){
                    printf("\nAinda nao ha musicas!\n");
                    break;
                }

                printf("\nDigite o texto que procura:\n");

                char texto[100];
                scanf("%*c%[^\n]", texto);

                BuscarMusicas(texto, musicas, qtdMusicas);
                break;

            case '2': /* Listar uma musica */
                if(qtdMusicas == 0){
                    printf("\nAinda nao ha musicas!\n");
                    break;
                }

                printf("\nDigite o indice da musica que deseja:\n");
                i = ExibeERetornaIndices(qtdMusicas-1);

                if( i < 0 || i >= qtdMusicas-1 ){
                    printf("\nEssa musica não existe!\n");
                    break;
                }

                ListarMusicaCompleto(musicas, artistas, i, qtdArtistas);
                EscutarMusica(i, musicas);
                break;

            case '3': /* Criar uma playlist */
                playlists = AlocaERealocaPlaylists(playlists, qtdPlaylists);
                printf("\nQual o nome da playlist que deseja criar?\n");

                char nome[100];
                scanf("%*c%[^\n]", nome);
                
                playlists = CriaPlaylist(playlists, nome, qtdPlaylists);
                qtdPlaylists++;
                
                break;

            case '4': /* Listar todas as playlists */
                if( qtdPlaylists == 0)
                    printf("\nAinda nao ha playlists. Crie uma!\n");
                else
                    ListarPlaylists(playlists, qtdPlaylists);

                break;
                
            case '5': /* Listar uma playlist */
                if(qtdPlaylists == 0){
                    printf("\nAinda nao ha playlists. Crie uma!\n");
                    break;
                }
        
                printf("\nDigite o indice da playlist que deseja:\n");

                i = ExibeERetornaIndices(qtdPlaylists);

                if( i < 0 || i > qtdPlaylists-1){
                    printf("\nEssa playlist não existe!\n");
                    break;
                }

                ListarPlaylistCompleta(playlists, i, musicas);
                
                break;
                
           case '6': /* Adiciona a musica na playlist */
                if(qtdMusicas == 0){
                    printf("\nAinda nao ha musicas!\n");
                    break;
                }

                if(qtdPlaylists == 0){
                    printf("\nAinda nao ha playlists. Crie uma!\n");
                    break;
                }

                printf("\nQue musica deseja adicionar?\n");
                int iM = ExibeERetornaIndices(qtdMusicas-1); 

                if( iM < 0 || iM >= qtdMusicas-1 ){
                    printf("\nEssa musica não existe!\n");
                    break;
                }

                printf("\nEm qual playlist?\n");
                int iP = ExibeERetornaIndices(qtdPlaylists);

                if( iP < 0 || iP > qtdPlaylists-1 ){
                    printf("\nEssa playlist não existe!\n");
                    break;
                }

                int confirma = VerificaPlaylist(playlists, iP, musicas, iM);

                if( !confirma ){
                    printf("\nEssa musica ja esta inserida na playlist!\n");
                    break;
                }

                playlists = IncrementaPlaylist(playlists, iP, musicas, iM);

                musicas = IncrementaVezesMusicaEmPlaylist(musicas, iM);
                artistas = IncrementaVezesArtistaEmPlaylist(musicas, iM, artistas, qtdArtistas); 
                
                break;

            case '7': /* Recomenda musicas parecidas com um a playlist */
                if(qtdPlaylists == 0){
                    printf("\nAinda nao ha playlists. Crie uma!\n");
                    break;
                }

                printf("\nDigite o indice da playlist que gostou:\n");
                i = ExibeERetornaIndices(qtdPlaylists);

                if( i < 0 || i > qtdPlaylists-1 ){
                    printf("\nEssa playlist não existe!\n");
                    break;
                }

                int qtdRecomendacoes;
                printf("\nQuantas recomendacoes voce deseja?\n");
                scanf("%d", &qtdRecomendacoes);

                RecomendaMusicas(playlists, i, musicas, qtdRecomendacoes, qtdMusicas);

                break;

            case '8': /* Gerar Relatorio */
                GerarRelatorioMusicas(musicas, qtdMusicas-1);
                GerarRelatorioArtistas(artistas, qtdArtistas-1);
                printf("\nRelatorios gerados!\n");

                break;
        }
    }
}