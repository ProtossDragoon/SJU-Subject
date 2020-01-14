#include<stdio.h>
#include<stdlib.h>

typedef struct node node;
struct node {

	int index_edge;
	node* next;
};

typedef struct edge edge;
struct edge {

	int id;
	int weight;
	int label;
	int index_vert_a;
	int index_vert_b;
};

typedef struct vert vert;
struct vert {

	int id;
	int d;
	int p;
	int label;
	node* incid_edges;
};

typedef struct graph graph;
struct graph {

	int num_vertices;
	int num_edges;
	edge* edges;
	vert* vertices;
};

node* getNode(int edgeid, node* next) {

	node* newnode;
	newnode = (node*)malloc(sizeof(node) * 1);
	newnode->index_edge = edgeid;
	newnode->next = next;
	return newnode;
}

void setEdge(graph *G, int edgeid, int vf, int vt, int weight) {

	G->edges[edgeid].index_vert_a = vf;
	G->edges[edgeid].index_vert_b = vt;
	G->edges[edgeid].id = edgeid;
	G->edges[edgeid].weight = weight;
}

void addIncidNode(graph* G, int edgeid, int index_vert) {

	node* nd = G->vertices[index_vert].incid_edges;
	node* newnode;

	newnode = getNode(edgeid, nd->next);
	nd->next = newnode;
}

void addDirectedEdge(graph *G, int edgeid, int vf, int vt, int weight) {

	setEdge(G, edgeid, vf, vt, weight);
	addIncidNode(G, edgeid, vf);
}

void addNormalEdge(graph *G, int edgeid, int v1, int v2, int weight) {

	setEdge(G, edgeid, v1, v2, weight);
	addIncidNode(G, edgeid, v1);
	if (v1 != v2) {
		addIncidNode(G, edgeid, v2);
	}
}

void removeGraph(graph* G) {

	node* nd;
	node* tmp;
	for (int i = 0; i < G->num_vertices; i++) {
		nd = G->vertices[i].incid_edges;
		while (nd->next) {
			tmp = nd;
			nd = nd->next;
			free(tmp);
		}
	}
	free(G->edges);
	free(G->vertices);
	free(G);
}

graph* getGraph(int num_vertices, int num_edges) {

	graph* newgraph = NULL;
	newgraph = (graph*)malloc(sizeof(graph) * 1);
	if (newgraph == NULL) return;
	newgraph->num_edges = num_edges;
	newgraph->num_vertices = num_vertices + 1;
	newgraph->edges = (edge*)malloc(sizeof(edge) * num_edges);
	if (newgraph->edges == NULL) return;
	newgraph->vertices = (vert*)malloc(sizeof(vert) * (num_vertices + 1));
	if (newgraph->vertices == NULL) return;

	for (int i = 0; i < num_vertices + 1; i++) {
		newgraph->vertices[i].label = 1;
		newgraph->vertices[i].id = i;
		newgraph->vertices[i].incid_edges = getNode(-1, NULL);
	}

	return newgraph;
}

int origin(graph* G, int index_edge) {

	return G->edges[index_edge].index_vert_a;
}

int opposit(graph *G, int index_edge, int index_vert){

	edge e = G->edges[index_edge];
	return index_vert == e.index_vert_a ? e.index_vert_b : e.index_vert_a;
}

// Alg

void BellmanFordAlgorithm(graph *G, int index_start) {

	// init
	for (int i = 1; i < G->num_vertices; i++) {
		G->vertices[i].d = 999999;
		G->vertices[i].label = 1;
	}
	G->vertices[index_start].d = 0;

	int ori, opp;
	for (int i = 1; i < G->num_vertices; i++) {
		for (int j = 0; j < G->num_edges; j++) {
			ori = origin(G, j);
			opp = opposit(G, j, ori);
			if (G->vertices[ori].d + G->edges[j].weight < G->vertices[opp].d) {
				G->vertices[opp].d = G->vertices[ori].d + G->edges[j].weight;
				G->vertices[opp].label = 0;
			}
		}
	}

	for (int i = 1; i < G->num_vertices; i++) {
		if (i != index_start) {
			if (G->vertices[i].label == 0)
				printf("%d %d\n", i, G->vertices[i].d);
		}
	}

}

int main() {

	int num_vertices, num_edges, index_start;
	scanf("%d %d %d", &num_vertices, &num_edges, &index_start);
	graph* G = getGraph(num_vertices, num_edges);

	int vf, vt, w;
	for (int i = 0; i < num_edges; i++) {
		scanf("%d %d %d", &vf, &vt, &w);
		addDirectedEdge(G, i, vf, vt, w);
	}

	BellmanFordAlgorithm(G, index_start);

	return 0;
}