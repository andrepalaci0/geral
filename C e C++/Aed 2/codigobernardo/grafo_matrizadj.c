//#include <stdio.h>
#include "grafo_matrizadj.h"
//#include <limits.h>
//#include <float.h>

#define BRANCO 0
#define CINZA 1
#define PRETO 2

bool inicializaGrafo (Grafo* grafo, int nv) {
    int i,j;
    if(nv > MAXNUMVERTICES) {return false;}
    if(nv <= 0) { return false;}
    grafo->numVertices = nv;
    grafo->numArestas = 0;
    for (i = 0; i <= grafo->numVertices; i++) {
        for(j=0; j <= grafo->numVertices; j++) {
            grafo->mat[i][j] = ArestaNula;
        }
    }
    return true;
}

bool verificaValidadeVertice(int v, Grafo* grafo) {
    if(v > grafo->numVertices) {return false;}
    if(v < 0) {return false;}
    return true;
}

void insereAresta (int v1, int v2, Peso peso, Grafo* grafo) {
    if (!(verificaValidadeVertice(v1, grafo) && verificaValidadeVertice(v2, grafo))) {return;}
    grafo->mat[v1][v2] = peso;
    grafo-> mat[v2][v1] = peso;
    grafo->numArestas++;
}

bool listaAdjVazia(int v, Grafo* grafo) {
    if(!verificaValidadeVertice(v, grafo)) {
        return true;
    }
    int i;
    for (i=0;i<=grafo->numVertices; i++) {
        if(grafo->mat[v][i] != ArestaNula) {return false;}
    }
    return true;
}

bool existeAresta(Grafo* grafo, int v1, int v2) {
    if(!verificaValidadeVertice(v1,grafo) || !verificaValidadeVertice(v2, grafo)) {return false;}
    if(grafo->mat[v1][v2] == ArestaNula) {return false;}
    return true;
}

Peso obtemPesoAresta(Grafo* grafo, int v1, int v2) {
    if(!existeAresta(grafo, v1, v2)) {return ArestaNula;}
    return grafo->mat[v1][v2];
}

Apontador proxListaAdj(int v, Apontador atual, Grafo* grafo) {
    if(!verificaValidadeVertice(v,grafo)) {return ApontadorNulo;}
    for(int i = 1; i<= grafo->numVertices - atual; i++) { // 1 2 3 4 5
        if(grafo->mat[v][atual+i] != ApontadorNulo) {return (atual+i);}
    }
    return ApontadorNulo;
}

Apontador primeiroListaAdj(int v, Grafo* grafo) {
    return (proxListaAdj(v, -1, grafo));
}

int obtemVerticeDestino(Apontador atual, Grafo* grafo) {
    return atual;
}





// Peso getMinWeigth(int u, int v, int antecessor[], Peso weigths[]) { // antecessor 0 1 2 3 4   -   
//     Peso h;
//     if (u == v) { h = weigths[v]; return h; }
//     else {
//         h = getMinWeigth(u, antecessor[v], antecessor, weigths);
//         if(weigths[v] < h) { h = weigths[v];}
//     }
//     return h;
// }

// int findMaxVertex(bool visited[], Peso weights[], int numVertices)
// {
 
//     // Stores the index of max-weight vertex
//     // from set of unvisited vertices
//     int index = -1;
 
//     // Stores the maximum weight from
//     // the set of unvisited vertices
//     Peso maxW = FLT_MIN;
 
//     // Iterate over all possible
//     // nodes of a graph
//     for (int i = 0; i <= numVertices; i++) {
 
//         // If the current node is unvisited
//         // and weight of current vertex is
//         // greater than maxW
//         if (visited[i] == false
//             && weights[i] > maxW) {
 
//             // Update maxW
//             maxW = weights[i];
 
//             // Update index
//             index = i;
//         }
//     }
//     return index;
// }
 
// // Utility function to find the maximum
// // spanning tree of graph

// // Function to find the maximum spanning tree
// void maximumSpanningTree(int numVertices, Grafo* grafo, int v1, int v2, FILE* outfile) {
 
//     // visited[i]:Check if vertex i
//     // is visited or not
//     bool visited[numVertices+1];
 
//     // weights[i]: Stores maximum weight of
//     // graph to connect an edge with i
//     Peso weights[numVertices+1];
 
//     // parent[i]: Stores the parent node
//     // of vertex i
//     int parent[numVertices+1];
 
//     // Initialize weights as -INFINITE,
//     // and visited of a node as false
//     for (int i = 0; i <= numVertices; i++) {
//         visited[i] = false;
//         weights[i] = FLT_MIN;
//     }
 
//     weights[v1] = FLT_MAX;
//     parent[v1]= -1;
//     // Include 1st vertex in
//     // maximum spanning tree
//     /*
//     for(int i =0; i <= numVertices; i++) {
//         if(!listaAdjVazia(i, grafo)) {
//             weights[i] = FLT_MAX;
//             parent[i] = -1;
//             break; 
//             }
//     } */
    
 
//     // Search for other (V-1) vertices
//     // and build a tree
//     for (int i = 0; i < numVertices; i++) {
 
//         // Stores index of max-weight vertex
//         // from a set of unvisited vertex
//         int maxVertexIndex
//             = findMaxVertex(visited, weights, numVertices);
 
//         // Mark that vertex as visited
//         visited[maxVertexIndex] = true;
 
//         // Update adjacent vertices of
//         // the current visited vertex
//         for (int j = 0; j <= numVertices; j++) {
 
//             // If there is an edge between j
//             // and current visited vertex and
//             // also j is unvisited vertex
//             if (grafo->mat[maxVertexIndex][j] != AN //criar função obtemPeso
//                 && visited[j] == false) {
 
//                 // If graph[v][x] is
//                 // greater than weight[v]
//                 if (grafo->mat[maxVertexIndex][j] > weights[j]) {
 
//                     // Update weights[j]
//                     weights[j] = grafo->mat[maxVertexIndex][j];
 
//                     // Update parent[j]
//                     parent[j] = maxVertexIndex;
//                 }
//             }
//         }
//     }

//     Peso h = getMinWeigth(v1, v2, parent, weights);
//     if (h >= 4.5) {fprintf(outfile,"4.5\n"); return;}
//     if (h >= 4) {fprintf(outfile,"4.0\n"); return;}
//     if (h >= 3.5) {fprintf(outfile,"3.5\n"); return;}
//     if (h >= 3) {fprintf(outfile,"3.0\n"); return;}
//     if (h >= 2.5) {fprintf(outfile,"2.5\n"); return;}
//     else {printf("Tamanhos de carreta maiores que o limite de %f metros", h);}
 
    
// }

// int main(int numargs, char *arg[]) {
//     FILE* ptr = fopen("entrada.txt", "r");
//         if (ptr == NULL) {
//             printf("no such file.");
//             return 0;
//         }
//     Grafo grafo; 
//     int numVertices, numArestas, numConsultas;
//     fscanf(ptr, "%d", &numVertices);
//     fscanf(ptr, "%d", &numArestas);
//     fscanf(ptr, "%d", &numConsultas);
//     inicializaGrafo(&grafo, numVertices);
//     for(int i = 0; i<numArestas; i++) {
//         int v1,v2;
//         Peso p;
//         fscanf(ptr, "%d", &v1);
//         fscanf(ptr, "%d", &v2);
//         fscanf(ptr, "%f", &p);
//         insereAresta(v1,v2,p,&grafo);
//     }

//     FILE* outfile = fopen("saida.txt","w");
//     if (outfile == NULL) {
//             printf("File can't be opened.");
//             return 0;
//     }
//     printf("USANDO MATRIZ\n");
//     for(int i = 0; i < numConsultas; i++) {
//         int v1,v2;
//         fscanf(ptr, "%d", &v1);
//         fscanf(ptr, "%d", &v2);
//         maximumSpanningTree(numVertices, &grafo, v1,v2, outfile);
//     }
//     fclose(outfile);
// }