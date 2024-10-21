#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 50
#define MAX 50

int visited[MAX_VERTEX]; // �湮 ���θ� üũ�ϱ� ���� �迭

// ���� ����� ����ϴ� �׷��� ����ü
typedef struct GraphType {
    int n;
    int adj_mat[MAX_VERTEX][MAX_VERTEX];
} GraphType;

// ���� ����Ʈ���� ����� ��� ����ü
typedef struct GraphNode {
    int vertex;
    struct GraphNode* link;
} GraphNode;

// ���� ����Ʈ�� ����ϴ� �׷��� ����ü
typedef struct GraphType_List {
    int n;
    GraphNode* adj_list[MAX_VERTEX]; // �� ������ ���� ����Ʈ�� ����Ŵ
} GraphType_List;

// ���� ����ü
typedef struct Stack {
    int top;
    int data[MAX]; // ���� ������ �迭
}Stack;

// ť ����ü
typedef struct Queue {
    int front, rear;
    int data[MAX]; // ť ������ �迭
}Queue;

// ���� �ʱ�ȭ �Լ�
void init_stack(Stack* s) {
    s->top = -1; // ������ ��������� ǥ��
}

// ť �ʱ�ȭ �Լ�
void init_queue(Queue* q) {
    q->front = 0;
    q->rear = 0; // ť�� ��, �� �ʱ�ȭ
}

// ������ ����ִ��� Ȯ��
int is_empty_stack(Stack* s) {
    return s->top == -1; // top�� -1�̸� �������
}

// ť�� ����ִ��� Ȯ��
int is_empty_queue(Queue* q) {
    return q->front == q->rear; // front�� rear�� ������ �������
}

// ���ÿ� �� �߰�
void push(Stack* s, int item) {
    s->data[++(s->top)] = item; // ���� top�� ������Ű�� �� �߰�
}

// ���ÿ��� �� ����
int pop(Stack* s) {
    if (s->top == -1) {
        printf("������ ���� �����Դϴ�.");
        return; // ������ ����ִ� ��� �޽��� ���
    }
    return s->data[(s->top)--]; // top ���� ��ȯ�ϰ� ����
}

// ť�� �� �߰�
void enqueue(Queue* q, int item) {
    if (q->front == (q->rear + 1) % MAX) {
        printf("ť�� ��ȭ �����Դϴ�.");
        return; // ť�� ���� �� ��� �޽��� ���
    }
    else {
        q->rear = (q->rear + 1) % (MAX); // rear ��ġ ������Ʈ
        q->data[q->rear] = item; // �� �߰�
    }
}

// ť���� �� ����
int dequeue(Queue* q) {
    if (q->front == q->rear) {
        printf("ť�� ���� �����Դϴ�.");
        return -1; // ť�� ����ִ� ��� �޽��� ���
    }
    else {
        q->front++; // front ��ġ ������Ʈ
        return(q->data[q->front]); // �� ��ȯ
    }
}

// �׷��� �ʱ�ȭ �Լ� (���� ����Ʈ ���)
void init_graph(GraphType_List* g) {
    int v;
    g->n = 0; // �׷����� ���� �� �ʱ�ȭ
    for (v = 0; v < MAX_VERTEX; v++) {
        g->adj_list[v] = NULL; // �� ������ ���� ����Ʈ �ʱ�ȭ
    }
}

// �׷����� ���� �߰�
void insert_vertex(GraphType_List* g, int v) {
    if (((g->n) + 1) > MAX_VERTEX) {
        printf("�׷���: ���� ��ȣ ����");
        return; // ���� ���� �ʰ��� ��� �޽��� ���
    }
    g->n++; // ���� �� ����
}

// �׷����� ���� �߰�
void insert_edge(GraphType_List* g, int u, int v) {
    GraphNode* node;
    if (u >= g->n || v >= g->n) {
        printf("�׷���: ���� ��ȣ ����");
        return; // ��ȿ���� ���� ������ ��� �޽��� ���
    }
    node = (GraphNode*)malloc(sizeof(GraphNode)); // �� ��� ����
    node->vertex = v;
    node->link = g->adj_list[u]; // �� ��带 �ش� ������ ���� ����Ʈ�� �߰�
    g->adj_list[u] = node;
}

// ���� �켱 Ž�� (DFS) �Լ�
void dfs_list(GraphType_List* g, int v, int key) {
    GraphNode* n;
    int node;
    Stack s;
    init_stack(&s); // ���� �ʱ�ȭ
    push(&s, v); // ���� ������ ���ÿ� �߰�
    for (int i = 0; i < g->n; i++) visited[i] = 0; // �湮 �迭 �ʱ�ȭ
    while (!is_empty_stack(&s)) {
        node = pop(&s); // ���ÿ��� ���� ����
        if (!visited[node]) {
            visited[node] = 1; // �ش� ���� �湮 ǥ��
            printf("%d ", node); // �湮�� ���� ���
            if (node == key) {
                printf("\nŽ�� ����: %d\n�湮�� ����� ��: %d\n", key, node);
                break; // ��ǥ ���� ã���� ����
            }
            for (n = g->adj_list[node]; n != NULL; n = n->link) {
                if (!visited[n->vertex]) {
                    push(&s, n->vertex); // ����� ���� ���ÿ� �߰�
                }
            }
        }
    }
}

// �ʺ� �켱 Ž�� (BFS) �Լ�
void bfs_list(GraphType_List* g, int v, int key) {
    GraphNode* n;
    int node;
    Queue q;
    init_queue(&q); // ť �ʱ�ȭ
    enqueue(&q, v); // ���� ������ ť�� �߰�
    for (int i = 0; i < g->n; i++) visited[i] = 0; // �湮 �迭 �ʱ�ȭ
    while (!is_empty_queue(&q)) {
        node = dequeue(&q); // ť���� ���� ����
        if (!visited[node]) {
            visited[node] = 1; // �ش� ���� �湮 ǥ��
            printf("%d ", node); // �湮�� ���� ���
            if (node == key) {
                printf("\nŽ�� ����: %d\n�湮�� ����� ��: %d\n", key, node);
                break; // ��ǥ ���� ã���� ����
            }
            for (n = g->adj_list[node]; n != NULL; n = n->link) {
                if (!visited[n->vertex]) {
                    enqueue(&q, n->vertex); // ����� ���� ť�� �߰�
                }
            }
        }
    }
}

// �׷����� ����� �Լ�
GraphType_List* make_Graph() {
    GraphType_List* g = (GraphType_List*)malloc(sizeof(GraphType_List));
    init_graph(g); // �׷��� �ʱ�ȭ

    for (int i = 0; i < 11; i++) {
        insert_vertex(g, i); // 0���� 10���� ���� �߰�
    }

    // ������ ���� ���� ���� �߰�
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

    // �������� ����
    for (int i = 0; i < 11; i++) {
        for (int j = 0; edges[i][j] != -1; j++) {
            insert_edge(g, i, edges[i][j]);
        }
    }
    return g; // �׷��� ��ȯ
}

int main(int argc, char* argv[]) {
    GraphType_List* g = make_Graph(); // �׷��� ����

    printf("1. ���� �켱 Ž��\n2. �ʺ� �켱 Ž��\n3. ����\n");
    int menu = 0;
    int start, item;
    while (1) {
        printf("\n�޴� �Է�: ");
        scanf_s("%d", &menu); // �޴� �Է� ����

        switch (menu) {
        case 1:
            printf("���� ��ȣ�� Ž���� �� �Է�: ");
            scanf_s("%d %d", &start, &item); // ���� ��ȣ�� Ž���� �� �Է�
            dfs_list(g, start, item); // DFS ����
            break;
        case 2:
            printf("���� ��ȣ�� Ž���� �� �Է�: ");
            scanf_s("%d %d", &start, &item); // ���� ��ȣ�� Ž���� �� �Է�
            bfs_list(g, start, item); // BFS ����
            break;
        case 3:
            printf("���α׷� ����");
            exit(1); // ���α׷� ����
            break;
        default:
            printf("Insert Error");
            break;
        }
    }
    free(g); // �׷��� �޸� ����

    return 0;
}
