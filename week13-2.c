//Kruskal 알고리즘
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct vertex {
	int vnum;
	int dv;
} vertex;

typedef struct edge {
	int endpoint1;
	int endpoint2;
	int weight;
} edge;

typedef struct graph {
	vertex* vertices;
	edge* edges;
	int edge_index;
} graph;

typedef struct sack {
	int nodenum;
	int insacknum;
} sack;

graph* initgraph(int n, int m) {
	graph* G = (graph*)malloc(sizeof(graph));
	G->vertices = (vertex*)malloc(sizeof(vertex) * n);
	for (int i = 0; i < n; i++) {
		//G->vertices[i].IL = NULL;
		G->vertices[i].vnum = i + 1;
	}
	G->edges = (edge*)malloc(sizeof(edge) * m);
	G->edge_index = 0;
	return G;
}

void addedge(graph* G, int u, int v, int w) {
	int i = G->edge_index;
	G->edges[i].endpoint1 = u;
	G->edges[i].endpoint2 = v;
	G->edges[i].weight = w;

	G->edge_index++;
}

int findsack(sack *S, int num) {
	return S[num - 1].insacknum;
}

void unionsack(sack* S, int u, int v, int n) {
	if (S[u - 1].insacknum <= S[v - 1].insacknum) {
		int sacknum = S[v - 1].insacknum;
		for (int i = 0; i < n; i++)
			if (S[i].insacknum == sacknum)
				S[i].insacknum = S[u - 1].insacknum;
	}
	else {
		int sacknum = S[u - 1].insacknum;
		for (int i = 0; i < n; i++)
			if (S[i].insacknum == sacknum)
				S[i].insacknum = S[v - 1].insacknum;
	}
}

void kruskal(graph* G, int n, int m) {
	sack* sacklist = (sack*)malloc(sizeof(sack) * n);
	for (int i = 0; i < n; i++) {
		sacklist[i].nodenum = i + 1;
		sacklist[i].insacknum = i + 1;
	}
	for (int i = 0; i < m - 1; i++) //edges를 weight 오름차순 정렬
		for (int j = 0; j < m - i - 1; j++)
			if (G->edges[j].weight > G->edges[j + 1].weight) {
				edge tmp = G->edges[j];
				G->edges[j] = G->edges[j + 1];
				G->edges[j + 1] = tmp;
			}

	int totalweight = 0;
	for (int i = 0; i < m; i++) {
		int u = G->edges[i].endpoint1;
		int v = G->edges[i].endpoint2;
		if (findsack(sacklist, u) != findsack(sacklist, v)) {
			unionsack(sacklist, u, v, n);
			printf(" %d", G->edges[i].weight);
			totalweight += G->edges[i].weight;
		}
	}
	printf("\n");
	printf("%d\n", totalweight);
}

int main()
{
	int n, m;
	scanf("%d %d", &n, &m);
	graph* G = initgraph(n, m);

	int u, v, w;
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &u, &v, &w);
		addedge(G, u, v, w);
	}
	kruskal(G, n, m);

	return 0;
}
