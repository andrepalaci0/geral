#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>


void leituraCen1(char *str, int* arrInts);
void leituraCen2(char *str);

void funcCen1();
void funcCen2();

void leituraCen1(char *str, int* arrInts)
{
    FILE *arq = fopen(str, "r");
    if(arq == NULL){
        printf("ERRO: Arquivo ausente");
    }
    int contador = 0;
    int firstIt = 0;
    int nAtts;
    fscanf(arq, "%d", &nAtts);
    printf("Atts: %d\n", nAtts);
    for (int i = 0; i < nAtts; i++)
    {
        fscanf(arq, "%i", &arrInts[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    int dur = atoi(argv[1]);
    if (dur < 14 || dur > 20)
    {
        printf("ERRO: DURACAO FORA DO LIMITE\nInsira duracao entre 14 e 20 horas\n");
        return 1; 
    }
    
    int cenario = atoi(argv[2]);
    int qtdAtts;

    FILE *arq = fopen(argv[3], "r");

    fscanf(arq, "%d", &qtdAtts);
    fclose(arq);
    int ArrAtts[qtdAtts]; 
    printf("Duração: %d\n", dur);
    if(cenario = 1){
        leituraCen1(argv[3], ArrAtts);
        //funcCen1();
        printf("Cenario 1\n");
    }else if(cenario = 2){
        //leituraCen2();
        //funcCen2();
        printf("Cenario 2\n");
    }
    printf("Vetor de ints: ");
    for (int i = 0; i < qtdAtts; i++)
    {
        printf("%i ", ArrAtts[i]);
    }
    printf("\nAtts: %d\n", qtdAtts);
    return 0;
}