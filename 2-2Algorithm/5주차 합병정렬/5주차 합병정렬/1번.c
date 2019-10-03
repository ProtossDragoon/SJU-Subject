
#include<stdio.h>
#include<stdlib.h>



typedef struct element element;
typedef struct node node;
typedef struct doublelinkedlist doublelinkedlist;
typedef struct doublelinkedlist_queue doublelinkedlist_queue;
typedef struct doublelinkedlist_priorityqueue doublelinkedlist_priorityqueue;

typedef struct treenode treenode;
typedef struct doublelinkedlist_tree dublelinkedlist_tree;
typedef struct tree_array tree_array;



struct element {
	int intelement;
	char charelement;
	char* stringelement;
};
struct node {
	node* prevnode;
	node* nextnode;
	element e;
};
struct doublelinkedlist {
	node* header;
	node* trailer;
	node* firstnode;
	int size;
	int single;
};
struct doublelinkedlist_priorityqueue {
	node* front;
	doublelinkedlist* doublelinkedlist;
	node* rear;
	int selection_or_insertion;
};
struct tree_array {
	int maxsize;
	int currentsize;
	element* elementarray;
};


#define SELECTION 0
#define INSERTION 1

#define MIN 2
#define MAX 3

#define SORT_AND_DEQUEUE 0
#define JUST_SORT 1
#define JUST_DEQUEUE 2

void invalidRankException() {
	printf("invalidRankExcpeion\n");
}

void init_element(element* e) {
	e->charelement = '0';
	e->intelement = 0;
	e->stringelement = NULL;
}
node* get_node() {
	node* newnode = NULL;
	newnode = (node*)malloc(sizeof(node) * 1);
	if (newnode == NULL) return;

	init_element(&(newnode->e));
	newnode->nextnode = NULL;
	newnode->prevnode = NULL;

	return newnode;
}
doublelinkedlist* get_doubleLinkedList() {

	doublelinkedlist* newlist = NULL;
	newlist = (doublelinkedlist*)malloc(sizeof(doublelinkedlist) * 1);
	if (newlist == NULL) return;


	//double linked list
	newlist->single = 2;

	//with header and trailer
	newlist->header = get_node();
	newlist->trailer = get_node();

	//init
	newlist->size = 0;
	newlist->header->nextnode = newlist->trailer;
	newlist->trailer->prevnode = newlist->header;
	newlist->header->prevnode = NULL;
	newlist->trailer->nextnode = NULL;
	newlist->firstnode = NULL;

	return newlist;
}
doublelinkedlist* get_singleLinkedList() {

	doublelinkedlist* newlist = NULL;
	newlist = (doublelinkedlist*)malloc(sizeof(doublelinkedlist) * 1);
	if (newlist == NULL) return;


	//single linked list
	newlist->single = 1;

	//with header and trailer
	newlist->header = get_node();
	newlist->trailer = get_node();

	//init
	newlist->size = 0;
	newlist->header->nextnode = newlist->trailer;
	newlist->trailer->nextnode = NULL;
	newlist->trailer->prevnode = NULL;
	newlist->firstnode = NULL;

	return newlist;

}

node* set_node(node* node, element e) {
	node->e = e;
	return node;
}
element remove_node(node* currentnode) {

	element e;
	e = currentnode->e;
	free(currentnode);
	return e;

}
int isEmpty_doubleLinkedList(doublelinkedlist* list) {

	if (list->header != NULL) {
		if (list->trailer != NULL) { // header, trailer exist
			if (list->header->nextnode == list->trailer) {
				return 1;
			}
			else {
				return 0;
			}
		}
		else { // header exist, trailer does not exist
			if (list->header->nextnode == NULL) {
				return 1;
			}
			else {
				return 0;
			}
		}
	}
	else { // header does not exist
		if (list->firstnode == NULL) {
			return 1;
		}
		else {
			return 0;
		}
	}

}
node* findNodeByRank_doubleLinkedList(doublelinkedlist* list, int rank) {
	
	if (rank == 0) {
		return list->header;
	}
	else if (list->size < rank || rank < 1) {
		invalidRankException();
		return;
	}

	node* np;
	np = list->header;

	int  i = 0;
	while(i < rank) {
		np = np->nextnode;
		i++;
	}

	return np;

}
void addNodeByRank_doubleLinkedList(doublelinkedlist* list, int rank, element e) {

	if ( list->size + 1 < rank || rank < 1 ) {
		invalidRankException();
		return;
	}

	node* np;
	node* newnode;

	newnode = get_node();
	set_node(newnode, e);
	
	np = findNodeByRank_doubleLinkedList(list, rank - 1);

	//single linked list
	if (list->single == 1) {

		node* tmpnode = NULL;
		tmpnode = np->nextnode;
		np->nextnode = newnode;
		newnode->nextnode = tmpnode;

	}

	//double linked list
	if (list->single == 2) {

		node* tmpnode = NULL;
		tmpnode = np->nextnode;

		np->nextnode = newnode;
		newnode->prevnode = np;
		
		newnode->nextnode = tmpnode;
		tmpnode->prevnode = newnode;

	}

	list->size++;
}
void addLastNode_doubleLinkedList(doublelinkedlist* list, element e) {
	addNodeByRank_doubleLinkedList(list, list->size + 1, e);
}
void addFirstNode_doubleLinkedList(doublelinkedlist* list, element e) {
	addNodeByRank_doubleLinkedList(list, 1, e);
}

element removeNodeByRank_doubleLinkedList(doublelinkedlist* list, int rank) {

	if (list->size < rank || rank < 1) {
		invalidRankException();
		return;
	}

	node* np = NULL;
	node* np2 = NULL;
	np2 = findNodeByRank_doubleLinkedList(list, rank - 1);
	np = np2->nextnode;

	//single linked list
	if (list->single == 1) {
		np2->nextnode = np->nextnode;
	}

	//double linked list
	else {
		node* tmpnode = NULL;
		tmpnode = np->prevnode;

		np->prevnode->nextnode = np->nextnode;
		np->nextnode->prevnode = tmpnode;
	}

	list->size--;

	return remove_node(np);
}
void printElements_doubleLinkedList(doublelinkedlist* list) {

	node* np = NULL;
	np = list->header->nextnode;

	while (np != list->trailer) {
		printf(" %d", np->e.intelement);
		np = np->nextnode;
	}
}
void removeList_doubleLinkedList(doublelinkedlist* list) {

	while (!isEmpty_doubleLinkedList(list)) {
		removeNodeByRank_doubleLinkedList(list, 1);
	}
	free(list);
}


// merge sort funciton (합병 정렬 관련 메소드)

#define MINFIRST 0
#define MAXFIRST 1

doublelinkedlist* merge_doubleLinkedList(doublelinkedlist* list1, doublelinkedlist* list2, int minfirst_or_maxfirst) {

	doublelinkedlist* merged_list = NULL;
	merged_list = get_singleLinkedList();

	node* node1 = NULL;
	node* node2 = NULL;

	element tmpelement;
	init_element(&tmpelement);

	while (!isEmpty_doubleLinkedList(list1) && !isEmpty_doubleLinkedList(list2)) {

		node1 = findNodeByRank_doubleLinkedList(list1, 1);
		node2 = findNodeByRank_doubleLinkedList(list2, 1);

		if (minfirst_or_maxfirst == MINFIRST) {

			if (node1->e.intelement < node2->e.intelement)
				tmpelement = removeNodeByRank_doubleLinkedList(list1, 1);
			else
				tmpelement = removeNodeByRank_doubleLinkedList(list2, 1);

		}
		if (minfirst_or_maxfirst == MAXFIRST) {

			if (node1->e.intelement > node2->e.intelement)
				tmpelement = removeNodeByRank_doubleLinkedList(list1, 1);
			else
				tmpelement = removeNodeByRank_doubleLinkedList(list2, 1);

		}

		addLastNode_doubleLinkedList(merged_list, tmpelement);
	}

	while (!isEmpty_doubleLinkedList(list1)) {

		node1 = findNodeByRank_doubleLinkedList(list1, 1);
		tmpelement = removeNodeByRank_doubleLinkedList(list1, 1);

		addLastNode_doubleLinkedList(merged_list, tmpelement);
	}
	while (!isEmpty_doubleLinkedList(list2)) {

		node2 = findNodeByRank_doubleLinkedList(list2, 1);
		tmpelement = removeNodeByRank_doubleLinkedList(list2, 1);

		addLastNode_doubleLinkedList(merged_list, tmpelement);
	}

	return merged_list;
}
doublelinkedlist** partition_doubleLinkedList(doublelinkedlist* list, int k) {

	//partition size1 : k
	//partition size2 : original list size - k

	if (list->size < 1) {
		invalidRankException();
		return;
	}

	doublelinkedlist** list_array = NULL;
	list_array = (doublelinkedlist**)malloc(sizeof(doublelinkedlist*) * 2);
	if (list_array == NULL)return;
	list_array[0] = get_singleLinkedList();
	list_array[1] = get_singleLinkedList();


	node* list_1_endpoint = NULL;
	node* list_2_startpoint = NULL;
	node* list_2_endpoint = NULL;
	int list_1_count, list_2_count;

	list_1_endpoint = findNodeByRank_doubleLinkedList(list, k);
	list_1_count = k;

	list_2_startpoint = list_1_endpoint->nextnode;
	list_2_count = list->size - k;
	list_2_endpoint = findNodeByRank_doubleLinkedList(list, list->size);


	//list 1
	list_array[0]->header->nextnode = findNodeByRank_doubleLinkedList(list, 1);
	list_1_endpoint->nextnode = list_array[0]->trailer;
	list_array[0]->size = list_1_count;

	//list 2
	list_array[1]->header->nextnode = list_2_startpoint;
	list_2_endpoint->nextnode = list_array[1]->trailer;
	list_array[1]->size = list_2_count;


	//free empty list
	free(list);

	return list_array;
}

doublelinkedlist* mergeSort_doubleLinkedList(doublelinkedlist *list, int minfirst_or_maxfirst) {

	doublelinkedlist** partition = NULL;
	
	if (list->size > 1) {
		//step1
		partition = partition_doubleLinkedList(list, list->size / 2);

		//step2
		partition[0] = mergeSort_doubleLinkedList(partition[0], minfirst_or_maxfirst);
		partition[1] = mergeSort_doubleLinkedList(partition[1], minfirst_or_maxfirst);

		//step3
		list = merge_doubleLinkedList(partition[0], partition[1], minfirst_or_maxfirst);

	}

	return list;

}



int main() {


	int n;

	scanf("%d", &n);
	
	element e;
	doublelinkedlist* list = NULL;
	list = get_singleLinkedList();


	int i;
	for (i = 0; i < n; i++) {
		init_element(&e);
		scanf("%d", &(e.intelement));
	
		addLastNode_doubleLinkedList(list, e);
	}


	list = mergeSort_doubleLinkedList(list, MINFIRST);

	printElements_doubleLinkedList(list);
	
	
	return 0;
}