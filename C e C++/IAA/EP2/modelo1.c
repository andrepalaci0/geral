#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>


void leituraCen1(char *str[], int* qtdAtts);
void leituraCen2(char *str[]);

void funcCen1();
void funcCen2();

void leituraCen1(char *str[], int* qtdAtts)
{
    FILE *arq = fopen(str, "r");
    if(arq == NULL){
        printf("ERRO: Arquivo ausente");
    }
    int firstIt = 0;
    while (fgetc(arq) != EOF) //usar fscanf
    {
        if(firstIt = 0){
            firstIt++;
        *qtdAtts = fgetc(arq);
        }

    }
    

}


int main(int argc, char *argv[])
{
    int dur = atoi(argv[1]);
    int cenario = atoi(argv[2]);
    int qtdAtts;
    printf("Duração: %d\n", dur);
    if(cenario = 1){
        leituraCen1(argv[3], &qtdAtts);
        //funcCen1();
        printf("Cenario 1\n");
    }else if(cenario = 2){
        //leituraCen2();
        //funcCen2();
        printf("Cenario 2\n");
    }
    return 0;
}