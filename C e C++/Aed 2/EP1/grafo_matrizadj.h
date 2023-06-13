
#include <stdio.h>
#include <stdbool.h>

#ifndef GRAFO_MATRIZADJ
#define GRAFO_MATRIZADJ
#define MAXNUMVERTICES 100
#define INVALIDNODE -1 //ARESTA NULA
#define NULLEDGE -1

typedef double Peso;
typedef struct {
	Peso mat[MAXNUMVERTICES + 1][MAXNUMVERTICES + 1];
	int nNodes;
	int nEdges;
} Graph;

typedef int Pointer;

bool graphInit(Graph* graph, int nv);
bool edgeValidation(int v, Graph* graph);
bool emptyList(int v, Graph* graph);
bool edgeExists(int node1, int node2, Graph* graph);
Pointer listNext(int v, Graph* graph, Pointer current);
Pointer listFirst(int v, Graph* graph);
Pointer getNode(Pointer current, int i, Graph* graph);
Peso getEdgeWeight(int node1, int node2, Graph* graph);
Peso getWeight(Peso peso[], int antecessores[], int node1, int node2);
int maxNode(bool visitados[], int nNodes, Peso pesos[]);
int getDest(Pointer current, Graph* graph);
void edgeInsert (int node1, int node2, Peso peso, Graph* graph);
void freeGraph(Graph* graph);
void printGraph (Graph* graph, int nodes);
void printOutText(Peso resp, FILE* saida);
void maxTree(int nNodes, int node1, int node2, Graph* graph, FILE* saida);
void iteration(int aux, bool visitados[], int antecessores[], Peso pesos[], Graph *graph, int i);
#endif