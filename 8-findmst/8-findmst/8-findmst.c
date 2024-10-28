#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100
#define MAX_EDGES 100

typedef struct {
    int start, end, weight;
} Edge;

typedef struct {
    int n; // ������ ����
    int m; // ������ ����
    Edge edges[MAX_EDGES];
} GraphType;

// Union-Find�� ���� �θ� �迭
int parent[MAX_VERTICES];

// ���� �ʱ�ȭ �Լ�
void set_init(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = -1;
    }
}

// ������ ��Ʈ�� ã�� �Լ�
int set_find(int vertex) {
    if (parent[vertex] == -1) return vertex;
    return parent[vertex] = set_find(parent[vertex]);
}

// �� ������ ��ġ�� �Լ�
void set_union(int root1, int root2) {
    parent[root1] = root2;
}

// qsort�� ���� ���� �� �Լ�
int compare(const void* a, const void* b) {
    Edge* e1 = (Edge*)a;
    Edge* e2 = (Edge*)b;
    return e1->weight - e2->weight;
}

// qsort ��� Kruskal �˰��� �Լ�
void QuickKruskal(GraphType* g) {
    set_init(g->n); // ���� �ʱ�ȭ
    qsort(g->edges, g->m, sizeof(Edge), compare); // ���� ����

    printf("Quick Based Kruskal\n");
    int edge_count = 0;
    for (int i = 0; i < g->m && edge_count < g->n - 1; i++) {
        int root1 = set_find(g->edges[i].start);
        int root2 = set_find(g->edges[i].end);
        if (root1 != root2) {
            printf("Edge (%d, %d) select %d\n", g->edges[i].start, g->edges[i].end, g->edges[i].weight);
            set_union(root1, root2); // �� ������ ��ħ
            edge_count++;
        }
    }
}

// MinHeap ���� �Լ�
void heapify(Edge arr[], int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].weight < arr[smallest].weight)
        smallest = left;

    if (right < n && arr[right].weight < arr[smallest].weight)
        smallest = right;

    if (smallest != i) {
        Edge temp = arr[i];
        arr[i] = arr[smallest];
        arr[smallest] = temp;
        heapify(arr, n, smallest);
    }
}

// MinHeap ���� �Լ�
void buildMinHeap(Edge arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
}

// MinHeap���� �ּ� ����ġ ������ �����ϴ� �Լ�
Edge extractMin(Edge arr[], int* n) {
    Edge min = arr[0];
    arr[0] = arr[*n - 1];
    (*n)--;
    heapify(arr, *n, 0);
    return min;
}

// MinHeap ��� Kruskal �˰��� �Լ�
void MinHeapKruskal(GraphType* g) {
    set_init(g->n); // ���� �ʱ�ȭ
    buildMinHeap(g->edges, g->m); // MinHeap ����

    printf("MinHeap Based Kruskal\n");
    int edge_count = 0;
    int m = g->m;
    while (m > 0 && edge_count < g->n - 1) {
        Edge min_edge = extractMin(g->edges, &m);
        int root1 = set_find(min_edge.start);
        int root2 = set_find(min_edge.end);
        if (root1 != root2) {
            printf("Edge (%d, %d) select %d\n", min_edge.start, min_edge.end, min_edge.weight);
            set_union(root1, root2); // �� ������ ��ħ
            edge_count++;
        }
    }
}

// �׷��� �ʱ�ȭ �Լ�
void graph_init(GraphType* g) {
    g->n = 10; // ������ �� ����
    g->m = 0;
}

// �׷��� ���� �Լ� (������ ���� �߰�)
void GenerateGraph(GraphType* g) {
    g->edges[g->m++] = (Edge){ 2, 5, 1 };
    g->edges[g->m++] = (Edge){ 3, 4, 2 };
    g->edges[g->m++] = (Edge){ 1, 2, 3 };
    g->edges[g->m++] = (Edge){ 2, 4, 4 };
    g->edges[g->m++] = (Edge){ 3, 8, 5 };
    g->edges[g->m++] = (Edge){ 3, 7, 6 };
    g->edges[g->m++] = (Edge){ 2, 6, 7 };
    g->edges[g->m++] = (Edge){ 9, 10, 10 };
    g->edges[g->m++] = (Edge){ 8, 10, 15 };
}

int main(void) {
    GraphType* g = (GraphType*)malloc(sizeof(GraphType));
    graph_init(g);

    GenerateGraph(g);
    QuickKruskal(g);     // qsort ��� Kruskal ����
    MinHeapKruskal(g);   // MinHeap ��� Kruskal ����

    free(g);
    return 0;
}
