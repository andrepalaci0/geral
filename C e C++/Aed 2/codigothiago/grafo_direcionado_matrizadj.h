#include <stdbool.h>

#define MAXNUMVERTICES 100
#define AN -1 /* aresta nula ou nao existente */
#define VERTICE_INVALIDO -1 /* numero de vertice invalido ou ausente */

typedef int Peso;
typedef struct {
	Peso mat[MAXNUMVERTICES + 1][MAXNUMVERTICES + 1];
	int numVertices;
	int numArestas;
} Grafo;

typedef int Apontador;

bool inicializaGrafo(Grafo* grafo, int nv);
void imprimeGrafo(Grafo* grafo);
bool verificaValidadeVertice(int v, Grafo* grafo);
void insereAresta(int v1, int v2, Peso peso, Grafo* grafo);
bool existeAresta(int v1, int v2, Grafo* grafo);
Peso obtemPesoAresta(int v1, int v2, Grafo* grafo);
bool removeAresta(int v1, int v2, Peso* peso, Grafo* grafo);
bool listaAdjVazia(int v, Grafo* grafo);
int proxListaAdj(int v, Grafo* grafo, int atual);
void liberaGrafo(Grafo* grafo);
