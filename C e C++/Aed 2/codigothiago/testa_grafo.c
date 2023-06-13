#include <stdio.h>
//#include "grafo_listaadj.h"
#include "grafo_direcionado_matrizadj.h"

int main() {
	Grafo g1;
	int numVertices;
	do {
		printf("Digite o numero de vertices do grafo\n");
		scanf("%d", &numVertices);
	} while(!inicializaGrafo(&g1, numVertices));
	insereAresta(3, 1, 1, &g1);
	insereAresta(2, 4, 1, &g1);
	insereAresta(4, 1, 1, &g1);
	imprimeGrafo(&g1);

	return 0;
}
