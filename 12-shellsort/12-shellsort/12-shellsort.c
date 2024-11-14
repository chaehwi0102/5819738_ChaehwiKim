#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 100
#define RUNS 20

// ���� ���� ���� �Լ�
void generateRandomNumbers(int array[]) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = rand() % 1000;  // 0���� 999 ������ ���� ���� ����
    }
}

// �迭�� ó�� 20�� ��Ҹ� ����ϴ� �Լ�
void printArray(int array[], int n) {
    for (int i = 0; i < n; i++) {
        if (i > 0 && i % 10 == 0) printf(" ");  // 10������ ���� �߰�
        printf("%d ", array[i]);
    }
    printf("...\n");
}

// �� ���� �Լ� (�� ������ ���� n/2 �Ǵ� n/3 ������� ����)
void doShellSort(int array[], int gapType, int* comparisonCount, int* moveCount) {
    int n = ARRAY_SIZE;
    int gap = gapType == 2 ? n / 2 : n / 3;  // n/2 �Ǵ� n/3���� ����

    *comparisonCount = 0;  // �� Ƚ�� �ʱ�ȭ
    *moveCount = 0;        // �̵� Ƚ�� �ʱ�ȭ

    while (gap > 0) {  // ���� 0���� Ŭ ������ �ݺ�
        printf("Sorting with gap = %d:\n", gap);
        for (int i = gap; i < n; i++) {
            int temp = array[i];
            (*moveCount)++;  // temp�� ���� �ִ� �̵� Ƚ�� ����
            int j;
            for (j = i; j >= gap && array[j - gap] > temp; j -= gap) {
                array[j] = array[j - gap];  // ���� �̵���Ű�鼭 �� Ƚ�� ����
                (*comparisonCount)++;
                (*moveCount)++;
            }
            array[j] = temp;  // temp ���� ���� ��ġ�� �����ϰ� �̵� Ƚ�� ����
            (*moveCount)++;
        }
        printArray(array, 20);  // �� �� �ܰ� �� �迭�� ó�� 20�� ��� ���

        // ���� �� ������ ���� ������ (n/2 �Ǵ� n/3)
        gap = gapType == 2 ? gap / 2 : gap / 3;
    }
}

// ���� ���� �Լ�
void doInsertionSort(int array[], int* comparisonCount, int* moveCount) {
    int n = ARRAY_SIZE;
    *comparisonCount = 0;  // �� Ƚ�� �ʱ�ȭ
    *moveCount = 0;        // �̵� Ƚ�� �ʱ�ȭ

    for (int i = 1; i < n; i++) {
        int temp = array[i];
        (*moveCount)++;  // temp�� ���� �ִ� �̵� Ƚ�� ����
        int j = i - 1;

        while (j >= 0 && array[j] > temp) {
            array[j + 1] = array[j];
            (*comparisonCount)++;  // �� Ƚ�� ����
            (*moveCount)++;        // �̵� Ƚ�� ����
            j--;
        }
        array[j + 1] = temp;  // temp ���� ���� ��ġ�� �����ϰ� �̵� Ƚ�� ����
        (*moveCount)++;
    }
}

// ���� �Լ�
int main() {
    int array[ARRAY_SIZE];
    int comparisonCount, moveCount;

    srand(time(NULL));

    generateRandomNumbers(array);
    printf("Shell Sort (n/2):\n");
    doShellSort(array, 2, &comparisonCount, &moveCount);
    printf("Sorted shellArray (gap = 2):\n");
    printArray(array, 20);
    printf("Shell Sort (n/2) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    generateRandomNumbers(array);
    printf("Shell Sort (n/3):\n");
    doShellSort(array, 3, &comparisonCount, &moveCount);
    printf("Sorted shellArray (gap = 3):\n");
    printArray(array, 20);
    printf("Shell Sort (n/3) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    generateRandomNumbers(array);
    printf("Insertion Sort:\n");
    doInsertionSort(array, &comparisonCount, &moveCount);
    printf("Sorted insertionArray:\n");
    printArray(array, 20);
    printf("Insertion Sort - Comparisons: %d, Moves: %d\n", comparisonCount, moveCount);

    return 0;
}
