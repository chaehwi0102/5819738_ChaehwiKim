#include <stdio.h>
#include <stdlib.h>

// ������ Ʈ�� ����
struct Node {
    char character; // ����
    int frequency;  // �󵵼�
    struct Node* left, * right; // ����, ������ �ڽ� ���
};

// ��� ����
struct Node* createNode(char character, int frequency) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->character = character;
    node->frequency = frequency;
    node->left = node->right = NULL;
    return node;
}

// �� ��带 ��ȯ
void swapNodes(struct Node** a, struct Node** b) {
    struct Node* temp = *a;
    *a = *b;
    *b = temp;
}

// �ּ� ���� �����ϴ� �Լ�
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

// ������ �ּ� �� ��带 ����
struct Node* extractMin(struct Node** arr, int* size) {
    struct Node* temp = arr[0];
    arr[0] = arr[*size - 1];
    (*size)--;
    minHeapify(arr, *size, 0);
    return temp;
}

// ���� ��带 ����
void insertHeap(struct Node** arr, int* size, struct Node* node) {
    (*size)++;
    int i = *size - 1;
    arr[i] = node;

    while (i && arr[i]->frequency < arr[(i - 1) / 2]->frequency) {
        swapNodes(&arr[i], &arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// �� �ܰ迡�� �� ���
void printHeap(struct Node** heap, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", heap[i]->frequency);
    }
    printf("\n");
}

// ������ Ʈ���� �����ϰ� �� �ܰ� ǥ��
struct Node* buildHuffmanTree(char characters[], int frequencies[], int size) {
    struct Node** heap = (struct Node**)malloc(size * sizeof(struct Node*));

    // 1�ܰ�: ���ڿ� �󵵸� ������ �ּ� �� ����
    for (int i = 0; i < size; i++)
        heap[i] = createNode(characters[i], frequencies[i]);

    int heapSize = size;
    for (int i = (heapSize - 2) / 2; i >= 0; i--)
        minHeapify(heap, heapSize, i);

    // �ʱ� �� ���
    printHeap(heap, heapSize);

    // 2�ܰ�: ������ Ʈ�� ����
    while (heapSize > 1) {
        struct Node* left = extractMin(heap, &heapSize);
        struct Node* right = extractMin(heap, &heapSize);

        // ���� �۾� ���
        printf("///%d + %d -> %d\n", left->frequency, right->frequency, left->frequency + right->frequency);

        // �� ���� ���� ���� ��带 �����Ͽ� ���ο� ���� ��� ����
        struct Node* newNode = createNode('$', left->frequency + right->frequency);
        newNode->left = left;
        newNode->right = right;

        insertHeap(heap, &heapSize, newNode);

        // �� ���� �� �� ���
        printHeap(heap, heapSize);
    }

    return heap[0];
}

// ������ �ڵ带 ���
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

// ������ �ڵ带 �����ϴ� ���� �Լ�
int main() {
    char characters[] = { 'a', 'e', 'i', 'o', 'u', 's', 't' };
    int frequencies[] = { 10, 15, 12, 3, 4, 13, 1 };
    int size = sizeof(characters) / sizeof(characters[0]);

    struct Node* root = buildHuffmanTree(characters, frequencies, size);

    int arr[100], top = 0;
    printCodes(root, arr, top);

    return 0;
}
