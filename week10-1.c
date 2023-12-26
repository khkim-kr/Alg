//그래프 구현 - 인접리스트
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct vertex {
    struct incidencelist *IL;
    int numv;
} vertex;

typedef struct edge {
    int endpoint1;
    int endpoint2;
    int weight;
} edge;

typedef struct incidencelist {
    int edgeindex;
    struct incidencelist *next;
} incidencelist;

typedef struct graph {
    struct vertex *vertices;
    struct edge *edges;
    int edge_index;
} graph;

graph *initgraph() {
    graph *G = (graph*)malloc(sizeof(graph));
    G->vertices = (vertex*)malloc(sizeof(vertex) * 6);
    for (int i = 0; i < 6; i++) {
        G->vertices[i].IL = NULL; //header 초기화
        G->vertices[i].numv = i + 1; //정점노드 번호
    }
    G->edges = (edge*)malloc(sizeof(edge) * 21); //m <= n(n-1)/2 + n (자기 자신)
    G->edge_index = 0;
    return G;
}

int otherendpoint(graph *G, int i, int nodenum) {
    return G->edges[i].endpoint2 == nodenum ? G->edges[i].endpoint1 : G->edges[i].endpoint2;
}

void addedge(graph *G, int u, int v, int w) {
    int i = G->edge_index;
    G->edges[i].endpoint1 = u;
    G->edges[i].endpoint2 = v;
    G->edges[i].weight = w;

    //정점 노드 u에 관한 간선 추가
    incidencelist *node1 = (incidencelist*)malloc(sizeof(incidencelist));
    node1->edgeindex = i;
    node1->next = NULL;

    incidencelist *prev1 = NULL;
    incidencelist *current1 = G->vertices[u - 1].IL;
    while (current1 != NULL && otherendpoint(G, current1->edgeindex, u) < v) {
        prev1 = current1;
        current1 = current1->next;
    }
    if (prev1 == NULL) {
        node1->next = G->vertices[u - 1].IL;
        G->vertices[u - 1].IL = node1;
    }
    else {
        node1->next = prev1->next;
        prev1->next = node1;
    }

    if (u == v) { //본인 출발, 본인 도착
        G->edge_index += 1;
        return;
    }

    //정점 노드 v에 관한 간선 추가
    incidencelist *node2 = (incidencelist*)malloc(sizeof(incidencelist));
    node2->edgeindex = i;
    node2->next = NULL;

    incidencelist *prev2 = NULL;
    incidencelist *current2 = G->vertices[v - 1].IL;
    while (current2 != NULL && otherendpoint(G, current2->edgeindex, v) < u) {
        prev2 = current2;
        current2 = current2->next;
    }
    if (prev2 == NULL) {
        node2->next = G->vertices[v - 1].IL;
        G->vertices[v - 1].IL = node2;
    }
    else {
        node2->next = prev2->next;
        prev2->next = node2;
    }
    G->edge_index += 1;
}

void searchAdjacency(graph *G, int nodenum) {
    if (nodenum < 1 || nodenum > 6) {
        printf("-1\n");
        return;
    }
    incidencelist *current = G->vertices[nodenum - 1].IL;
    while (current != NULL) {
        int i = current->edgeindex;
        int endpoint = otherendpoint(G, i, nodenum);
        int w = G->edges[i].weight;
        printf(" %d %d", endpoint, w);
        current = current->next;
    }
    printf("\n");
}

void removeedge(graph *G, int u, int v) {
    incidencelist *prev1 = NULL;
    incidencelist *current1 = G->vertices[u - 1].IL;
    while (current1 != NULL) {
        int i = current1->edgeindex;
        if ((G->edges[i].endpoint1 == v && G->edges[i].endpoint2 == u) || (G->edges[i].endpoint2 == v && G->edges[i].endpoint1 == u)) {
            if (prev1 == NULL) //IL의 첫번째 노드가 삭제할 노드인 경우
                G->vertices[u - 1].IL = current1->next;
            else
                prev1->next = current1->next;
            break;
        }
        prev1 = current1;
        current1 = current1->next;
    }
    incidencelist *prev2 = NULL;
    incidencelist *current2 = G->vertices[v - 1].IL;
    while (current2 != NULL) {
        int i = current2->edgeindex;
        if ((G->edges[i].endpoint1 == u && G->edges[i].endpoint2 == v) || (G->edges[i].endpoint2 == u && G->edges[i].endpoint1 == v)) {
            if (prev2 == NULL)
                G->vertices[v - 1].IL = current2->next;
            else
                prev2->next = current2->next;
            break;
        }
        prev2 = current2;
        current2 = current2->next;
    }
}

void modifyGraph(graph *G, int u, int v, int w) {
    if (u < 1 || u > 6 || v < 1 || v > 6) {
        printf("-1\n");
        return;
    }
    if (w == 0) { //간선 삭제 - 삭제할 간선 없을 경우 error
        removeedge(G, u, v);
        return;
    }
    incidencelist *current = G->vertices[u - 1].IL;
    while (current != NULL) { //간선 가중치 변경
        int i = current->edgeindex;
        if ((G->edges[i].endpoint1 == v && G->edges[i].endpoint2 == u) || (G->edges[i].endpoint1 == u && G->edges[i].endpoint2 == v)) {
            G->edges[i].weight = w;
            return;
        }
        current = current->next;
    }
    if (current == NULL) //간선 없을 경우
        addedge(G, u, v, w);
}

int main() {
    //무방향 가중그래프 생성
    graph *G = initgraph();
    
    addedge(G, 1, 2, 1);
    addedge(G, 1, 3, 1);
    addedge(G, 1, 4, 1);
    addedge(G, 1, 6, 2);
    addedge(G, 2, 3, 1);
    addedge(G, 3, 5, 4);
    addedge(G, 5, 5, 4);
    addedge(G, 5, 6, 3);

    //대화식 프로그램 시작
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
