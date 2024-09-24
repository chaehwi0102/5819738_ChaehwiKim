#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct Stack {
    TreeNode* nodes[100];
    int top;
} Stack;

void InitStack(Stack* stack) {
    stack->top = -1;
}

int IsEmpty(Stack* stack) {
    return stack->top == -1;
}

void Push(Stack* stack, TreeNode* node) {
    stack->nodes[++stack->top] = node;
}

TreeNode* Pop(Stack* stack) {
    return stack->nodes[stack->top--];
}

void PlaceNode(TreeNode* node, int direction, int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;

    if (direction == 0) {
        node->left = newNode;
    }
    else {
        node->right = newNode;
    }
}

void GenerateLinkTree(TreeNode* root) {
    PlaceNode(root, 0, 2);
    PlaceNode(root, 1, 3);

    PlaceNode(root->left, 0, 4);
    PlaceNode(root->left, 1, 5);

    PlaceNode(root->right, 0, 6);
    PlaceNode(root->right, 1, 7);

    PlaceNode(root->left->left, 0, 8);
    PlaceNode(root->left->left, 1, 9);

    PlaceNode(root->left->right, 0, 10);
    PlaceNode(root->left->right, 1, 11);

    PlaceNode(root->right->left, 0, 12);
    PlaceNode(root->right->left, 1, 13);

    PlaceNode(root->right->right, 0, 14);
    PlaceNode(root->right->right, 1, 15);
}

int GetSumOfNodes(TreeNode* root) {
    if (root == NULL) return 0;

    Stack stack;
    InitStack(&stack);
    Push(&stack, root);

    int sum = 0;

    while (!IsEmpty(&stack)) {
        TreeNode* current = Pop(&stack);
        sum += current->data;

        if (current->right) {
            Push(&stack, current->right);
        }
        if (current->left) {
            Push(&stack, current->left);
        }
    }

    return sum;
}

int GetNumberOfNodes(TreeNode* root) {
    if (root == NULL) return 0;

    Stack stack;
    InitStack(&stack);
    Push(&stack, root);

    int count = 0;

    while (!IsEmpty(&stack)) {
        TreeNode* current = Pop(&stack);
        count++;

        if (current->right) {
            Push(&stack, current->right);
        }
        if (current->left) {
            Push(&stack, current->left);
        }
    }

    return count;
}

int GetHeightOfTree(TreeNode* root) {
    if (root == NULL) return 0;

    Stack stack;
    InitStack(&stack);
    Push(&stack, root);

    int maxDepth = 0;
    TreeNode* current = root;

    while (current != NULL || !IsEmpty(&stack)) {
        if (current != NULL) {
            Push(&stack, current);
            current = current->left;
        }
        else {
            current = Pop(&stack);
            if (current->left == NULL && current->right == NULL) {
                int depth = stack.top + 1;
                if (depth > maxDepth) maxDepth = depth;
            }
            current = current->right;
        }
    }

    return maxDepth;
}

int GetNumberOfLeafNodes(TreeNode* root) {
    if (root == NULL) return 0;

    Stack stack;
    InitStack(&stack);
    Push(&stack, root);

    int leafCount = 0;

    while (!IsEmpty(&stack)) {
        TreeNode* current = Pop(&stack);

        if (current->left == NULL && current->right == NULL) {
            leafCount++;
        }

        if (current->right) {
            Push(&stack, current->right);
        }
        if (current->left) {
            Push(&stack, current->left);
        }
    }

    return leafCount;
}

int main() {
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->data = 1;
    root->left = root->right = NULL;

    GenerateLinkTree(root);

    printf("Sum of nodes: %d\n", GetSumOfNodes(root));
    printf("Number of nodes: %d\n", GetNumberOfNodes(root));
    printf("Height of Tree: %d\n", GetHeightOfTree(root));
    printf("Number of leaf nodes: %d\n", GetNumberOfLeafNodes(root));

    return 0;
}
