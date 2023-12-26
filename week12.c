//방향그래프 - 위상순서 찾기
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct vertex {
    struct incidencelist *IL;
    char vname;
    int indegree;
} vertex;

typedef struct edge {
    char endpoint1;
    char endpoint2;
} edge;

typedef struct incidencelist {
    int edgeindex;
    struct incidencelist *next;
} incidencelist;

typedef struct graph {
    vertex *vertices;
    edge *edges;
    int edge_index;
} graph;

typedef struct queue {
    int front, rear;
    char *element;
} queue;

graph *initgraph(int n) {
    graph *G = (graph*)malloc(sizeof(graph));
    G->vertices = (vertex*)malloc(sizeof(vertex) * n);
    G->edge_index = 0;
    return G;
}

void insertVertex(graph *G, char vName, int i) {
    G->vertices[i].vname = vName;
    G->vertices[i].indegree = 0;
}

graph *initgraphedge(graph *G, int m) {
    G->edges = (edge*)malloc(sizeof(edge) * m);
    return G;
}

int findindex(graph *G, int n, char vName) {
    int idx = -1;
    for (int i = 0; i < n; i++)
        if (G->vertices[i].vname == vName) {
            idx = i;
            break;
        }
    return idx;
}

void addedge(graph *G, char u, char v, int n) {
    int i = G->edge_index;
    G->edges[i].endpoint1 = u;
    G->edges[i].endpoint2 = v;

    incidencelist *node = (incidencelist*)malloc(sizeof(incidencelist));
    int vindex = findindex(G, n, u);
    incidencelist *first = G->vertices[vindex].IL;
    
    node->edgeindex = i;
    node->next = first;
    G->vertices[vindex].IL = node; //맨 앞에 삽입

    int opposite = findindex(G, n, v);
    G->vertices[opposite].indegree++; //진입 차수 갱신
    
    G->edge_index++;
}

queue *initqueue(int n) {
    queue *Q = (queue*)malloc(sizeof(queue));
    Q->front = 0;
    Q->rear = 0;
    Q->element = (char*)malloc(sizeof(char) * n);
    for (int i = 0; i < n; i++)
        Q->element[i] = '\0';
    return Q;
}

int isEmpty(queue *Q) {
    return Q->front == Q->rear;
}

void enqueue(queue *Q, char c) {
    Q->element[Q->rear] = c;
    Q->rear++;
}

char dequeue(queue *Q) {
    int c = Q->element[Q->front];
    Q->front++;
    return c;
}

char *topologicalSort(graph *G, int n) {
    char *toporder = (char*)malloc(sizeof(char) * (n + 1));
    int *in = (int*)malloc(sizeof(int) * n);
    queue *Q = initqueue(n);
    for (int i = 0; i < n; i++) {
        in[i] = G->vertices[i].indegree;
        if (in[i] == 0)
            enqueue(Q, G->vertices[i].vname);
    }
    int i = 1;
    while (!isEmpty(Q)) {
        toporder[i] = dequeue(Q);
        int vindex = findindex(G, n, toporder[i]);
        i++;
        incidencelist *current = G->vertices[vindex].IL;
        while (current != NULL) {
            int ei = current->edgeindex;
            int opposite = findindex(G, n, G->edges[ei].endpoint2);
            //G->vertices[opposite].indegree -= 1;
            in[opposite] -= 1;
            if (in[opposite] == 0)
                enqueue(Q, G->vertices[opposite].vname);
            current = current->next;
        }
    }
    if (i <= n)
        toporder[0] = '0';
    else
        toporder[0] = '1';
    return toporder;
}

int main()
{
    int n;
    scanf("%d", &n);
    getchar();
    
    graph *G = initgraph(n);
    
    char vName;
    for (int i = 0; i < n; i++) {
        scanf("%c", &vName);
        getchar();
        insertVertex(G, vName, i);
    }
    int m;
    scanf("%d", &m);
    getchar();
    
    G = initgraphedge(G, m);
    
    char u, v;
    for (int i = 0; i < m; i++) {
        scanf("%c %c", &u, &v);
        getchar();
        addedge(G, u, v, n);
    }
    char *toporder = topologicalSort(G, n);
    if (toporder[0] == '0')
        printf("0\n");
    else {
        printf("%c", toporder[1]);
        for (int i = 2; i <= n; i++)
            printf(" %c", toporder[i]);
        printf("\n");
    }

    return 0;
}
