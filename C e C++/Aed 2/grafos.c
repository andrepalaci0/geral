#include <stdio.h>
#include <stdbool.h>

#define MAXNUMVERTICES 100

typedef int Peso;

typedef struct
{
    Peso mat[100][100];
    int numVertices;
    int numArestas;
} Grafo;

bool inicializaGrafo(Grafo *grafo, int nv)
{
    int i, j;
    if(nv > MAXNUMVERTICES){
        fprintf(stderr, "ERRO na chamada de inicializaGrafo: Numero de vertices maior que o perimitido \n");
        return false;
    }
    if( nv <= 0){
        
    }
}

int main()
{
    int giba = 0;
}