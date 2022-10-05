#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>



void lerArq(int n, int m[n][n], char* str);
void imprimir(int n, int m[n][n]);
void preencherMatriz(int n, int m[n][n]);
void dividirConquistarIni(int n, int m[n][n]);


void dividirConquistarIni(int n, int m[n][n])
{


    return false;
}


void lerArq(int n, int m[n][n], char* arg )//le o arquivo e preenche a matriz, transformando os chars em ints;
{
    //ZERO = PRETOS
    //UM = BRANCOS
    FILE* arq = fopen(arg , "r");
    if(arq == NULL) printf("Arquivo ausente\n");
    else printf("Arquivo aberto em leitura\n");
    int chToInt;
    int i = 0;
    int j = 0;                    
    while((chToInt = fgetc(arq)) != EOF)
    {
        printf("%c", chToInt);
        m[i][j] = chToInt - 48; //transforma o ASCII do char em int. 48 = 0
        if(j == n){
            i++;
            j = 0;
        }else j++;
    }
    printf(" \n");
    fclose(arq);
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

//LEMBRETE: definir (N = *argv[1] - 48) !

int main(int argc, char* argv[]) //necessario passar o arquivo entrada.txt como argumento -> ./modelo1 ./ins1.txt
{
    int n = 3;    
    int m[n][n];
    //preencherMatriz(n, m);
    lerArq(n, m, argv[1]);
    imprimir(n, m);
    return 0;
}