#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100 // �迭 ũ�⸦ ����� ����

int comparisonCount = 0; // �� Ƚ��
int moveCount = 0;       // �̵� Ƚ��

// �迭 ��� �Լ�
void printArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
}

// ���� �迭 ���� �Լ�
void generateRandomArray(int array[]) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000; // 0~999 ���� ���� ��
    }
}

// ���� �Լ�
void merge(int array[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int* tempLeft = (int*)malloc(n1 * sizeof(int));
    int* tempRight = (int*)malloc(n2 * sizeof(int));

    // ����, ������ �迭�� ����
    for (int i = 0; i < n1; i++) {
        tempLeft[i] = array[left + i];
        moveCount++; // �̵� Ƚ�� ����
    }
    for (int j = 0; j < n2; j++) {
        tempRight[j] = array[mid + 1 + j];
        moveCount++;
    }

    // ����
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        comparisonCount++; // �� Ƚ�� ����
        if (tempLeft[i] <= tempRight[j]) {
            array[k++] = tempLeft[i++];
            moveCount++;
        }
        else {
            array[k++] = tempRight[j++];
            moveCount++;
        }
    }

    // ������ ����
    while (i < n1) {
        array[k++] = tempLeft[i++];
        moveCount++;
    }
    while (j < n2) {
        array[k++] = tempRight[j++];
        moveCount++;
    }

    free(tempLeft);
    free(tempRight);
}

// �պ� ���� ��� �Լ�
void mergeSort(int array[], int left, int right, int* rounds, int isFirst) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(array, left, mid, rounds, isFirst);
        mergeSort(array, mid + 1, right, rounds, isFirst);

        merge(array, left, mid, right);

        (*rounds)++;
        if (*rounds % 10 == 0 && isFirst == 0) {
            for (int i = 0; i < 10; i++) {
                printf("%3d ", array[i]);
            }
            printf("| ");
            for (int i = SIZE / 2 - 1; i < SIZE / 2 + 10; i++) {
                printf("%3d ", array[i]);
            }
            printf("\n");
        }
    }
}

int main() {
    int array[SIZE];
    int totalComparisons = 0, totalMoves = 0;

    srand((unsigned)time(NULL));

    for (int i = 0; i < 20; i++) {
        generateRandomArray(array);
        comparisonCount = 0;
        moveCount = 0;
        int rounds = 0;

        if (i == 0) {
            printf("Merge Sort Run\n");
            mergeSort(array, 0, SIZE - 1, &rounds, 0);
            printf("\nResult\n");
            printArray(array, SIZE);
            printf("\n");
        }
        else {
            mergeSort(array, 0, SIZE - 1, &rounds, 1);
        }
        totalComparisons += comparisonCount;
        totalMoves += moveCount;
    }

    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoves / 20.0);

    return 0;
}
