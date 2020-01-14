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
	int index_vert_a;
	int index_vert_b;
};

typedef struct vert vert;
struct vert {

	int d;
	int label;
	int id;
	node* out_edge;
};

typedef struct graph graph;
struct graph {

	int num_edges;
	int num_vertices;
	edge* edges;
	vert* vertices;
};


node* getNode(int edgeid, node* next) {
	
	node* newnode;
	newnode = (node*)malloc(sizeof(node) * 1);
	if (newnode == NULL)return;

	newnode->index_edge = edgeid;
	newnode->next = next;
	return newnode;
}

void freeGraph(graph *G) {

	node* nd, *tmp;
	for (int i = 0; i < G->num_vertices; i++) {
		nd = G->vertices[i].out_edge;
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

void setEdge(graph* G, int edgeid, int vfrom , int vto, int weight) {

	G->edges[edgeid].index_vert_a = vfrom;
	G->edges[edgeid].index_vert_b = vto;
	G->edges[edgeid].weight = weight;
	G->edges[edgeid].id = edgeid;
}

void addOutNode(graph* G, int edgeid, int vfrom, int vto) {
	
	node *nd = G->vertices[vfrom].out_edge;

	// 정점들을 오름차순으로 하려면..?
	node* newnode = getNode(edgeid, nd->next);

	nd->next = newnode;
	newnode->index_edge = edgeid;
}

int origin(graph *G, int edgeid) {

	return G->edges[edgeid].index_vert_a;
}

int opposit(graph* G, int edgeid, int original) {

	return G->edges[edgeid].index_vert_a == original ? 
		G->edges[edgeid].index_vert_b : G->edges[edgeid].index_vert_a;
}

void addNormalEdge(graph* G, int edgeid, int va, int vb, int weight) {

	setEdge(G, edgeid, va, vb, weight);
	addOutNode(G, edgeid, va, vb);
	if (va != vb) {
		addOutNode(G, edgeid, vb, va);
	}
}

void addDirectedEdge(graph* G, int edgeid, int vfrom, int vto, int weight) {

	setEdge(G, edgeid, vfrom, vto, weight);
	addOutNode(G, edgeid, vfrom, vto);
}

graph* getGraph(int num_vertices, int num_edges) {

	graph* newgraph;
	newgraph = (graph*)malloc(sizeof(graph) * 1);
	if (newgraph == NULL) return;

	newgraph->num_edges = num_edges;
	newgraph->num_vertices = num_vertices + 1;
	newgraph->edges = (edge*)malloc(sizeof(edge) * num_edges);
	if (newgraph->edges == NULL) return;
	newgraph->vertices = (vert*)malloc(sizeof(vert) * (num_vertices + 1));
	if (newgraph->vertices == NULL) return;

	for (int i = 0; i < num_vertices + 1; i++) {
		newgraph->vertices[i].id = i;
		newgraph->vertices[i].out_edge = getNode(-1 , NULL);
	}

	return newgraph;
}

void printGraph(graph* G) {

	for (int i = 1; i < G->num_vertices; i++) {
		printf("%d %d\n", G->vertices[i].id, G->vertices[i].d);
	}
}

typedef struct key_val key_val;
struct key_val {
	
	int key;
	int val;
};

typedef struct p_queue p_queue;
struct p_queue {

	int currsize;
	int totalsize;
	key_val* data;
};


void removeQueue(p_queue *Q) {

	free(Q->data);
	free(Q);
}

void enqueue(p_queue *Q, int key, int val) {

	Q->data[Q->currsize].key = key;
	Q->data[Q->currsize].val = val;
	Q->currsize++;
}

int dequeue(p_queue* Q) {

	int minindex;
	key_val mindata;
	for (int i = 0; i < Q->totalsize; i++) {
		if (i == 0) {
			minindex = i;
			mindata = Q->data[i];
		}
		else {
			if (Q->data[i].key < mindata.key) {
				minindex = i;
				mindata = Q->data[i];
			}
		}
	}

	Q->data[minindex].key = 1000000;
	Q->data[minindex].val = -1;
	Q->currsize--;

	return mindata.val;
}

p_queue* getQueue(int size) {

	p_queue* newqueue;
	newqueue = (p_queue*)malloc(sizeof(p_queue) * 1);
	if (newqueue == NULL) return;

	newqueue->currsize = 0;
	newqueue->totalsize = size;
	newqueue->data = (key_val*)malloc(sizeof(key_val) * size);
	if (newqueue->data == NULL) return;


	return newqueue;
}

int isQueueEmpty(p_queue *Q) {

	if (Q->currsize == 0) return 1;
	else return 0;
}

void updateElement(p_queue* Q, int originkey, int originval, int newkey) {

	for (int i = 0; i < Q->totalsize; i++) {
		if (Q->data[i].key == originkey) {
			if (Q->data[i].val == originval) {
				Q->data[i].key = newkey;
				return;
			}
		}
	}
}

int isInQueue(p_queue* Q, int val) {

	for (int i = 0; i < Q->totalsize; i++) {
		if (Q->data[i].val == val) {
			return 1;
		}
	}

	return 0;
}


// algorithms

// dijkstra , bellman-ford , DAG 
// prim-jarnik , kruskal , baruvka
// 

#define FRESH 1
#define VISITED 0
void DijkstraShortestPath(graph *G, int index_start) {

	// init
	for (int i = 0; i < G->num_vertices; i++) {
		G->vertices[i].d = 999999;
		G->vertices->label = FRESH;
	}
	G->vertices[index_start].d = 0;

	// queue
	p_queue* Q;
	Q = getQueue(G->num_vertices);
	for (int i = 0; i < G->num_vertices; i++) {
		enqueue(Q, G->vertices[i].d, i);
	}

	node* nd;
	int index_origin, index_opposit;
	int index_edge;
	while (!isQueueEmpty(Q)) {
		index_origin = dequeue(Q);
		nd = G->vertices[index_origin].out_edge;
		while (nd->next) {
			index_edge = (nd->next)->index_edge;
			index_opposit = opposit(G, index_edge, index_origin);
			G->vertices[index_opposit].label = VISITED;
			if (isInQueue(Q, index_opposit))
				if (G->edges[index_edge].weight + G->vertices[index_origin].d < G->vertices[index_opposit].d) {
					updateElement(Q, G->vertices[index_opposit].d, index_opposit, 
						G->edges[index_edge].weight + G->vertices[index_origin].d);
					G->vertices[index_opposit].d = Q->data[index_opposit].key;
				}
			nd = nd->next;
		}
	}

	for (int i = 1; i < G->num_vertices; i++) {
		if (i != index_start) {
			if (G->vertices[i].label == VISITED) {
				printf("%d %d\n", i, G->vertices[i].d);
			}
		}
	}


	removeQueue(Q);
}

void BellmanFordShortestPath() {

}

void DagShortestPath() {

}

int main() {

	graph* G;

	int num_vertices, num_edges, index_start;
	scanf("%d %d %d", &num_vertices, &num_edges, &index_start);
	G = getGraph(num_vertices, num_edges);

	int v1, v2, w;
	for (int i = 0; i < num_edges; i++) {
		scanf("%d %d %d", &v1, &v2, &w);
		addNormalEdge(G, i, v1, v2, w);
	}

	DijkstraShortestPath(G, index_start);

	freeGraph(G);

	return 0;
}