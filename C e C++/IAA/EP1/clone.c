//Andre Palacio Braga Tivo
//NUSP 13835534

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

int folhas(int nEst, int m[nEst][nEst], int l, int c, int maxL, int maxC, int *contAux1, int *contAux2, int *contP, int *contB, int nMut);
int defineIndex(int n);
void lerArq(int n, int m[n][n], char *str);
void imprimir(int n, int m[n][n]);
void preencherMatriz(int n, int m[n][n]);

int defineIndex(int n)
{
    if (n == 1)
        return 0;
    if (n == 2)
        return 1; 
    if (n == 4)
        return 2;
    if (n == 8)
        return 3;
    if (n == 16)
        return 4;
    if (n == 32)
        return 5;
    if (n == 64)
        return 6;
    if (n == 128)
        return 7;
    if (n == 256)
        return 8;
    if (n == 512)
        return 9;
    if (n == 1024)
        return 10;

}

int folhas(int nEst, int m[nEst][nEst], int l, int c, int maxL, int maxC, int *contAux1, int *contAux2, int *contP, int *contB, int nMut)
{
    //printf("n = %d\n", nMut); 
    int indexArr = defineIndex(nMut);

    if ((nMut == 1))
    {
            if (m[l][c] == 0)
        {
            return 0;
        }
            else if (m[l][c] == 1)
            return 1;
    }
    else
    {   
        //nEst = N Estavel; nMut = N Mutavel
        int TL = 0; int TR = 0; int BL = 0; int BR = 0; int soma = 0;
        TL = folhas(nEst, m, l, c, nMut / 2, nMut / 2, contAux1, contAux2, contP, contB, nMut / 2); // canto superior esquerdo
        TR = folhas(nEst, m, l, c + nMut / 2, nMut / 2, nMut, contAux1, contAux2, contP, contB, nMut / 2); // canto superior direito
        BL = folhas(nEst, m, l + nMut / 2, c, nMut, nMut / 2, contAux1, contAux2, contP, contB, nMut / 2); // canto inferior esquerdo
        BR = folhas(nEst, m, l + nMut / 2, c + nMut / 2, nMut, nMut, contAux1, contAux2, contP, contB, nMut / 2); // canto inferior direito
        soma = TL + TR + BL + BR;
        
        //printf("Index: %d\n" , indexArr);
        printf("TL: %d TR: %d BL: %d BR: %d \n", TL, TR, BL, BR);
        if(TL == -1 || TR == -1 || BL == -1 || BR == -1 )
        {
            int a = (indexArr);
            if (TL == 0)
                contP[a]+= 1;
            else if (TL ==1)
                contB[a]+= 1;

            if (TR == 0)
                contP[a]+= 1;
            else if (TR == 1)
                contB[a]+= 1;

            if (BL == 0)
                contP[a]+= 1;
            else if (BL == 1)
                contB[a]+= 1;

            if (BR == 0)
                contP[a]+= 1;
            else if (BR == 1)
                contB[a]+= 1;
            return -1; //retornando -1, evidencio que o quadrante nunca será maximal de fato e que ja foram contadadas suas partes maximais
        }else if (soma == 0) //se a soma for igual a 0, é um quadrante maximal preto que deve ser comparado no proximo quadrante maior 
        {
            return 0;
        }
        else if (soma == 4) //se a soma for igual a 4, é um quadrante totalmente branco
        {
            return 1;
        }
        else
        {
            int a = (indexArr);
            if (TL == 0)
                contP[a]+= 1;
            else if (TL ==1)
                contB[a]+= 1;

            if (TR == 0)
                contP[a]+= 1;
            else if (TR == 1)
                contB[a]+= 1;

            if (BL == 0)
                contP[a]+= 1;
            else if (BL == 1)
                contB[a]+= 1;

            if (BR == 0)
                contP[a]+= 1;
            else if (BR == 1)
                contB[a]+= 1;
            return -1; //retornando -1, evidencio que o quadrante nunca será maximal de fato e que ja foram contadadas suas partes maximais
        } 
    }
}

void imprimirResp(int n, int m[n][n], int *contP, int *contB, int tamArr)
{
    for (int i = tamArr; i > 0; i--)
    {
        printf("%ix%i %i %i\n", n, n, contB[i], contP[i]);
        n = n / 2;
    }
}

bool raiz(int n, int m[n][n])
{
    double giba = log(n) / log(2);
    int tamArrR = (int)giba+1;
    int arrP[tamArrR];
    int arrB[tamArrR];
    for (int i = 0; i < tamArrR+1; i++)
    {
        printf("LOCAL ARRAY: %i\n", i);
        arrP[i] = 0;
        arrB[i] = 0;
    }

    int cont = 0;
    int cont2 = 0;

    int resp = folhas(n, m, 0, 0, 0, 0, &cont, &cont2, arrP, arrB, n);
    if(resp == 1) arrB[tamArrR] = 1; //se a resposta final é 1, a imagem é totalmente branco
    else if(resp == 0) arrP[tamArrR] = 1; //se a resposta final é 0, a imagem é totalmente preta
    imprimirResp(n, m, arrP, arrB, tamArrR);
    return false;
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
    char chToInt;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            chToInt = fgetc(arq);
            if (chToInt == '\n') chToInt = fgetc(arq);
            if (chToInt == '0') m[i][j] = 0;
            else if (chToInt == '1') m[i][j] =1;
        }
    }
    
    //printf(" \n");
    fclose(arq);
}

void preencherMatriz(int n, int m[n][n])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            m[i][j] = 0;
        }
    }
    
}

void imprimir(int n, int m[n][n])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%i", m[i][j]);
        }
        printf("\n");
    }
}


int main(int argc, char *argv[]) // necessario passar o arquivo entrada.txt como argumento -> ./modelo1 ./ins1.txt
{   
    int n = atoi(argv[1]);
    int m[n][n];
    //preencherMatriz(n, m);
    lerArq(n, m, argv[2]);
    //imprimir(n, m);
    raiz(n, m);
    return 0;
}