#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left, * right;
} TreeNode;

typedef struct ThreadNode {
    int data;
    struct ThreadNode* left, * right;
    int ltag, rtag;
} ThreadNode;

ThreadNode* previous = NULL;

TreeNode* Insert(TreeNode* root, int data) {
    if (root == NULL) {
        TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
        newNode->data = data;
        newNode->left = newNode->right = NULL;
        return newNode;
    }
    if (data < root->data) {
        root->left = Insert(root->left, data);
    }
    else {
        root->right = Insert(root->right, data);
    }
    return root;
}

TreeNode* GenerateBinaryTree(int inputData[], int size) {
    TreeNode* root = NULL;
    for (int i = 0; i < size; i++) {
        root = Insert(root, inputData[i]);
    }
    return root;
}

void BinaryTreeInOrder(TreeNode* root) {
    if (root == NULL) return;
    BinaryTreeInOrder(root->left);
    printf("%d ", root->data);
    BinaryTreeInOrder(root->right);
}

ThreadNode* CreateThreadNode(TreeNode* root) {
    if (root == NULL) return NULL;

    ThreadNode* tnode = (ThreadNode*)malloc(sizeof(ThreadNode));
    tnode->data = root->data;
    tnode->left = tnode->right = NULL;
    tnode->ltag = tnode->rtag = 0;

    if (root->left != NULL) {
        tnode->left = CreateThreadNode(root->left);
    }
    else {
        tnode->ltag = 1;
        tnode->left = previous;
    }

    if (previous != NULL && previous->rtag == 1) {
        previous->right = tnode;
    }

    previous = tnode;

    if (root->right != NULL) {
        tnode->right = CreateThreadNode(root->right);
    }
    else {
        tnode->rtag = 1;
    }

    return tnode;
}

ThreadNode* GenerateThreadTree(TreeNode* root) {
    previous = NULL;
    return CreateThreadNode(root);
}

void ThreadTreeInOrder(ThreadNode* troot) {
    ThreadNode* current = troot;

    while (current != NULL && current->ltag == 0) {
        current = current->left;
    }

    while (current != NULL) {
        printf("%d ", current->data);

        if (current->rtag == 1) {
            current = current->right;
        }
        else {
            current = current->right;
            while (current != NULL && current->ltag == 0) {
                current = current->left;
            }
        }
    }
}

int main() {
    int inputData[] = { 4, 1, 9, 13, 15, 3, 6, 14, 7, 10, 12, 2, 5, 8, 11 };
    int size = sizeof(inputData) / sizeof(inputData[0]);

    TreeNode* root = GenerateBinaryTree(inputData, size);
    printf("Binary tree inorder: ");
    BinaryTreeInOrder(root);
    printf("\n");

    ThreadNode* troot = GenerateThreadTree(root);
    printf("Thread tree inorder: ");
    ThreadTreeInOrder(troot);
    printf("\n");

    free(root);
    free(troot);

    return 0;
}
