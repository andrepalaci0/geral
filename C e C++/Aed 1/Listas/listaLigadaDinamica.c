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

LISTALIGDIN* copiar(LISTALIGDIN* l1);
NO* buscaSeqOrd(int ch, LISTALIGDIN l, NO* *ant); //problema nessa funcao de busca !!!!
bool inserir(LISTALIGDIN *l1, int chaveIn);
void inicializar(LISTALIGDIN *l1);
void anexar(LISTALIGDIN *l1, int chaveAnex);
void movPFrente(LISTALIGDIN *l1, NO* p);
void destruir(LISTALIGDIN* l1);
int contar(LISTALIGDIN *l1);

int main()
{
    LISTALIGDIN l1;
    inicializar(&l1);
    return 0;
}

LISTALIGDIN* copiar(LISTALIGDIN* l1)
{
    LISTALIGDIN resposta;
    resposta.inicio = NULL;
    NO* p = l1->inicio;
    NO* ultimo = NULL;
    while(p)
    {
        NO* novo = (NO*)mallocc(sizeof(NO));
        novo->chave = p->chave;
        novo->prox = NULL;
        if(!resposta.inicio){
            resposta.inicio = novo;
        }
        if(ultimo)
        {
            ultimo->prox = novo;
        }
        ultimo = novo;
        p = p->prox;
    }
    return &resposta;
}

void destruir(LISTALIGDIN *l1)
{
    NO* p = l1->inicio;
    while(p)
    {
        NO* seguinte = p->prox;
        free(p);
    }
    l1->inicio = NULL;
}

void movPFrente(LISTALIGDIN *l1, NO* p)
{
    if(p==l1->inicio)return;
    NO* ant;
    NO* pos = buscaSeqOrd(p->chave, *l1, &ant);
    ant->prox = p->prox;
    p->prox = l1->inicio;
    l1->inicio = p;
    return;
}

bool inserir(LISTALIGDIN *l1, int chaveIn)
{
    NO* ant = NULL;
    NO* pos = buscaSeqOrd(chaveIn, *l1, &ant);
    if(pos) return false; //ja existe
    NO* novo = (NO*) malloc(sizeof(NO));
    novo->chave = chaveIn;
    if(!l1->inicio)
    {
        l1->inicio = novo;
        novo->prox = NULL;
        return true;
    }
    if(ant)
    {
        novo->prox = ant->prox;
        ant->prox = novo;
    }else{
        novo->prox = l1->inicio;
        l1->inicio = novo;
        return true;
    }
}

NO* buscaSeqOrd(int ch, LISTALIGDIN l, NO** ant) 
{
    NO* p = l.inicio;
    *ant = NULL;

    while(p) {
        
        if(p->chave >= ch) break;
        *ant = p;
        p = p->prox;
    }

    if(p) {

        if(p->chave == ch) return(p);
    }
    return(NULL);
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
    if (anterior)
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