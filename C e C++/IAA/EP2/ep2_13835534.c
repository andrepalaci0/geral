#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

//Andre Palacio Braga Tivo

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

void leituraCen1(char *str, int *arrInts);
void arquivoSaidaTxtCen1(ATT *arr, int atualizacoesSomadas);
void leituraCen2(char *str, int *arrInts, ATT *arr);

void funcCen1(ATT arr[], int tamArr, int dur);
void funcCen2();

ATT2 *criaNo(ATT2 *p, int *arr);
void defineArrATT(int *arrInt, ATT *arrATT, int tamArr);

void arquivoSaidaTxtCen1(ATT *arr, int atualizacoesSomadas)
{
        FILE *saida1 = fopen("saida1.txt", "w");

    fprintf(saida1, "%i ", atualizacoesSomadas);
    for (int i = 0; i < atualizacoesSomadas; i++)
    {
        fprintf(saida1, "%i ", arr[i].indice);
    }
    fclose(saida1);
}

void funcCen1(ATT arr[], int tamArr, int dur)
{
    int i, j;
    ATT aux;
    for (i = 1; i < tamArr; i++)
    {
        aux = arr[i];
        j = i - 1;
        while ((j >= 0) && (aux.valor < arr[j].valor))
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = aux;
    }
}

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

void leituraCen2(char *str, int *arrInts, ATT *arr)
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
    for (int i = 0; i < nAtts; i++)
    {
        fscanf(arq, "%i", &arrInts[i]);
    }
    defineArrATT(arrInts, arr, nAtts);
    char CouI;
    int indiceNovaAtt = 0;
    int momentoNovaAtt  = 0;    
    int tempoNovaAtt = 0;
}

void leituraCen1(char *str, int *arrInts)
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
    for (int i = 0; i < nAtts; i++)
    {
        fscanf(arq, "%i", &arrInts[i]);
    }
    fclose(arq);
}

void defineArrATT(int *arrInt, ATT *arrATT, int tamArr)
{
    for (int i = 0; i < tamArr; i++)
    {
        arrATT[i].valor = arrInt[i];
        arrATT[i].indice = (i + 1);
    }
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
    ATT ArrAtts[qtdAtts];
    if (cenario = 1)
    {
        leituraCen1(argv[3], ArrInts);
        defineArrATT(ArrInts, ArrAtts, qtdAtts);
        funcCen1(ArrAtts, qtdAtts, dur);
        int durAtual = 0;
        int atualizacoesInseridas = 0;
        while (durAtual < dur)
        {
            durAtual += ArrAtts[atualizacoesInseridas].valor;
            atualizacoesInseridas++;
        }
        if(durAtual > dur){
            atualizacoesInseridas--;
        }
        ATT resp[durAtual];
        for (int i = 0; i < atualizacoesInseridas; i++)
        {
            resp[i] = ArrAtts[i];
        }
        arquivoSaidaTxtCen1(resp, atualizacoesInseridas);
    }
    else if (cenario = 2)
    {
        // leituraCen2();
        // funcCen2();
        // leituraCen2(argv[3], ArrInts);
        // defineArrATT(ArrInts, ArrAtts, qtdAtts);
        // funcCen1(ArrAtts, qtdAtts, dur);

        printf("Cenario 2\n");
    }
    return 0;
}