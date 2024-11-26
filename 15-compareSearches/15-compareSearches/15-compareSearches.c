#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000 // �迭 ũ�� ����

// �Լ� ���� ����
void generateRandomArray(int* array); // ���� �迭 ����
float getAverageLinearSearchCompareCount(int* array); // ���� Ž���� ��� �� Ƚ�� ���
int getQuickSortCompareCount(int* array); // �� ���� �� Ƚ�� ���
float getAverageBinarySearchCompareCount(int* array); // ���� Ž���� ��� �� Ƚ�� ���
void quickSort(int* array, int low, int high); // �� ���� ����
int partition(int* array, int low, int high); // �� ������ ���� �Լ�
void printArray(int* array); // �迭 ���

int compareCount = 0; // �� ������ �� Ƚ���� ������ ���� ����

int main(int argc, char* argv[]) {
    srand(time(NULL)); // ���� �õ� �ʱ�ȭ

    for (int run = 1; run <= 3; run++) { // ��ü ������ 3�� �ݺ�
        int array[SIZE];

        // ���� �迭 ����
        generateRandomArray(array);

        // ���� Ž�� 100ȸ ���� �� ��� �� Ƚ�� ���
        printf("Average Linear Search Compare Count: %.2f\n",
            getAverageLinearSearchCompareCount(array));

        // �� ���� ���� �� �� Ƚ�� ���
        compareCount = 0; // �� Ƚ�� �ʱ�ȭ
        getQuickSortCompareCount(array);
        printf("Quick Sort Compare Count: %d\n", compareCount);

        // ���ĵ� �迭�� ���� ���� Ž�� 100ȸ ���� �� ��� �� Ƚ�� ���
        printf("Average Binary Search Compare Count: %.2f\n\n",
            getAverageBinarySearchCompareCount(array));

        // ���ĵ� �迭 ��� (ó�� 20���� ������ 20�� ��� ���)
        printArray(array);

        printf("\n");
    }

    return 0;
}

// ���� �迭 ���� �Լ�
void generateRandomArray(int* array) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000; // 0���� 999 ������ ���� �� ����
    }
}

// ���� Ž���� ��� �� Ƚ�� ��� �Լ�
float getAverageLinearSearchCompareCount(int* array) {
    int totalComparisons = 0;

    for (int i = 0; i < 100; i++) { // 100ȸ Ž�� ����
        int target = array[rand() % SIZE]; // �迭���� ������ ���� Ž�� ���(target)���� ����
        int comparisons = 0;

        for (int j = 0; j < SIZE; j++) { // �迭�� ���������� Ž��
            comparisons++;
            if (array[j] == target) { // Ž�� ����� �߰ߵǸ� ���� ����
                break;
            }
        }

        totalComparisons += comparisons; // Ž�� �� �� Ƚ�� ����
    }

    return (float)totalComparisons / 100; // ��� �� Ƚ�� ��ȯ
}

// �� ���� �� Ƚ�� ��� �Լ�
int getQuickSortCompareCount(int* array) {
    quickSort(array, 0, SIZE - 1); // �� ���� ����
    return compareCount; // ��ü �� Ƚ�� ��ȯ
}

// �� ���� �Լ�
void quickSort(int* array, int low, int high) {
    if (low < high) { // ������ �ʿ��� ���
        int pivot = partition(array, low, high); // ���� ���� �� �ǹ� ��ġ ��ȯ
        quickSort(array, low, pivot - 1); // ���� ���� �迭 ����
        quickSort(array, pivot + 1, high); // ������ ���� �迭 ����
    }
}

// �� ������ ���� �Լ�
int partition(int* array, int low, int high) {
    int pivot = array[high]; // �ǹ� ���� (�迭�� ������ ���)
    int i = low - 1; // ���� ��Ҹ� ������ �ε��� �ʱ�ȭ

    for (int j = low; j < high; j++) { // �ǹ����� ���� ��Ҹ� �������� �̵�
        compareCount++; // �� Ƚ�� ����
        if (array[j] <= pivot) { // ���� ��Ұ� �ǹ� ������ ���
            i++;
            // ��� ��ȯ
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }

    // �ǹ� ��Ҹ� �ùٸ� ��ġ�� �̵�
    int temp = array[i + 1];
    array[i + 1] = array[high];
    array[high] = temp;

    return i + 1; // �ǹ� ��ġ ��ȯ
}

// ���� Ž���� ��� �� Ƚ�� ��� �Լ�
float getAverageBinarySearchCompareCount(int* array) {
    int totalComparisons = 0;

    for (int i = 0; i < 100; i++) { // 100ȸ Ž�� ����
        int target = array[rand() % SIZE]; // �迭���� ������ ���� Ž�� ���(target)���� ����
        int low = 0, high = SIZE - 1, comparisons = 0;

        while (low <= high) { // ���� Ž�� �ݺ�
            comparisons++;
            int mid = (low + high) / 2; // �߰� ��ġ ���

            if (array[mid] == target) { // ����� �߰ߵǸ� ���� ����
                break;
            }
            else if (array[mid] < target) { // ����� �߰� ������ ũ�� ������ Ž��
                low = mid + 1;
            }
            else { // ����� �߰� ������ ������ ���� Ž��
                high = mid - 1;
            }
        }

        totalComparisons += comparisons; // Ž�� �� �� Ƚ�� ����
    }

    return (float)totalComparisons / 100; // ��� �� Ƚ�� ��ȯ
}

// �迭 ��� �Լ� (ó�� 20���� ������ 20�� ��� ���)
void printArray(int* array) {
    printf("Array Sorting Result:\n");

    for (int i = 0; i < 20; i++) // ó�� 20�� ��� ���
        printf("%3d ", array[i]);
    printf("\n");
    for (int i = SIZE - 20; i < SIZE; i++) // ������ 20�� ��� ���
        printf("%3d ", array[i]);
    printf("\n");
}
