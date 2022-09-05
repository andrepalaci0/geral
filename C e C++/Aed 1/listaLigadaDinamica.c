#include <stdio.h>
#include <stdlib.h> //p usar malloc e free 
#include <stdbool.h>

// obter no tem o equivalente (em aloc dinamica):
//  NO* p = (NO*) malloc(sizeof(NO));

typedef struct est
{
    int chave;
    struct est *prox;
} NO;

typedef struct
{
    NO *inicio;
} LISTALIGDIN;

void inicializar(LISTALIGDIN *l1);
void anexar(LISTALIGDIN *l1, int chaveAnex);
int contar(LISTALIGDIN *l1);

int main()
{
    LISTALIGDIN l1;
    inicializar(&l1);
    return 0;
}

void inicializar(LISTALIGDIN *l1)
{
    l1->inicio = NULL;
}

void anexar(LISTALIGDIN *l1, int chaveAnex)
{
    NO *novo = (NO *)malloc(sizeof(NO));
    novo->chave = chaveAnex;
    novo->prox = NULL;
    NO *p = l1->inicio;
    NO *anterior = NULL;
    while (p)
    { // trecho de codigo que procura o fim da lista
        anterior = p;
        p = p->prox;
    }
    if (anterior)x
        anterior->prox = novo;
    else
        l1->inicio = novo;
}

int contar(LISTALIGDIN *l1)
{
    int contagem = 0;
    NO *p = l1->inicio;
    while (p) // enquanto P existir, faca.
    {
        contagem++;
        p = p->prox;
    }
}