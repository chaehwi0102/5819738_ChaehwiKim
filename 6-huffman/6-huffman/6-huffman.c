#include <stdio.h>
#include <stdlib.h>

// 허프만 트리 정의
struct Node {
    char character; // 문자
    int frequency;  // 빈도수
    struct Node* left, * right; // 왼쪽, 오른쪽 자식 노드
};

// 노드 생성
struct Node* createNode(char character, int frequency) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->character = character;
    node->frequency = frequency;
    node->left = node->right = NULL;
    return node;
}

// 두 노드를 교환
void swapNodes(struct Node** a, struct Node** b) {
    struct Node* temp = *a;
    *a = *b;
    *b = temp;
}

// 최소 힙을 정렬하는 함수
void minHeapify(struct Node** arr, int size, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < size && arr[left]->frequency < arr[smallest]->frequency)
        smallest = left;

    if (right < size && arr[right]->frequency < arr[smallest]->frequency)
        smallest = right;

    if (smallest != idx) {
        swapNodes(&arr[smallest], &arr[idx]);
        minHeapify(arr, size, smallest);
    }
}

// 힙에서 최소 빈도 노드를 추출
struct Node* extractMin(struct Node** arr, int* size) {
    struct Node* temp = arr[0];
    arr[0] = arr[*size - 1];
    (*size)--;
    minHeapify(arr, *size, 0);
    return temp;
}

// 힙에 노드를 삽입
void insertHeap(struct Node** arr, int* size, struct Node* node) {
    (*size)++;
    int i = *size - 1;
    arr[i] = node;

    while (i && arr[i]->frequency < arr[(i - 1) / 2]->frequency) {
        swapNodes(&arr[i], &arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// 각 단계에서 힙 출력
void printHeap(struct Node** heap, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", heap[i]->frequency);
    }
    printf("\n");
}

// 허프만 트리를 구축하고 각 단계 표시
struct Node* buildHuffmanTree(char characters[], int frequencies[], int size) {
    struct Node** heap = (struct Node**)malloc(size * sizeof(struct Node*));

    // 1단계: 문자와 빈도를 가지고 최소 힙 생성
    for (int i = 0; i < size; i++)
        heap[i] = createNode(characters[i], frequencies[i]);

    int heapSize = size;
    for (int i = (heapSize - 2) / 2; i >= 0; i--)
        minHeapify(heap, heapSize, i);

    // 초기 힙 출력
    printHeap(heap, heapSize);

    // 2단계: 허프만 트리 구축
    while (heapSize > 1) {
        struct Node* left = extractMin(heap, &heapSize);
        struct Node* right = extractMin(heap, &heapSize);

        // 병합 작업 출력
        printf("///%d + %d -> %d\n", left->frequency, right->frequency, left->frequency + right->frequency);

        // 두 개의 가장 작은 노드를 병합하여 새로운 내부 노드 생성
        struct Node* newNode = createNode('$', left->frequency + right->frequency);
        newNode->left = left;
        newNode->right = right;

        insertHeap(heap, &heapSize, newNode);

        // 각 병합 후 힙 출력
        printHeap(heap, heapSize);
    }

    return heap[0];
}

// 허프만 코드를 출력
void printCodes(struct Node* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 1;
        printCodes(root->left, arr, top + 1);
    }

    if (root->right) {
        arr[top] = 0;
        printCodes(root->right, arr, top + 1);
    }

    if (!(root->left) && !(root->right)) {
        printf("%c: ", root->character);
        for (int i = 0; i < top; i++)
            printf("%d", arr[i]);
        printf("\n");
    }
}

// 허프만 코드를 생성하는 메인 함수
int main() {
    char characters[] = { 'a', 'e', 'i', 'o', 'u', 's', 't' };
    int frequencies[] = { 10, 15, 12, 3, 4, 13, 1 };
    int size = sizeof(characters) / sizeof(characters[0]);

    struct Node* root = buildHuffmanTree(characters, frequencies, size);

    int arr[100], top = 0;
    printCodes(root, arr, top);

    return 0;
}
