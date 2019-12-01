#include<stdio.h>
#include<stdlib.h>

typedef struct linked_list linked_list;
typedef struct edges edges;
typedef struct node node;
typedef struct vertex vertex;
typedef struct edge edge;
typedef union data data;
typedef union pointers pointers;
typedef struct node_np node_np;


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
union pointers {
	node* npp;
	linked_list* li;
};
struct node {
	node* next;
	node* prev;
	pointers p;
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

static void put_node(node* nd);
static void put_linkedList(linked_list* li);


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
void put_adjmatrix(adjmatrix* matrix) {

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
	newnode->p.li = NULL;
	newnode->p.npp = NULL;

	return newnode;
}
int isEmpty(linked_list* li) {

	if (li->header->next == li->trailer) {
		return 1;
	}
	else return 0;
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
void put_node(node* nd) {
	free(nd);
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

	node* next = nd->next;
	node* prev = nd->prev;

	next->prev = prev;
	prev->next = next;
	put_node(nd);
}
void removeFirst(linked_list* li) {
	
	if (isEmpty(li)) {
		printf("empty list, delete error!!\n");
		return;
	}
	removeElementNode(li, li->header->next);
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
node* findNode(linked_list* li, int vertex_or_edge, int e) {

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
node* findVertexByName(graph* G, int name) {

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

void insertVert(graph* G, node* vertnode) {

	addLast(G->vertics, vertnode);
}
void insertEdge(graph* G, node* edgenode) {

	addLast(G->edges, edgenode);
	node* vert1, * vert2;
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
void adjacent_print(graph* G, int nodenumber) {

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

#define FRESH 0	// label : 방문된적없음!
#define VISIT 1	// label : 방문됨!
#define BACK -1	// label : 후향간선
#define TREE 2	// label : 트리노드
#define CROSS 3 // label : 교차간선

void rDFS(graph *G, node* vertex) {

	vertex->data.data_vertex.label = VISIT;
	node* edgenode, *vertexnode;
	int currentnumber = vertex->data.data_vertex.name;
	printf("%d\n", currentnumber);

	for (int i = 0; i < G->adjmatrix->size; i++) {
		edgenode = (G->adjmatrix->matrix)[currentnumber][i];
		if (edgenode == NULL) {
			continue;
		}
		if (edgenode->data.data_edge.label == FRESH) {
			vertexnode = opposit(vertex, edgenode);
			if (vertexnode->data.data_vertex.label == FRESH) {
				edgenode->data.data_edge.label = TREE;
				rDFS(G, vertexnode);
			}
			else {
				edgenode->data.data_edge.label = BACK;
			}
		}
	}
}
void DFS(graph *G, node* startingvertex) {

	node* np;
	
	np = G->edges->header->next;
	while (np != G->edges->trailer) {
		np->data.data_edge.label = FRESH;
		np = np->next;
	}

	np = G->vertics->header->next;
	while (np != G->vertics->trailer) {
		np->data.data_vertex.label = FRESH;
		np = np->next;
	}

	np = G->vertics->header->next;
	while (np != G->vertics->trailer) {
		if (np->data.data_vertex.label == FRESH) {
			rDFS(G, np);
		}
		np = np->next;
	}
}


node* get_nodepointernode(node* nd) {

	node* newnode;
	newnode = get_node();
	newnode->p.npp = nd;

	return newnode;
}
node* get_linkedlistnode(linked_list* li) {

	node* newnode;
	newnode = get_node();
	newnode->p.li = li;

	return newnode;
}
void BFSP(linked_list* level_i_list) {

	node* np1, *np2;
	np1 = level_i_list->header->next;
	int level = 1;
	while (np1 != level_i_list->trailer) {
		np2 = np1->p.li->header->next;
		while (np2 != np1->p.li->trailer) {
//			printf("level %d : ", level);
			printf("%d\n", np2->p.npp->data.data_vertex.name);
			np2 = np2->next;
		}
		level += 1;
		np1 = np1->next;
	}
}
void BFSL(graph* G, node* vertex) {

	vertex->data.data_vertex.label = VISIT;

	node *edgenode, *vertexnode, *oppositvertexnode;
	node *vertextnodepointer;
	int currentnumber;

	// list's list
	linked_list* level_i_list = NULL;
	level_i_list = get_linkedList();

	// list
	linked_list* level_i_1 = NULL;
	linked_list* level_i_2 = NULL;
	node* nodepointernode, *linkedlistnode;
	
	level_i_1 = get_linkedList();
	nodepointernode = get_nodepointernode(vertex);

	// list add
	addLast(level_i_1, nodepointernode);
	while (!isEmpty(level_i_1)) {
		
		// save  (level i)'s list
		linkedlistnode = get_linkedlistnode(level_i_1);
		addLast(level_i_list, linkedlistnode);

		// new (level i+1)'s list
		level_i_2 = get_linkedList();

		vertextnodepointer = level_i_1->header->next;
		while (vertextnodepointer != level_i_1->trailer) {
			vertexnode = vertextnodepointer->p.npp;
			currentnumber = vertexnode->data.data_vertex.name;
			for (int i = 0; i < G->adjmatrix->size; i++) {
				edgenode =  G->adjmatrix->matrix[currentnumber][i];
				if (edgenode == NULL) {
					continue;
				}
				if (edgenode->data.data_edge.label == FRESH) {
					oppositvertexnode = opposit(vertexnode, edgenode);
					if (oppositvertexnode->data.data_vertex.label == FRESH) {
						edgenode->data.data_edge.label = TREE;
						oppositvertexnode->data.data_vertex.label = VISIT;
						nodepointernode = get_nodepointernode(oppositvertexnode);
						addLast(level_i_2 ,nodepointernode);
					}
					else {
						edgenode->data.data_edge.label = CROSS;
					}
				}
			}
			vertextnodepointer = vertextnodepointer->next;
		}

		level_i_1 = level_i_2;
	}

	BFSP(level_i_list);
	
	node* np = level_i_list->header->next;
	while (np != level_i_list->trailer) {
		np = np->next;
		put_linkedList(np->prev->p.li);
	}
	put_linkedList(level_i_list);
}
void BFS(graph* G, node* startingvertex) {
	
	node* np;

	np = G->edges->header->next;
	while (np != G->edges->trailer) {
		np->data.data_edge.label = FRESH;
		np = np->next;
	}

	np = G->vertics->header->next;
	while (np != G->vertics->trailer) {
		np->data.data_vertex.label = FRESH;
		np = np->next;
	}

	np = G->vertics->header->next;

	BFSL(G, startingvertex);

	/*	
	while (np != G->vertics->trailer) {
		if (np->data.data_vertex.label == FRESH) {
			BFSL(G, np);
		}
		np = np->next;
	}
	*/

}


int main() {


	int n, m, start_vertex;
	graph *G;

	scanf("%d %d %d", &n, &m, &start_vertex);
	G = get_graph(n);

	node* vertexnode;
	for (int i = 0; i < n; i++) {
		vertexnode = aVert(i + 1);
		insertVert(G, vertexnode);
	}

	node* edgenode;
	node* vertex1, * vertex2;
	int vert1, vert2;

	for (int i = 0; i < m; i++) {
		scanf("%d %d", &vert1, &vert2);
		vertex1 = findVertexByName(G, vert1);
		vertex2 = findVertexByName(G, vert2);
		edgenode = aEdge(0, vertex1, vertex2);
		insertEdge(G, edgenode);
	}

	BFS(G, findVertexByName(G, start_vertex));


	return 0;
}