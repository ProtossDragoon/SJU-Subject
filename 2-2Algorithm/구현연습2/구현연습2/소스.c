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
	int label;
	int d;
	int p;
	node* incid_edge;
};

typedef struct graph graph;
struct graph {

	int num_edge;
	int num_vertices;
	vert* vertices;
	edge* edges;
};

node* getNode(node *next, int edgeid) {

	node* newnode;
	newnode = (node*)malloc(sizeof(node) * 1);
	if (newnode == NULL) return;

	newnode->next = next;
	newnode->index_edge = edgeid;
	return newnode;
}

void setEdgeData(graph *G, int edgeid, int v1, int v2, int w) {

	G->edges[edgeid].id = edgeid;
	G->edges[edgeid].index_vert_a = v1;
	G->edges[edgeid].index_vert_b = v2;
	G->edges[edgeid].weight = w;
}

void addIncidNode(graph *G, int edgeid, int from, int to) {

	node* nd = G->vertices[from].incid_edge;
	node* newnode;
	newnode = getNode(nd->next, edgeid);
	nd->next = newnode;
}

void addEdge(graph *G, int edgeid, int v1, int v2, int w) {

	setEdgeData(G, edgeid, v1, v2, w);

	addIncidNode(G, edgeid, v1, v2);
	if (v1 != v2) {
		addIncidNode(G, edgeid, v2, v1);
	}
}

void freeGraph(graph* G) {

	node* nd, *tmp;
	for (int i = 0; i < G->num_vertices; i++) {
		nd = G->vertices[i].incid_edge;
		while (nd->next) {
			tmp = nd;
			nd = nd->next;
			free(tmp);
		}
	}
	free(G->vertices);
	free(G->edges);
	free(G);
}

graph* getGraph(int num_vertices, int num_edges) {

	graph* newgraph;
	newgraph = (graph*)malloc(sizeof(graph) * 1);
	if (newgraph == NULL) return;

	newgraph->num_edge = num_edges;
	newgraph->num_vertices = num_vertices;
	newgraph->edges = (edge*)malloc(sizeof(edge) * num_edges);
	if (newgraph->edges == NULL) return;
	newgraph->vertices = (vert*)malloc(sizeof(vert) * num_vertices);
	if (newgraph->vertices == NULL) return;

	for (int i = 0; i < num_vertices; i++) {
		newgraph->vertices[i].id = i;
		newgraph->vertices[i].incid_edge = getNode(NULL, -1);
	}

	return newgraph;
}


#define Noset -1
typedef struct set set;
struct set {
	int size;
	int kind;
	int* setdata;
};

set* getSet(int range, int kind) {

	set* newset;
	newset = (set*)malloc(sizeof(set) * 1);
	if (newset == NULL) return;

	newset->size = range + 1;
	newset->kind = kind;
	newset->setdata = (int*)malloc(sizeof(sizeof(int) * (range + 1)));
	if (newset->setdata == NULL) return;

	for (int i = 0; i < newset->size; i++) {
		newset->setdata[i] = Noset;
	}

	return newset;
}

// 해당 원소가 어떤 집합의 원소인지를 반환함.
int setFind(set* S, int element) {

	return S->setdata[element];
}

// 두 집합을 통합함.
void setUnion(set* S, int seta, int setb) {

	S->kind--;
	for (int i = 0; i < S->size; i++) {
		if (S->setdata[i] == setb) {
			S->setdata[i] = seta;
		}
	}
}


typedef struct p_queue p_queue;
typedef struct key_val key_val;
struct key_val {
	int key;
	int val;
};
struct p_queue {
	int maxsize;
	int cursize;
	key_val* data;
};

void getQueue(p_queue* Q, int size) {

	Q->maxsize = size;
	Q->cursize = 0;
	Q->data = (key_val*)malloc(sizeof(key_val) * size);
	for (int i = 0; i < Q->maxsize; i++) {
		Q->data[i].key = -1;
		Q->data[i].val = -1;
	}
}

void enQueue(p_queue* Q, int key, int val) {

	Q->data[Q->cursize].key = key;
	Q->data[Q->cursize].val = val;
	Q->cursize++;
}

int deQueue(p_queue* Q) {

	int minindex;
	key_val mindata;
	
	for (int i = 0; i < Q->maxsize; i++) {
		if (i == 0) {
			minindex = i;
			mindata = Q->data[i];
		}

		else {
			if (mindata.key > Q->data[i].key) {
				minindex = i;
				mindata = Q->data[i];
			}
		}
	}

	Q->data[minindex].key = 1000000;
	Q->data[minindex].val = -1;

	Q->cursize--;

	return mindata.val;
}

int isQueueEmpty(p_queue* Q) {

	return !(Q->cursize);
}

// MSTKruskal algorithm
void KruskalMST(graph* G) {

	// Queue
	p_queue Q;
	getQueue(&Q, G->num_edge);
	for (int i = 0; i < G->num_edge; i++) {
		enQueue(&Q, G->edges[i].weight, i);
	}
	
	// Set
	set *S;
	S = getSet(G->num_vertices, G->num_vertices);
	for (int i = 1; i < G->num_vertices; i++) {
		S->setdata[i] = i;
	}

	int index_edge;
	int a, b;
	int sum = 0;
	while (!isQueueEmpty(&Q)) {
		index_edge = deQueue(&Q);
		a = G->edges[index_edge].index_vert_a;
		b = G->edges[index_edge].index_vert_b;
		if (setFind(S, a) != setFind(S, b)) {
			// add this edge to MST bag
			sum = sum + G->edges[index_edge].weight;
			printf(" %d", G->edges[index_edge].weight);
			setUnion(S, setFind(S,a), setFind(S, b));
		}
	}
	printf("\n%d", sum);
}


int main() {

	graph* G;

	int num_vertices, num_edges;
	
	scanf("%d %d", &num_vertices, &num_edges);
	G = getGraph(num_vertices + 1, num_edges);

	int v1, v2, w;
	for (int i = 0; i < num_edges; i++) {
		scanf("%d %d %d", &v1, &v2, &w);
		addEdge(G, i, v1, v2, w);
	}

	KruskalMST(G);

	freeGraph(G);

	return 0;
}