#include "grafo_direcionado_matrizadj.h"
#include <stdio.h>

bool inicializaGrafo(Grafo* grafo, int nv) {
	if(nv > MAXNUMVERTICES) {
		fprintf(stderr, "ERRO na chamada de inicializaGrafo: Numero de vertices maior que o maximo permitido de %d\n", MAXNUMVERTICES);
		return false;
	}
	if(nv < 0) {
		fprintf(stderr, "ERRO na chamada de inicializaGrafo: Numero de vertices deve ser positivo");
		return false;
	}
	grafo->numVertices = nv;
	grafo->numArestas = 0;
	for(int i = 0; i < grafo->numVertices; i++) {
		for(int j = 0; j < grafo->numArestas; j++) {
			grafo->mat[i][j] = AN;
		}
	}
	return true;
}

void imprimeGrafo(Grafo* grafo) {
	for(int i = 0; i < grafo->numVertices; i++) {
		printf("%d: ", i);
		for(int j = 0; j < grafo->numVertices; j++) {
			printf("%d ", grafo->mat[i][j]);
		}
		printf("\n");
	}
}

bool verificaValidadeVertice(int v, Grafo* grafo) {
	if(v > grafo->numVertices) {
		fprintf(stderr, "ERRO: Numero de vertices (%d) maior que o numero total de vertices (%d)\n", v, grafo->numVertices);
		return false;
	}
	if(v <= 0) {
		fprintf(stderr, "ERRO: Numero do vertice (%d) deve ser positivo\n", v);
		return false;
	}
	return true;
}

void insereAresta(int v1, int v2, Peso peso, Grafo* grafo) {
	if(!(verificaValidadeVertice(v1, grafo) && verificaValidadeVertice(v2, grafo)))
		return;
	grafo->mat[v1][v2] = peso;
	grafo->numArestas++;
}

bool existeAresta(int v1, int v2, Grafo* grafo) {
	return (grafo->mat[v1][v2] == AN ? true : false);
}

Peso obtemPesoAresta(int v1, int v2, Grafo* grafo) {
	return grafo->mat[v1][v2];
}

bool removeAresta(int v1, int v2, Peso* peso, Grafo* grafo) {
	if(!(verificaValidadeVertice(v1, grafo) && verificaValidadeVertice(v2, grafo)))
		return false;
	
	/* se aresta existe */
	if(grafo->mat[v1][v2] != AN) {
		*peso = grafo->mat[v1][v2];
		grafo->mat[v1][v2] = AN;
		grafo->numArestas--;
		return true;
	}
	return false;
}

bool listaAdjVazia(int v, Grafo* grafo) {
	if(!verificaValidadeVertice(v, grafo))
		return true;

	for(int i = 0; i <= grafo->numVertices; i++)
		if(grafo->mat[v][i] != AN) return false;

	return true;
}

int proxListaAdj(int v, Grafo* grafo, int atual) {
	if(!verificaValidadeVertice(v, grafo))
		return VERTICE_INVALIDO;
	atual++;

	while((atual <= grafo->numVertices) && (grafo->mat[v][atual] == AN)) atual++;

	if(atual > grafo->numVertices) return VERTICE_INVALIDO;

	return atual;
}

void liberaGrafo(Grafo* grafo) {}
