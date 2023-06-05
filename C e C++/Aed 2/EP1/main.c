// André Palacio Braga Tivo
// NUSP: 13835534

#include <float.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

// #include "grafo_listaadj.h"
#include "grafo_matrizadj.h"

void printOutText(Peso resp, FILE *saida) {
  double out;
  // printf("%f\n" , resp);
  if (resp >= 4.5)
    out = 4.5;
  else if (resp < 4.5 && resp >= 4.0)
    out = 4.0;
  else if (resp < 4.0 && resp >= 3.5)
    out = 3.5;
  else if (resp < 3.5 && resp >= 3.0)
    out = 3.0;
  else if (resp < 3.0 && resp >= 2.5)
    out = 2.5;
  else
    out = 0;

  printf("%f\n", out);
  fprintf(saida, "%.1f\n", out);
  fflush(saida);
}

int maxNode(bool visitados[], int nNodes, Peso pesos[]) {
  // printf("ENTROU MAX NODE\n");
  int aux = NULLEDGE; //-1
  Peso pesoMax = FLT_MIN;
  // printf("%f" , pesoMax);
  for (int i = 0; i <= nNodes; i++) {
    if (visitados[i] == false && pesoMax < pesos[i]) {
      pesoMax = pesos[i];
      aux = i;
    }
  }
  return aux;
}

Peso getWeight(Peso pesos[], int *antecessores, int node1, int node2) {
  Peso aux;
  // printf("node1: %d, node2: %d", node1, node2);
  if (node1 == node2) {
    aux = pesos[node2];
    return aux;
  } else {
    aux = getWeight(pesos, antecessores, node1, antecessores[node2]);
    if (aux > pesos[node2]) {
      aux = pesos[node2];
    }
  }
  return aux;
}

void maxTree(int nNodes, int node1, int node2, Graph *graph, FILE *saida) {
  // func magica que vai resolver meus problemas
  // ja existe nos arquivos .h , só esta sendo refeita aqui devido a
  // especificação da profa provavelmente irei deixar as outras funcoes maxtree
  // comentadas
  int tamArray = nNodes + 1;
  Peso pesos[tamArray];
  bool visitados[tamArray];
  int antecessores[tamArray];

  for (int i = 0; i <= nNodes; i++) {
    pesos[i] = FLT_MIN;
    visitados[i] = false;
  }
  antecessores[node1] = -1;
  pesos[node1] = FLT_MAX;
  // ARVORE MATRIZ

  for (int i = 0; i < nNodes; i++) {
    fflush(saida);
    // printf("entrou no for\n");
    int aux = maxNode(visitados, nNodes, pesos);
    printf("maxNode: %d\n", aux);

    visitados[aux] = true;
    // printf("%d %d %f \n", visitados[i], nNodes, pesos[i]);

    for (int j = 0; j < nNodes; j++) {
      if (visitados[j] == false && graph->mat[aux][j] != NULLEDGE) {  //transformar isso em uma funcao que percorre a lista
        if (graph->mat[aux][j] > pesos[j]) {
          antecessores[j] = aux;
          printf("ANT %d", antecessores[i]);
          pesos[j] = graph->mat[aux][j];
        }
      }
    }
    printf("ant: %d\n", antecessores[i]);
  }

  // FUNCAO LISTA ADJ
  /*

  for (int i = 0; i < nNodes; i++) {
    // printf("rodou o for\n");
    int j = maxNode(visitados, nNodes, pesos);
    // printf("passou o maxnode\n");
    printf("j: %d ", j);
    visitados[j] = true;
    Pointer current = graph->list[j];
    while ((current)) {
      if ((current) && visitados[current->vdest] == false) {
        if (pesos[current->vdest] < current->peso) {
          antecessores[current->vdest] = j;
          pesos[current->vdest] = current->peso;
        }
      }
      // printf("current");
      current = current->prox;
    }
  } */

  Peso resp = getWeight(pesos, antecessores, node1, node2);
  printf("RESPOSTA: %f \n", resp);
  printOutText(resp, saida);
}

int main(int argc, char *argv[]) {
  FILE *arq = fopen(argv[1], "r");
  if (!arq || arq == NULL) {
    printf("File error");
    return -1;
  }
  int centros; // nodes -pq eu escrevo em portugues em ingles?
  int rotas;   // edges
  int consultas;
  // read operation:
  fscanf(arq, "%i", &centros);
  fscanf(arq, "%i", &rotas);
  fscanf(arq, "%i", &consultas);
  Graph graph;
  graphInit(&graph, centros);
  for (int i = 0; i < rotas; i++) {
    int node1, node2;
    Peso peso;
    fscanf(arq, "%d", &node1);
    fscanf(arq, "%d", &node2);
    fscanf(arq, "%lf", &peso);
    // printf("%i %i PESO:%.1f\n", node1, node2, peso);
    edgeInsert(node1, node2, peso, &graph);
  }
  int qtdConsultas = consultas;
  int mConsultas[qtdConsultas][2];
  for (int i = 0; i < consultas; i++) {
    for (int j = 0; j < 2; j++) {
      int aux;
      fscanf(arq, "%d\n", &aux);
      mConsultas[i][j] = aux;
      // printf("%i " , mConsultas[i][j]);
    }
    // printf("\n");
  }

  printGraph(&graph, centros);
  // printf("centros: %i\nrotas: %i\nconsultas: %i\n", centros, rotas,
  // consultas);
  fflush(arq);
  fclose(arq);
  FILE *out = fopen("saida.txt", "w");
  if (!out || out == NULL) {
    printf("Error: output file");
    return -1;
  }
  for (int i = 0; i < consultas; i++) {
    int node1 = mConsultas[i][0];
    int node2 = mConsultas[i][1];
    maxTree(graph.nNodes, mConsultas[i][0], mConsultas[i][1], &graph, out);
  }
  fclose(out);
  return 0;
}
