//
// Created by machi on 10/23/2025.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* left;
    struct node* right;
}node;

node* create(const int data) {
    node* newNode = malloc(sizeof(node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

void insert(node* (*root), node* newNode) {
    if (*root == NULL) {
        *root = newNode;
        return;
    }
    // if (*root) val < new val, check if right exist; if not, make it, else, go right
    // if (*root) val > new val, check if left exist; if not, make it, else, go left

    if ((*root)->data < newNode->data) {
        if ((*root)->right) {
            insert(&(*root)->right, newNode);
        } else {
            (*root)->right = newNode;
        }
    } else {
        if ((*root)->left) {
            insert(&(*root)->left, newNode);
        } else {
            (*root)->left = newNode;
        }
    }
}

node* min(node* root) {
    if (root->left) {
        return min(root->left);
    }
    return root;
}

node* delete(node* root, int data) {
    if (root->data < data) {
        root->right = delete(root->right, data);
    } else if (root->data > data) {
        root->left = delete(root->left, data);
    } else {
        node* temp;
        if (root->left == NULL) {
            temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            temp = root->left;
            free(root);
            return temp;
        } else {
            temp = min(root->right);
            root->data = temp->data;
            root->right = delete(root->right, temp->data);
        }
    }

    return root;
    // if root val < data then go right
    // if root val > data then go left
    // if root val == data then
    //    check if root->left exist
    //      if yes, replace root with root->left
    //      if no, check if root->right exist
    //         if yes, find successor
    //         if no, just delete the node
}

void inorder(node* root) {
    if (root == NULL) {
        return;
    }
    inorder(root->left);
    printf("[%d] ", root->data);
    inorder(root->right);
    // go left
    // print curr
    // go right
}

void preorder(node* root) {
    if (root == NULL) {
        return;
    }
    printf("[%d] ", root->data);
    preorder(root->left);
    preorder(root->right);
    // print curr
    // go left
    // go right
}

void postorder(node* root) {
    if (root == NULL) {
        return;
    }
    postorder(root->left);
    postorder(root->right);
    printf("[%d] ", root->data);
    // go left
    // go right
    // print curr
}

void levelorder(node* root) {
    node* queue[20];
    int head = 0; int tail = 0;
    queue[tail++] = root;
    int level;
    while (head < tail) {
        level = tail - head;
        for (int i = 0; i < level; i++) {
            node* curr = queue[head++];
            printf("[%d] ", curr->data);
            if (curr->left) {
                queue[tail++] = curr->left;
            }
            if (curr->right) {
                queue[tail++] = curr->right;
            }
            if (!curr->left && !curr->right) {
                printf("[X] ");
            }
        }
        printf("\n");
    }
}

void printIndented(node* (root), int level, char side) {
    if (!(root)) return;
    for (int i = 0; i < (int)(level*1.5); i++) printf("  ");
    printf("%c->%d\n", side, (root)->data);
    printIndented((root)->left, level + 1, 'L');
    printIndented((root)->right, level + 1, 'R');
}

void pretty_print(node* (*root)) {}

int main() {
    node* (root) = NULL;
    insert((&root), create(10));
    insert((&root), create(3));
    insert((&root), create(12));
    insert((&root), create(11));
    insert((&root), create(8));

    printIndented((root), 0, 'X');

    preorder(root);
    printf("\n");
    inorder(root);
    printf("\n");
    postorder(root);
    printf("\n");
    levelorder(root);
    printf("\n");

    delete(root, 3);
    printIndented(root, 0, 'X');

    return 0;
}








