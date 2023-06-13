#include <stdbool.h>

#define VERTICE_INVALIDO NULL /* numero de vertice invalido ou ausente */
#define AN -1 /* aresta nula, ou inexistente */

typedef int Peso;

typedef struct str_aresta {
	int vdest;
	Peso peso;
	struct str_aresta* prox;
} Aresta;

typedef struct {
	Aresta** listaadj;
	int numVertices;
	int numArestas;
} Grafo;

typedef Aresta* Apontador;
