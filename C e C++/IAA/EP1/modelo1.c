#include <stdio.h>
#include <stdbool.h>

//entender melhor como se relacionam ponteiros e matrizes


void lerArq(int n, int m[n][n]);
void imprimir(int n, int m[n][n]);
void preencherMatriz(int n, int m[n][n]);


void lerArq(int n, int m[n][n])
{
    FILE* arq = fopen("USP/Codigos/C e C++/IAA/EP1/ins1.txt" , "r");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            m[i][j] = fscanf(arq, "%i" , &m[i][j]);
        }
        
    }
    

}

void preencherMatriz(int n, int m[n][n])
{
    int a = 7;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if(i > j) m[i][j] = a; 
            else m[i][j] = 0;  
        }
    }
}

void imprimir(int n, int m[n][n])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%i ", m[i][j]);
        }
        printf("\n");
    }
    
}

int main()
{
    int n = 7;    
    int m[n][n];
    //m[0][0] = 1; m[0][1] = 2; m[1][0] = 3; m[1][1] = 4;
    //preencherMatriz(n, m);
    lerArq(n, m);
    imprimir(n, m);
    return 0;
}