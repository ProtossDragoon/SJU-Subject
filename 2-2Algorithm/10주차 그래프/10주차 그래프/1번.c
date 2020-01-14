#include<stdio.h>
#include<stdlib.h>

// graph type
typedef struct adjgraph adjgraph;

// linked list
typedef struct ll_edge ll_edge;
typedef struct ll_vert ll_vert;

// node
typedef struct nd_edge nd_edge;
typedef struct nd_vert nd_vert;

// real data
typedef struct edge edge;
typedef struct vert vert;


struct adjgraph {
	ll_edge* edges;
	ll_vert* vertexes;
	int _counter_edge;
	int _counter_vert;
};
struct ll_edge {
	nd_edge* header;
	nd_edge* trailer;
};
struct ll_vert {
	nd_vert* header;
	nd_vert* trailer;
};
struct nd_edge {
	nd_edge* prev;
	nd_edge* next;
	edge* elem;
};
struct nd_vert {
	nd_vert* prev;
	nd_vert* next;
	vert* elem;
};
struct edge {
	vert* a;
	vert* b;
	int _edge_name;
	int _edge_data;
	int _edge_label;
	int _edge_weight;
};
struct vert {
	ll_edge* incident;
	int _vert_name;
	int _vert_data;
	int _vert_label;
	int _vert_dist;
};

nd_edge* get_ndedge() {
	nd_edge* newnode = NULL;
	newnode = (nd_edge*)malloc(sizeof(nd_edge) * 1);
	if (newnode == NULL)return;

	//init
	newnode->next = NULL;
	newnode->prev = NULL;
	newnode->elem = NULL;

	//return
	return newnode;
}
ll_edge* get_edgelist() {
	ll_edge* newedgelist = NULL;
	newedgelist = (ll_edge*)malloc(sizeof(ll_edge) * 1);
	if (newedgelist == NULL) return;
	newedgelist->header = get_ndedge();
	newedgelist->trailer = get_ndedge();

	//init
	newedgelist->header->next = newedgelist->trailer;
	newedgelist->trailer->prev = newedgelist->header;

	//return
	return newedgelist;
}
nd_vert* get_ndvert() {
	nd_vert* newnode = NULL;
	newnode = (nd_vert*)malloc(sizeof(nd_vert) * 1);
	if (newnode == NULL)return;

	//init
	newnode->next = NULL;
	newnode->prev = NULL;
	newnode->elem = NULL;

	//return
	return newnode;
}
ll_vert* get_vertexlist() {
	ll_vert* newvertexlist = NULL;
	newvertexlist = (ll_vert*)malloc(sizeof(ll_vert) * 1);
	if (newvertexlist == NULL) return;
	newvertexlist->header = get_ndvert();
	newvertexlist->trailer = get_ndvert();

	//init
	newvertexlist->header->next = newvertexlist->trailer;
	newvertexlist->trailer->prev = newvertexlist->header;

	//return
	return newvertexlist;
}
adjgraph* get_adjgraph() {
	adjgraph* newadjgraph = NULL;
	newadjgraph = (adjgraph*)malloc(sizeof(adjgraph) * 1);
	if (newadjgraph == NULL) return;
	newadjgraph->edges = get_edgelist();
	newadjgraph->vertexes = get_vertexlist();

	//init
	newadjgraph->_counter_edge = 0;
	newadjgraph->_counter_vert = 0;

	//return
	return newadjgraph;
}

int numVertices(adjgraph* graph) {
	return graph->_counter_vert;
}
int numEdges(adjgraph* graph) {
	return graph->_counter_edge;
}
vert* opposit(edge* edge, vert* vertex) {

	vert* oppositvertex;
	oppositvertex = edge->a;
	if (oppositvertex == vertex) {
		oppositvertex = edge->b;
	}
	return oppositvertex;
}

#define OPPOSIT_NODE_NUMBER 0
#define CURRENT_EDGE_WEIGHT 1
// error
void priorityQueue_insertionSort_lledge(vert* node, int sortingrule) {

	ll_edge* list;
	nd_edge* np1, *np2, * save;
	list = node->incident;

	// this function's list parameter needs itself that has more than one elements
	if (list->trailer->prev == list->header) return;

	save = list->trailer->prev;
	np1 = save->prev;
	while (np1 != list->header && opposit(np1->elem, node)->_vert_data > node->_vert_data) {
		np1 = np1->prev;
	}

	// insert final node (save) after np node
	if (np1->next == save) {
		return;
	}
	else {
		np2 = np1->next;
		save->prev->next = list->trailer;
		
		save->prev = np1;
		save->next = np2;
		np1->next = save;
		np2->prev = save;
	}
}
void priorityQueue_insertionSort_llvert(ll_vert* list, int sortingrule) {

}

void addVertLast(ll_vert* list, vert* v) {
	nd_vert* np1, * np2;
	nd_vert* newnode;
	newnode = get_ndvert();

	np1 = list->trailer;
	np2 = list->trailer->prev;

	// set
	np1->prev = newnode;
	np2->next = newnode;
	newnode->next = np1;
	newnode->prev = np2;
	newnode->elem = v;
}
void insertVertex(adjgraph* graph, vert* v) {
	addVertLast(graph->vertexes, v);
	
	// set graph data
	graph->_counter_vert++;
}
void addEdgeLast(ll_edge* list, edge* e) {
	nd_edge* np1, * np2;
	nd_edge* newnode;
	newnode = get_ndedge();

	np1 = list->trailer;
	np2 = list->trailer->prev;

	// set
	np1->prev = newnode;
	np2->next = newnode;
	newnode->next = np1;
	newnode->prev = np2;
	newnode->elem = e;
}
void insertEdge(adjgraph* graph, edge* e, vert* a, vert* b) {
	addEdgeLast(graph->edges, e);
	// set edge data
	e->a = a;
	e->b = b;

	// set vertex data
	addEdgeLast(a->incident, e);
	if (a != b) {
		addEdgeLast(b->incident, e);
	}

	// set graph data
	graph->_counter_edge++;
}

edge* aEdge(int data, int name, int weight) {
	edge* newedge = NULL;
	newedge = (edge*)malloc(sizeof(edge) * 1);
	if (newedge == NULL) return;

	// init
	newedge->_edge_data = data;
	newedge->_edge_label = 0;
	newedge->_edge_name = name;
	newedge->_edge_weight = weight;

	// return
	return newedge;
}
vert* aVertex(int data, int name) {
	vert* newvertex = NULL;
	newvertex = (vert*)malloc(sizeof(vert) * 1);
	if (newvertex == NULL) return;

	// init
	newvertex->incident = get_edgelist();
	newvertex->_vert_data = data;
	newvertex->_vert_name = name;
	newvertex->_vert_dist = 0;
	newvertex->_vert_label = 0;

	// return
	return newvertex;
}

nd_vert* find_vertex(adjgraph* graph, int nodenumber) {

	// find a vertex with number
	nd_vert* vert_np = NULL;
	vert_np = graph->vertexes->header->next;
	while (vert_np != graph->vertexes->trailer) {
		if (vert_np->elem->_vert_data == nodenumber) {
			break;
		}
		vert_np = vert_np->next;
	}
	if (vert_np == graph->vertexes->trailer) {
	//	printf("-1\n");
		return NULL;
	}

	// return
	return vert_np;
}

void removeEdgeFromList(ll_edge* list, nd_edge* node) {

	// list setting and remove
	nd_edge* prev, * next;
	prev = node->prev;
	next = node->next;
	prev->next = next;
	next->prev = prev;
	free(node);
}
void removeEdge_type1(adjgraph* graph, vert* a, nd_edge* edges_node) {

	// find a edge with incident list's node
	nd_edge* edge_np_a = NULL;
	edge_np_a = a->incident->header->next;
	while (edge_np_a != a->incident->trailer) {
		if (opposit(edge_np_a->elem, a) == a) {
			break;
		}
		edge_np_a = edge_np_a->next;
	}

	removeEdgeFromList(a->incident, edge_np_a);
	free(edges_node->elem);
	removeEdgeFromList(graph->edges, edges_node);
	graph->_counter_edge--;
}
void removeEdge_type2(adjgraph* graph, vert* a, vert* b, nd_edge* edges_node) {

	// find a edge with incident list's node
	nd_edge* edge_np_a = NULL, *edge_np_b = NULL;
	edge_np_a = a->incident->header->next;
	edge_np_b = b->incident->header->next;

	// edge_np_a : Vertex A 의 edges 리스트를 담은곳으로 접근
	while (edge_np_a != a->incident->trailer) {
		if (opposit(edge_np_a->elem, a) == b) {
			break;
		}
		edge_np_a = edge_np_a->next;
	}

	while (edge_np_b != b->incident->trailer) {
		if (opposit(edge_np_b->elem, b) == a) {
			break;
		}
		edge_np_b = edge_np_b->next;
	}
	
	removeEdgeFromList(a->incident, edge_np_a);
	removeEdgeFromList(b->incident, edge_np_b);
	free(edges_node->elem);
	removeEdgeFromList(graph->edges, edges_node);
	graph->_counter_edge--;
}

void adjacent_print(adjgraph *graph, int nodenumber) {
	
	// find a vertex with number
	nd_vert* vertex;
	vertex = find_vertex(graph, nodenumber);
	if (vertex == NULL) {
		printf("-1\n");
		return;
	}
	// get vertex's edge list and search opposit
	nd_edge* edge_np;
	ll_edge* list = vertex->elem->incident;
	edge_np = list->header->next;
	while (edge_np != list->trailer) {
		printf(" %d %d", opposit(edge_np->elem, vertex->elem)->_vert_data, edge_np->elem->_edge_weight);
		edge_np = edge_np->next;
	}
	printf("\n");
}
void modify_edge(adjgraph* graph, vert* a, vert* b, int modifyweight) {

	if (a == NULL || b == NULL) {
		printf("-1\n");
		return;
	}

	// get edge list
	ll_edge* list;
	nd_edge* edge_np;
	vert* find_a, *find_b;
	list = graph->edges;
	edge_np = list->header->next;
	while (edge_np != list->trailer) {
		find_a = edge_np->elem->a;
		find_b = edge_np->elem->b;
		if (find_a != a) {
			find_a = edge_np->elem->b;
			find_b = edge_np->elem->a;
		}
		if (find_a == a && find_b == b) {
			// remove
			if (modifyweight == 0) {
				if (a != b) {
					removeEdge_type2(graph, a, b, edge_np);
				}
				else {
					removeEdge_type1(graph, a, edge_np);
				}
				break;
			}
			// revise
			else {
				edge_np->elem->_edge_weight = modifyweight;
				break;
			}

		}
		edge_np = edge_np->next;
	}
	if (edge_np == list->trailer && modifyweight == 0) {
		// there is no removable edge.
		printf("-1\n");
		return;
	}
	else if (edge_np == list->trailer && modifyweight != 0){
		// there is no edge, make new edge
		edge* newedge;
		newedge = aEdge(modifyweight, modifyweight, modifyweight);
		insertEdge(graph, newedge, a, b);
		printf("");
		return;
	}
	else {
		// modifiy (remove or revise) successfully.
		printf("");
		return;
	}
}


int main() {

	// make a graph
	adjgraph* graph = NULL;
	graph = get_adjgraph();

	vert* vertex1 = NULL;
	vert* vertex2 = NULL;
	vert* vertex3 = NULL;
	vert* vertex4 = NULL;
	vert* vertex5 = NULL;
	vert* vertex6 = NULL;
	vertex1 = aVertex(1, 1);
	vertex2 = aVertex(2, 2);
	vertex3 = aVertex(3, 3);
	vertex4 = aVertex(4, 4);
	vertex5 = aVertex(5, 5);
	vertex6 = aVertex(6, 6);

	edge* edge12 = NULL;
	edge* edge13 = NULL;
	edge* edge14 = NULL;
	edge* edge16 = NULL;
	edge* edge23 = NULL;
	edge* edge35 = NULL;
	edge* edge55 = NULL;
	edge* edge56 = NULL;
	edge12 = aEdge(1, 1, 1);
	edge13 = aEdge(1, 1, 1);
	edge14 = aEdge(1, 1, 1);
	edge16 = aEdge(2, 2, 2);
	edge23 = aEdge(1, 1, 1);
	edge35 = aEdge(4, 4, 4);
	edge55 = aEdge(4, 4, 4);
	edge56 = aEdge(3, 3, 3);

	insertVertex(graph, vertex1);
	insertVertex(graph, vertex2);
	insertVertex(graph, vertex3);
	insertVertex(graph, vertex4);
	insertVertex(graph, vertex5);
	insertVertex(graph, vertex6);

	insertEdge(graph, edge12, vertex1, vertex2);
	insertEdge(graph, edge13, vertex1, vertex3);
	insertEdge(graph, edge14, vertex1, vertex4);
	insertEdge(graph, edge16, vertex1, vertex6);
	insertEdge(graph, edge23, vertex2, vertex3);
	insertEdge(graph, edge35, vertex3, vertex5);
	insertEdge(graph, edge55, vertex5, vertex5);
	insertEdge(graph, edge56, vertex5, vertex6);


	// requests
	char inputch;
	int inputint;
	int a, b;
	nd_vert* tmp = NULL;
	vert* vert_a = NULL, *vert_b = NULL;
	while (1) {
		scanf("%c", &inputch);
		if (inputch == 'a') {
			scanf("%d", &inputint);
			adjacent_print(graph,inputint);
		}
		else if (inputch == 'm') {
			scanf("%d %d %d", &a, &b, &inputint);
			tmp = find_vertex(graph, a);
			if (tmp != NULL) vert_a = tmp->elem;
			else vert_a = NULL;
			tmp = find_vertex(graph, b);
			if (tmp != NULL) vert_b = tmp->elem;
			else vert_b = NULL;
			modify_edge(graph, vert_a, vert_b, inputint);
		}
		else { // input == 'q'
			break;
		}
		getchar();
	}

	// free graph

	return 0;
}