#include <stdio.h>
#include <stdbool.h>

#define MAXNUMVERTICES 100
#define AN -1 //aresta nula, ausencia de aresta

typedef int Peso;

typedef struct
{
    Peso mat[MAXNUMVERTICES+1][MAXNUMVERTICES+1];
    int numVertices;
    int numArestas;
} Grafo;

bool inicializaGrafo(Grafo* grafo, int nv) //nv == num de vertices
{ 
    if(nv > MAXNUMVERTICES){
        fprinf(stderr, "ERRO na inicilizacao de grafo, num de vertices maior que o max de %d\n",  MAXNUMVERTICES);
        return false;
    }
    if (nv <= 0)
    {
        fprintf(stderr, "ERRO na inicialicao do grafo, num de vertices deve ser positivo\n");
    }
    grafo->numVertices = nv; //VERTICE == NODULO, VALOR ATRIBUIDO AO GRAFO
    grafo->numArestas = 0;  //ARESTA == LINHA/CONEXAO DO GRAFO A OUTROS
    for(int i = 0; i <= grafo->numVertices; i++){
        for(int j = 0; j <= grafo->numVertices; j++)
        grafo->mat[i][j] = AN;
    }
    return true;
}

int main()
{
    int giba = 0;
}