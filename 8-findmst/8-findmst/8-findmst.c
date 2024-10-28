#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100
#define MAX_EDGES 100

typedef struct {
    int start, end, weight;
} Edge;

typedef struct {
    int n; // 정점의 개수
    int m; // 간선의 개수
    Edge edges[MAX_EDGES];
} GraphType;

// Union-Find에 사용될 부모 배열
int parent[MAX_VERTICES];

// 집합 초기화 함수
void set_init(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = -1;
    }
}

// 집합의 루트를 찾는 함수
int set_find(int vertex) {
    if (parent[vertex] == -1) return vertex;
    return parent[vertex] = set_find(parent[vertex]);
}

// 두 집합을 합치는 함수
void set_union(int root1, int root2) {
    parent[root1] = root2;
}

// qsort를 위한 간선 비교 함수
int compare(const void* a, const void* b) {
    Edge* e1 = (Edge*)a;
    Edge* e2 = (Edge*)b;
    return e1->weight - e2->weight;
}

// qsort 기반 Kruskal 알고리즘 함수
void QuickKruskal(GraphType* g) {
    set_init(g->n); // 집합 초기화
    qsort(g->edges, g->m, sizeof(Edge), compare); // 간선 정렬

    printf("Quick Based Kruskal\n");
    int edge_count = 0;
    for (int i = 0; i < g->m && edge_count < g->n - 1; i++) {
        int root1 = set_find(g->edges[i].start);
        int root2 = set_find(g->edges[i].end);
        if (root1 != root2) {
            printf("Edge (%d, %d) select %d\n", g->edges[i].start, g->edges[i].end, g->edges[i].weight);
            set_union(root1, root2); // 두 집합을 합침
            edge_count++;
        }
    }
}

// MinHeap 구성 함수
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

// MinHeap 생성 함수
void buildMinHeap(Edge arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
}

// MinHeap에서 최소 가중치 간선을 추출하는 함수
Edge extractMin(Edge arr[], int* n) {
    Edge min = arr[0];
    arr[0] = arr[*n - 1];
    (*n)--;
    heapify(arr, *n, 0);
    return min;
}

// MinHeap 기반 Kruskal 알고리즘 함수
void MinHeapKruskal(GraphType* g) {
    set_init(g->n); // 집합 초기화
    buildMinHeap(g->edges, g->m); // MinHeap 생성

    printf("MinHeap Based Kruskal\n");
    int edge_count = 0;
    int m = g->m;
    while (m > 0 && edge_count < g->n - 1) {
        Edge min_edge = extractMin(g->edges, &m);
        int root1 = set_find(min_edge.start);
        int root2 = set_find(min_edge.end);
        if (root1 != root2) {
            printf("Edge (%d, %d) select %d\n", min_edge.start, min_edge.end, min_edge.weight);
            set_union(root1, root2); // 두 집합을 합침
            edge_count++;
        }
    }
}

// 그래프 초기화 함수
void graph_init(GraphType* g) {
    g->n = 10; // 정점의 수 설정
    g->m = 0;
}

// 그래프 생성 함수 (간선을 직접 추가)
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
    QuickKruskal(g);     // qsort 기반 Kruskal 실행
    MinHeapKruskal(g);   // MinHeap 기반 Kruskal 실행

    free(g);
    return 0;
}
