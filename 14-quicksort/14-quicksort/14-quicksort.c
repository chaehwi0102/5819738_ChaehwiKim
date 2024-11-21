#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

int comparisonCount = 0; // 비교 횟수
int moveCount = 0;       // 이동 횟수
int rounds = 0;          // 출력 제어용 변수
int isFirst = 0;         // 첫 번째 실행 여부 확인 변수

// 배열 출력 함수
void printArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

// 랜덤 배열 생성 함수
void generateRandomArray(int array[]) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000; // 0~999 범위의 랜덤 값 생성
    }
}

// 퀵 정렬의 분할 함수
int partition(int array[], int low, int high) {
    int pivot = array[high]; // 피벗 설정 (마지막 요소)
    int i = low - 1;         // 작은 요소의 인덱스

    for (int j = low; j < high; j++) {
        comparisonCount++; // 비교 횟수 증가
        if (array[j] < pivot) {
            i++;
            // 배열 요소 교환
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            moveCount += 3; // 이동: temp 저장, array[i]와 array[j] 교환
        }
    }

    // 피벗을 올바른 위치로 이동
    int temp = array[i + 1];
    array[i + 1] = array[high];
    array[high] = temp;
    moveCount += 3; // 이동: temp 저장, array[i+1]와 array[high] 교환

    return i + 1; // 피벗의 최종 위치 반환
}

// 반복적 퀵 정렬 함수
void doIterativeQuickSort(int array[], int low, int high) {
    int stack[SIZE]; // 스택 생성
    int top = -1;    // 스택의 최상위 인덱스

    // 초기 범위를 스택에 저장
    stack[++top] = low;
    stack[++top] = high;

    // 스택이 빌 때까지 반복
    while (top >= 0) {
        // 스택에서 현재 정렬 범위 꺼내기
        high = stack[top--];
        low = stack[top--];

        // 분할 수행
        int pi = partition(array, low, high);

        // 출력 제어: 14번째 실행마다 40~60번 인덱스 출력
        if (rounds % 14 == 0 && isFirst == 0) {
            for (int i = 40; i < 60; i++) {
                printf("%d ", array[i]);
            }
            printf("\n\n");
        }
        rounds++;

        // 분할 후 왼쪽 하위 배열을 스택에 저장
        if (pi - 1 > low) {
            stack[++top] = low;
            stack[++top] = pi - 1;
        }

        // 분할 후 오른쪽 하위 배열을 스택에 저장
        if (pi + 1 < high) {
            stack[++top] = pi + 1;
            stack[++top] = high;
        }
    }
}

// 메인 함수
int main(int argc, char* argv[]) {
    srand(time(NULL)); // 랜덤 시드 설정
    int array[SIZE];
    double totalComparisons = 0; // 총 비교 횟수
    double totalMoveCount = 0;   // 총 이동 횟수

    for (int i = 0; i < 20; i++) {
        generateRandomArray(array); // 랜덤 배열 생성
        comparisonCount = 0;        // 비교 횟수 초기화
        moveCount = 0;              // 이동 횟수 초기화

        if (i == 0) { // 첫 번째 실행 시 출력
            printf("Quick Sort Run\n");
            doIterativeQuickSort(array, 0, SIZE - 1); // 반복적 퀵 정렬 실행
            printf("Result\n");
            printArray(array, SIZE); // 정렬 결과 출력
            isFirst++;
        }
        else {
            doIterativeQuickSort(array, 0, SIZE - 1); // 반복적 퀵 정렬 실행
        }

        totalComparisons += comparisonCount; // 총 비교 횟수 누적
        totalMoveCount += moveCount;         // 총 이동 횟수 누적
    }

    // 평균 비교 및 이동 횟수 출력
    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoveCount / 20.0);

    return 0;
}
