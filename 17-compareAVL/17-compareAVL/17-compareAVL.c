#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 노드 구조체 정의
typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height; // AVL 트리를 위한 높이
} Node;

// 전역 변수
int compareCount = 0; // 비교 횟수
int searchCount = 0;  // 탐색 횟수

// 노드 생성 함수
Node* createNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1; // AVL 트리를 위한 초기 높이
    return node;
}

// 트리 높이 반환
int height(Node* node) {
    return node ? node->height : 0;
}

// AVL 트리의 균형 계수 반환
int getBalance(Node* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

// AVL 트리 오른쪽 회전
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T = x->right;

    x->right = y;
    y->left = T;

    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));

    return x;
}

// AVL 트리 왼쪽 회전
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T = y->left;

    y->left = x;
    x->right = T;

    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));

    return y;
}

// AVL 삽입
Node* insertAVL(Node* node, int key) {
    if (!node) return createNode(key);

    compareCount++;
    if (key < node->key)
        node->left = insertAVL(node->left, key);
    else if (key > node->key)
        node->right = insertAVL(node->right, key);
    else
        return node; // 중복 키 무시

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

// BST 삽입
Node* insertBST(Node* node, int key) {
    if (!node) return createNode(key);

    compareCount++;
    if (key < node->key)
        node->left = insertBST(node->left, key);
    else if (key > node->key)
        node->right = insertBST(node->right, key);

    return node;
}

// 탐색
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

// 트리 메모리 해제
void freeTree(Node* node) {
    if (!node) return;
    freeTree(node->left);
    freeTree(node->right);
    free(node);
}

// AVL 테스트 배치
void doAVLBatch(Node* root) {
    for (int i = 0; i < 2000; i++) {
        int A = rand() % 3;   // 0, 1, 2 중 하나
        int B = rand() % 1000; // 0 ~ 999 중 하나

        if (A == 0) {
            root = insertAVL(root, B);
        }
        else if (A == 1) {
            // AVL 삭제 구현 생략 가능
        }
        else if (A == 2) {
            search(root, B); // search 함수에 두 개의 인수 넘기기
            searchCount++;
        }
    }
}

// BST 테스트 배치
void doBinaryBatch(Node* root) {
    for (int i = 0; i < 2000; i++) {
        int A = rand() % 3;   // 0, 1, 2 중 하나
        int B = rand() % 1000; // 0 ~ 999 중 하나

        if (A == 0) {
            root = insertBST(root, B);
        }
        else if (A == 1) {
            // BST 삭제 구현 생략 가능
        }
        else if (A == 2) {
            search(root, B); // search 함수에 두 개의 인수 넘기기
            searchCount++;
        }
    }
}

// 메인 함수
int main(int argc, char* argv[]) {
    for (int i = 0; i < 3; i++) {
        Node* root = NULL;
        srand(time(NULL) + i); // 시드값 변경

        float allCount = 0.0;

        // AVL 트리 배치 실행
        doAVLBatch(root);
        allCount = (float)compareCount / searchCount;
        printf("average AVL compare count: %.2f\n", allCount);

        // 트리 해제
        freeTree(root);
        root = NULL;
        compareCount = searchCount = 0;

        // 이진 탐색 트리 배치 실행
        doBinaryBatch(root);
        allCount = (float)compareCount / searchCount;
        printf("average Bin compare count: %.2f\n", allCount);

        freeTree(root);

        if (i < 2) {
            printf("\n"); // 결과 간 공백
        }
    }

    return 0;
}
