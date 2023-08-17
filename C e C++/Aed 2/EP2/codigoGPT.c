#include<stdio.h>
#include<stdlib.h>

struct BTreeNode {
    int *data;
    struct BTreeNode **child_ptr;
    int leaf;
    int n;
};

struct BTreeNode *root = NULL;
struct BTreeNode *np = NULL;
struct BTreeNode *x = NULL;

struct BTreeNode * init() {
    int i;
    np = (struct BTreeNode*)malloc(sizeof(struct BTreeNode));
    np->data = (int*)malloc(5 * sizeof(int));
    np->child_ptr = (struct BTreeNode**)malloc(6 * sizeof(struct BTreeNode*));
    np->leaf = 1;
    np->n = 0;
    for (i = 0; i < 6; i++) {
        np->child_ptr[i] = NULL;
    }
    return np;
}

void traverse(struct BTreeNode *p) {
    printf("\n");
    int i;
    for (i = 0; i < p->n; i++) {
        if (p->leaf == 0) {
            traverse(p->child_ptr[i]);
        }
        printf(" %d", p->data[i]);
    } 
    if (p->leaf == 0) {
        traverse(p->child_ptr[i]);
    }
    printf("\n");
}

void sort(int *p, int n) {
    int i, j, temp;
    for (i = 0; i < n; i++) {
        for (j = i; j <= n; j++) {
            if (p[i] > p[j]) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

int split_child(struct BTreeNode *x, int i) {
    int j, mid;
    struct BTreeNode *np1, *np3, *y;
    np3 = init();
    np3->leaf = 1;
    if (i == -1) {
        mid = x->data[2];
        x->data[2] = 0;
        x->n--;
        np1 = init();
        np1->leaf = 0;
        x->leaf = 1;
        for (j = 3; j < 5; j++) {
            np3->data[j - 3] = x->data[j];
            np3->child_ptr[j - 3] = x->child_ptr[j];
            np3->n++;
            x->data[j] = 0;
            x->n--;
        }
        for(j = 0; j < 6; j++) {
            x->child_ptr[j] = NULL;
        }
        np1->data[0] = mid;
        np1->child_ptr[np1->n] = x;
        np1->child_ptr[np1->n + 1] = np3;
        np1->n++;
        root = np1;
    }
    else {
        y = x->child_ptr[i];
        mid = y->data[2];
        y->data[2] = 0;
        y->n--;
        for (j = 3; j < 5; j++) {
            np3->data[j - 3] = y->data[j];
            np3->n++;
            y->data[j] = 0;
            y->n--;
        }
        x->child_ptr[i + 1] = y;
        x->child_ptr[i + 1] = np3; 
    }
    return mid;
}

void insert(int a) {
    int i, temp;
    x = root;
    if (x == NULL) {
        root = init();
        x = root;
    }
    else {
        if (x->leaf == 1 && x->n == 5) {
            temp = split_child(x, -1);
            x = root;
            for (i = 0; i < (x->n); i++) {
                if ((a > x->data[i]) && (a < x->data[i + 1])) {
                    i++;
                    break;
                }
                else if (a < x->data[0]) {
                    break;
                }
                else {
                    continue;
                }
            }
            x = x->child_ptr[i];
        }
        else {
            while (x->leaf == 0) {
                for (i = 0; i < (x->n); i++) {
                    if ((a > x->data[i]) && (a < x->data[i + 1])) {
                        i++;
                        break;
                    }
                    else if (a < x->data[0]) {
                        break;
                    }
                    else {
                        continue;
                    }
                }
                if ((x->child_ptr[i])->n == 5) {
                    temp = split_child(x, i);
                    x->data[x->n] = temp;
                    x->n++;
                    continue;
                }
                else {
                    x = x->child_ptr[i];
                }
            }
        }
    }
    x->data[x->n] = a;
    sort(x->data, x->n);
    x->n++;
}

void print_tree(struct BTreeNode *ptr, int level, FILE *outputFile) {
    if (!ptr) {
        return;
    }

    if (ptr->n == 0) {
        fprintf(outputFile, "Vazia");
        return;
    }

    int i;
    fprintf(outputFile, "(");
    for (i = 0; i <= ptr->n - 1; i++) {
        print_tree(ptr->child_ptr[i], level + 1, outputFile);

        if (i != 0 && (i == ptr->n - 1 || i != ptr->n)) {
            fprintf(outputFile, " ");
        }
        else if (i <= level && !ptr->leaf) {
            fprintf(outputFile, " ");
        }

        fprintf(outputFile, "%d", ptr->data[i]);

        if (!ptr->leaf) {
            fprintf(outputFile, " ");
        }
    }
    print_tree(ptr->child_ptr[i], level + 1, outputFile);
    fprintf(outputFile, ")");
}

int main(int argc, char *argv[]) {
    int i, n, t;
    printf("enter the no of elements to be inserted\n");
    scanf("%d", &n);
    for(i = 0; i < n; i++) {
        printf("enter the element\n");
        scanf("%d", &t);
        insert(t);
    }
    printf("traversal of constructed tree\n");
    traverse(root);
    FILE* out = fopen(argv[1], "w");
    print_tree(root, 0, out);
    fclose(out);
    return 0;
}
