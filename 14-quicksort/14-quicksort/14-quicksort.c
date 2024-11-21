#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

int comparisonCount = 0; // �� Ƚ��
int moveCount = 0;       // �̵� Ƚ��
int rounds = 0;          // ��� ����� ����
int isFirst = 0;         // ù ��° ���� ���� Ȯ�� ����

// �迭 ��� �Լ�
void printArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

// ���� �迭 ���� �Լ�
void generateRandomArray(int array[]) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000; // 0~999 ������ ���� �� ����
    }
}

// �� ������ ���� �Լ�
int partition(int array[], int low, int high) {
    int pivot = array[high]; // �ǹ� ���� (������ ���)
    int i = low - 1;         // ���� ����� �ε���

    for (int j = low; j < high; j++) {
        comparisonCount++; // �� Ƚ�� ����
        if (array[j] < pivot) {
            i++;
            // �迭 ��� ��ȯ
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            moveCount += 3; // �̵�: temp ����, array[i]�� array[j] ��ȯ
        }
    }

    // �ǹ��� �ùٸ� ��ġ�� �̵�
    int temp = array[i + 1];
    array[i + 1] = array[high];
    array[high] = temp;
    moveCount += 3; // �̵�: temp ����, array[i+1]�� array[high] ��ȯ

    return i + 1; // �ǹ��� ���� ��ġ ��ȯ
}

// �ݺ��� �� ���� �Լ�
void doIterativeQuickSort(int array[], int low, int high) {
    int stack[SIZE]; // ���� ����
    int top = -1;    // ������ �ֻ��� �ε���

    // �ʱ� ������ ���ÿ� ����
    stack[++top] = low;
    stack[++top] = high;

    // ������ �� ������ �ݺ�
    while (top >= 0) {
        // ���ÿ��� ���� ���� ���� ������
        high = stack[top--];
        low = stack[top--];

        // ���� ����
        int pi = partition(array, low, high);

        // ��� ����: 14��° ���ึ�� 40~60�� �ε��� ���
        if (rounds % 14 == 0 && isFirst == 0) {
            for (int i = 40; i < 60; i++) {
                printf("%d ", array[i]);
            }
            printf("\n\n");
        }
        rounds++;

        // ���� �� ���� ���� �迭�� ���ÿ� ����
        if (pi - 1 > low) {
            stack[++top] = low;
            stack[++top] = pi - 1;
        }

        // ���� �� ������ ���� �迭�� ���ÿ� ����
        if (pi + 1 < high) {
            stack[++top] = pi + 1;
            stack[++top] = high;
        }
    }
}

// ���� �Լ�
int main(int argc, char* argv[]) {
    srand(time(NULL)); // ���� �õ� ����
    int array[SIZE];
    double totalComparisons = 0; // �� �� Ƚ��
    double totalMoveCount = 0;   // �� �̵� Ƚ��

    for (int i = 0; i < 20; i++) {
        generateRandomArray(array); // ���� �迭 ����
        comparisonCount = 0;        // �� Ƚ�� �ʱ�ȭ
        moveCount = 0;              // �̵� Ƚ�� �ʱ�ȭ

        if (i == 0) { // ù ��° ���� �� ���
            printf("Quick Sort Run\n");
            doIterativeQuickSort(array, 0, SIZE - 1); // �ݺ��� �� ���� ����
            printf("Result\n");
            printArray(array, SIZE); // ���� ��� ���
            isFirst++;
        }
        else {
            doIterativeQuickSort(array, 0, SIZE - 1); // �ݺ��� �� ���� ����
        }

        totalComparisons += comparisonCount; // �� �� Ƚ�� ����
        totalMoveCount += moveCount;         // �� �̵� Ƚ�� ����
    }

    // ��� �� �� �̵� Ƚ�� ���
    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoveCount / 20.0);

    return 0;
}
