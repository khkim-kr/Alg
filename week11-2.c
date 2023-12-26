//그래프 순회 - BFS
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct vertex {
    int vnum;
    int v_visit;
} vertex;

typedef struct edge {
    int endpoint1;
    int endpoint2;
    int e_visit;
} edge;

typedef struct graph {
    vertex *vertices;
    edge *edges;
    int **matrix;
    int edge_index;
} graph;

graph *initGraph(int n, int m) {
    graph *G = (graph*)malloc(sizeof(graph));
    G->vertices = (vertex*)malloc(sizeof(vertex) * n);
    for (int i = 0; i < n; i++) {
        G->vertices[i].vnum = i + 1;
        G->vertices[i].v_visit = 0;
    }
    G->edges = (edge*)malloc(sizeof(edge) * m);
    G->edge_index = 0;
    G->matrix = (int**)malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++) {
        G->matrix[i] = (int*)malloc(sizeof(int) * n);
        for (int j = 0; j < n; j++)
            G->matrix[i][j] = -1;
    }
    return G;
}

void addedge(graph *G, int u, int v) {
    int i = G->edge_index;
    G->edges[i].endpoint1 = u;
    G->edges[i].endpoint2 = v;
    G->edges[i].e_visit = 0;

    G->matrix[u - 1][v - 1] = i;
    G->matrix[v - 1][u - 1] = i;
    G->edge_index += 1;
}

int otherendpoint(graph *G, int i, int nodenum) {
    return G->edges[i].endpoint2 == nodenum ? G->edges[i].endpoint1 : G->edges[i].endpoint2;
}

void BFS(graph *G, int s, int n) {
    int *Queue = (int*)malloc(sizeof(int) * n);
    int front = 0, rear = 0; //L0 <- empty
    Queue[rear++] = s; //L0.addLast(v)
    G->vertices[s - 1].v_visit = 1; //l(v) = visited

    while (front < rear) {
        int current = Queue[front];
        printf("%d\n", current);

        for (int p = 0; p < n; p++) {
            int i = G->matrix[current - 1][p];
            if (i != -1) { //if (l(e) = fresh)
                int other = otherendpoint(G, i, current);
                if (G->vertices[other - 1].v_visit == 0) { //if (l(w) = fresh)
                    G->edges[i].e_visit = 1; //l(e) <- Tree
                    G->vertices[other - 1].v_visit = 1; //l(w) <- visited
                    Queue[rear++] = other;
                }
                else
                    G->edges[i].e_visit = 2; //l(e) <- Cross
            }
        }
        front++;
    }
}

int main()
{
    int n, m, s;
    scanf("%d %d %d", &n, &m, &s);
    
    graph *G = initGraph(n, m);

    int u, v;
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);
        addedge(G, u, v);
    }
    BFS(G, s, n);

    return 0;
}
