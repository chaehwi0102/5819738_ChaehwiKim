#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 100
#define RUNS 20

// 랜덤 숫자 생성 함수
void generateRandomNumbers(int array[]) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = rand() % 1000;  // 0부터 999 사이의 랜덤 숫자 생성
    }
}

// 배열의 처음 20개 요소를 출력하는 함수
void printArray(int array[], int n) {
    for (int i = 0; i < n; i++) {
        if (i > 0 && i % 10 == 0) printf(" ");  // 10개마다 공백 추가
        printf("%d ", array[i]);
    }
    printf("...\n");
}

// 쉘 정렬 함수 (갭 유형에 따라 n/2 또는 n/3 방식으로 정렬)
void doShellSort(int array[], int gapType, int* comparisonCount, int* moveCount) {
    int n = ARRAY_SIZE;
    int gap = gapType == 2 ? n / 2 : n / 3;  // n/2 또는 n/3에서 시작

    *comparisonCount = 0;  // 비교 횟수 초기화
    *moveCount = 0;        // 이동 횟수 초기화

    while (gap > 0) {  // 갭이 0보다 클 때까지 반복
        printf("Sorting with gap = %d:\n", gap);
        for (int i = gap; i < n; i++) {
            int temp = array[i];
            (*moveCount)++;  // temp에 값을 넣는 이동 횟수 증가
            int j;
            for (j = i; j >= gap && array[j - gap] > temp; j -= gap) {
                array[j] = array[j - gap];  // 값을 이동시키면서 비교 횟수 증가
                (*comparisonCount)++;
                (*moveCount)++;
            }
            array[j] = temp;  // temp 값을 원래 위치에 삽입하고 이동 횟수 증가
            (*moveCount)++;
        }
        printArray(array, 20);  // 각 갭 단계 후 배열의 처음 20개 요소 출력

        // 갭을 갭 유형에 따라 나누기 (n/2 또는 n/3)
        gap = gapType == 2 ? gap / 2 : gap / 3;
    }
}

// 삽입 정렬 함수
void doInsertionSort(int array[], int* comparisonCount, int* moveCount) {
    int n = ARRAY_SIZE;
    *comparisonCount = 0;  // 비교 횟수 초기화
    *moveCount = 0;        // 이동 횟수 초기화

    for (int i = 1; i < n; i++) {
        int temp = array[i];
        (*moveCount)++;  // temp에 값을 넣는 이동 횟수 증가
        int j = i - 1;

        while (j >= 0 && array[j] > temp) {
            array[j + 1] = array[j];
            (*comparisonCount)++;  // 비교 횟수 증가
            (*moveCount)++;        // 이동 횟수 증가
            j--;
        }
        array[j + 1] = temp;  // temp 값을 원래 위치에 삽입하고 이동 횟수 증가
        (*moveCount)++;
    }
}

// 메인 함수
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
