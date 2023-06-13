#include "grafo_listaadj.h"
//#include "grafo_matrizadj.h"

Peso getMinWeigth(int u, int v, int antecessor[], Peso weigths[]) { 
    Peso h;
    if (u == v) { h = weigths[v]; return h; }
    else {
        h = getMinWeigth(u, antecessor[v], antecessor, weigths);
        if(weigths[v] < h) { h = weigths[v];}
    }
    return h;
}

int findMaxVertex(bool visited[], Peso weights[], int numVertices)
{
 
    // Stores the index of max-weight vertex
    // from set of unvisited vertices
    int index = -1;
 
    // Stores the maximum weight from
    // the set of unvisited vertices
    Peso maxW = FLT_MIN;
 
    // Iterate over all possible
    // nodes of a graph
    for (int i = 0; i <= numVertices; i++) {
 
        // If the current node is unvisited
        // and weight of current vertex is
        // greater than maxW
        if (visited[i] == false
            && weights[i] > maxW) {
 
            // Update maxW
            maxW = weights[i];
 
            // Update index
            index = i;
        }
    }
    return index;
}

void maximumSpanningTree(int numVertices, Grafo* grafo, int v1, int v2, FILE* outfile) {
 

    Apontador atual;

    // visited[i]:Check if vertex i
    // is visited or not
    bool visited[numVertices+1];
 
    // weights[i]: Stores maximum weight of
    // graph to connect an edge with i
    Peso weights[numVertices+1];
 
    // parent[i]: Stores the parent node
    // of vertex i
    int parent[numVertices+1];
 
    // Initialize weights as -INFINITE,
    // and visited of a node as false
    for (int i = 0; i <= numVertices; i++) {
        visited[i] = false;
        weights[i] = FLT_MIN;
    }
 
    // Include 1st vertex in
    // maximum spanning tree
    weights[v1] = FLT_MAX;
    parent[v1] = -1;
 
    // Search for other (V-1) vertices
    // and build a tree
    for (int i = 0; i < numVertices; i++) {
 
        // Stores index of max-weight vertex
        // from a set of unvisited vertex
        int maxVertexIndex
            = findMaxVertex(visited, weights, numVertices);
 
        // Mark that vertex as visited
        visited[maxVertexIndex] = true;
        
        // Update adjacent vertices of
        // the current visited vertex
        atual = primeiroListaAdj(maxVertexIndex, grafo); // aresta atual maxvertex -> atual
        
        while(atual != ApontadorNulo) {
            int vdest = obtemVerticeDestino(atual, grafo);
            if(visited[vdest] == false ) {
                if(obtemPesoAresta(grafo, maxVertexIndex, vdest) > weights[vdest]) {
                    weights[vdest] = obtemPesoAresta(grafo, maxVertexIndex, vdest);
                    parent[vdest] = maxVertexIndex;
                }
            }
            atual = proxListaAdj(maxVertexIndex, atual, grafo);
        }
    }

    Peso h = getMinWeigth(v1, v2, parent, weights);
    if (h >= 4.5) {fprintf(outfile,"4.5\n"); return;}
    if (h >= 4) {fprintf(outfile,"4.0\n"); return;}
    if (h >= 3.5) {fprintf(outfile,"3.5\n"); return;}
    if (h >= 3) {fprintf(outfile,"3.0\n"); return;}
    if (h >= 2.5) {fprintf(outfile,"2.5\n"); return;}
    else {printf("Tamanhos de carreta maiores que o limite de %f metros", h);}
    fclose(outfile);
    
}

int main(int numargs, char *arg[]) {
    FILE* ptr = fopen("entrada.txt", "r");
        if (ptr == NULL) {
            printf("no such file.");
            return 0;
        }
    Grafo grafo; 
    int numVertices, numArestas, numConsultas;
    fscanf(ptr, "%d", &numVertices);
    fscanf(ptr, "%d", &numArestas);
    fscanf(ptr, "%d", &numConsultas);
    inicializaGrafo(&grafo, numVertices);
    for(int i = 0; i<numArestas; i++) {
        int v1,v2;
        Peso p;
        fscanf(ptr, "%d", &v1);
        fscanf(ptr, "%d", &v2);
        fscanf(ptr, "%f", &p);
        insereAresta(v1,v2,p,&grafo);
    }

    FILE* outfile = fopen("saida.txt","w");
    if (outfile == NULL) {
            printf("File can't be opened.");
            return 0;
    }
    //printf("USANDO LISTA\n");
    for(int i = 0; i < numConsultas; i++) {
        int v1,v2;
        fscanf(ptr, "%d", &v1);
        fscanf(ptr, "%d", &v2);
        maximumSpanningTree(numVertices, &grafo, v1,v2, outfile);
    }
    fclose(outfile);
}