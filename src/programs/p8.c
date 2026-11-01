#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

Node *createNode(int value) {
    Node *n = (Node *)malloc(sizeof(Node));
    if (n == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    n->data = value;
    n->left = n->right = NULL;
    return n;
}

/* 1. Insert a new node */
Node *insert(Node *root, int value) {
    if (root == NULL)
        return createNode(value);
    if (value < root->data)
        root->left = insert(root->left, value);
    else if (value > root->data)
        root->right = insert(root->right, value);
    else
        printf("Value %d already exists. Duplicate ignored.\n", value);
    return root;
}

/* Traversals */
void inorder(Node *root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void preorder(Node *root) {
    if (root == NULL) return;
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node *root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

/* 2. Number of nodes in the longest path from the root */
int longestPath(Node *root) {
    int l, r;
    if (root == NULL) return 0;
    l = longestPath(root->left);
    r = longestPath(root->right);
    return 1 + (l > r ? l : r);
}

/* 3. Minimum data value (leftmost node) */
Node *findMin(Node *root) {
    if (root == NULL) return NULL;
    while (root->left != NULL)
        root = root->left;
    return root;
}

/* 4. Swap left and right pointers at every node */
void mirror(Node *root) {
    Node *temp;
    if (root == NULL) return;
    temp = root->left;
    root->left = root->right;
    root->right = temp;
    mirror(root->left);
    mirror(root->right);
}

/* 5. Search a value */
Node *search(Node *root, int key) {
    while (root != NULL && root->data != key) {
        if (key < root->data)
            root = root->left;
        else
            root = root->right;
    }
    return root;
}

void freeTree(Node *root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int readInt(const char *prompt, int *x) {
    int c;
    printf("%s", prompt);
    if (scanf("%d", x) == 1)
        return 1;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
    return 0;
}

int main() {
    Node *root = NULL;
    Node *res;
    int n, i, val, choice;
    char prompt[40];

    if (!readInt("Enter the number of nodes: ", &n) || n < 0) {
        printf("Invalid input.\n");
        return 1;
    }

    for (i = 1; i <= n; i++) {
        sprintf(prompt, "Enter value %d: ", i);
        if (readInt(prompt, &val))
            root = insert(root, val);
        else
            i--;
    }

    do {
        printf("\n===== BST OPERATIONS =====\n");
        printf("1. Insert a new node\n");
        printf("2. Display traversals\n");
        printf("3. Number of nodes in the longest path from root\n");
        printf("4. Minimum data value in the tree\n");
        printf("5. Mirror the tree (swap left and right pointers)\n");
        printf("6. Search a value\n");
        printf("0. Exit\n");

        if (!readInt("Enter your choice: ", &choice)) {
            if (feof(stdin)) break;
            printf("Invalid choice.\n");
            continue;
        }

        switch (choice) {
        case 1:
            if (readInt("Enter value to insert: ", &val)) {
                root = insert(root, val);
                printf("Insert operation done for %d.\n", val);
            }
            break;

        case 2:
            if (root == NULL) {
                printf("Tree is empty.\n");
            } else {
                printf("Inorder   -> "); inorder(root);   printf("\n");
                printf("Preorder -> "); preorder(root); printf("\n");
                printf("Postorder -> "); postorder(root); printf("\n");
            }
            break;

        case 3:
            printf("Number of nodes in the longest path from root = %d\n", longestPath(root));
            break;

        case 4:
            res = findMin(root);
            if (res == NULL)
                printf("Tree is empty.\n");
            else
                printf("Minimum data value in the tree = %d\n", res->data);
            break;

        case 5:
            mirror(root);
            printf("Tree mirrored (left and right swapped at every node).\n");
            break;

        case 6:
            if (readInt("Enter value to search: ", &val)) {
                if (search(root, val) != NULL)
                    printf("Value %d FOUND in the tree.\n", val);
                else
                    printf("Value %d NOT FOUND in the tree.\n", val);
            }
            break;

        case 0:
            printf("Exiting program.\n");
            break;

        default:
            printf("Invalid choice. Try again.\n");
        }
    } while (choice != 0);

    freeTree(root);
    return 0;
}