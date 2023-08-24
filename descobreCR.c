#include <stdio.h>

void ImprimeInicio();
void ImprimeCR(double cr);
double MultiplicaNotaPeso(int peso, double nota);

int main(){
    int totalpeso = 0, peso = 0;
    double cr = 0, nota = 0, notaXpeso = 0;

    ImprimeInicio();
    printf("\nDigite o peso da materia: ");
    scanf("%d", &peso);

    while( peso != 0 ){
        printf("\nDigite sua media: ");
        scanf("%lf", &nota);

        notaXpeso += MultiplicaNotaPeso(peso, nota);
        totalpeso += peso;

        printf("\nDigite o peso da materia: ");
        scanf("%d", &peso);
    }
    
    cr = notaXpeso / totalpeso;
    ImprimeCR(cr);

}

void ImprimeInicio(){
    printf("Ola! Para usar esse programa, se atente as instrucoes:\n");
    printf("\nPASSOS:\n");
    printf("1 - Digite o peso da materia\n");
    printf("2 - Em seguida, digite a media final\n");
    printf("3 - Caso deseje finalizar o programa, digite peso 0 para alguma materia e ele ira finalizar\n*(Nao funciona se digitar 0 no lugar da media)*\n\n");
}

void ImprimeCR(double cr){
    printf("\n\nFinalizado!\nSeu Coeficiente de Rendimento eh igual a: %.2lf\n", cr);

}

double MultiplicaNotaPeso(int peso, double nota){
    return (double)peso * nota;
}