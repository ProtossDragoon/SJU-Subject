#include<stdio.h>
#include<stdlib.h>

typedef struct incid_edge incid_edge;
struct incid_edge {
	int weight;
	int label;
	int vertexid;
	incid_edge* next;
};
typedef struct node_vertex node_vertex;
struct node_vertex {
	int name;
	int label;
	int order;
//	incid_edge* inedge;
	incid_edge* outedge;
};

#define FRESH 1
#define VISITED 0
#define CYCLE -1

incid_edge* get_incidEdge(int weight, incid_edge *next) {

	incid_edge* newedge = NULL;
	newedge = (incid_edge*)malloc(sizeof(incid_edge) * 1);
	if (newedge == NULL) return;

	newedge->next = next;
	newedge->weight = weight;

	return newedge;
}

// 방향간선 삽입
void add_directedEdge(node_vertex* vertexes, int weight, int from, int to) {

	incid_edge* newInedge;
	incid_edge* newOutedge;

	incid_edge* node = vertexes[from].outedge;
	while (node->next && node->next->vertexid < to) {
		node = node->next;
	}
	// 진출간선
	newOutedge = get_incidEdge(weight, node->next);
	node->next = newOutedge;
	newOutedge->vertexid = to;

/*
 	// 진입간선
	newInedge = get_incidEdge(weight, vertexes[to].inedge->next);
	vertexes[to].inedge->next = newInedge;
	newInedge->vertexid = from;
*/
}
node_vertex* init_vertexes(int size) {

	node_vertex* vertexes;
	vertexes = (node_vertex*)malloc(sizeof(node_vertex) * (size + 1));
	if (vertexes == NULL) return;

	for (int i = 1; i < size + 1; i++) {
		vertexes[i].name = i;
//		vertexes[i].inedge = get_incidEdge(-1, NULL);
		vertexes[i].outedge = get_incidEdge(-1, NULL);
	}

	return vertexes;
}

int topologicalWithRBFS(node_vertex* vertexes, int starting, int *order, int *sum) {

	vertexes[starting].label = VISITED;

	incid_edge* node = vertexes[starting].outedge;
	
	while (node->next) {
		if (vertexes[(node->next)->vertexid].label == FRESH) {
			*sum = *sum + (node->next)->weight;
			topologicalWithRBFS(vertexes, node->next->vertexid, order, sum);
		}
		else {
			// nontree edge
		}
		node = node->next;
	}
//	printf("%d", starting);
	vertexes[starting].order = *order;
	*order = *order - 1;
	return 0;
}

int print_topologicalWithBFS(node_vertex* vertexes, int vertexes_num) {

	// init label
	incid_edge* node;
	for (int i = 1; i < vertexes_num + 1; i++) {
		// init vertex label
		vertexes[i].label = FRESH;
		// init edge label
		node = vertexes[i].outedge;
		while (node->next) {
			node = node->next;
			node->label = FRESH;
		}
	}

	// starting
	int order = vertexes_num;
	int sum = 0;
	for (int i = 1; i < vertexes_num + 1; i++) {
		if (vertexes[i].label == FRESH) {
			topologicalWithRBFS(vertexes, i, &order, &sum);
		}
	}

	for (int i = vertexes_num; i > 0; i--) {
		for (int j = 0; j < vertexes_num + 1; j++) {
			if (vertexes[j].order == i) {
				printf("%d", j);
				if (i != 1) {
					printf(" ");
				}
			}
		}
	}
	printf("\n%d", sum);

	return 0;
}

void free_vertexes(node_vertex* vertexes, int vertexes_num) {

	incid_edge* node, *freenode;
	for (int i = 1; i < vertexes_num + 1; i++) {
		node = vertexes[i].outedge;
		while (node->next) {
			freenode = node;
			node = node->next;
			free(freenode);
		}
		free(node);
	}
//	printf("remove incidedge please!\n");

	free(vertexes);
//	printf("free vertex please!\n");
}

void q13_1() {

	int n, m;
	scanf("%d %d", &n, &m);

	node_vertex* vertexes = NULL;
	vertexes = init_vertexes( n);

	int w, in, out;
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &out, &in, &w);
		add_directedEdge(vertexes, w, out, in);
	}
	print_topologicalWithBFS(vertexes, n);
	free_vertexes(vertexes, n);
}
int main() {

	q13_1();
	return 0;
}