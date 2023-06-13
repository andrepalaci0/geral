#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "grafo_direcionado_listaadj.h"

bool incializaGrafo(Grafo* grafo, int nv) {
	if(nv <= 0) {
		fprintf(stderr, "Erro, o numero de vertices deve ser positivo\n");
		return false;
	}
	grafo->numVertices = nv;

	/* calloc ja inicializa com zeros */
	if(!(grafo->listaadj = (Aresta**) calloc(nv + 1, sizeof(Aresta*)))) {
		fprintf(stderr, "Erro, falha na alocacao de memoria na funcao inicializar\n");
		return false;
	}

	grafo->numArestas = 0;
	return true;
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

bool listaAdjVazia(int v, Grafo* grafo) {
	if(!verificaValidadeVertice(v, grafo))
		return false;
	return (grafo->listaadj[v] == NULL);
}

Apontador proxListaAdj(int v, Grafo *grafo, Apontador atual) {
	if(atual == NULL) {
		fprintf(stderr, "atual == NULL\n");
		return VERTICE_INVALIDO;
	}
	return (atual->prox);
}

Apontador primeiroListaAdj(int v, Grafo* grafo) {
	return (grafo->listaadj[v]);
}

bool existeAresta(int v1, int v2, Grafo* grafo) {
	if(!(verificaValidadeVertice(v1, grafo) && verificaValidadeVertice(v2, grafo))) 
		return false;

	Apontador q = grafo->listaadj[v1];
	while((q != NULL) && (q->vdest != v2))
		q = q->prox;

	if(q != NULL)
		return true;
	return false;
}

Peso obtemPesoAresta(int v1, int v2, Grafo* grafo) {
	if(!(verificaValidadeVertice(v1, grafo) && verificaValidadeVertice(v2, grafo)))
		return AN;
	
	Apontador q = grafo->listaadj[v1];
	while((q != NULL) && (q->vdest != v2))
		q = q->prox;

	if(q != NULL)
		return q->peso;
	return AN;
}

void insereAresta(int v1, int v2, Peso peso, Grafo* grafo) {
	if(!(verificaValidadeVertice(v1, grafo) && verificaValidadeVertice(v2, grafo)))
		return;
	
	Apontador p;
	if(!(p = (Apontador) calloc(1, sizeof(Aresta)))) {
		fprintf(stderr, "ERRO: Falha na alocacao de memoria na funcao insereAresta\n");
		return;
	}

	p->vdest = v2;
	p->peso = peso;
	p->prox = grafo->listaadj[v1];
	grafo->listaadj[v1] = p;
	grafo->numArestas++;
}

bool removeArestaObtendoPeso(int v1, int v2, Peso* peso, Grafo* grafo) {
	return true;
}

void liberaGrafo(Grafo* grafo) {
	return;
}

void imprimeGrafo(Grafo* grafo) {
	Apontador q;
	for(int i = 0; i < grafo->numVertices; i++) {
		printf("v%d: ", i + 1);
		q = grafo->listaadj[i];
		while(q != NULL) {
			printf("(adj%d%d, peso)");
		}
	}
	return;
}
