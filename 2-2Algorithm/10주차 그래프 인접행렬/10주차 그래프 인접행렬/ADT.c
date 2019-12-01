#include<stdio.h>
#include<stdlib.h>

typedef struct linked_list linked_list;
typedef struct edges edges;
typedef struct node node;
typedef struct vertex vertex;
typedef struct edge edge;
typedef union data data;

struct vertex { // 4 byte * 2
	int label;
	int name;
};
struct edge { // 4 byte * 2
	int label;
	int weight;
	node* linked_vertex1;
	node* linked_vertex2;
};
union data { // size : max(sturct vertex, struct edge) byte
	vertex data_vertex;
	edge data_edge;
};
struct node {
	node* next;
	node* prev;
	data data;
};
struct linked_list {
	node* header;
	node* trailer;
};


typedef struct adjmatrix adjmatrix;
struct adjmatrix {
	int size;
	node*** matrix;
};
typedef struct graph graph;
struct graph {
	linked_list* vertics;
	linked_list* edges;
	adjmatrix* adjmatrix;
};


adjmatrix* get_adjmatrix(int size) {

	adjmatrix* newmatrix = NULL;
	newmatrix = (adjmatrix*)malloc(sizeof(adjmatrix) * 1);
	if (newmatrix == NULL) return;
	newmatrix->size = size + 1;

	(newmatrix->matrix) = (node***)malloc(sizeof(node**) * newmatrix->size);
	if (newmatrix->matrix == NULL) return;
	for (int i = 0; i < newmatrix->size; i++) {
		(newmatrix->matrix)[i] = (node**)malloc(sizeof(node*) * newmatrix->size);
		if ((newmatrix->matrix)[i] == NULL) return;
		for (int j = 0; j < newmatrix->size; j++) {
			(newmatrix->matrix)[i][j] = NULL;
		}
	}

	return newmatrix;
}
void put_adjmatrix(adjmatrix* matrix){

	int size = matrix->size;
	for (int i = 0; i < size; i++) {
		free((matrix->matrix)[i]);
	}
	free(matrix->matrix);
	free(matrix);
}
node* get_node() {

	node* newnode = NULL;
	newnode = (node*)malloc(sizeof(node) * 1);
	if (newnode == NULL) return;

	newnode->next = NULL;
	newnode->prev = NULL;

	return newnode;
}
void put_node(node* nd) {
	free(nd);
}
linked_list* get_linkedList() {

	linked_list* newlinkedlist = NULL;
	newlinkedlist = (linked_list*)malloc(sizeof(linked_list) * 1);
	if (newlinkedlist == NULL) return;

	newlinkedlist->header = get_node();
	newlinkedlist->trailer = get_node();

	newlinkedlist->header->prev = NULL;
	newlinkedlist->header->next = newlinkedlist->trailer;
	newlinkedlist->trailer->prev = newlinkedlist->header;
	newlinkedlist->trailer->next = NULL;

	return newlinkedlist;
}
void put_linkedList(linked_list* li) {

	node* nd;
	nd = li->header->next;
	while (nd != li->trailer) {
		nd = nd->next;
		put_node(nd->prev);
	}
	put_node(li->header);
	put_node(li->trailer);
}
graph* get_graph(int size) {

	graph* newgraph = NULL;
	newgraph = (graph*)malloc(sizeof(graph) * 1);
	if (newgraph == NULL) return;

	linked_list* vertics = NULL;
	linked_list* edges = NULL;
	adjmatrix* matrix = NULL;
	vertics = get_linkedList();
	edges = get_linkedList();
	matrix = get_adjmatrix(size);

	newgraph->edges = edges;
	newgraph->vertics = vertics;
	newgraph->adjmatrix = matrix;

	return newgraph;
}
void put_graph(graph* G) {
	
	put_adjmatrix(G->adjmatrix);
	put_linkedList(G->edges);
	put_linkedList(G->vertics);
	free(G);
}
void addLast(linked_list* li, node* nd) {

	node* prev;
	node* next;
	prev = li->trailer->prev;
	next = li->trailer;

	prev->next = nd;
	nd->prev = prev;
	next->prev = nd;
	nd->next = next;
}
void removeElementNode(linked_list* li, node* nd) {
	
	nd->next->prev = nd->prev;
	nd->prev->next = nd->next;
	put_node(nd);
}

node* aVert(int name) {

	node* newnode = NULL;
	newnode = get_node();
	newnode->data.data_vertex.name = name;
	newnode->data.data_vertex.label = -1;
	
	return newnode;
}
node* aEdge(int weight, node* linked_vert1, node* linked_vert2) {

	node* newnode = NULL;
	newnode = get_node();
	newnode->data.data_edge.weight = weight;
	newnode->data.data_edge.label = -1;
	newnode->data.data_edge.linked_vertex1 = linked_vert1;
	newnode->data.data_edge.linked_vertex2 = linked_vert2;

	return newnode;
}

#define VERTEX 0 
#define	EDGE 1
node* findNode(linked_list *li, int vertex_or_edge, int e) {

	node* np;
	np = li->header->next;
	while (np != li->trailer) {
		if (vertex_or_edge == VERTEX) {
			if (np->data.data_vertex.name == e) return np;
		}
		if (vertex_or_edge == EDGE) {
			if (np->data.data_edge.weight == e) return np;
		}
		np = np->next;
	}

	// printf("error : no data in list!\n");
	return NULL;
}
node* findVertexByName(graph *G, int name) {

	node* nd;
	nd = findNode(G->vertics, VERTEX, name);
	return nd;
}
node* findEdgeByVert(graph* G, node* linked_vert1, node* linked_vert2) {

	node* nd;
	int a, b;
	a = linked_vert1->data.data_vertex.name;
	b = linked_vert2->data.data_vertex.name;
	nd = (G->adjmatrix->matrix)[a][b];
	return nd;
}
node* findEdgeByVertName(graph* G, int name1, int name2) {

	node* nd1, * nd2;
	node* nd;
	nd1 = findNode(G->vertics, VERTEX, name1);
	nd2 = findNode(G->vertics, VERTEX, name2);
	nd = findEdgeByVert(G, nd1, nd2);
	return nd;
}

void insertVert(graph *G, node* vertnode) {

	addLast(G->vertics, vertnode);
}
void insertEdge(graph *G, node* edgenode) {

	addLast(G->edges, edgenode);
	node *vert1, *vert2;
	int a, b;
	vert1 = edgenode->data.data_edge.linked_vertex1;
	vert2 = edgenode->data.data_edge.linked_vertex2;
	a = vert1->data.data_vertex.name;
	b = vert2->data.data_vertex.name;

	(G->adjmatrix->matrix)[a][b] = edgenode;
	(G->adjmatrix->matrix)[b][a] = edgenode;
}
void removeEdge(graph* G, node* edgenode) {

	int a, b;
	a = edgenode->data.data_edge.linked_vertex1->data.data_vertex.name;
	b = edgenode->data.data_edge.linked_vertex2->data.data_vertex.name;
	removeElementNode(G->edges, edgenode);
	(G->adjmatrix->matrix)[a][b] = NULL;
	(G->adjmatrix->matrix)[b][a] = NULL;
}

node* opposit(node* vertexnode, node* edgenode) {

	node* oppositnode;
	oppositnode = edgenode->data.data_edge.linked_vertex1;
	if (vertexnode == oppositnode) {
		return edgenode->data.data_edge.linked_vertex2;
	}
	else return oppositnode;
}
void adjacent_print(graph *G, int nodenumber) {

	node* edgenode;
	node* vertexnode;
	node* nd;
	int cnt = 0;

	if (nodenumber <= 0) {
		printf("-1\n");
		return;
	}
	if (nodenumber >= G->adjmatrix->size) {
		printf("-1\n");
		return;
	}


	vertexnode = findVertexByName(G, nodenumber);
	for (int i = 0; i < G->adjmatrix->size; i++) {
		edgenode = (G->adjmatrix->matrix)[nodenumber][i];
		if (edgenode == NULL) {
			continue;
		}
		else {
			cnt++;
			nd = opposit(vertexnode, edgenode);
			printf(" %d %d", nd->data.data_vertex.name, edgenode->data.data_edge.weight);
		}
	}
	
	if (cnt == 0) {
		printf("-1");
	}
	printf("\n");
}
void modify_edge(graph* G, node* vertexnode1, node* vertexnode2, int modifynumber) {

	node* edgenode;
	
	int a, b;
	a = vertexnode1->data.data_vertex.name;
	b = vertexnode2->data.data_vertex.name;
	edgenode = findEdgeByVert(G, vertexnode1, vertexnode2);
	
	if (modifynumber == 0) {
		//remove
		removeEdge(G, edgenode);
	}
	if (edgenode == NULL) {
		node* newedge;
		newedge = aEdge(modifynumber, vertexnode1, vertexnode2);
		insertEdge(G, newedge);
	}
	else {
		edgenode->data.data_edge.weight = modifynumber;
	}
}


int main() {

	graph* G;
	G = get_graph(6);

	node *v1, *v2, *v3, *v4, *v5, *v6;
	v1 = aVert(1);
	v2 = aVert(2);
	v3 = aVert(3);
	v4 = aVert(4);
	v5 = aVert(5);
	v6 = aVert(6);
	insertVert(G, v1);
	insertVert(G, v2);
	insertVert(G, v3);
	insertVert(G, v4);
	insertVert(G, v5);
	insertVert(G, v6);

	node* e1, * e2, * e3, * e4, * e5, * e6, * e7, * e8;
	e1 = aEdge(1, v1, v2);
	e2 = aEdge(1, v1, v3);
	e3 = aEdge(1, v1, v4);
	e4 = aEdge(2, v1, v6);
	e5 = aEdge(1, v2, v3);
	e6 = aEdge(4, v3, v5);
	e7 = aEdge(3, v5, v6);
	e8 = aEdge(4, v5, v5);
	insertEdge(G, e1);
	insertEdge(G, e2);
	insertEdge(G, e3);
	insertEdge(G, e4);
	insertEdge(G, e5);
	insertEdge(G, e6);
	insertEdge(G, e7);
	insertEdge(G, e8);

	// requests
	char inputch;
	int inputint;
	int a, b;
	node *vert1, *vert2;

	while (1) {
		scanf("%c", &inputch);
		if (inputch == 'a') {
			scanf("%d", &inputint);
			adjacent_print(G, inputint);
		}
		else if (inputch == 'm') {
			scanf("%d %d %d", &a, &b, &inputint);
			vert1 = findVertexByName(G, a);
			if (vert1 == NULL) {
				getchar();
				printf("-1\n");
				continue;
			}
			vert2 = findVertexByName(G, b);
			if (vert2 == NULL) {
				printf("-1\n");
				getchar();
				continue;
			}
			modify_edge(G, vert1, vert2, inputint);
		}
		else { // input == 'q'
			break;
		}
		getchar();
	}

	// free graph
	put_graph(G);

	return 0;
	
}