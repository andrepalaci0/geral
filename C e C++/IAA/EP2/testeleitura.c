#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
typedef struct att
{
    int indice;
    int valor;
} ATT;

typedef struct att2
{
    struct att2 *prox;
    int infos[4];
} ATT2;

ATT2 *criaNo(ATT2 *p, int *arr)
{
    ATT2 *novo = (ATT2 *)malloc(sizeof(ATT2));
    novo->infos[0] = arr[0]; // TIPO DE MUDANÇA (c = 99) (i = 105)
    novo->infos[1] = arr[1]; // instante em que ocorrerá a atualização
    novo->infos[2] = arr[2]; // numero da atualização, se for maior que a quantidade atual é uma nova atualização
    novo->infos[3] = arr[3]; // duracao da nova att
    novo->prox = NULL;
    return novo;
}

ATT2 *leituraCen3(char *str, int *arrInts, ATT2 *p)
{
    FILE *arq = fopen(str, "r");
    if (arq == NULL)
    {
        printf("ERRO: Arquivo ausente");
    }
    int contador = 0;
    int firstIt = 0;
    int nAtts;
    fscanf(arq, "%d", &nAtts);
    printf("Atts: %d\n", nAtts);
    bool primeiraLinha = true;
    int i = 0;
    int atribuir;

    for (int i = 0; i < nAtts; i++)
    {
        fscanf(arq, "%i", &arrInts[i]);
    }

    while (fscanf(arq, "%c")     != EOF)
    {
        fscanf(arq, "%c", &atribuir);
        if (atribuir == 'c')
        {
            printf("giba");
        }
        printf("cu");
    }
    return p;
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
    int ArrInts[qtdAtts];
    ATT2 *p = (ATT2 *)malloc(sizeof(ATT2));
    p->prox = leituraCen3(argv[3], ArrInts, p);
}
