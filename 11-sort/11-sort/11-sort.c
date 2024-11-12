#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

// Generate random data between 0 and 999
void generateRandomData(int* data) {
    for (int i = 0; i < SIZE; i++) {
        data[i] = rand() % 1000;
    }
}

// Selection Sort with step output at 10th and 20-interval steps
void doSelectionSort(int* data) {
    int temp[SIZE];
    for (int i = 0; i < SIZE; i++) temp[i] = data[i];

    printf("Selection Sort steps:\n");
    for (int i = 0; i < SIZE - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < SIZE; j++) {
            if (temp[j] < temp[minIndex]) minIndex = j;
        }
        int swap = temp[i];
        temp[i] = temp[minIndex];
        temp[minIndex] = swap;

        if ((i == 9) || (i >= 10 && (i - 9) % 20 == 0) || i == 98) {
            printf("Step %d: ", i + 1);
            for (int k = 0; k < SIZE; k++) printf("%d ", temp[k]);
            printf("\n");
        }
    }
}

// Insertion Sort with average comparisons over 20 trials
void doInsertionSort(int* data) {
    int totalComparisons = 0;

    for (int t = 0; t < 20; t++) {
        int temp[SIZE];
        for (int i = 0; i < SIZE; i++) temp[i] = data[i];

        int comparisons = 0;
        for (int i = 1; i < SIZE; i++) {
            int key = temp[i], j = i - 1;
            while (j >= 0 && temp[j] > key) {
                temp[j + 1] = temp[j];
                j--;
                comparisons++;
            }
            comparisons++;
            temp[j + 1] = key;
        }
        totalComparisons += comparisons;
    }

    printf("Insertion Sort Average Comparisons: %d\n", totalComparisons / 20);
    printf("Sorted result: ");
    for (int i = 0; i < SIZE; i++) printf("%d ", data[i]);
    printf("\n");
}

// Bubble Sort with average moves over 20 trials
void doBubbleSort(int* data) {
    int totalMoves = 0;

    for (int t = 0; t < 20; t++) {
        int temp[SIZE];
        for (int i = 0; i < SIZE; i++) temp[i] = data[i];

        int moves = 0;
        for (int i = 0; i < SIZE - 1; i++) {
            for (int j = 0; j < SIZE - i - 1; j++) {
                if (temp[j] > temp[j + 1]) {
                    int swap = temp[j];
                    temp[j] = temp[j + 1];
                    temp[j + 1] = swap;
                    moves++;
                }
            }
        }
        totalMoves += moves;
    }

    printf("Bubble Sort Average Moves: %d\n", totalMoves / 20);
    printf("Sorted result: ");
    for (int i = 0; i < SIZE; i++) printf("%d ", data[i]);
    printf("\n");
}

int main() {
    srand(time(0));
    int randomData[SIZE];
    generateRandomData(randomData);

    doSelectionSort(randomData);
    printf("\n");
    doInsertionSort(randomData);
    printf("\n");
    doBubbleSort(randomData);

    return 0;
}
