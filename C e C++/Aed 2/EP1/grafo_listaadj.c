#include "grafo_listaadj.h"
#include <float.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool graphInit(Graph *graph, int nv) {
  if (nv <= 0) {
    fprintf(stderr, "Erro:, num de vertices deve ser positivo");
    return false;
  }
  graph->nNodes = nv;
  if (!(graph->list = (Pointer *)calloc(nv + 1, sizeof(Pointer)))) {
    fprintf(stderr, "Erro: falha na alocacao da memoria na inicializaçao");
    return false;
  }
  graph->nEdges = 0;
  return true;
}

bool edgeValidation(int v, Graph *graph) {
  if (v > graph->nNodes) {
    fprintf(stderr,
            "Erro: Num de vertices (%d) maior que o numero total de vertices "
            "(%d)\n",
            v, graph->nEdges);
    return false;
  }
  if (v < 0) {
    fprintf(stderr, "Erro: Num do vertice (%d) deve ser positivo\n", v);
    return false;
  }
  return true;
}

bool emptyList(int v, Graph *graph) {
  if (!edgeValidation(v, graph))
    return false;
  return graph->list[v] == NULL;
}

int getDest(Pointer current, Graph *graph) { return current->vdest; }

Pointer listNext(int v, Graph *graph, Pointer current) {
  if (current == NULL) {
    fprintf(stderr, "atual == NULL\n");
    return INVALIDNODE;
  }
  if (current->prox) {
    return (current->prox);
  }
  return NULL;
}

Pointer listFirst(int v, Graph graph) { return (graph.list[v]); }

bool edgeExists(int node1, int node2, Graph *graph) {
  if (!(edgeValidation(node1, graph) && edgeValidation(node2, graph)))
    return false;

  Pointer q = graph->list[node1];
  while ((q != NULL) && (q->vdest != node2))
    q = q->prox;
  if (q != NULL)
    return true;
  return false;
}

Pointer getNode(Pointer current, int i, Graph *graph) { return (Edge *)(graph->list[i]); }

Peso getEdgeWeight(int node1, int node2, Graph *graph) {
  if (!(edgeValidation(node1, graph) && edgeValidation(node2, graph)))
    return NULLEDGE;
  Pointer q = graph->list[node1];
  while ((q != NULL) && (q->vdest != node2))
    q = q->prox;
  if (q != NULL)
    return q->peso;
  return NULLEDGE;
}

void edgeInsert(int node1, int node2, Peso peso, Graph *graph) {
  if (!(edgeValidation(node1, graph) && edgeValidation(node2, graph)))
    return;

  Pointer q;
  if (!(q = (Pointer)calloc(1, sizeof(Edge)))) {
    fprintf(stderr,
            "Erro: falha na alocacao de memoria na funcao edgeInsert\n");
    return;
  }
  q->vdest = node2;
  q->peso = peso;
  q->prox = graph->list[node1];
  graph->list[node1] = q;

  Pointer q2;
  if (!(q2 = (Pointer)calloc(1, sizeof(Edge)))) {
    fprintf(stderr,
            "Erro: falha na alocacao de memoria na funcao edgeInsert\n");
    return;
  }
  q2->vdest = node1;
  q2->peso = peso;
  q2->prox = graph->list[node2];
  graph->list[node2] = q2;

  graph->nEdges++;
}

void freeGraph(Graph *graph) {
  int n;
  Pointer p;

  for (n = 0; n <= graph->nEdges; n++) {
    graph->list[n] = p->prox;
    p->prox = NULL;
    free(p);
  }
}

void printGraph(Graph *graph, int nodes) {
  Pointer aux;
  for (int i = 1; i <= graph->nNodes; i++) {
    printf("v%d: ", i);
    aux = graph->list[i];
    while (aux != NULL) {
      printf("(adj %d - %.1f, peso)", (aux->vdest), aux->peso);
      printf("\n");
      aux = aux->prox;
    }
    printf("----\n");
  }
  return;
}

// Peso getWeight(Peso pesos[], int antecessores[], int node1, int node2)
//{
//     Peso aux;
//     //printf("getWeight\n");
//     if(node1 == node2)
//     {
//         aux = pesos[node2];
//         return aux;
//     }else{
//         aux = getWeight(pesos, antecessores, node1, antecessores[node2]);
//         if(aux > pesos[node2])
//             aux = pesos[node2];
//     }
//     return aux;
// }

// int maxNode(bool visitados[], int nNodes, Peso pesos[])
//{
//     //printf("ENTROU MAX NODE\n");
//     int aux = NULLEDGE;
//     Peso pesoMax = FLT_MIN;
//     //printf("%f" , pesoMax);
//     for (int i = 0; i <= nNodes; i++)
//     {
//         if(visitados[i]==false && pesoMax < pesos[i])
//         {
//             pesoMax = pesos[i];
//             aux = i;
//         }
//     }
//     return aux;
// }

// void printOutText(Peso resp, FILE* saida)
//{
//     double out;
//     //printf("%f\n" , resp);
//     if(resp >= 4.5) out = 4.5;
//     else if(resp < 4.5 && resp >= 4.0) out = 4.0;
//     else if(resp < 4.0 && resp >= 3.5) out = 3.5;
//     else if(resp < 3.5 && resp >= 3.0) out = 3.0;
//     else if(resp < 3.0 && resp >= 2.5) out = 2.5;
//     else printf("ERRO: Tamanho invalido");
//
//     printf("%f\n",out);
//     fprintf(saida, "%.1f\n", out);
//     fflush(saida);
// }
//
// void maxTree(int nNodes, int node1, int node2, Graph* graph, FILE* saida)
//{
//     printf("CHAMADA MAX TREE\n");
//     fflush(saida); //se nao ouver o flush de buffer, acontece erro de
//     ponteiro
//
//     int tamArray = nNodes + 1;
//     Peso pesos[tamArray];
//     bool visitados[tamArray];
//     int pai[tamArray];
//     for (int i = 1; i <= nNodes; i++)
//     {
//         visitados[i] = false;
//         pesos[i] = FLT_MIN;
//     }
//     pai[node1] = -1;
//     pesos[node1] = FLT_MAX;
//     //printf("%f \n" , pesos[node1]);
//
//     for (int i = 0; i < nNodes; i++)
//     {
//         //printf("rodou o for\n");
//         int j = maxNode(visitados, nNodes, pesos);
//         //printf("passou o maxnode\n");
//         printf("j: %d " , j);
//         visitados[j] = true;
//         Pointer current = graph->list[j];
//         while ((current))
//         {
//             if((current)&& visitados[current->vdest] == false)
//             {
//                 if(pesos[current->vdest] < current->peso)
//                 {
//                     pesos[current->vdest] = current->peso;
//                     pai[current->vdest] = j;
//                 }
//             }
//             //printf("current");
//             current = current->prox;
//         }
//     }
//     Peso resp = getWeight(pesos, pai, node1, node2);
//     //printf("passou o peso");
//     printOutText(resp, saida);
//     //printf("consulta\n");
// }
//
//