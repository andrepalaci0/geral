#include  <stdio.h>
#include <malloc.h>
#include <stdbool.h>


typedef struct est1
{
    int chave; //ou valor
    struct est1 *prox;
    //struct est1 *ant; para lista duplamente ligada

} NO;

typedef struct 
{
    NO* inicio;    
    //NO* sentinela; para lista com sentinela, o sent deve ser sempre o ultimo elemento da lista
} listaDin;






int main()
{


    return 0;
}