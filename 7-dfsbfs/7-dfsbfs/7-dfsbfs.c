#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 50
#define MAX 50

int visited[MAX_VERTEX]; // 방문 여부를 체크하기 위한 배열

// 인접 행렬을 사용하는 그래프 구조체
typedef struct GraphType {
    int n;
    int adj_mat[MAX_VERTEX][MAX_VERTEX];
} GraphType;

// 인접 리스트에서 사용할 노드 구조체
typedef struct GraphNode {
    int vertex;
    struct GraphNode* link;
} GraphNode;

// 인접 리스트를 사용하는 그래프 구조체
typedef struct GraphType_List {
    int n;
    GraphNode* adj_list[MAX_VERTEX]; // 각 정점의 연결 리스트를 가리킴
} GraphType_List;

// 스택 구조체
typedef struct Stack {
    int top;
    int data[MAX]; // 스택 데이터 배열
}Stack;

// 큐 구조체
typedef struct Queue {
    int front, rear;
    int data[MAX]; // 큐 데이터 배열
}Queue;

// 스택 초기화 함수
void init_stack(Stack* s) {
    s->top = -1; // 스택이 비어있음을 표시
}

// 큐 초기화 함수
void init_queue(Queue* q) {
    q->front = 0;
    q->rear = 0; // 큐의 앞, 뒤 초기화
}

// 스택이 비어있는지 확인
int is_empty_stack(Stack* s) {
    return s->top == -1; // top이 -1이면 비어있음
}

// 큐가 비어있는지 확인
int is_empty_queue(Queue* q) {
    return q->front == q->rear; // front와 rear가 같으면 비어있음
}

// 스택에 값 추가
void push(Stack* s, int item) {
    s->data[++(s->top)] = item; // 스택 top을 증가시키고 값 추가
}

// 스택에서 값 제거
int pop(Stack* s) {
    if (s->top == -1) {
        printf("스택이 공백 상태입니다.");
        return; // 스택이 비어있는 경우 메시지 출력
    }
    return s->data[(s->top)--]; // top 값을 반환하고 감소
}

// 큐에 값 추가
void enqueue(Queue* q, int item) {
    if (q->front == (q->rear + 1) % MAX) {
        printf("큐가 포화 상태입니다.");
        return; // 큐가 가득 찬 경우 메시지 출력
    }
    else {
        q->rear = (q->rear + 1) % (MAX); // rear 위치 업데이트
        q->data[q->rear] = item; // 값 추가
    }
}

// 큐에서 값 제거
int dequeue(Queue* q) {
    if (q->front == q->rear) {
        printf("큐가 공백 상태입니다.");
        return -1; // 큐가 비어있는 경우 메시지 출력
    }
    else {
        q->front++; // front 위치 업데이트
        return(q->data[q->front]); // 값 반환
    }
}

// 그래프 초기화 함수 (인접 리스트 방식)
void init_graph(GraphType_List* g) {
    int v;
    g->n = 0; // 그래프의 정점 수 초기화
    for (v = 0; v < MAX_VERTEX; v++) {
        g->adj_list[v] = NULL; // 각 정점의 연결 리스트 초기화
    }
}

// 그래프에 정점 추가
void insert_vertex(GraphType_List* g, int v) {
    if (((g->n) + 1) > MAX_VERTEX) {
        printf("그래프: 정점 번호 오류");
        return; // 정점 수가 초과될 경우 메시지 출력
    }
    g->n++; // 정점 수 증가
}

// 그래프에 간선 추가
void insert_edge(GraphType_List* g, int u, int v) {
    GraphNode* node;
    if (u >= g->n || v >= g->n) {
        printf("그래프: 정점 번호 오류");
        return; // 유효하지 않은 정점일 경우 메시지 출력
    }
    node = (GraphNode*)malloc(sizeof(GraphNode)); // 새 노드 생성
    node->vertex = v;
    node->link = g->adj_list[u]; // 새 노드를 해당 정점의 연결 리스트에 추가
    g->adj_list[u] = node;
}

// 깊이 우선 탐색 (DFS) 함수
void dfs_list(GraphType_List* g, int v, int key) {
    GraphNode* n;
    int node;
    Stack s;
    init_stack(&s); // 스택 초기화
    push(&s, v); // 시작 정점을 스택에 추가
    for (int i = 0; i < g->n; i++) visited[i] = 0; // 방문 배열 초기화
    while (!is_empty_stack(&s)) {
        node = pop(&s); // 스택에서 정점 추출
        if (!visited[node]) {
            visited[node] = 1; // 해당 정점 방문 표시
            printf("%d ", node); // 방문한 정점 출력
            if (node == key) {
                printf("\n탐색 성공: %d\n방문한 노드의 수: %d\n", key, node);
                break; // 목표 정점 찾으면 종료
            }
            for (n = g->adj_list[node]; n != NULL; n = n->link) {
                if (!visited[n->vertex]) {
                    push(&s, n->vertex); // 연결된 정점 스택에 추가
                }
            }
        }
    }
}

// 너비 우선 탐색 (BFS) 함수
void bfs_list(GraphType_List* g, int v, int key) {
    GraphNode* n;
    int node;
    Queue q;
    init_queue(&q); // 큐 초기화
    enqueue(&q, v); // 시작 정점을 큐에 추가
    for (int i = 0; i < g->n; i++) visited[i] = 0; // 방문 배열 초기화
    while (!is_empty_queue(&q)) {
        node = dequeue(&q); // 큐에서 정점 추출
        if (!visited[node]) {
            visited[node] = 1; // 해당 정점 방문 표시
            printf("%d ", node); // 방문한 정점 출력
            if (node == key) {
                printf("\n탐색 성공: %d\n방문한 노드의 수: %d\n", key, node);
                break; // 목표 정점 찾으면 종료
            }
            for (n = g->adj_list[node]; n != NULL; n = n->link) {
                if (!visited[n->vertex]) {
                    enqueue(&q, n->vertex); // 연결된 정점 큐에 추가
                }
            }
        }
    }
}

// 그래프를 만드는 함수
GraphType_List* make_Graph() {
    GraphType_List* g = (GraphType_List*)malloc(sizeof(GraphType_List));
    init_graph(g); // 그래프 초기화

    for (int i = 0; i < 11; i++) {
        insert_vertex(g, i); // 0부터 10까지 정점 추가
    }

    // 인접한 정점 간의 간선 추가
    int edges[11][7] = {
       {2, 4, 5, 6, 9, -1},
       {4, 5, 7, 10, -1},
       {3, 4, -1},
       {4, 5, -1},
       {5, 6, 7, -1},
       {0, 1, 3, 4, -1},
       {0, 4, 7, 8, -1},
       {1, 4, 6, 10, -1},
       {6, 9, 10, -1},
       {0, 8, -1},
       {1, 7, 8, -1}
    };

    // 간선들을 삽입
    for (int i = 0; i < 11; i++) {
        for (int j = 0; edges[i][j] != -1; j++) {
            insert_edge(g, i, edges[i][j]);
        }
    }
    return g; // 그래프 반환
}

int main(int argc, char* argv[]) {
    GraphType_List* g = make_Graph(); // 그래프 생성

    printf("1. 깊이 우선 탐색\n2. 너비 우선 탐색\n3. 종료\n");
    int menu = 0;
    int start, item;
    while (1) {
        printf("\n메뉴 입력: ");
        scanf_s("%d", &menu); // 메뉴 입력 받음

        switch (menu) {
        case 1:
            printf("시작 번호와 탐색할 값 입력: ");
            scanf_s("%d %d", &start, &item); // 시작 번호와 탐색할 값 입력
            dfs_list(g, start, item); // DFS 실행
            break;
        case 2:
            printf("시작 번호와 탐색할 값 입력: ");
            scanf_s("%d %d", &start, &item); // 시작 번호와 탐색할 값 입력
            bfs_list(g, start, item); // BFS 실행
            break;
        case 3:
            printf("프로그램 종료");
            exit(1); // 프로그램 종료
            break;
        default:
            printf("Insert Error");
            break;
        }
    }
    free(g); // 그래프 메모리 해제

    return 0;
}
