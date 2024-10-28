#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 10
#define TRUE 1
#define FALSE 0

typedef struct {
    int weight[MAX_VERTICES][MAX_VERTICES];
    int n; // number of vertices
} GraphType;

int selected[MAX_VERTICES]; // To keep track of included vertices

void graph_init(GraphType* g) {
    g->n = MAX_VERTICES;
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            g->weight[i][j] = (i == j) ? 0 : INT_MAX;
        }
    }
}

void GenerateGraph(GraphType* g) {
    // Manually input edges with given weights
    g->weight[0][1] = 3; g->weight[1][0] = 3;
    g->weight[0][5] = 11; g->weight[5][0] = 11;
    g->weight[0][6] = 12; g->weight[6][0] = 12;
    g->weight[1][2] = 5; g->weight[2][1] = 5;
    g->weight[1][3] = 4; g->weight[3][1] = 4;
    g->weight[1][4] = 1; g->weight[4][1] = 1;
    g->weight[1][5] = 7; g->weight[5][1] = 7;
    g->weight[1][6] = 8; g->weight[6][1] = 8;
    g->weight[2][3] = 2; g->weight[3][2] = 2;
    g->weight[2][6] = 6; g->weight[6][2] = 6;
    g->weight[2][7] = 5; g->weight[7][2] = 5;
    g->weight[3][4] = 13; g->weight[4][3] = 13;
    g->weight[3][7] = 14; g->weight[7][3] = 14;
    g->weight[3][9] = 16; g->weight[9][3] = 16;
    g->weight[4][5] = 9; g->weight[5][4] = 9;
    g->weight[4][8] = 18; g->weight[8][4] = 18;
    g->weight[4][9] = 17; g->weight[9][4] = 17;
    g->weight[6][7] = 13; g->weight[7][6] = 13;
    g->weight[7][9] = 15; g->weight[9][7] = 15;
    g->weight[8][9] = 10; g->weight[9][8] = 10;
}

void FindPrimMST(GraphType* g) {
    int min, u, v;

    for (int i = 0; i < g->n; i++)
        selected[i] = FALSE;

    selected[0] = TRUE; // Start with vertex 1 (index 0)
    printf("Prim MST Algorithm\n정점 1 추가\n");

    for (int edges = 0; edges < g->n - 1; edges++) {
        min = INT_MAX;
        u = v = -1;

        for (int i = 0; i < g->n; i++) {
            if (selected[i]) {
                for (int j = 0; j < g->n; j++) {
                    if (!selected[j] && g->weight[i][j] != INT_MAX) {
                        if (g->weight[i][j] < min) {
                            min = g->weight[i][j];
                            u = i;
                            v = j;
                        }
                    }
                }
            }
        }

        selected[v] = TRUE;
        printf("정점 %d 추가\n", v + 1); // Print 1-based index for vertices
    }
}

int main(void) {
    GraphType* g;
    g = (GraphType*)malloc(sizeof(GraphType));
    graph_init(g);

    // Create graph
    GenerateGraph(g);

    // Find and print MST using Prim's algorithm
    FindPrimMST(g);

    free(g);
    return 0;
}
