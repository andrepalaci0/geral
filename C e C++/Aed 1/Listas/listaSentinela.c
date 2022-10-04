#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


typedef struct
{
    int chave;
    struct est *prox;
} NO;

typedef struct
{
    NO* inicio;
    NO* sent;
} LISTASENT;

void inicializar(LISTASENT* l1);
void extrair(LISTASENT* l1);

int main()
{

    return 0;
}

void extrair(LISTASENT* l1)
{
    NO* p = l1->inicio;
    while(p != l1->sent)
    {
        printf("%d", p->chave);
        p = p->prox;
    }
}

void inicializar(LISTASENT* l1)
{
    l1->sent = (NO*)malloc(sizeof(NO));
    l1->inicio = l1->sent;
}