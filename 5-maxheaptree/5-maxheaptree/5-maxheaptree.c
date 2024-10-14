#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int key;
    struct TreeNode* left;
    struct TreeNode* right;
    struct TreeNode* parent;
} TreeNode;

TreeNode* insertMaxHeapTree(TreeNode* root, int key, int* moves);
TreeNode* deleteMaxHeapTree(TreeNode* root, int* moves);
void heapify(TreeNode* node, int* moves);
void printCurrentHeap(TreeNode* root);
void printLevelOrder(TreeNode* root);
void freeTree(TreeNode* root);
void runUserInterface(TreeNode* root);
void buildMaxHeap(TreeNode** root, int* arr, int size);

TreeNode* createNode(int key) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;
    return newNode;
}

void printCurrentHeap(TreeNode* root) {
    if (!root) return;

    TreeNode** queue = (TreeNode**)malloc(100 * sizeof(TreeNode*));
    int front = 0, rear = 0;

    queue[rear++] = root;

    while (front < rear) {
        TreeNode* current = queue[front++];
        printf("%d ", current->key);
        if (current->left) queue[rear++] = current->left;
        if (current->right) queue[rear++] = current->right;
    }
    printf("\n");
    free(queue);
}

TreeNode* insertMaxHeapTree(TreeNode* root, int key, int* moves) {
    TreeNode* newNode = createNode(key);
    if (!root) {
        return newNode;
    }

    TreeNode** queue = (TreeNode**)malloc(100 * sizeof(TreeNode*));
    int front = 0, rear = 0;

    queue[rear++] = root;

    while (front < rear) {
        TreeNode* current = queue[front++];

        if (!current->left) {
            current->left = newNode;
            newNode->parent = current;
            break;
        }
        queue[rear++] = current->left;

        if (!current->right) {
            current->right = newNode;
            newNode->parent = current;
            break;
        }
        queue[rear++] = current->right;
    }

    free(queue);

    TreeNode* temp = newNode;
    while (temp->parent && temp->key > temp->parent->key) {
        int parentKey = temp->parent->key;
        temp->parent->key = temp->key;
        temp->key = parentKey;

        printCurrentHeap(root);

        temp = temp->parent;
        (*moves)++;
    }

    return root;
}

TreeNode* deleteMaxHeapTree(TreeNode* root, int* moves) {
    if (!root) return NULL;

    if (!root->left && !root->right) {
        free(root);
        return NULL;
    }

    TreeNode* lastNode = NULL;
    TreeNode** queue = (TreeNode**)malloc(100 * sizeof(TreeNode*));
    int front = 0, rear = 0;

    queue[rear++] = root;

    while (front < rear) {
        lastNode = queue[front++];

        if (lastNode->left) {
            queue[rear++] = lastNode->left;
        }
        if (lastNode->right) {
            queue[rear++] = lastNode->right;
        }
    }

    root->key = lastNode->key;

    if (lastNode->parent) {
        if (lastNode->parent->left == lastNode) {
            lastNode->parent->left = NULL;
        }
        else {
            lastNode->parent->right = NULL;
        }
    }
    free(lastNode);
    (*moves)++;

    printCurrentHeap(root);

    heapify(root, moves);

    printCurrentHeap(root);

    free(queue);
    return root;
}

void heapify(TreeNode* node, int* moves) {
    if (!node) return;

    TreeNode* largest = node;
    TreeNode* left = node->left;
    TreeNode* right = node->right;

    if (left && left->key > largest->key) {
        largest = left;
    }

    if (right && right->key > largest->key) {
        largest = right;
    }

    if (largest != node) {
        int temp = node->key;
        node->key = largest->key;
        largest->key = temp;
        (*moves)++;

        heapify(largest, moves);
    }
}

void printLevelOrder(TreeNode* root) {
    if (!root) return;

    TreeNode** queue = (TreeNode**)malloc(100 * sizeof(TreeNode*)); // ������ ť ���
    int front = 0, rear = 0;

    queue[rear++] = root;

    int level = 1;
    while (front < rear) {
        int levelSize = rear - front;
        printf("[%d] ", level++);
        for (int i = 0; i < levelSize; i++) {
            TreeNode* current = queue[front++];
            printf("%d ", current->key);
            if (current->left) queue[rear++] = current->left;
            if (current->right) queue[rear++] = current->right;
        }
        printf("\n");
    }
    free(queue);
}

void freeTree(TreeNode* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

void runUserInterface(TreeNode* root) {
    char choice;
    int value;
    int moves;

    while (1) {
        printf("\n�޴� �׸� ����\n");
        printf("i: �Է��� �޾� �ִ� ������ �߰�\n");
        printf("d: �ִ� �������� ��Ʈ ��� ����\n");
        printf("p: ������ ��Ʈ�������� �������� ���\n");
        printf("c: ����\n");
        printf("\n�޴� �Է�: ");
        scanf(" %c", &choice);

        switch (choice) {
        case 'i':
            printf("�߰��� �� �Է�: ");
            scanf("%d", &value);
            moves = 0;
            root = insertMaxHeapTree(root, value, &moves);
            printf("��尡 �̵��� Ƚ��: %d\n", moves);
            break;
        case 'd':
            moves = 0;
            root = deleteMaxHeapTree(root, &moves);
            printf("��尡 �̵��� Ƚ��: %d\n", moves);
            break;
        case 'p':
            printf("Ʈ�� ������ ���\n");
            printLevelOrder(root);
            break;
        case 'c':
            printf("���α׷� ����");
            return;
        default:
            printf("�߸��� �����Դϴ�. �ٽ� �õ��ϼ���.\n");
        }
    }
}

void buildMaxHeap(TreeNode** root, int* arr, int size) {
    for (int i = 0; i < size; i++) {
        int moves = 0;
        *root = insertMaxHeapTree(*root, arr[i], &moves);
    }
}

int main() {
    int inputData[] = { 90, 89, 70, 36, 75, 63, 65, 21, 18, 15 };
    int size = sizeof(inputData) / sizeof(inputData[0]);
    TreeNode* root = NULL;

    buildMaxHeap(&root, inputData, size);

    runUserInterface(root);

    freeTree(root);
    return 0;
}