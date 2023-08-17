#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define t 3 // ordem
#define MAX_KEYS 2 * t - 1
#define MAX_CHILDREN 2 * t
#define MIN_KEYS t - 1

typedef struct no {
  bool leaf;
  int nKeys;        // nmr de chaves
  int *keys;        // array de chaves
  struct no **children; // arrays de filhos
  struct no *next;  // proximo (lista ligada quando for folha)
} NO;

typedef struct {
  NO *root;
} BPTREE;

NO* create_no() {
  NO* node = (NO*)malloc(sizeof(NO));
  if (node == NULL) {
    fprintf(stderr, "Error: Could not allocate memory!\n");
    return NULL;
  }

  node->keys = (int*)malloc(sizeof(int) * MAX_KEYS);
  node->children = (NO**)malloc(sizeof(NO*) * MAX_CHILDREN);
  if (!node->keys || !node->children) {
    free(node->keys);
    free(node->children);
    free(node);
    return NULL;
  }

  node->leaf = true;
  node->nKeys = 0;
  node->next = NULL;

  for (int i = 0; i < MAX_CHILDREN; i++) {
    node->children[i] = NULL;
  }

  return node;
}

BPTREE* create_bptree() {
  BPTREE* tree = (BPTREE*)malloc(sizeof(BPTREE));
  if (tree == NULL) {
    fprintf(stderr, "Error: Could not allocate memory!\n");
    return NULL;
  }

  tree->root = NULL;

  return tree;
}

NO* search(NO* ptr, int key) {
  if (!ptr) {
    return NULL;
  }

  int i = 0;

  while ((i < ptr->nKeys) && (key > ptr->keys[i])) {
    i++;
  }

  if ((i < ptr->nKeys) && (ptr->leaf) && (key == ptr->keys[i])) {
    return ptr;
  }

  if (ptr->leaf) {
    return NULL;
  }

  return search(ptr->children[i], key);
}
NO* splitNode(NO* nodeWithSpace, int index, NO* nodeWithoutSpace) {
  NO* new_node = create_no();
  if (!new_node) {
    return NULL;
  }
  new_node->leaf = nodeWithoutSpace->leaf;

  int pivot = t - 1;

  if (!nodeWithoutSpace->leaf) {
    new_node->nKeys = pivot;

    for (int j = 0; j < pivot; j++) {
      new_node->keys[j] = nodeWithoutSpace->keys[j + t];
    }

    for (int j = 0; j < t; j++) {
      new_node->children[j] = nodeWithoutSpace->children[j + t];
      nodeWithoutSpace->children[j + t] = NULL;
    }
  } else {
    new_node->nKeys = t;

    for (int j = 0; j < t; j++) {
      new_node->keys[j] = nodeWithoutSpace->keys[j + pivot];
    }

    nodeWithoutSpace->next = new_node;
  }

  nodeWithoutSpace->nKeys = pivot;

  for (int j = nodeWithSpace->nKeys; j >= index; j--) {
    nodeWithSpace->children[j + 1] = nodeWithSpace->children[j];
  }

  nodeWithSpace->children[index] = new_node;

  for (int j = nodeWithSpace->nKeys; j >= index; j--) {
    nodeWithSpace->keys[j] = nodeWithSpace->keys[j - 1];
  }

  nodeWithSpace->keys[index - 1] = nodeWithoutSpace->keys[pivot];
  nodeWithSpace->nKeys++;

  return nodeWithSpace;
}

void insertWithRoom(NO* node, int key) {
  int i = node->nKeys - 1;

  if (node->leaf) {
    while (i >= 0 && (key < node->keys[i])) {
      node->keys[i + 1] = node->keys[i];
      i--;
    }

    node->keys[i + 1] = key;
    node->nKeys++;
  } else {
    while (i >= 0 && (key < node->keys[i])) {
      i--;
    }
    i++;

    if (node->children[i]->nKeys == MAX_KEYS) {
      node = splitNode(node, i + 1, node->children[i]);

      if (key > node->keys[i]) {
        i++;
      }
    }

    insertWithRoom(node->children[i], key);
  }
}
void insert(BPTREE* tree, int key) {
  if (search(tree->root, key) != NULL) {
    return;
  }

  if (tree->root == NULL) {
    tree->root = create_no();
    if (!tree->root) {
      return;
    }

    tree->root->keys[0] = key;
    tree->root->nKeys = 1;
    return;
  }

  if (tree->root->nKeys == MAX_KEYS) {
    NO* newRoot = create_no();
    if (!newRoot) {
      return;
    }

    newRoot->leaf = false;
    newRoot->children[0] = tree->root;
    newRoot = splitNode(newRoot, 1, tree->root);
    insertWithRoom(newRoot, key);
    tree->root = newRoot;
    return;
  }

  insertWithRoom(tree->root, key);
}
void printInOrder(NO *node, FILE *out) {
  if (node) {
    if (node->leaf) {
      printf("(");
      fprintf(out, "(");
      for (int i = 0; i < node->nKeys; i++) {
        printf("%d", node->keys[i]);
        fprintf(out, "%d", node->keys[i]);
        if (i < node->nKeys - 1) {
          printf(" ");
          fprintf(out, " ");
        }
      }
      printf(")");
      fprintf(out, ")");
    } else {
      printf("(");
      fprintf(out, "(");
      for (int i = 0; i < node->nKeys; i++) {
        printInOrder(node->children[i], out);
        printf(" %d ", node->keys[i]);
        fprintf(out, " %d ", node->keys[i]);
      }
      printInOrder(node->children[node->nKeys], out);
      printf(")");
      fprintf(out, ")");
    }
  } else {
    printf("Vazia");
    fprintf(out, "Vazia");
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
  BPTREE *bptree = (BPTREE*)malloc(sizeof(BPTREE));
  char instruction;
  int inputValue;
  
  while (fscanf(in, "%c", &instruction) && instruction != 'f') {
    if (instruction == 'p') {
      printf("print\n");
      printInOrder(bptree->root,out);
      fprintf(out, "\n");
    } else if (instruction == 'i') {
      fscanf(in, "%i", &inputValue);
      printf("Insert: %i\n", inputValue);
      insert(bptree->root, inputValue);
    } else if (instruction == 'r') {
      fscanf(in, "%i\n", &inputValue);
      printf("Remov: %i\n", inputValue);
      // chama a funcao de remove
    } else if (instruction == 'f') {
      free(bptree);
    }
  }
  fclose(in);
  fclose(out);

  return 0;
}