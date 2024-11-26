#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000 // 배열 크기 정의

// 함수 원형 선언
void generateRandomArray(int* array); // 랜덤 배열 생성
float getAverageLinearSearchCompareCount(int* array); // 선형 탐색의 평균 비교 횟수 계산
int getQuickSortCompareCount(int* array); // 퀵 정렬 비교 횟수 계산
float getAverageBinarySearchCompareCount(int* array); // 이진 탐색의 평균 비교 횟수 계산
void quickSort(int* array, int low, int high); // 퀵 정렬 수행
int partition(int* array, int low, int high); // 퀵 정렬의 분할 함수
void printArray(int* array); // 배열 출력

int compareCount = 0; // 퀵 정렬의 비교 횟수를 저장할 전역 변수

int main(int argc, char* argv[]) {
    srand(time(NULL)); // 랜덤 시드 초기화

    for (int run = 1; run <= 3; run++) { // 전체 과정을 3번 반복
        int array[SIZE];

        // 랜덤 배열 생성
        generateRandomArray(array);

        // 선형 탐색 100회 수행 후 평균 비교 횟수 출력
        printf("Average Linear Search Compare Count: %.2f\n",
            getAverageLinearSearchCompareCount(array));

        // 퀵 정렬 수행 후 비교 횟수 출력
        compareCount = 0; // 비교 횟수 초기화
        getQuickSortCompareCount(array);
        printf("Quick Sort Compare Count: %d\n", compareCount);

        // 정렬된 배열에 대해 이진 탐색 100회 수행 후 평균 비교 횟수 출력
        printf("Average Binary Search Compare Count: %.2f\n\n",
            getAverageBinarySearchCompareCount(array));

        // 정렬된 배열 출력 (처음 20개와 마지막 20개 요소 출력)
        printArray(array);

        printf("\n");
    }

    return 0;
}

// 랜덤 배열 생성 함수
void generateRandomArray(int* array) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000; // 0부터 999 사이의 랜덤 값 생성
    }
}

// 선형 탐색의 평균 비교 횟수 계산 함수
float getAverageLinearSearchCompareCount(int* array) {
    int totalComparisons = 0;

    for (int i = 0; i < 100; i++) { // 100회 탐색 수행
        int target = array[rand() % SIZE]; // 배열에서 임의의 값을 탐색 대상(target)으로 설정
        int comparisons = 0;

        for (int j = 0; j < SIZE; j++) { // 배열을 순차적으로 탐색
            comparisons++;
            if (array[j] == target) { // 탐색 대상이 발견되면 루프 종료
                break;
            }
        }

        totalComparisons += comparisons; // 탐색 시 비교 횟수 누적
    }

    return (float)totalComparisons / 100; // 평균 비교 횟수 반환
}

// 퀵 정렬 비교 횟수 계산 함수
int getQuickSortCompareCount(int* array) {
    quickSort(array, 0, SIZE - 1); // 퀵 정렬 수행
    return compareCount; // 전체 비교 횟수 반환
}

// 퀵 정렬 함수
void quickSort(int* array, int low, int high) {
    if (low < high) { // 정렬이 필요한 경우
        int pivot = partition(array, low, high); // 분할 수행 및 피벗 위치 반환
        quickSort(array, low, pivot - 1); // 왼쪽 하위 배열 정렬
        quickSort(array, pivot + 1, high); // 오른쪽 하위 배열 정렬
    }
}

// 퀵 정렬의 분할 함수
int partition(int* array, int low, int high) {
    int pivot = array[high]; // 피벗 설정 (배열의 마지막 요소)
    int i = low - 1; // 작은 요소를 추적할 인덱스 초기화

    for (int j = low; j < high; j++) { // 피벗보다 작은 요소를 왼쪽으로 이동
        compareCount++; // 비교 횟수 증가
        if (array[j] <= pivot) { // 현재 요소가 피벗 이하일 경우
            i++;
            // 요소 교환
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }

    // 피벗 요소를 올바른 위치로 이동
    int temp = array[i + 1];
    array[i + 1] = array[high];
    array[high] = temp;

    return i + 1; // 피벗 위치 반환
}

// 이진 탐색의 평균 비교 횟수 계산 함수
float getAverageBinarySearchCompareCount(int* array) {
    int totalComparisons = 0;

    for (int i = 0; i < 100; i++) { // 100회 탐색 수행
        int target = array[rand() % SIZE]; // 배열에서 임의의 값을 탐색 대상(target)으로 설정
        int low = 0, high = SIZE - 1, comparisons = 0;

        while (low <= high) { // 이진 탐색 반복
            comparisons++;
            int mid = (low + high) / 2; // 중간 위치 계산

            if (array[mid] == target) { // 대상이 발견되면 루프 종료
                break;
            }
            else if (array[mid] < target) { // 대상이 중간 값보다 크면 오른쪽 탐색
                low = mid + 1;
            }
            else { // 대상이 중간 값보다 작으면 왼쪽 탐색
                high = mid - 1;
            }
        }

        totalComparisons += comparisons; // 탐색 시 비교 횟수 누적
    }

    return (float)totalComparisons / 100; // 평균 비교 횟수 반환
}

// 배열 출력 함수 (처음 20개와 마지막 20개 요소 출력)
void printArray(int* array) {
    printf("Array Sorting Result:\n");

    for (int i = 0; i < 20; i++) // 처음 20개 요소 출력
        printf("%3d ", array[i]);
    printf("\n");
    for (int i = SIZE - 20; i < SIZE; i++) // 마지막 20개 요소 출력
        printf("%3d ", array[i]);
    printf("\n");
}
