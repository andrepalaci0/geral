#include <stdbool.h>
#include <stdio.h>
#ifndef GRAFO_LISTAADJ
#define GRAFO_LISTAADJ
#define INVALIDNODE NULL //vertice invalido
#define NULLEDGE 0 //aresta nula


typedef double Peso;

typedef struct edge{
    int vdest; //vertice destino
    Peso peso;
    struct edge* prox;
} Edge;

typedef struct {
    Edge** list;
    int nNodes;
    int nEdges;
} Graph;

typedef Edge* Pointer;

bool graphInit(Graph* graph, int nv);
bool edgeValidation(int v, Graph* graph);
bool emptyList(int v, Graph* graph);
bool edgeExists(int node1, int node2, Graph* graph);
Pointer listNext (int v, Graph* graph, Pointer current);
Pointer listFirst(int v, Graph graph);
Pointer getNode(Pointer current, int i, Graph* graph);
Peso getEdgeWeight(int node1, int node2, Graph* graph);
Peso getWeight(Peso peso[], int antecessores[], int node1, int node2);
int maxNode(bool visitados[], int nNodes, Peso pesos[]);
int getDest(Pointer current, Graph* graph);
void edgeInsert (int node1, int node2, Peso peso, Graph* graph);
void freeGraph(Graph* graph);
void printGraph(Graph* graph, int nodes);
void printOutText(Peso resp, FILE* saida);
void maxTree(int nNodes, int node1, int node2, Graph* graph, FILE* saida);

#endif