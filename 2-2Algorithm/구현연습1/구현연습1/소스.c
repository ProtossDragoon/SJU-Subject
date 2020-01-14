#include<stdio.h>
#include<stdlib.h>

typedef struct node node;
struct node {

	int index_edge;
	node* next;
};

typedef struct vert vert;
struct vert {

	int id;
	int label;
	int d;
	int p;
	node* incid_list;
};

typedef struct edge edge;
struct edge {

	int index_vert_a;
	int index_vert_b;
	int label;
	int weight;
};

typedef struct graph graph;
struct graph {

	int num_vertices;
	vert* vertices;
	int num_edges;
	edge* edges;
};

node* get_node(int index_edge, node* next) {

	node* newnode = NULL;
	newnode = (node*)malloc(sizeof(node) * 1);
	if (newnode == NULL) return;

	newnode->index_edge = index_edge;
	newnode->next = next;

	return newnode;
}

int opposit(graph *G, node* e, int vs) {

	edge edgedata = G->edges[e->index_edge];
	return edgedata.index_vert_a == vs ? edgedata.index_vert_b : edgedata.index_vert_a;
}

void set_edges_arr(graph* G, int edgeid, int v1, int v2, int weight) {

	G->edges[edgeid].index_vert_a = v1;
	G->edges[edgeid].index_vert_b = v2;
	G->edges[edgeid].weight = weight;
}

// 노드 vs 의 부착리스트에 (vs, vd) 노드 추가.
void add_incid_edge(graph* G, int edgeid, int vs, int vd) {

	node* nd = G->vertices[vs].incid_list;
	node* newnode;
	
	while (nd->next) {
		nd = nd->next;
	}

	newnode = get_node(edgeid, nd->next);
	nd->next = newnode;
}

// 그래프에 간선 (v1, v2) 추가
void add_edge(graph* G, int edgeid, int v1, int v2, int w) {

	set_edges_arr(G, edgeid, v1, v2, w);

	add_incid_edge(G, edgeid, v1, v2);
	if (v1 != v2)
		add_incid_edge(G, edgeid, v2, v1);
}


void free_graph(graph* G) {

	node* nd;
	node* tmp;
	for (int i = 0; i < G->num_vertices; i++) {
		nd = G->vertices[i].incid_list;
		while (nd->next) {
			tmp = nd;
			nd = nd->next;
			free(tmp);
		}
		free(nd);
	}

	free(G->edges);
	free(G->vertices);
	free(G);
}

graph* get_graph(int num_edges, int num_vertices) {

	graph* newgraph = NULL;
	newgraph = (graph*)malloc(sizeof(graph) * 1);
	if (newgraph == NULL) return;

	newgraph->num_edges = num_edges;
	newgraph->num_vertices = num_vertices;
	newgraph->edges = (edge*)malloc(sizeof(edge) * num_edges);
	newgraph->vertices = (vert*)malloc(sizeof(vert) * num_vertices);
	for (int i = 0; i < num_vertices; i++) {
		newgraph->vertices[i].id = i;
		newgraph->vertices[i].incid_list = get_node(-1, NULL);
	}

	return newgraph;
}



/*
typedef struct p_queue p_queue;
struct p_queue {
	int key;
	int value;
	p_queue* next;
};
p_queue* getqueuenode(int key, int value, p_queue* next) {

	p_queue* newnode;
	newnode = (p_queue*)malloc(sizeof(p_queue) * 1);
	newnode->next = next;
	newnode->key = key;
	newnode->value = value;
	return newnode;
}
void enqueue(int key, int value, p_queue* Q) {

	p_queue* nd = Q;
	p_queue* newnode;
	newnode = getqueuenode(key, value, Q->next);
}
int dequeue(p_queue* Q) {


}
*/

typedef struct p_queue p_queue;
typedef struct key_val key_val;
struct p_queue {
	int maxsize;
	int size;
	key_val* data;
};
struct key_val {
	int key;
	int val;
};

int isEmpty(p_queue* Q) {
	if (Q->size == 0) {
		return 1;
	}
	else return 0;
}
void newpqueue(p_queue *Q, int size) {
	Q->maxsize = size;
	Q->size = 0;
	Q->data = (key_val*)malloc(sizeof(key_val) * size);
}
void enqueue(p_queue* Q, int key, int val) {
	Q->data[Q->size].key = key;
	Q->data[Q->size].val = val;
	Q->size++;
}
int dequeue(p_queue* Q) {

	int value;
	key_val mindata;
	int minindex;
	for (int i = 0; i < Q->maxsize; i++) {
		if (i == 0) {
			mindata = Q->data[i];
			minindex = i;
		}
		else {
			if (Q->data[i].key < mindata.key) {
				mindata = Q->data[i];
				minindex = i;
			}
		}
	}

	Q->data[minindex].key = 1000000;
	Q->data[minindex].val = -1;

	Q->size--;
	return mindata.val;
}
void replaceKey(p_queue* Q, int targetVertexIndex, int newkey) {

	for (int i = 0; i < Q->maxsize; i++) {
		if (Q->data[i].val == targetVertexIndex) {
			Q->data[i].key = newkey;
		}
	}
}
int isExist(p_queue* Q, int findVertexIndex) {

	for (int i = 0; i < Q->maxsize; i++) {
		if (Q->data[i].val == findVertexIndex) {
			return 1;
		}
	}
	
	return 0;
}


#define None -1
void PrimJarnikMST(graph* G, int startvertexindex) {

	for (int i = 1; i < G->num_vertices; i++) {
		G->vertices[i].d = 999999;
		G->vertices[i].p = None;
	}
	G->vertices[startvertexindex].d = 0;

	// make priority Queue
	p_queue Q;
	newpqueue(&Q, G->num_vertices - 1);
	for (int i = 1; i < G->num_vertices; i++) {
		enqueue(&Q, G->vertices[i].d, i);
	}

	int vert_index = -1;
	int w;
	int e;
	node* nd;
	int sum = 0;
	while (!isEmpty(&Q)) {
		vert_index = dequeue(&Q);
		printf(" %d", vert_index);
		sum = sum + G->vertices[vert_index].d;
		// while queue is Empty
		nd = G->vertices[vert_index].incid_list;
		while (nd->next) {
			// for each e in incid node
			w = opposit(G, nd->next, vert_index);
			e = (nd->next->index_edge);
			if (isExist(&Q, w) && G->edges[e].weight < G->vertices[w].d) {
				G->vertices[w].p = vert_index;
				G->vertices[w].d = G->edges[e].weight;
				replaceKey(&Q, w, G->vertices[w].d);
			}
			nd = nd->next;
		}
	}
	printf("\n%d", sum);
}


int main() {

	graph* G;


	int n, m;
	scanf("%d %d", &n, &m);

	G = get_graph(m, n+1);

	int v1, v2, w;
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &v1, &v2, &w);
		add_edge(G, i, v1, v2, w);
	}

	PrimJarnikMST(G, 1);
	free_graph(G);

	return 0;
}