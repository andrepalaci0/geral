#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*
  NOME: Andre Palacio Braga Tivo
  NUSP: 13835534

  Esse programa foi testado em um
  OS: Pop!_OS 22.04 LTS x86_64 
  com GCC:
  gcc (Ubuntu 11.3.0-1ubuntu1~22.04.1) 11.3.0

  Também foi testado no replit
*/

#define t 3 // ordem
#define MAX_KEYS 2 * t - 1
#define MIN_KEYS t - 1
#define MAX_CHILDREN 2 * t

typedef struct no {
  bool leaf;
  int nKeys;            // nmr de chaves
  int *keys;            // array de chaves
  struct no **children; // arrays de filhos
  struct no *next;      // proximo (lista ligada quando for folha)
} NO;

typedef struct {
  NO *root;
} BPTREE;


NO *criaNo(bool leaf) {
  NO *aux = (NO *)malloc(sizeof(NO));
  aux->leaf = leaf;
  aux->nKeys = 0;
  aux->keys = (int *)malloc(MAX_KEYS * sizeof(int));
  aux->children = (NO **)malloc(MAX_CHILDREN * sizeof(NO *));
  aux->next = NULL;
  return aux;
}

BPTREE *criaArvore() {
  BPTREE *aux = (BPTREE *)malloc(sizeof(BPTREE));
  aux->root = criaNo(true);
  return aux;
}

NO *inserWithRoom(NO *p, int key);
NO *split(NO *p, int index);
NO *insert(BPTREE *tree, int key);

void printInOrdem(NO *p, FILE *out);
void freeTree(NO *p);

NO *insertWithRoom(NO *p, int key) {
  int i = p->nKeys - 1;

  if (!p->leaf) { // nao eh folah
    while (i >= 0 && key < p->keys[i])
      i--;

    i++;

    if (p->children[i]->nKeys == MAX_KEYS) {
      split(p, i);

      if (key > p->keys[i]) {
        i++;
      }
    }

    insertWithRoom(p->children[i], key);

  } else { // eh folha

    while (i >= 0 && key < p->keys[i]) {
      p->keys[i + 1] = p->keys[i];
      i--;
    }

    p->nKeys++;
    p->keys[i + 1] = key;
  }
  return p;
}

NO *split(NO *p, int index) {
  NO *child = p->children[index];
  NO *aux = criaNo(child->leaf);
  aux->nKeys = MIN_KEYS;

  for (int j = 0; j < MIN_KEYS; j++) {
    aux->keys[j] = child->keys[j + t];
  }

  if (!child->leaf) { // nao for folha
    for (int j = 0; j < t; j++)
      aux->children[j] = child->children[j + t];

    child->nKeys = MIN_KEYS;

    for (int j = p->nKeys; j >= index + 1; j--)
      p->children[j + 1] = p->children[j];

    p->children[index + 1] = aux;

    for (int j = p->nKeys - 1; j >= index; j--)
      p->keys[j + 1] = p->keys[j];

    p->keys[index] = child->keys[t - 1];
    p->nKeys++;
  } else { // eh folha
    child->nKeys = MIN_KEYS;
    child->next = aux;
    aux->next = child->next;
    aux->nKeys = MIN_KEYS + 1;

    for (int i = 0; i < t; i++)
      aux->keys[i] = child->keys[i + MIN_KEYS];

    for (int j = p->nKeys; j >= index + 1; j--)
      p->children[j + 1] = p->children[j];

    p->children[index + 1] = aux;

    for (int j = p->nKeys - 1; j >= index; j--)
      p->keys[j + 1] = p->keys[j];

    p->keys[index] = child->keys[MIN_KEYS];
    p->nKeys++;
  }

  return p;
}

NO *insert(BPTREE *tree, int key) {
  if (tree->root == NULL) { // caso insira a arvore vazia
    tree->root = criaNo(true);
  }

  if (tree->root->nKeys == MAX_KEYS) { // caso o no esteja cheio
    NO *newRoot = criaNo(false);
    newRoot->children[0] = tree->root;
    tree->root = newRoot;
    split(newRoot, 0);
  }
  // caso padrao
  insertWithRoom(tree->root, key);
  return tree->root;
}

void printInOrdem(NO *p, FILE *out) {
  if (p->nKeys > 0) {
    if (p->leaf) {
      fprintf(out, "(");
      for (int i = 0; i < p->nKeys; i++) {
        fprintf(out, "%d", p->keys[i]);
        if (i < p->nKeys - 1) {
          fprintf(out, " ");
        }
      }
      fprintf(out, ")");
    } else {
      fprintf(out, "(");
      for (int i = 0; i < p->nKeys; i++) {
        printInOrdem(p->children[i], out);
        fprintf(out, " %d ", p->keys[i]);
      }
      printInOrdem(p->children[p->nKeys], out);
      fprintf(out, ")");
    }
  } else {
    fprintf(out, "Vazia");
  }
}

void freeTree(NO *p) { // apaga a arvre / limpa a memoria (evita memory leak)
  if (p) {
    if (!p->leaf) {
      for (int i = 0; i <= p->nKeys; i++) {
        freeTree(p->children[i]);
      }
    }
    free(p->keys);
    free(p->children);
    free(p);
  }
}

int main(int argc, char *argv[]) {
  FILE *in = fopen(argv[1], "r");
  FILE *out = fopen(argv[2], "w");
  if (!in) {
    printf("ERRO: Arquivo de entrada ausente ou invalido\n");
  }
  if (!out) {
    printf("ERRO: Arquivo de saída ausente ou invalido\n");
  }
  // inicializa arvore b +
  BPTREE *bptree = criaArvore();
  char instruction;
  int inputValue;
  while (fscanf(in, "%c", &instruction) && instruction != 'f') {
    if (instruction == 'p') {
      // printf("print ");
      printInOrdem(bptree->root, out);
      // printf("\n");
      fprintf(out, "\n");
    } else if (instruction == 'i') {
      fscanf(in, "%i", &inputValue);
      // printf("Insert: %i\n", inputValue);
      insert(bptree, inputValue);
    } else if (instruction == 'r') {
      fscanf(in, "%i\n", &inputValue);
      // printf("Remov: %i\n", inputValue);
      //  chama a funcao de remove (n fiz)
    }
  }
  freeTree(bptree->root);
  free(bptree);
  fclose(in);
  fclose(out);

  return 0;
}