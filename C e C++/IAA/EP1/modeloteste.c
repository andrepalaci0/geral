#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>


void lerArq(int n, int m[n][n], char* str);
void imprimir(int n, int m[n][n]);
void preencherMatriz(int n, int m[n][n]);
void dividirConquistarIni(int n, int m[n][n]);


bool folhas(int n, int m[n][n], int l, int c,int maxL, int maxC, int* cont)
{       
    
    if( (n == 0) || *cont == 1){
        *cont++;
        if(m[l][c] == 0){
            return true;
        }else if(m[l][c] == 1) return false;
    }else{
        if(folhas(n/2,m, 0, 0, n/2, n/2, cont) && folhas(n/2,m, 0, n/2, n/2, n, cont) && folhas(n/2,m, n/2, 0, n, n/2, cont) && folhas(n/2,m, n/2, n/2, n, n, cont))
        {

           printf("%ix%i %i  %i MAXIMAL \n", n, n, *cont, *cont);

        }else printf("%ix%i %i  %i NAO MAXIMAL\n", n, n, *cont, *cont);
        
        //folhas(n,m, 0, 0, n/2, n/2, cont); //canto superior esquerdo
        //folhas(n,m, 0, n/2, n/2, n, cont); //canto superior direito
        //folhas(n,m, n/2, 0, n, n/2, cont); //canto inferior esquerdo
        //folhas(n,m, n/2, n/2, n, n, cont); //canto inferior direito
    }
}


bool raiz(int n, int m[n][n])
{
    double giba = log(n)/log(2);
    int tamArrR = (int) giba;
    int arrR[tamArrR];
    int cont = 0;
    return folhas(n, m, n, n, n, n,&cont);    

    return false;
}


void lerArq(int n, int m[n][n], char* str) //le o arquivo e preenche a matriz, transformando os chars em ints;
{
    //ZERO = PRETOS
    //UM = BRANCOS
    FILE* arq = fopen(str , "r");
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
    int n = 4;    
    int m[n][n];
    //preencherMatriz(n, m);
    lerArq(n, m, argv[1]);
    raiz(n, m);
    imprimir(n, m);
    return 0;
}