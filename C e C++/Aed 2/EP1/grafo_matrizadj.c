#include "grafo_matrizadj.h"
#include <float.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>



bool graphInit(Graph *graph, int nv) {
  if (nv > MAXNUMVERTICES) {
    fprintf(stderr, "ERRO INICIALIZACAO, N VERTICES EXCEDE LIMITEE");
    return false;
  }
  if (nv < 0) {
    fprintf(stderr, "ERRO INICIALIZAÇAO, N VERTICES NEGATIVO");
    return false;
  }
  graph->nEdges = 0;
  graph->nNodes = nv;

  for (int i = 0; i < graph->nNodes; i++) {
    for (int j = 0; j < graph->nEdges; j++) {
      graph->mat[i][j] = NULLEDGE;
    }
  }
  return true;
}

void edgeInsert(int node1, int node2, Peso peso, Graph *graph) {
  if ((node1 == node2) && peso > 0) {
    printf("achei");
    return;
  }
  graph->nEdges++;
  graph->mat[node1][node2] = peso;
  graph->mat[node2][node1] = peso;
}

bool edgeValidation(int v, Graph *graph) {
  if (v > graph->nNodes) {
    fprintf(stderr, "ERRO NUM DE VERTICES INVALIDO\n");
    return false;
  }
  if (v < 0) {
    fprintf(stderr, "ERRO NUM DE VERTICES DEVE SER MAIOR QUE ZERO\n");
    return false;
  }
  return true;
}

Pointer getNode(Pointer current, int j, Graph* graph)
{
  Pointer out = listNext(j, graph, current);
  return out;
}

Peso getEdgeWeight(int node1, int node2, Graph *graph) {
  return graph->mat[node1][node2];
}

int getDest(Pointer current, Graph* graph)
{
  return current;
}

int listNext(int j, Graph *graph, Pointer current) {
  int aux = graph->nNodes - current;
  for (int i = 1; i <= aux; i++)
  {
    if(graph->mat[j][current+1] != INVALIDNODE)
    {
      int out = current + i;
      return out;
    } 
  }
  return -1;
}

bool edgeExists(int node1, int node2, Graph *graph) {
  return graph->mat[node1][node2] == NULLEDGE;
}

// Peso getWeight(Peso pesos[], int *antecessores, int node1, int node2) {
//   Peso aux;
//   //printf("node1: %d, node2: %d", node1, node2);
//   if (node1 == node2) {
//     aux = pesos[node2];
//     return aux;
//   } else {
//     aux = getWeight(pesos, antecessores, node1, antecessores[node2]);
//     if (aux > pesos[node2]) {
//       aux = pesos[node2];
//     }
//   }
//   return aux;
// }
//
// int maxNode(bool visitados[], int nNodes, Peso pesos[]) {
//   // printf("ENTROU MAX NODE\n");
//   int aux = NULLEDGE; //-1
//   Peso pesoMax = FLT_MIN;
//   // printf("%f" , pesoMax);
//   for (int i = 0; i <= nNodes; i++) {
//     if (visitados[i] == false && pesoMax < pesos[i]) {
//       pesoMax = pesos[i];
//       aux = i;
//     }
//   }
//   return aux;
// }

void printGraph(Graph *graph, int nodes) {
  for (int i = 0; i < graph->nNodes; i++) {
    for (int j = 0; j < graph->nNodes; j++) {
      printf("%.1f", graph->mat[i][j]);
    }
    printf("\n");
  }
}

// void printOutText(Peso resp, FILE *saida) {
//   double out;
//   // printf("%f\n" , resp);
//   if (resp >= 4.5)
//     out = 4.5;
//   else if (resp < 4.5 && resp >= 4.0)
//     out = 4.0;
//   else if (resp < 4.0 && resp >= 3.5)
//     out = 3.5;
//   else if (resp < 3.5 && resp >= 3.0)
//     out = 3.0;
//   else if (resp < 3.0 && resp >= 2.5)
//     out = 2.5;
//   else
//     printf("ERRO: Tamanho invalido");
//
//   printf("%f\n", out);
//   fprintf(saida, "%.1f\n", out);
//   fflush(saida);
// }

// void maxTree(int nNodes, int node1, int node2, Graph *graph, FILE *saida) {
//   int tamArray = nNodes + 1;
//   Peso pesos[tamArray];
//   bool visitados[tamArray];
//   int antecessores[tamArray];
//
//   for (int i = 0; i <= nNodes; i++) {
//     pesos[i] = FLT_MIN;
//     visitados[i] = false;
//   }
//   antecessores[node1] = -1;
//   pesos[node1] = FLT_MAX;
//   for (int i = 0; i < nNodes; i++) {
//     fflush(saida);
//     // printf("entrou no for\n");
//     int aux = maxNode(visitados, nNodes, pesos);
//     printf("maxNode: %d\n", aux);
//
//     visitados[aux] = true;
//     //printf("%d %d %f \n", visitados[i], nNodes, pesos[i]);
//
//     for (int j = 0; j < nNodes; j++) {
//       if (visitados[j] == false && graph->mat[aux][j] != NULLEDGE) {
//         if (graph->mat[aux][j] > pesos[j]) {
//           antecessores[j] = aux;
//           printf("ANT %d",antecessores[i]);
//           pesos[j] = graph->mat[aux][j];
//         }
//       }
//      }
//      printf("ant: %d\n", antecessores[i]);
//   }
//   Peso resp = getWeight(pesos, antecessores, node1, node2);
//   printf("RESPOSTA: %f \n", resp);
//   printOutText(resp, saida);
// }
//