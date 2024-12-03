#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ��� ����ü ����
typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height; // AVL Ʈ���� ���� ����
} Node;

// ���� ����
int compareCount = 0; // �� Ƚ��
int searchCount = 0;  // Ž�� Ƚ��

// ��� ���� �Լ�
Node* createNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1; // AVL Ʈ���� ���� �ʱ� ����
    return node;
}

// Ʈ�� ���� ��ȯ
int height(Node* node) {
    return node ? node->height : 0;
}

// AVL Ʈ���� ���� ��� ��ȯ
int getBalance(Node* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

// AVL Ʈ�� ������ ȸ��
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T = x->right;

    x->right = y;
    y->left = T;

    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));

    return x;
}

// AVL Ʈ�� ���� ȸ��
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T = y->left;

    y->left = x;
    x->right = T;

    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));

    return y;
}

// AVL ����
Node* insertAVL(Node* node, int key) {
    if (!node) return createNode(key);

    compareCount++;
    if (key < node->key)
        node->left = insertAVL(node->left, key);
    else if (key > node->key)
        node->right = insertAVL(node->right, key);
    else
        return node; // �ߺ� Ű ����

    node->height = 1 + (height(node->left) > height(node->right) ? height(node->left) : height(node->right));
    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
        return rotateRight(node);
    if (balance < -1 && key > node->right->key)
        return rotateLeft(node);
    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// BST ����
Node* insertBST(Node* node, int key) {
    if (!node) return createNode(key);

    compareCount++;
    if (key < node->key)
        node->left = insertBST(node->left, key);
    else if (key > node->key)
        node->right = insertBST(node->right, key);

    return node;
}

// Ž��
void search(Node* node, int key) {
    if (!node) return;

    compareCount++;
    if (key == node->key)
        return;
    else if (key < node->key)
        search(node->left, key);
    else
        search(node->right, key);
}

// Ʈ�� �޸� ����
void freeTree(Node* node) {
    if (!node) return;
    freeTree(node->left);
    freeTree(node->right);
    free(node);
}

// AVL �׽�Ʈ ��ġ
void doAVLBatch(Node* root) {
    for (int i = 0; i < 2000; i++) {
        int A = rand() % 3;   // 0, 1, 2 �� �ϳ�
        int B = rand() % 1000; // 0 ~ 999 �� �ϳ�

        if (A == 0) {
            root = insertAVL(root, B);
        }
        else if (A == 1) {
            // AVL ���� ���� ���� ����
        }
        else if (A == 2) {
            search(root, B); // search �Լ��� �� ���� �μ� �ѱ��
            searchCount++;
        }
    }
}

// BST �׽�Ʈ ��ġ
void doBinaryBatch(Node* root) {
    for (int i = 0; i < 2000; i++) {
        int A = rand() % 3;   // 0, 1, 2 �� �ϳ�
        int B = rand() % 1000; // 0 ~ 999 �� �ϳ�

        if (A == 0) {
            root = insertBST(root, B);
        }
        else if (A == 1) {
            // BST ���� ���� ���� ����
        }
        else if (A == 2) {
            search(root, B); // search �Լ��� �� ���� �μ� �ѱ��
            searchCount++;
        }
    }
}

// ���� �Լ�
int main(int argc, char* argv[]) {
    for (int i = 0; i < 3; i++) {
        Node* root = NULL;
        srand(time(NULL) + i); // �õ尪 ����

        float allCount = 0.0;

        // AVL Ʈ�� ��ġ ����
        doAVLBatch(root);
        allCount = (float)compareCount / searchCount;
        printf("average AVL compare count: %.2f\n", allCount);

        // Ʈ�� ����
        freeTree(root);
        root = NULL;
        compareCount = searchCount = 0;

        // ���� Ž�� Ʈ�� ��ġ ����
        doBinaryBatch(root);
        allCount = (float)compareCount / searchCount;
        printf("average Bin compare count: %.2f\n", allCount);

        freeTree(root);

        if (i < 2) {
            printf("\n"); // ��� �� ����
        }
    }

    return 0;
}
