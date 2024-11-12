#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

// 0과 999 사이의 랜덤 데이터를 생성하는 함수
void generateRandomData(int* data) {
    for (int i = 0; i < SIZE; i++) {
        data[i] = rand() % 1000;  // 0과 999 사이의 랜덤 수를 생성하여 배열에 저장
    }
}

// 선택 정렬을 수행하고 10번째, 20단위 간격으로 정렬 과정을 출력하는 함수
void doSelectionSort(int* data) {
    int temp[SIZE];
    for (int i = 0; i < SIZE; i++) temp[i] = data[i];  // 데이터를 임시 배열에 복사하여 정렬

    printf("Selection Sort steps:\n");
    for (int i = 0; i < SIZE - 1; i++) {
        int minIndex = i;
        // 정렬되지 않은 부분에서 최소값의 인덱스를 찾음
        for (int j = i + 1; j < SIZE; j++) {
            if (temp[j] < temp[minIndex]) minIndex = j;
        }
        // 현재 값과 최소값을 서로 교환
        int swap = temp[i];
        temp[i] = temp[minIndex];
        temp[minIndex] = swap;

        // 10번째, 20단위 간격, 마지막 단계에서 배열 상태 출력
        if ((i == 9) || (i >= 10 && (i - 9) % 20 == 0) || i == 98) {
            printf("Step %d: ", i + 1);
            for (int k = 0; k < SIZE; k++) printf("%d ", temp[k]);
            printf("\n");
        }
    }
}

// 삽입 정렬을 20번 실행하고 평균 비교 횟수와 정렬 결과를 출력하는 함수
void doInsertionSort(int* data) {
    int totalComparisons = 0;  // 전체 비교 횟수

    for (int t = 0; t < 20; t++) {  // 20번 실행
        int temp[SIZE];
        for (int i = 0; i < SIZE; i++) temp[i] = data[i];  // 데이터를 임시 배열에 복사

        int comparisons = 0;  // 각 실행에 대한 비교 횟수
        for (int i = 1; i < SIZE; i++) {
            int key = temp[i], j = i - 1;
            // key 값보다 큰 값은 한 칸씩 뒤로 이동
            while (j >= 0 && temp[j] > key) {
                temp[j + 1] = temp[j];
                j--;
                comparisons++;  // 비교 횟수 증가
            }
            comparisons++;  // key 값과 비교
            temp[j + 1] = key;  // key 값을 올바른 위치에 삽입
        }
        totalComparisons += comparisons;  // 총 비교 횟수에 더함
    }

    printf("Insertion Sort Average Comparisons: %d\n", totalComparisons / 20);  // 평균 비교 횟수 출력
    printf("Sorted result: ");
    for (int i = 0; i < SIZE; i++) printf("%d ", data[i]);  // 정렬된 배열 출력
    printf("\n");
}

// 버블 정렬을 20번 실행하고 평균 이동 횟수와 정렬 결과를 출력하는 함수
void doBubbleSort(int* data) {
    int totalMoves = 0;  // 전체 이동 횟수

    for (int t = 0; t < 20; t++) {  // 20번 실행
        int temp[SIZE];
        for (int i = 0; i < SIZE; i++) temp[i] = data[i];  // 데이터를 임시 배열에 복사

        int moves = 0;  // 각 실행에 대한 이동 횟수
        for (int i = 0; i < SIZE - 1; i++) {
            for (int j = 0; j < SIZE - i - 1; j++) {
                if (temp[j] > temp[j + 1]) {  // 인접한 값이 크면 교환
                    int swap = temp[j];
                    temp[j] = temp[j + 1];
                    temp[j + 1] = swap;
                    moves++;  // 이동 횟수 증가
                }
            }
        }
        totalMoves += moves;  // 총 이동 횟수에 더함
    }

    printf("Bubble Sort Average Moves: %d\n", totalMoves / 20);  // 평균 이동 횟수 출력
    printf("Sorted result: ");
    for (int i = 0; i < SIZE; i++) printf("%d ", data[i]);  // 정렬된 배열 출력
    printf("\n");
}

int main() {
    srand(time(0));  // 난수 생성기 초기화
    int randomData[SIZE];
    generateRandomData(randomData);  // 랜덤 데이터 생성

    doSelectionSort(randomData);  // 선택 정렬 수행
    printf("\n");
    doInsertionSort(randomData);  // 삽입 정렬 수행
    printf("\n");
    doBubbleSort(randomData);  // 버블 정렬 수행

    return 0;
}
