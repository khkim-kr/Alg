//그래프 구현 - 인접행렬
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct vertex {
    int vnum;
} vertex;

typedef struct edge {
    int endpoint1;
    int endpoint2;
    int weight;
} edge;

typedef struct graph {
    vertex *vertices;
    edge *edges;
    int **matrix;
    int edge_index;
} graph;

graph *initGraph() {
    graph *G = (graph*)malloc(sizeof(graph));
    G->vertices = (vertex*)malloc(sizeof(vertex) * 6);
    for (int i = 0; i < 6; i++)
        G->vertices[i].vnum = i + 1;
    G->edges = (edge*)malloc(sizeof(edge) * 21);
    G->edge_index = 0;
    G->matrix = (int**)malloc(sizeof(int*) * 6);
    for (int i = 0; i < 6; i++) {
        G->matrix[i] = (int*)malloc(sizeof(int) * 6);
        for (int j = 0; j < 6; j++)
            G->matrix[i][j] = -1; //연결 없음 : -1
    }
    return G;
}

void addedge(graph *G, int u, int v, int w) {
    int i = G->edge_index;
    G->edges[i].endpoint1 = u;
    G->edges[i].endpoint2 = v;
    G->edges[i].weight = w;

    G->matrix[u - 1][v - 1] = i;
    G->matrix[v - 1][u - 1] = i;
    G->edge_index += 1;
}

int otherendpoint(graph *G, int i, int nodenum) {
    return G->edges[i].endpoint2 == nodenum ? G->edges[i].endpoint1 : G->edges[i].endpoint2;
}

void searchAdjacency(graph *G, int nodenum) {
    if (nodenum < 1 || nodenum > 6) {
        printf("-1\n");
        return;
    }
    for (int p = 0; p < 6; p++) {
        int i = G->matrix[nodenum - 1][p];
        if (i != -1) {
            int other = otherendpoint(G, i, nodenum);
            int w = G->edges[i].weight;
            printf(" %d %d", other, w);
        }
    }
    printf("\n");
}

void modifyGraph(graph *G, int u, int v, int w) {
    if (u < 1 || u > 6 || v < 1 || v > 6) {
        printf("-1\n");
        return;
    }
    if (w == 0) {
        G->matrix[u - 1][v - 1] = -1;
        G->matrix[v - 1][u - 1] = -1;
        return;
    }
    int i = G->matrix[u - 1][v - 1];
    if (i == -1)
        addedge(G, u, v, w);
    else
        G->edges[i].weight = w;
}

int main()
{
    graph *G = initGraph();

    addedge(G, 1, 2, 1);
    addedge(G, 1, 3, 1);
    addedge(G, 1, 4, 1);
    addedge(G, 1, 6, 2);
    addedge(G, 2, 3, 1);
    addedge(G, 3, 5, 4);
    addedge(G, 5, 5, 4);
    addedge(G, 5, 6, 3);

    char c;
    do {
        scanf("%c", &c);
        if (c == 'a') {
            int nodenum;
            scanf("%d", &nodenum);
            searchAdjacency(G, nodenum);
        }
        else if (c == 'm') {
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            modifyGraph(G, u, v, w);
        }
        getchar();
    } while (c != 'q');

    return 0;
}
