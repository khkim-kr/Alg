//Prim-Jarnik 알고리즘
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

#define infinite 20000

typedef struct vertex {
	struct incidencelist* IL;
	int vnum;
	int dv;
} vertex;

typedef struct edge {
	int endpoint1;
	int endpoint2;
	int weight;
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

void addedge(graph* G, int u, int v, int w) {
	int i = G->edge_index;
	G->edges[i].endpoint1 = u;
	G->edges[i].endpoint2 = v;
	G->edges[i].weight = w;

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

void downHeap(int* H, graph* G, int w, int n) {
	if (w * 2 > n)
		return;
	int smaller = w * 2;
	if (n >= w * 2 + 1 && G->vertices[H[smaller] - 1].dv > G->vertices[H[smaller + 1] - 1].dv)
		smaller = w * 2 + 1;
	else if (n >= w * 2 + 1 && G->vertices[H[smaller] - 1].dv == G->vertices[H[smaller + 1] - 1].dv)
		if (H[smaller] > H[smaller + 1])
			smaller = w * 2 + 1;
	if (G->vertices[H[w] - 1].dv < G->vertices[H[smaller] - 1].dv)
		return;
	else if (G->vertices[H[w] - 1].dv == G->vertices[H[smaller] - 1].dv)
		if (H[w] < H[smaller])
			return;
	int tmp = H[w];
	H[w] = H[smaller];
	H[smaller] = tmp;
	downHeap(H, G, smaller, n);
}

int removeMin(int* H, graph* G, int n) {
	int d = H[1];
	int tmp = H[1];
	H[1] = H[n];
	H[n] = tmp;
	n--;
	downHeap(H, G, 1, n);
	return d;
}

int inHeap(int* H, int z, int n) {
	int check = 0;
	for (int i = 1; i <= n; i++)
		if (H[i] == z) {
			check = 1;
			break;
		}
	return check;
}

void replaceHeap(int* H, graph* G, int z, int n) {
	int findidx = 0;
	for (int i = 1; i <= n; i++)
		if (H[i] == z) {
			findidx = i;
			break;
		}
	int save = H[findidx];
	int j = findidx - 1;
	while (j >= 1) {
		if (G->vertices[H[j] - 1].dv > G->vertices[save - 1].dv)
			H[j + 1] = H[j];
		else if (G->vertices[H[j] - 1].dv == G->vertices[save - 1].dv) {
			if (H[j] > save)
				H[j + 1] = H[j];
		}
		else
			break;
		j--;
	}
	H[j + 1] = save;
}

void prim_jarnikMST(graph* G, int n, int m) {
	for (int i = 0; i < n; i++)
		G->vertices[i].dv = infinite;
	G->vertices[0].dv = 0;
	int* H = (int*)malloc(sizeof(int) * (n + 1));
	for (int i = 1; i <= n; i++)
		H[i] = G->vertices[i - 1].vnum;
	int num = n;
	int totalweight = 0;
	while (num > 0) {
		int u = removeMin(H, G, num);
		printf(" %d", u);
		num--;
		totalweight += G->vertices[u - 1].dv;
		incidencelist* current = G->vertices[u - 1].IL;
		while (current != NULL) {
			int z = opposite(G, current->edgeindex, u);
			int w = G->edges[current->edgeindex].weight;
			if (inHeap(H, z, num) && G->vertices[z - 1].dv > w) {
				G->vertices[z - 1].dv = w;
				replaceHeap(H, G, z, num);
			}
			current = current->next;
		}
	}
	printf("\n%d\n", totalweight);
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
	prim_jarnikMST(G, n, m);
}
