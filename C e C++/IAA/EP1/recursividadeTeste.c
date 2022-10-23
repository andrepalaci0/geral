#include <stdio.h>
#include <stdlib.h>

int raiz();
int folhas(int n, int m[n][n], int l, int c, int maxL, int maxC, int auxN);
void lerArq(int n, int m[n][n], char *str);
void imprimir(int n, int m[n][n], int i, int j, int maxL, int maxC);
void preencherMatriz(int n, int m[n][n]);
void dividirConquistarIni(int n, int m[n][n]);

int raiz(int n, int m[n][n])
{

    return folhas(n, m, n, n, n,n, n);
}


int folhas(int n, int m[n][n], int l, int c, int maxL, int maxC, int auxN)
{

imprimir(n, m, l, c, maxL, maxC);
 if( auxN == 1) 
 {
    printf("giba\n");
    return 1;
 }
 else {
    printf("N: %d\n", auxN);
    int TL = folhas(n, m, 0, 0, auxN / 2, auxN / 2,  auxN / 2); // canto superior esquerdo
    int TR = folhas(n, m, 0, auxN / 2, auxN / 2, auxN,  auxN / 2); // canto superior direito
    int BL = folhas(n, m, auxN / 2, 0, auxN, auxN / 2,  auxN / 2); // canto inferior esquerdo
    int BR = folhas(n, m, auxN / 2, auxN / 2, auxN, auxN,  auxN / 2); // canto inferior direito
    int soma = TL + TR + BL + BR;
    if(soma == 0 || soma ==4){
        return 1;
    }else return 0;
 }
}


void lerArq(int n, int m[n][n], char *str) // le o arquivo e preenche a matriz, transformando os chars em ints;
{
    // ZERO = PRETOS
    // UM = BRANCOS
    FILE *arq = fopen(str, "r");
    if (arq == NULL)
        printf("Arquivo ausente\n");
    else
        printf("Arquivo aberto em leitura\n");
    int chToInt;
    int i = 0;
    int j = 0;
    while ((chToInt = fgetc(arq)) != EOF)
    {
        printf("%c", chToInt);
        m[i][j] = chToInt - 48; // transforma o ASCII do char em int. 48 = 0
        if (j == n)
        {
            i++;
            j = 0;
        }
        else
            j++;
    }
    printf(" \n");
    fclose(arq);
}

void imprimir(int n, int m[n][n], int i, int j, int maxL, int maxC)
{
    for (int i = i; i <= maxL; i++)
    {
        for (int j = j; j <= maxC; j++)
        {
            printf("%i ", m[i][j]);
        }
        printf("\n");
    }
}

// LEMBRETE: definir (N = *argv[1] - 48) !

int main(int argc, char *argv[]) // necessario passar o arquivo entrada.txt como argumento -> ./modelo1 ./ins1.txt
{
    int n = 4;
    int m[n][n];
    // preencherMatriz(n, m);
    lerArq(n, m, argv[1]);
    raiz(n, m);
    return 0;
}
