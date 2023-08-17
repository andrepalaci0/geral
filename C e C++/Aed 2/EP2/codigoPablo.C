#include <stdio.h>
#include <stdlib.h>

#define T 3

typedef int keyType;

typedef struct node {
    keyType keys[2*T-1];
    struct node* childNodes[2*T];
    int qtyKeys;
    int isLeaf;
    struct node* next;
} NODE;

typedef struct {
    NODE* root;
} TREE;

void removeFromNode(NODE* node, keyType key);

// Helper function to create a new node
NODE* createNode(int isLeaf) {
    NODE* newNode = (NODE*)malloc(sizeof(NODE));
    newNode->qtyKeys = 0;
    newNode->isLeaf = isLeaf;
    newNode->next = NULL;
    for (int i = 0; i < 2*T; i++) {
        newNode->childNodes[i] = NULL;
    }
    return newNode;
}

TREE* createTree() {
    TREE* newTree = (TREE*)malloc(sizeof(TREE));
    newTree->root = NULL;
    return newTree;
}

void printParentheses(NODE* node, FILE* dest) {
    if (node) {
        if (node->isLeaf) {
            printf("(");
            fprintf(dest, "(");
            for (int i = 0; i < node->qtyKeys; i++) {
                printf("%d", node->keys[i]);
                fprintf(dest, "%d", node->keys[i]);
                if (i < node->qtyKeys - 1) {
                    printf(" ");
                    fprintf(dest, " ");
                }
            }
            printf(")");
            fprintf(dest, ")");
        } else {
            printf("(");
            fprintf(dest, "(");
            for (int i = 0; i < node->qtyKeys; i++) {
                printParentheses(node->childNodes[i], dest);
                printf(" %d ", node->keys[i]);
                fprintf(dest, " %d ", node->keys[i]);
            }
            printParentheses(node->childNodes[node->qtyKeys], dest);
            printf(")");
            fprintf(dest, ")");
        }
    } else {
        printf("Vazia");
        fprintf(dest, "Vazia");
    }
}

void splitChild(NODE* parentNode, int childIndex) {
    NODE* childNode = parentNode->childNodes[childIndex];
    NODE* newNode = createNode(childNode->isLeaf);
    newNode->qtyKeys = T - 1;
    for (int i = 0; i < T - 1; i++) {
        newNode->keys[i] = childNode->keys[i+T];
    }
    if (childNode->isLeaf) {
        // Splitting a leaf node
        newNode->next = childNode->next;
        childNode->next = newNode;

        for (int i = 0; i < T; i++) {
            newNode->keys[i] = childNode->keys[i+T-1];
        }

        newNode->qtyKeys = T;
        childNode->qtyKeys = T - 1;

        for (int i = parentNode->qtyKeys; i >= childIndex + 1; i--) {
            parentNode->childNodes[i+1] = parentNode->childNodes[i];
        }

        parentNode->childNodes[childIndex+1] = (NODE*)newNode;

        for (int i = parentNode->qtyKeys - 1; i >= childIndex; i--) {
            parentNode->keys[i+1] = parentNode->keys[i];
        }

        parentNode->keys[childIndex] = newNode->keys[0];
        parentNode->qtyKeys++;
    } else {
        // Splitting an internal node
        for (int i = 0; i < T; i++) {
            newNode->childNodes[i] = childNode->childNodes[i+T];
        }

        for (int i = parentNode->qtyKeys; i >= childIndex + 1; i--) {
            parentNode->childNodes[i+1] = parentNode->childNodes[i];
        }

        parentNode->childNodes[childIndex+1] = newNode;

        for (int i = parentNode->qtyKeys - 1; i >= childIndex; i--) {
            parentNode->keys[i+1] = parentNode->keys[i];
        }

        parentNode->keys[childIndex] = childNode->keys[T-1];
        parentNode->qtyKeys++;
        childNode->qtyKeys = T - 1;
    }
}

// Helper function to insert a key into a non-full node
void insertNonFull(NODE* node, keyType key) {
    int i = node->qtyKeys - 1;
    if (node->isLeaf) {
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i+1] = node->keys[i];
            i--;
        }
        node->keys[i+1] = key;
        node->qtyKeys++;
    } else {
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        i++;
        if (node->childNodes[i]->qtyKeys == 2*T-1) {
            splitChild(node, i);
            if (key > node->keys[i]) {
                i++;
            }
        }
        insertNonFull(node->childNodes[i], key);
    }
}

// Function to insert a key into the B+ tree
void insert(TREE* tree, keyType key) {
    if (tree->root == NULL) {
        NODE* newLeaf = createNode(1);
        newLeaf->keys[0] = key;
        newLeaf->qtyKeys = 1;
        tree->root = newLeaf;
        return;
    }
    NODE* rootNode = tree->root;
    if (rootNode->qtyKeys == 2*T-1) {
        NODE* newRootNode = createNode(0);
        newRootNode->childNodes[0] = rootNode;
        tree->root = newRootNode;
        splitChild(newRootNode, 0);
        insertNonFull(newRootNode, key);
    } else {
        insertNonFull(rootNode, key);
    }
}

// Function to borrow a key from the previous child node
void borrowFromPrev(NODE* node, int index) {
    // printf("Borrowing from previous child node\n");
    NODE* childNode = node->childNodes[index];
    NODE* prevChild = node->childNodes[index - 1];

    for (int i = childNode->qtyKeys - 1; i >= 0; i--) {
        printf("%d\n", childNode->keys[i]);
        childNode->keys[i+1] = childNode->keys[i];
    }


    childNode->keys[0] = prevChild->keys[prevChild->qtyKeys - 1];
    node->keys[index-1] = prevChild->keys[prevChild->qtyKeys - 1];

    childNode->qtyKeys++;
    prevChild->qtyKeys--;
}

// Function to borrow a key from the next child node
void borrowFromNext(NODE* node, int index) {
    // printf("Borrowing from next child node\n");
    NODE* childNode = node->childNodes[index];
    NODE* nextChild = node->childNodes[index + 1];

    childNode->keys[childNode->qtyKeys] = node->keys[index];

    node->keys[index] = nextChild->keys[0];

    for (int i = 1; i < nextChild->qtyKeys; i++) {
        nextChild->keys[i - 1] = nextChild->keys[i];
    }

    if (!nextChild->isLeaf) {
        for (int i = 1; i <= nextChild->qtyKeys; i++) {
            nextChild->childNodes[i - 1] = nextChild->childNodes[i];
        }
    }

    childNode->qtyKeys++;
    nextChild->qtyKeys--;
}

// Function to merge two nodes
void mergeNodes(NODE* node, int index) {
    // printf("Merging nodes\n");
    NODE* childNode = node->childNodes[index];
    NODE* nextChild = node->childNodes[index + 1];

    childNode->keys[T - 1] = node->keys[index];

    for (int i = 0; i < nextChild->qtyKeys; i++) {
        childNode->keys[i + T - 1] = nextChild->keys[i];
    }

    if (!childNode->isLeaf) {
        for (int i = 0; i <= nextChild->qtyKeys; i++) {
            childNode->childNodes[i + T] = nextChild->childNodes[i];
        }
    }

    for (int i = index + 1; i < node->qtyKeys; i++) {
        node->keys[i - 1] = node->keys[i];
        node->childNodes[i] = node->childNodes[i + 1];
    }

    childNode->qtyKeys += nextChild->qtyKeys;
    node->qtyKeys--;

    free(nextChild);
}

// Function to fill the child node with keys
int fillChild(NODE* node, int index) {
    // printf("Filling child node\n");
    NODE* childNode = node->childNodes[index];
    
    // Try to borrow a key from the previous sibling
    if (index != 0 && node->childNodes[index - 1]->qtyKeys >= T) {
        borrowFromPrev(node, index);
        return index;
    }
    // Try to borrow a key from the next sibling
    else if (index != node->qtyKeys && node->childNodes[index + 1]->qtyKeys >= T) {
        borrowFromNext(node, index);
        return index;
    }
    // Merge with the previous sibling
    else if (index != 0) {
        mergeNodes(node, index - 1);
        return index - 1;
    }
    // Merge with the next sibling
    else {
        mergeNodes(node, index);
        return index;
    }
}

void removeFromLeaf(NODE* node, int index) {
    for (int i = index + 1; i < node->qtyKeys; i++) {
        node->keys[i-1] = node->keys[i];
    }
    node->qtyKeys--;
}

// Function to get the predecessor key in a node
keyType getPredecessor(NODE* node, int index) {
    NODE* currNode = node->childNodes[index];
    while (!currNode->isLeaf) {
        currNode = currNode->childNodes[currNode->qtyKeys];
    }
    return currNode->keys[currNode->qtyKeys - 1];
}

// Function to get the successor key in a node
keyType getSuccessor(NODE* node, int index) {
    NODE* currNode = node->childNodes[index + 1];
    while (!currNode->isLeaf) {
        currNode = currNode->childNodes[0];
    }
    return currNode->keys[0];
}

// Function to remove a key from a non-leaf node
void removeFromNonLeaf(NODE* node, int index) {
    keyType key = node->keys[index];
    NODE* prevChild = node->childNodes[index];
    NODE* nextChild = node->childNodes[index + 1];

    if (prevChild->qtyKeys >= T) {
        if(prevChild->isLeaf) {
            node->keys[index] = prevChild->keys[prevChild->qtyKeys-1];
            nextChild->keys[0] = prevChild->keys[prevChild->qtyKeys-1];
            prevChild->qtyKeys--;
        } else {
            keyType predecessor = getPredecessor(node, index);
            node->keys[index] = predecessor;
            removeFromNode(prevChild, predecessor);
        }
    } else if (nextChild->qtyKeys >= T) {
        if(nextChild->isLeaf) {
            removeFromLeaf(nextChild, 0);
            node->keys[index] = nextChild->keys[0];
        } else {
            keyType successor = getSuccessor(node, index);
            node->keys[index] = successor;
            removeFromNode(nextChild, successor);
        }
    } else {
        mergeNodes(node, index);
        removeFromNode(prevChild, key);
    }
}

// Function to remove a key from a node
void removeFromNode(NODE* node, keyType key) {
    int index = 0;
    while (index < node->qtyKeys && key > node->keys[index]) {
        index++;
    }
    if (index < node->qtyKeys && key == node->keys[index]) {
        if (node->isLeaf) {
            removeFromLeaf(node, index);
        } else {
            removeFromNonLeaf(node, index);
        }
    } else {
        if (node->isLeaf) {
            printf("Error: Key not found in the tree.\n");
            return;
        }
        int lastKey = (index == node->qtyKeys) ? 1 : 0;
        NODE* childNode = node->childNodes[index];
        if (childNode->qtyKeys < T) {
            fillChild(node, index);
        }
        if (lastKey && index > node->qtyKeys) {
            removeFromNode(node->childNodes[index - 1], key);
        } else {
            removeFromNode(node->childNodes[index], key);
        }
    }
}

void removeKey(TREE* tree, NODE* node, keyType key) {
    int i = 0;

    while (i < node->qtyKeys && key >= node->keys[i]) i++;

    if (node->isLeaf){
        if (i > 0 && key == node->keys[i-1]) {
            // printf("Key %d found in leaf Node\n", key);
            removeFromLeaf(node, i-1);
        } else {
            printf("Key not found\n");
        }
        return;
    } else if (i > 0 && key == node->keys[i-1]) {
        // printf("Key %d found in inner Node\n", key);
        removeFromNonLeaf(node, i-1);
        return;
    }

    if (!node->isLeaf && node->childNodes[i]->qtyKeys < T) {
        i = fillChild(node, i);
    }

    removeKey(tree, node->childNodes[i], key);
    return;
}

void printByLeafs(TREE* tree){
    printf("The tree by leafs nodes is: ");
    if (tree->root == NULL) {
        printf("Empty tree\n");
        return;
    }
    NODE* currNode = tree->root;
    while (!currNode->isLeaf) {
        currNode = currNode->childNodes[0];
    }
    while (currNode != NULL) {
        for (int i = 0; i < currNode->qtyKeys; i++) {
            printf("%d ", currNode->keys[i]);
        }
        currNode = currNode->next;
    }
    printf("\n");
}

int readFile(char* path, char* dest) {
    // Open the file
    printf("Opening file...\n");
    printf("Path: %s\n", path);

    FILE* file = fopen(path, "r");
    FILE* destFile = fopen(dest, "w");

    // Check if the file is open
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    printf("File opened\n\n");
    printf("Reading file...\n");

    char op;
    int key;

    TREE* tree = createTree();

    while (op != 'f'){
    // Read operation
        if (fscanf(file, "%s", &op)) {
            switch (op) {
                case 'i':
                    if (fscanf(file, "%d", &key)) {
                        //printf("Inserting key: %d\n", key);
                        insert(tree, key);
                    } else {
                        printf("Invalid key\n");
                    }
                    //printf("Key inserted\n");
                    break;
                case 'r':
                    if (fscanf(file, "%d", &key)) {
                        //printf("Removing key: %d\n", key);
                        removeKey(tree, tree->root, key);
                    } else {
                        printf("Invalid key\n");
                    }
                    break;
                case 'p':
                    //printf("Printing in dest file\n");
                    printParentheses(tree->root, destFile);
                    printf("\n");
                    printByLeafs(tree);
                    fprintf(destFile, "\n");
                    break;
                case 'f':
                    printf("Finishing program\n");
                    break;
                default:
                    printf("Invalid operation: %c\n", op);
                    return 1;
            }
        }
    }

    fclose(file);
    printf("File closed\n");
    return 0;
}

int main(int argc, char* argv[]) {
    if(argc < 3) {
        printf("Missing files path\n");
        return 1;
    }

    char* path = argv[1];
    char* dest = argv[2];

    printf("Path: %s\n", path);

    readFile(path, dest);
    return 0;
}