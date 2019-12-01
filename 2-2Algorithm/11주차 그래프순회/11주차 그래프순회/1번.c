#include<stdio.h>
#include<stdlib.h>

typedef struct graph graph;
typedef struct vertex_list vertex_list;
typedef struct edge_list edge_list;
typedef struct vert vert;
typedef struct edg edg;

struct graph {
	vertex_list *vertexes;
	edge_list *edges;
};
struct vert {
	int name;
	int _label;
	int incident_edges_cnt;
	edge_list* incident_edges[100];
};
struct edg {
	int weight;
	int _label;
	vert* a;
	vert* b;
};
struct vertex_list {
	int vert_cnt;
	vert vertex;
};
struct edge_list {
	int edge_cnt;
	edg edge;
};

#define FRESH 0
#define VISITED 1
#define TREE 2
#define BACK 3


edg* aEdge(int weight) {

	edg* newedge = NULL;
	newedge = (edg*)malloc(sizeof(edg) * 1);
	if (newedge == NULL) return;
	newedge->weight = weight;
	newedge->_label = 0;

	return newedge;
}
edg* aEdgeData(edg* aedge) {

	edge_list* edgedata = NULL;
	edgedata = (edge_list*)malloc(sizeof(edge_list) * 1);
	if (edgedata == NULL) return;

	edgedata->edge = *aedge;
	edgedata->edge_cnt = 1;
	free(aedge);
	return edgedata;
}
vert* find_vertex(vertex_list* list, int name) {
	
	for (int i = 0; i < list->vert_cnt; i++) {
		if (list[i].vertex.name == name) {
			return &(list[i].vertex);
		}
	}
	printf("error !\n");

	return NULL;
}

void insertEdge(vert* a, vert* b, edge_list* edgedata) {
	
	a->incident_edges[a->incident_edges_cnt] = edgedata;
	a->incident_edges_cnt++;
	b->incident_edges[b->incident_edges_cnt] = edgedata;
	b->incident_edges_cnt++;
	edgedata->edge.a = a;
	edgedata->edge.b = b;
}


vert* opposit(vert* startingvertex, edg* edge) {

	vert* oppositvertex = NULL;
	oppositvertex = edge->a;
	if (oppositvertex == startingvertex) {
		oppositvertex = edge->b;
	}

	return oppositvertex;
}


void sort_edge_list_with_vertex_name(vert* startingvertex) {

	// 삽입정렬 하자 insertion sort.
	edge_list** edges = startingvertex->incident_edges;
	int edge_cnt = startingvertex->incident_edges_cnt;
	int pass;

	edge_list* save;
	for (int look = 1; look < edge_cnt; look++) {

		save = (edges[look]);

		pass = look-1;
		while (pass >= 0 && 
			opposit(startingvertex, &(edges[pass]->edge))->name > opposit(startingvertex, &(save->edge))->name) {
			edges[pass + 1] = edges[pass];
			pass--;
		}

		edges[pass + 1] = save;
	}
}

void rDFS(vert* startingvertex) {

	edge_list** edges = startingvertex->incident_edges;
	int edges_cnt = startingvertex->incident_edges_cnt;

	vert* w = NULL;

	sort_edge_list_with_vertex_name(startingvertex);
	printf("%d\n", startingvertex->name);
	startingvertex->_label = VISITED;
	for (int i = 0; i < edges_cnt; i++) {
		if (edges[i]->edge._label == FRESH) {
			w = opposit(startingvertex, &(edges[i]->edge));
			if (w->_label == FRESH) {
				edges[i]->edge._label = TREE;
				rDFS(w);
			}
			else  edges[i]->edge._label = BACK;
		}
	}
}
void DFS(graph G, vert* startingvertx) {
	
	edge_list* edges = G.edges;
	vertex_list* vertexes = G.vertexes;
	
	for (int i = 0; i < edges->edge_cnt; i++) {
		G.edges[i].edge._label = FRESH;
	}
	for (int i = 0; i < vertexes->vert_cnt; i++) {
		G.vertexes[i].vertex._label = FRESH;
	}
	rDFS(startingvertx);
}


int main() {

	int n, m, start_vertex;

	graph G;
	vertex_list *vertexes;
	edge_list *edges;

	scanf("%d %d %d", &n, &m, &start_vertex);

	vertexes = (vertex_list*)malloc(sizeof(vertex_list) * m);
	if (vertexes == NULL) return;
	for (int i = 0; i < n; i++) {
		vertexes[i].vertex.name = (i + 1);
		vertexes[i].vertex.incident_edges_cnt = 0;
	}
	edges = (edge_list*)malloc(sizeof(edge_list) * m);
	if (edges == NULL) return;
	vertexes->vert_cnt = n;
	edges->edge_cnt = m;

	G.vertexes = vertexes;
	G.edges = edges;

	int vert1, vert2;
	vert* a, *b;
	edg* edge;
	edge_list* edgedata;
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &vert1, &vert2);
		edge = aEdge(0);
		edgedata = aEdgeData(edge);
		a = find_vertex(vertexes, vert1);
		b = find_vertex(vertexes, vert2);
		insertEdge(a, b, edgedata);
	}

	DFS(G, find_vertex(vertexes, start_vertex));


	return 0;
}