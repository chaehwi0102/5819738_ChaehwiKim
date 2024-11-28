#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 10000

void generateRandomArray(int* array);
void QuickSort(int* array, int left, int right);
int partition(int* array, int left, int right);
void printArray(int* array);
double getAverageBinarySearchCompareCount(int* array);
double getAverageInterpolationSearchCompareCount(int* array);
int binarySearch(int* array, int size, int target, int* compareCount);
int interpolationSearch(int* array, int size, int target, int* compareCount);

int main() {
    srand(time(NULL)); // Seed ����

    for (int run = 0; run < 3; run++) { // 3�� �ݺ�
        int array[SIZE];
        generateRandomArray(array);

        // QuickSort ����
        QuickSort(array, 0, SIZE - 1);

        // �迭 ���
        printArray(array);

        // Binary Search ��� �� Ƚ�� ���
        printf("Average Compare Count of Binary Search: %.2f\n",
            getAverageBinarySearchCompareCount(array));

        // Interpolation Search ��� �� Ƚ�� ���
        printf("Average Compare Count of Interpolation Search: %.2f\n",
            getAverageInterpolationSearchCompareCount(array));

        printf("\n"); // �� ���� ��� ������ ���� �ٹٲ� �߰�
    }

    return 0;
}

// ���� �迭 ���� �Լ�
void generateRandomArray(int* array) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 10000; // 0 ~ 9999 ������ ���� ����
    }
}

// QuickSort ���� �Լ�
void QuickSort(int* array, int left, int right) {
    if (left < right) {
        int pivot = partition(array, left, right);
        QuickSort(array, left, pivot - 1);
        QuickSort(array, pivot + 1, right);
    }
}

// QuickSort �ǹ� ���� �Լ�
int partition(int* array, int left, int right) {
    int pivot = array[right];
    int i = left - 1;
    for (int j = left; j < right; j++) {
        if (array[j] <= pivot) {
            i++;
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    int temp = array[i + 1];
    array[i + 1] = array[right];
    array[right] = temp;
    return i + 1;
}

// �迭 ��� �Լ�
void printArray(int* array) {
    printf("Array Sorting Result:\n");

    for (int i = 0; i < 20; i++)
        printf("%4d ", array[i]);
    printf("\n");
    for (int i = SIZE - 20; i < SIZE; i++)
        printf("%4d ", array[i]);
    printf("\n\n");
}

// Binary Search ��� �� Ƚ�� ���
double getAverageBinarySearchCompareCount(int* array) {
    int totalCompareCount = 0;
    for (int i = 0; i < 1000; i++) {
        int compareCount = 0;
        int target = array[rand() % SIZE];
        binarySearch(array, SIZE, target, &compareCount);
        totalCompareCount += compareCount;
    }
    return totalCompareCount / 1000.0;
}

// Binary Search ����
int binarySearch(int* array, int size, int target, int* compareCount) {
    int left = 0, right = size - 1;
    while (left <= right) {
        (*compareCount)++;
        int mid = left + (right - left) / 2;
        if (array[mid] == target)
            return mid;
        if (array[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

// Interpolation Search ��� �� Ƚ�� ���
double getAverageInterpolationSearchCompareCount(int* array) {
    int totalCompareCount = 0;
    for (int i = 0; i < 1000; i++) {
        int compareCount = 0;
        int target = array[rand() % SIZE];
        interpolationSearch(array, SIZE, target, &compareCount);
        totalCompareCount += compareCount;
    }
    return totalCompareCount / 1000.0;
}

// Interpolation Search ����
int interpolationSearch(int* array, int size, int target, int* compareCount) {
    int left = 0, right = size - 1;
    while (left <= right && target >= array[left] && target <= array[right]) {
        (*compareCount)++;
        if (left == right) {
            if (array[left] == target)
                return left;
            return -1;
        }
        int pos = left + ((double)(right - left) /
            (array[right] - array[left]) * (target - array[left]));
        if (array[pos] == target)
            return pos;
        if (array[pos] < target)
            left = pos + 1;
        else
            right = pos - 1;
    }
    return -1;
}
