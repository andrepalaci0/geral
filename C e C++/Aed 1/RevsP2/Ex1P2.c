#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

//Seja uma matriz esparça em listas cruzadas
//Escreva um algoritmo que cire uma lista ligada contendo todos os 
//elementos da sua diagonal principal (incluindo os zeros)
//retornando seu ponteiro de inicio

#define MAXLin 100
#define MAXCol 100

typedef struct s
{
    int valor;
    int l;
    int c;
    struct s proxL;
    struct s proxC;

}NO;

typedef struct {
    NO linhas[MAXLin];
    NO colunas[MAXCol];

}matriz;


NO* listaDiagonal(matriz* m)
{
    NO* resp = (NO*)malloc(sizeof(NO));
    if(m->linhas[0].l == NULL && m->colunas[0].c == NULL)
    {
        resp->valor = 0;
        resp->l = 0;
        resp->c = 0;
    }else{
        resp->valor = m->linhas[0].valor;
    }



}


int main()
{

    int x = 0;

    return 0;
}
