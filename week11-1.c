//그래프 순회 - DFS
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct vertex {
	struct incidencelist* IL;
	int vnum;
	int v_visit;
} vertex;

typedef struct edge {
	int endpoint1;
	int endpoint2;
	int e_visit;
} edge;

typedef struct incidencelist {
	int edgeindex;
	struct incidencelist* next;
} incidencelist;

typedef struct graph {
	vertex* vertices;
	edge* edges;
	int edge_index;
} graph;

graph* initgraph(int n, int m) {
	graph* G = (graph*)malloc(sizeof(graph));
	G->vertices = (vertex*)malloc(sizeof(vertex) * n);
	for (int i = 0; i < n; i++) {
		G->vertices[i].IL = NULL;
		G->vertices[i].vnum = i + 1;
	}
	G->edges = (edge*)malloc(sizeof(edge) * m);
	G->edge_index = 0;
	return G;
}

int opposite(graph* G, int i, int nodenum) {
	return G->edges[i].endpoint2 == nodenum ? G->edges[i].endpoint1 : G->edges[i].endpoint2;
}

void addedge(graph* G, int u, int v) {
	int i = G->edge_index;
	G->edges[i].endpoint1 = u;
	G->edges[i].endpoint2 = v;

	incidencelist* node1 = (incidencelist*)malloc(sizeof(incidencelist));
	node1->edgeindex = i;
	node1->next = NULL;

	incidencelist* current1 = G->vertices[u - 1].IL;
	incidencelist* prev1 = NULL;
	while (current1 != NULL && v > opposite(G, current1->edgeindex, u)) {
		prev1 = current1;
		current1 = current1->next;
	}
	if (prev1 == NULL) {
		node1->next = G->vertices[u - 1].IL;
		G->vertices[u - 1].IL = node1;
	}
	else {
		node1->next = current1;
		prev1->next = node1;
	}

	incidencelist* node2 = (incidencelist*)malloc(sizeof(incidencelist));
	node2->edgeindex = i;
	node2->next = NULL;

	incidencelist* current2 = G->vertices[v - 1].IL;
	incidencelist* prev2 = NULL;
	while (current2 != NULL && opposite(G, current2->edgeindex, v) < u) {
		prev2 = current2;
		current2 = current2->next;
	}
	if (prev2 == NULL) {
		node2->next = G->vertices[v - 1].IL;
		G->vertices[v - 1].IL = node2;
	}
	else {
		node2->next = current2;
		prev2->next = node2;
	}
	G->edge_index++;
}

void rDFS(graph* G, int v) {
	G->vertices[v - 1].v_visit = 1;
	printf("%d\n", v);
	incidencelist* current = G->vertices[v - 1].IL;
	while (current != NULL) {
		int w = opposite(G, current->edgeindex, v);
		if (G->vertices[w - 1].v_visit == 0)
			rDFS(G, w);
		current = current->next;
	}
}

void DFS(graph* G, int n, int m, int s) {
	for (int i = 0; i < n; i++)
		G->vertices[i].v_visit = 0;
	for (int i = 0; i < m; i++)
		G->edges[i].e_visit = 0;
	rDFS(G, s);
	for (int i = 0; i < n; i++)
		if (G->vertices[i].v_visit == 0)
			rDFS(G, i + 1);
}

int main()
{
	int n, m, s;
	scanf("%d %d %d", &n, &m, &s);

	graph* G = initgraph(n, m);
	int u, v;
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &u, &v);
		addedge(G, u, v);
	}
	DFS(G, n, m, s);
}
