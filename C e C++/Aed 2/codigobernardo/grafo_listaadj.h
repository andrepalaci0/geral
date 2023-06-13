#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#define ArestaNula -1
#define ApontadorNulo NULL


typedef float Peso;

typedef struct str_aresta {
    int vdest;
    Peso peso;
    struct str_aresta* prox;
} Aresta;

typedef Aresta* Apontador;

typedef struct {
    Apontador* listaadj;
    int numVertices;
    int numArestas;
} Grafo;



bool inicializaGrafo (Grafo* grafo, int nv);
bool verificaValidadeVertice(int v, Grafo* grafo);
void insereAresta (int v1, int v2, Peso peso, Grafo* grafo);
bool listaAdjVazia(int v, Grafo* grafo);
bool existeAresta(Grafo* grafo, int v1, int v2);
Peso obtemPesoAresta(Grafo* grafo, int v1, int v2);
Apontador proxListaAdj(int v, Apontador atual, Grafo* grafo);
Apontador primeiroListaAdj(int v, Grafo* grafo);
int obtemVerticeDestino(Apontador atual, Grafo* grafo);