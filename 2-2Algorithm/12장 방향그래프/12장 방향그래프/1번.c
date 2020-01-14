#include<stdio.h>
#include<stdlib.h>

typedef struct node node; // 부착 리스트의 노드
typedef struct vert vert;
typedef struct edge edge;
typedef struct graph graph;


struct node {
	int edgeIndex;
	node* next;
};
struct vert { //정점배열 리스트 원소
	int label;
	int vertname;
	int topological;
	node* incid_list;
	node* incid_list_in;
	int indegree;
	node* incid_list_out;
};
struct edge { //간선배열 리스트 원소
	int label;	  // visited , fresh 등..
	int edgename; // 그냥 이름
	int weight;	  // 간선 가중치
	int vertex1index, vertex2index;
};
struct graph {
	vert* vertex_list;
	int vsize;
	edge* edge_list;
	int esize;
};	


node* get_incidnode(int edgeIndex, node* next) {
	
	node* newnode = NULL;
	newnode = (node*)malloc(sizeof(node) * 1);
	if (newnode == NULL) return NULL;

	newnode->edgeIndex = edgeIndex;
	newnode->next = next;

	return newnode;
}

// interface
// int opposit_vertex_index
//	내가 겨냥하는 vertex 의 반대편 vertex - array 에서의 index 찾기
int opposit_vertex_index(graph *G, node *nd, int currentvertexindex) {

	edge edgedata = G->edge_list[nd->edgeIndex];
	return currentvertexindex == edgedata.vertex1index ? edgedata.vertex2index : edgedata.vertex1index;
}


void set_edges_arr(graph* G, int edgeId, int vertex1index, int vertex2index, int weight) {

	G->edge_list[edgeId].edgename = edgeId;
	G->edge_list[edgeId].vertex1index = vertex1index;
	G->edge_list[edgeId].vertex2index = vertex2index;
	G->edge_list[edgeId].weight = weight;
}
void insert_incid_node(graph* G, int edgeId, int vertexFromindex, int vertexToindex) { // node 의 부착리스트에 간선 추가
	
	node* newnode = NULL;
	node* nd = G->vertex_list[vertexFromindex].incid_list;

	while (nd->next && opposit_vertex_index(G, nd->next, vertexFromindex) < vertexToindex) {
		// 다른 애들의 opposit 의 index number 보다 항상 큰 상태로 유지하기 위해.
		// 즉, opposit 이 오름차순으로 정렬되어 있다.
		nd = nd->next;
	}

	newnode = get_incidnode(edgeId, nd->next);
	nd->next = newnode;
}
void insert_directed_node(graph* G, int edgeId, int vertexFromindex, int vertexToindex) { // node 의 부착리스트에 간선 추가

	node* newnode = NULL;
	node* nd = G->vertex_list[vertexFromindex].incid_list_out;

	/*
	while (nd->next && opposit_vertex_index(G, nd->next, vertexFromindex) < vertexToindex) {
		nd = nd->next;
	}
	*/
	newnode = get_incidnode(edgeId, nd->next);
	nd->next = newnode;


	node* newnode2 = NULL;
	node* nd2 = G->vertex_list[vertexToindex].incid_list_in;

	/*
	while (nd2->next && opposit_vertex_index(G, nd2->next, vertexToindex) < vertexFromindex) {
		nd2 = nd2->next;
	}
	*/

	newnode2 = get_incidnode(edgeId, nd2->next);
	nd2->next = newnode2;
}


// interface
// void add_edge
//	새로운 edge 삽입하기 - 파라미터의 정보에 해당하는 정보의 
void add_edge(graph *G, int edgeid, int vertex1index, int vertex2index, int weight) {

	set_edges_arr(G, edgeid, vertex1index, vertex2index, weight);
	insert_incid_node(G, edgeid, vertex1index, vertex2index);
	if (vertex1index != vertex2index) {
		insert_incid_node(G, edgeid, vertex2index, vertex1index);
	}
}
// void add_directed_edge
//	새로운 directed edge 삽입하기 - 파라미터의 정보에 해당하는
void add_directed_edge(graph* G, int edgeid, int vertexFromindex, int vertexToindex, int weight) {

	set_edges_arr(G, edgeid, vertexFromindex, vertexToindex, weight);
	insert_directed_node(G, edgeid, vertexFromindex, vertexToindex);
}
int find_with_vertexname(graph *G, int vertexname) {

	int vertexindex = 0;
	for (int i = 0; i < G->vsize; i++) {
		if (G->vertex_list[i].vertname == vertexname) {
			vertexindex = i;
			break;
		}
	}

	return vertexindex;
}


#define DEFAULTLABEL -1
void free_incid_list(node* header) {

	node* np = header;
	node* tmp;

	while (np) {
		tmp = np->next;
		free(np);
		np = tmp;
	}
}



// interface
void build_vlist(graph* G, int vsize) {

	G->vsize = vsize;
	G->vertex_list = (vert*)malloc(sizeof(vert) * vsize);
	if (G->vertex_list == NULL) return;

	for (int i = 0; i < vsize; i++) {
		G->vertex_list[i].incid_list = get_incidnode(-1, NULL);
		G->vertex_list[i].incid_list_in = get_incidnode(-1, NULL);
		G->vertex_list[i].incid_list_out = get_incidnode(-1, NULL);
		G->vertex_list[i].label = DEFAULTLABEL;
		G->vertex_list[i].vertname = i;
	}
}
void build_elist(graph* G, int esize) {

	G->esize = esize;
	G->edge_list = (edge*)malloc(sizeof(edge) * esize);
	if (G->edge_list == NULL) return;

	for (int i = 0; i < esize; i++) {
		G->edge_list[i].vertex1index = -1;
		G->edge_list[i].vertex2index = -1;
		G->edge_list[i].edgename = i;
		G->edge_list[i].weight = 0;
		G->edge_list[i].label = DEFAULTLABEL;
	}
}
// void build_graph
//	graph 에 list 들을 할당함
void build_graph(graph* G, int vsize, int esize) {

	build_vlist(G, vsize);
	build_elist(G, esize);
}

// void free_graph
//	graph 제거
void free_graph(graph* G) {

	for (int i = 0; i < G->vsize; i++) {
		free_incid_list(G->vertex_list[i].incid_list);
	}
	for (int i = 0; i < G->vsize; i++) {
		free_incid_list(G->vertex_list[i].incid_list_in);
	}
	for (int i = 0; i < G->vsize; i++) {
		free_incid_list(G->vertex_list[i].incid_list_out);
	}

	free(G->vertex_list);
	free(G->edge_list);
}



#define FRESH 0
#define VISITED -1
#define BACK -2
#define CYCLE 8
#define DAG 1 //directed acyclic graph

// 진입간선 차수 구하기
int init_inDegree(graph* G, int vertid) {

	node* np;
	np = G->vertex_list[vertid].incid_list_in;
	int cnt = 0;
	while (np->next) {
		cnt++;
		np = np->next;
	}

	G->vertex_list[vertid].indegree = cnt;
	return cnt;
}
int inDegree(graph* G, int vertid){

	return G->vertex_list[vertid].indegree;
}
// 위상순서 구하고 출력하기
// interface
typedef struct queue queue;
struct queue {
	int front;
	int rear;
	int size;
	int* elements;
};
int isEmpty(queue *Q){

	if ((Q->rear + 1) % Q->size == Q->front) {
		return 1;
	}
	else return 0;
}
int isFull(queue* Q) {

	if ((Q->rear + 2) % Q->size == Q->front) {
		return 1;
	}
	else return 0;
}
void enqueue(queue *Q,int element) {

	Q->rear = (Q->rear + 1) % Q->size;
	Q->elements[Q->rear] = element;
}
int dequeue(queue *Q) {

	if (isEmpty(Q)) {
		printf("empty queue exception !");
		return -1;
	}
	int e = Q->elements[Q->front];
	Q->front = (Q->front + 1) % Q->size;
	return e;
}
void initQueue(queue* newqueue, int max_size) {

	newqueue->front = 0;
	newqueue->rear = max_size - 1;
	newqueue->size = max_size;
	newqueue->elements = (int*)malloc(sizeof(int) * max_size);
	if (newqueue->elements == NULL) return;
	return newqueue;
}


void topological_order_print(graph* G) {

	int TF = topological_order(G);
	if (TF == DAG) {

		for (int j = 0; j < G->vsize; j++) {
			for (int i = 0; i < G->vsize; i++) {
				if (G->vertex_list[i].topological == j+1) {
					printf("%c", G->vertex_list[i].vertname);
					break;
				}
			}
			if(j+1 < G->vsize) printf(" ");
		}

	}
	else {
		printf("0");
		return;
	}
}
int topological_order(graph *G) {


	// init_indegree
	queue Q;
	initQueue(&Q, G->vsize);
	int inI;
	for (int i = 0; i < G->vsize; i++) {
		inI = init_inDegree(G, i);
		if (inI == 0) {
			enqueue(&Q, i);
		}
	}

	int topo = 1;
	int vertid;
	int oppovertindex;
	node* np;
	while (!isEmpty(&Q)) {
		vertid = dequeue(&Q);
		G->vertex_list[vertid].topological = topo;
		topo++;

		np = G->vertex_list[vertid].incid_list_out;
		while (np->next) {
			oppovertindex = opposit_vertex_index(G, np->next, vertid);
			G->vertex_list[oppovertindex].indegree--;
			inI = inDegree(G, oppovertindex);
			if (inI == 0) {
				enqueue(&Q, oppovertindex);
			}
			np = np->next;
		}
	}
	
	if (G->vsize > topo) {
		return CYCLE;
	}
	else return DAG;
}



void test() {

	graph G;
	int vsize = 5;
	int esize = 4;
	build_graph(&G, vsize, esize);

	add_edge(&G, 0, 1, 2, 1);
	add_edge(&G, 0, 1, 2, 1);
	add_edge(&G, 0, 1, 2, 1);
	add_edge(&G, 0, 1, 2, 1);
	add_edge(&G, 0, 1, 2, 1);
	add_edge(&G, 0, 1, 2, 1);

	free_graph(&G);
}

void q12_1() {

	graph G;
	int vsize;
	int esize;

	scanf("%d", &vsize);
	getchar();
	build_vlist(&G, vsize);
	char input;
	for (int i = 0; i < vsize; i++) {
		scanf("%c", &input);
		getchar();
		G.vertex_list[i].vertname = input;
	}

	scanf("%d", &esize);
	getchar();
	build_elist(&G, esize);
	char from, to;
	for (int i = 0; i < esize; i++) {
		scanf("%c %c", &from , &to);
		getchar();
		int a = find_with_vertexname(&G, from);
		int b = find_with_vertexname(&G, to);
		add_directed_edge(&G, i, a, b, 0);
	}


	topological_order_print(&G);

	free_graph(&G);
}

int main() {


	q12_1();
	

	return 0;
}