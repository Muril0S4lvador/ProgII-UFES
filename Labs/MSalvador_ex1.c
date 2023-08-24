#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/* O programa so para quando le um ponto final
 - Murilo Salvador Dalmonech */

void TransformaTexto(char texto[], int tam);
void ImprimeSufixo(int tam);

int main(){
    char texto[50];
    int tam;

    while(scanf("%s", texto) == 1){
        tam = strlen(texto);
        TransformaTexto(texto, tam);
        printf(" ");

    }

    return 0;
}

void ImprimeSufixo(int tam){

    if(tam <= 3){
        printf("an");

    } else {
        printf("o");

    }

}

void TransformaTexto(char texto[], int tam){
    int i;
    char letrainicio = texto[0], letrafinal = texto[tam-1], letrarenegada = '\0';

    if(!isalpha(letrafinal)){
        tam--;
        letrarenegada = letrafinal;
        letrafinal = texto[tam-1];
    }

    if(isupper(texto[0])){
        texto[0] = tolower(texto[0]);
        texto[1] = toupper(texto[1]);

    }

    if(isalpha(letrafinal)){
        for(i=1; i < tam; i++){
            printf("%c", texto[i]);

        }
        printf("%c", texto[0]);
        ImprimeSufixo(tam);

    } else {
        for(i=1; i < tam-1; i++){
            printf("%c", texto[i]);

        }
        printf("%c", texto[0]);
        ImprimeSufixo(tam);
        printf("%c", letrafinal);

    }
    
    if(letrarenegada != '.'){
        printf("%c", letrarenegada);
    } else {
        exit(0);
    }
}