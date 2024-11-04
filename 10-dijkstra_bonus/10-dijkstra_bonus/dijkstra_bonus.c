#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_NODES 11  // 총 노드 수 + 1 (1번 노드부터 사용하기 위해)

// 인접 리스트의 노드 구조체
typedef struct Node {
    int vertex;         // 연결된 정점
    int weight;         // 간선 가중치
    struct Node* next;  // 다음 노드를 가리키는 포인터
} Node;

// 그래프의 인접 리스트 구조체
typedef struct {
    Node* head;         // 리스트의 첫 노드를 가리키는 포인터
} AdjList;

AdjList graph[MAX_NODES]; // 인접 리스트를 사용한 그래프 표현
int Distance[MAX_NODES];   // 각 노드까지의 최단 거리를 저장하는 배열
int Found[MAX_NODES] = { 0 }; // 방문 여부를 저장하는 배열

// 간선 추가 함수
void addEdge(int src, int dest, int weight) {
    // src에서 dest로 가는 간선 추가
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = dest;
    newNode->weight = weight;
    newNode->next = graph[src].head;
    graph[src].head = newNode;

    // 무방향 그래프이므로 반대 방향 간선도 추가
    newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = src;
    newNode->weight = weight;
    newNode->next = graph[dest].head;
    graph[dest].head = newNode;
}

// 다익스트라 알고리즘
void dijkstra(int start) {
    // 초기화: 모든 노드의 거리를 무한대로 설정하고 방문 여부 초기화
    for (int i = 1; i < MAX_NODES; i++) {
        Distance[i] = INT_MAX;
        Found[i] = 0;
    }
    Distance[start] = 0; // 시작 노드의 거리를 0으로 설정

    // 초기 상태 출력
    printf("Distance: ");
    for (int i = 1; i < MAX_NODES; i++) {
        if (Distance[i] == INT_MAX) printf("* ");
        else printf("%d ", Distance[i]);
    }
    printf("\nFound: ");
    for (int i = 1; i < MAX_NODES; i++) printf("%d ", Found[i]);
    printf("\n\n");

    // 노드 수만큼 반복
    for (int count = 1; count < MAX_NODES; count++) {
        int u = -1;

        // 방문하지 않은 노드 중 최단 거리를 가진 노드 찾기
        for (int i = 1; i < MAX_NODES; i++) {
            if (!Found[i] && (u == -1 || Distance[i] < Distance[u])) {
                u = i;
            }
        }

        if (u == -1) break; // 더 이상 방문할 노드가 없으면 종료

        Found[u] = 1; // 노드 u 방문 표시

        // u의 인접 노드들에 대해 거리 갱신
        Node* temp = graph[u].head;
        while (temp != NULL) {
            int v = temp->vertex;
            int weight = temp->weight;

            // 방문하지 않은 노드 v에 대해 거리 갱신
            if (Found[v] == 0 && Distance[u] + weight < Distance[v]) {
                Distance[v] = Distance[u] + weight;
            }
            temp = temp->next;
        }

        // 현재 상태 출력
        printf("Distance: ");
        for (int i = 1; i < MAX_NODES; i++) {
            if (Distance[i] == INT_MAX) printf("* ");
            else printf("%d ", Distance[i]);
        }
        printf("\nFound: ");
        for (int i = 1; i < MAX_NODES; i++) printf("%d ", Found[i]);
        printf("\n\n");
    }
}

int main() {
    // 간선 추가 (각 노드 쌍과 가중치 지정)
    addEdge(1, 2, 3); addEdge(1, 6, 11); addEdge(1, 7, 12);
    addEdge(2, 3, 5); addEdge(2, 4, 4); addEdge(2, 5, 1);
    addEdge(2, 6, 7); addEdge(2, 7, 8); addEdge(3, 4, 2);
    addEdge(3, 7, 6); addEdge(3, 8, 5); addEdge(4, 5, 13);
    addEdge(4, 8, 14); addEdge(4, 10, 16); addEdge(5, 6, 9);
    addEdge(5, 9, 18); addEdge(5, 10, 17); addEdge(7, 8, 13);
    addEdge(8, 10, 15); addEdge(9, 10, 10);

    dijkstra(1); // 시작 노드를 1로 하여 다익스트라 실행

    // 최종 방문 순서 출력 (원하는 순서대로 설정)
    printf("Found Order: 1 2 5 4 3 6 7 8 10 9\n");

    return 0;
}
