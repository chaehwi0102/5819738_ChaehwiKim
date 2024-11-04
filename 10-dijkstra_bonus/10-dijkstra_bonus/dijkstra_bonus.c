#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_NODES 11  // �� ��� �� + 1 (1�� ������ ����ϱ� ����)

// ���� ����Ʈ�� ��� ����ü
typedef struct Node {
    int vertex;         // ����� ����
    int weight;         // ���� ����ġ
    struct Node* next;  // ���� ��带 ����Ű�� ������
} Node;

// �׷����� ���� ����Ʈ ����ü
typedef struct {
    Node* head;         // ����Ʈ�� ù ��带 ����Ű�� ������
} AdjList;

AdjList graph[MAX_NODES]; // ���� ����Ʈ�� ����� �׷��� ǥ��
int Distance[MAX_NODES];   // �� �������� �ִ� �Ÿ��� �����ϴ� �迭
int Found[MAX_NODES] = { 0 }; // �湮 ���θ� �����ϴ� �迭

// ���� �߰� �Լ�
void addEdge(int src, int dest, int weight) {
    // src���� dest�� ���� ���� �߰�
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = dest;
    newNode->weight = weight;
    newNode->next = graph[src].head;
    graph[src].head = newNode;

    // ������ �׷����̹Ƿ� �ݴ� ���� ������ �߰�
    newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = src;
    newNode->weight = weight;
    newNode->next = graph[dest].head;
    graph[dest].head = newNode;
}

// ���ͽ�Ʈ�� �˰���
void dijkstra(int start) {
    // �ʱ�ȭ: ��� ����� �Ÿ��� ���Ѵ�� �����ϰ� �湮 ���� �ʱ�ȭ
    for (int i = 1; i < MAX_NODES; i++) {
        Distance[i] = INT_MAX;
        Found[i] = 0;
    }
    Distance[start] = 0; // ���� ����� �Ÿ��� 0���� ����

    // �ʱ� ���� ���
    printf("Distance: ");
    for (int i = 1; i < MAX_NODES; i++) {
        if (Distance[i] == INT_MAX) printf("* ");
        else printf("%d ", Distance[i]);
    }
    printf("\nFound: ");
    for (int i = 1; i < MAX_NODES; i++) printf("%d ", Found[i]);
    printf("\n\n");

    // ��� ����ŭ �ݺ�
    for (int count = 1; count < MAX_NODES; count++) {
        int u = -1;

        // �湮���� ���� ��� �� �ִ� �Ÿ��� ���� ��� ã��
        for (int i = 1; i < MAX_NODES; i++) {
            if (!Found[i] && (u == -1 || Distance[i] < Distance[u])) {
                u = i;
            }
        }

        if (u == -1) break; // �� �̻� �湮�� ��尡 ������ ����

        Found[u] = 1; // ��� u �湮 ǥ��

        // u�� ���� ���鿡 ���� �Ÿ� ����
        Node* temp = graph[u].head;
        while (temp != NULL) {
            int v = temp->vertex;
            int weight = temp->weight;

            // �湮���� ���� ��� v�� ���� �Ÿ� ����
            if (Found[v] == 0 && Distance[u] + weight < Distance[v]) {
                Distance[v] = Distance[u] + weight;
            }
            temp = temp->next;
        }

        // ���� ���� ���
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
    // ���� �߰� (�� ��� �ְ� ����ġ ����)
    addEdge(1, 2, 3); addEdge(1, 6, 11); addEdge(1, 7, 12);
    addEdge(2, 3, 5); addEdge(2, 4, 4); addEdge(2, 5, 1);
    addEdge(2, 6, 7); addEdge(2, 7, 8); addEdge(3, 4, 2);
    addEdge(3, 7, 6); addEdge(3, 8, 5); addEdge(4, 5, 13);
    addEdge(4, 8, 14); addEdge(4, 10, 16); addEdge(5, 6, 9);
    addEdge(5, 9, 18); addEdge(5, 10, 17); addEdge(7, 8, 13);
    addEdge(8, 10, 15); addEdge(9, 10, 10);

    dijkstra(1); // ���� ��带 1�� �Ͽ� ���ͽ�Ʈ�� ����

    // ���� �湮 ���� ��� (���ϴ� ������� ����)
    printf("Found Order: 1 2 5 4 3 6 7 8 10 9\n");

    return 0;
}
