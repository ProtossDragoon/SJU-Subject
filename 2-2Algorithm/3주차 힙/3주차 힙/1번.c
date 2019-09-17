#include<stdio.h>
#include<stdlib.h>
// #include<Windows.h>
#include<time.h>


//코드 재사용부

/*

<!> typedef 는 "struct" 를 작성하지 않기 위해 사용합니다.

<!> ADT(추상자료구조) 는 A_B_C... 와 같은 형태로 이루어집니다.
	- 만약 이름이 A_B_C 라면 최종 구현된 ADT는 C이고, A와 B를 이용해 구현되었을 것입니다.

<!> ADT Function (추상자료구조 함수) 는 A_B_C... 와 같은 형태로 이루어집니다.
	- 만약 이름이 A_B_C 라면, 기능은 A 이고, B와 C를 이용해 구현되었을 것입니다.

<!> element 구조체에 대하여
	- 취지 : element 구조체는 (강의교안에 있는 의사코드를 본따) 유연한 코드 재사용을 위해 도입했습니다.
	- 구조 : int 형, char 형, string 형을 모두 담고 있습니다. float 형, custom 구조체가 필요하면 함수만 추가해서 사용하면 됩니다.
	- 사용 : 저장할 때 자료형을 함수 인자로 넘겨주면 코드 전체가 그에 맞게 돌아갑니다.

	- intelement : 1개의 정수
	- charelement : 1개의 문자. 
	** element 자료형을 이용하여 만들어지는 배열, 그리고 그로 구현한 이진트리에서는
	** charelement 에 '#' 를 넣어서 NULL 마커를 지정합니다.

	- stringelement* : 동적 할당을 해서 사용하는 형태입니다.

	- 자료형 함수 작성법 :

<!> doublelinkedlist 구조체에 관하여
	- header을 사용하지 않는 자료형에서는 firstnode 를 이용하여 리스트에 접근합니다.

<!> swapElements_doubleLinkedList_priorityQueue 함수에 관하여
	<-------중요 개정------>
	- element 의 포인터만 교체하는 식이 나을것 같다는 생각이 들었습니다.
	- 하지만, element 자체를 포인터(element *e) 로 구현하지 않고, 그냥 value (element e) 로 구현했기에, 값을 바꾸는 것으로 수정합니다.
	- 이전 내용은 주석처리합니다.
	-- swapElement 의 취지는 element 를 교환하는 것이지, 리스트 자체를 흩뜨리면 안된다고 생각합니다.
	-- 리스트 자체를 변경할 경우, 해당 자료구조를 이용하는 queue 등에서 front 와 rear 의 순서가 뒤죽박죽 되는 등의 문제점이 있을 것.

		<----과거 버전--->
			- 이 함수는, element 를 교체하는 방식이 아니라, 해당 노드 자체의 위치를 바꾸는 형태로 동작합니다.
			- element 가 포인터가 아니기 때문에, element 내용만 교환하는 것은 element 가 커질 때 비효율적이기 때문입니다.



	<--- 개정 --->
	- 2019 09 10 나중채교수님께 질문
	- "큐" 라는 것에 의미가 있는 것이 아니고, 그냥 아예 정렬 방법이 다른 것으로 인식.
	- 리스트에 모두 input 을 받고 (혹은 어느정도 받고) 삽입정렬과 선택정렬을 수행하면 그 알고리즘으로 전체가 정렬되는 방식으로 생각.


<!> 주의
	- 일반 node 와 treenode 는 구조적으로 다릅니다. tree 를 구현할 때에는 treenode 를 사용해야 합니다.
	- 반드시 linked list 의 맨 앞 노드의 prevnode, 맨 뒤 노드의 nextnode 는 NULL 로 초기화되어있어야 합니다.
	- 이것이 옳은 방법인지는 모르겠으나, 트리가 배열로 구현될 때에는 널문자로 초기화함.

<!> 작성
	- 2019/09

*/

#define SELECTION 0
#define INSERTION 1

#define MIN 2
#define MAX 3

#define SORT_AND_DEQUEUE 0
#define JUST_SORT 1
#define JUST_DEQUEUE 2

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
	/* Here! */
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


void emptyListException() {
	printf("empteyListException");
}
void emptyQueueException() {
	printf("emptyQueueException");
}
void fullQueueException() {
	printf("fullQueueException");
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
element remove_node(node* currentnode) {

	element e;
	e = currentnode->e;
	free(currentnode);
	return e;
}
doublelinkedlist* get_doubleLinkedList() {

	doublelinkedlist* newlist = NULL;
	newlist = (doublelinkedlist*)malloc(sizeof(doublelinkedlist) * 1);
	if (newlist == NULL) return;

	//with header and trailer
	newlist->header = get_node();
	newlist->trailer = get_node();

	//init
	newlist->header->nextnode = newlist->trailer;
	newlist->trailer->prevnode = newlist->header;
	newlist->firstnode = NULL;

	return newlist;
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
doublelinkedlist_priorityqueue* get_doubleLinkedList_prioritiyQueue(int selection_or_insertion) {

	doublelinkedlist* newlist = NULL;
	newlist = get_doubleLinkedList();

	doublelinkedlist_priorityqueue* newqueue = NULL;
	newqueue = (doublelinkedlist_priorityqueue*)malloc(sizeof(doublelinkedlist_priorityqueue) * 1);
	if (newqueue == NULL) return;


	//remove header and trailer
	remove_node(newlist->header);
	remove_node(newlist->trailer);
	newlist->header = NULL;
	newlist->trailer = NULL;

	//init
	newqueue->doublelinkedlist = newlist;
	newqueue->front = NULL;
	newqueue->rear = NULL;
	newqueue->selection_or_insertion = selection_or_insertion;

	return newqueue;
}
void enqueue_doubleLinkedList_prioritiyQueue(doublelinkedlist_priorityqueue* queue, element e) {

	node* newnode = NULL;
	newnode = get_node();
	newnode->e = e;


	if (isEmpty_doubleLinkedList(queue->doublelinkedlist)) {
		queue->front = newnode;
		queue->rear = newnode;
		queue->doublelinkedlist->firstnode = newnode;
	}
	else {
		newnode->prevnode = queue->rear;
		queue->rear->nextnode = newnode;
		queue->rear = newnode;
	}

}
void swapElements_doubleLinkedList_priorityQueue(doublelinkedlist* list, node* frontnode, node* backnode) {


	element tmpelement;
	tmpelement = frontnode->e;
	frontnode->e = backnode->e;
	backnode->e = tmpelement;

	/*
	node* fronttmpnode = NULL;
	node* backtmpnode = NULL;
	fronttmpnode = frontnode;
	backtmpnode = backnode;

	if		((frontnode->prevnode == NULL) && (backnode->nextnode == NULL)) {
		frontnode->prevnode = backtmpnode->prevnode;
		frontnode->nextnode = NULL;
		backnode->prevnode = NULL;
		backnode->nextnode = fronttmpnode->nextnode;
	}
	else if ((frontnode->prevnode == NULL) && (backnode->nextnode != NULL)) {
		frontnode->prevnode = backtmpnode->prevnode;
		frontnode->nextnode = backtmpnode->nextnode;
		backnode->prevnode = NULL;
		backnode->nextnode = fronttmpnode->nextnode;
	}
	else if ((frontnode->prevnode != NULL) && (backnode->nextnode == NULL)) {
		frontnode->prevnode = backtmpnode->prevnode;
		frontnode->nextnode = NULL;
		backnode->prevnode = fronttmpnode->prevnode;
		backnode->nextnode = fronttmpnode->nextnode;
	}
	else if ((frontnode->prevnode != NULL) && (backnode->nextnode != NULL)) {
		frontnode->prevnode = backtmpnode->prevnode;
		frontnode->nextnode = backtmpnode->nextnode;
		backnode->prevnode = fronttmpnode->prevnode;
		backnode->nextnode = fronttmpnode->nextnode;
	}
	else {
		printf("nothing");
	}
	*/

}
void sortElementsSelection_doubleLinkedList_priorityQueue(doublelinkedlist_priorityqueue* queue, int min_or_max) {

	//매 반복마다 가장 크거나 작은 값을 찾아, 왼쪽부터 채우는 방식으로 작동. 문제 2번과 같이 구현함.
	node* tmpnode_i = NULL;
	node* tmpnode_j = NULL;
	node* min_or_max_loc = NULL;

	// 만약 큐에 저장된 원소의 개수가 1개일 경우, 오류가 발생할 수 있습니다.
	for (tmpnode_i = queue->front; tmpnode_i != queue->rear; tmpnode_i = tmpnode_i->nextnode) {
		min_or_max_loc = tmpnode_i;
		for (tmpnode_j = tmpnode_i->nextnode; tmpnode_j != NULL; tmpnode_j = tmpnode_j->nextnode) {
			if (min_or_max == MIN) {
				if (tmpnode_j->e.intelement < min_or_max_loc->e.intelement)
					min_or_max_loc = tmpnode_j;
			}
			else {
				if (tmpnode_j->e.intelement > min_or_max_loc->e.intelement)
					min_or_max_loc = tmpnode_j;
			}
		}
		swapElements_doubleLinkedList_priorityQueue(queue->doublelinkedlist, tmpnode_i, min_or_max_loc);
	}

}
void sortElementsReverseSelection_doubleLinkedList_priorityQueue(doublelinkedlist_priorityqueue* queue, int min_or_max) {

	//매 반복마다 가장 크거나 작은 값을 찾아, 오른쪽부터 채우는 방식으로 작동. 문제 1번과 같이 구현함.
	node* tmpnode_i = NULL;
	node* tmpnode_j = NULL;
	node* min_or_max_loc = NULL;

	// 만약 큐에 저장된 원소의 개수가 1개일 경우, 오류가 발생할 수 있습니다.
	for (tmpnode_i = queue->rear; tmpnode_i != queue->front; tmpnode_i = tmpnode_i->prevnode) {
		min_or_max_loc = tmpnode_i;
		for (tmpnode_j = tmpnode_i->prevnode; tmpnode_j != NULL; tmpnode_j = tmpnode_j->prevnode) {
			if (min_or_max == MIN) {
				if (tmpnode_j->e.intelement < min_or_max_loc->e.intelement)
					min_or_max_loc = tmpnode_j;
			}
			else {
				if (tmpnode_j->e.intelement > min_or_max_loc->e.intelement)
					min_or_max_loc = tmpnode_j;
			}
		}
		swapElements_doubleLinkedList_priorityQueue(queue->doublelinkedlist, tmpnode_i, min_or_max_loc);
	}

}
void sortElementsInsertion_doubleLinkedList_priorityQueue(doublelinkedlist_priorityqueue* queue, int min_or_max) {

	node* tmpnode_i = NULL;
	node* tmpnode_j = NULL;
	element e;


	for (tmpnode_i = queue->doublelinkedlist->firstnode->nextnode; tmpnode_i != NULL; tmpnode_i = tmpnode_i->nextnode) {

		e = tmpnode_i->e;
		tmpnode_j = tmpnode_i->prevnode;
		if (min_or_max == MIN) {
			//작은 순서대로 정렬
			while ((tmpnode_j != NULL) && (tmpnode_j->e.intelement > e.intelement)) {
				tmpnode_j->nextnode->e = tmpnode_j->e;
				tmpnode_j = tmpnode_j->prevnode;
			}
		}
		else {
			//큰 순서대로 정렬
			while ((tmpnode_j != NULL) && (tmpnode_j->e.intelement < e.intelement)) {
				tmpnode_j->nextnode->e = tmpnode_j->e;
				tmpnode_j = tmpnode_j->prevnode;
			}
		}
		if (tmpnode_j == NULL)
			queue->doublelinkedlist->firstnode->e = e;
		//null 이 되어버리면 다음꺼 참조를 못해서.
		else tmpnode_j->nextnode->e = e;
	}

}
element dequeue_doubleLinkdedList_priorityQueue(doublelinkedlist_priorityqueue* queue, int min_or_max, int sort_or_dequeue) {

	if (isEmpty_doubleLinkedList(queue->doublelinkedlist)) {
		emptyQueueException();
		return;
	}

	if (sort_or_dequeue == SORT_AND_DEQUEUE || sort_or_dequeue == JUST_SORT) {
		if (queue->selection_or_insertion == SELECTION) {
			/* 문제 풀이. */
			// 1 번
			if (min_or_max == MAX) sortElementsReverseSelection_doubleLinkedList_priorityQueue(queue, MAX);
			// 2 번
			if (min_or_max == MIN) sortElementsSelection_doubleLinkedList_priorityQueue(queue, MIN);
		}
		else {
			if (min_or_max == MIN) sortElementsInsertion_doubleLinkedList_priorityQueue(queue, MIN);
			if (min_or_max == MAX) sortElementsInsertion_doubleLinkedList_priorityQueue(queue, MAX);
		}
	}
	if (sort_or_dequeue == SORT_AND_DEQUEUE || sort_or_dequeue == JUST_DEQUEUE) {
		//front 는 가만히 있고, 위에서 알아서 정렬을 함.
		element e;
		node* removingnode = NULL;
		removingnode = queue->front;
		e = removingnode->e;

		if (queue->doublelinkedlist->firstnode != NULL) {
			//만약 제거하고자 하는 노드가 맨 앞에 있는 노드라면
			if (queue->doublelinkedlist->firstnode == queue->front) {
				queue->doublelinkedlist->firstnode = queue->doublelinkedlist->firstnode->nextnode;
			}
		}

		queue->front = queue->front->nextnode;
		remove_node(removingnode);
		return e;
	}
	return;
}





// binary tree method with array
//상수 정의 추가할것 : 비재귀 방식 알고리즘, 재귀 방식 알고리즘

#define UPSMALL 0
#define UPBIG 1

int isRoot_array_tree(int index) {
	if (index == 1) {
		return 1;
	}
	else return 0;
}
element elementInTree_array_tree(element *tree, int index) {
	return tree[index];
}
int parentIndex_array_tree(int index) {
	if (index == 1) {
		return 1;
	}
	else {
		return index / 2;
	}
}
int isParentExist_array_tree(tree_array* tree, int index) {
	if ((tree->elementarray)[parentIndex_array_tree(index)].charelement != '#') {
		return 1;
	}
	else return 0;
}
tree_array* get_array_tree(int arraysize) {

	tree_array* newtree = NULL;
	newtree = (tree_array*)malloc(sizeof(tree_array) * 1);
	if (newtree == NULL) return;

	//init
	newtree->maxsize = arraysize;
	newtree->elementarray = (element*)malloc(sizeof(element) * arraysize);
	if (newtree->elementarray == NULL) return;
	newtree->currentsize = 0;
	
	int i;
	for (i = 1; i < arraysize; i++) {
		//index == 0 인 위치는 초기화하지 않음.
		(newtree->elementarray)[i].charelement = '#';
	}
	
	return newtree;
}
element parentElementInTree_array_tree(element* tree, int index) {
	return tree[parentIndex_array_tree(index)];
}
int lastNodeIndex_array_tree(tree_array* tree) {
	return tree->currentsize;
}
int leftChildIndex_array_tree(int index) {
	return 2 * index;
}
int isLeftChildIndex_array_tree(int index) {
	return (index % 2);
}
int rightChildIndex_array_tree(int index) {
	return 2 * index + 1;
}
int isRightChildIndex_array_tree(int index) {
	return !(index % 2);
}
int isInternalIndex_array_tree(element *tree, int arraysize, int index) {
	return (2 * index < arraysize) && (tree[2 * index].charelement != '#');
}
int isExternalIndex_array_tree(element* tree, int arraysize, int index) {
	return ((2 * index >= arraysize) || (tree[2 * index].charelement == '#'));
}
int isExternalIndex_array_tree_heap(tree_array* tree, int index) {
	if (isExternalIndex_array_tree(tree->elementarray, tree->maxsize, index)) {
		if (tree->currentsize >= index) {
			return 0;
		}
		else return 1;
	}
	else {
		return 0;
	}
}
int isInternalIndex_array_tree_heap(tree_array* tree, int index) {
	if (isExternalIndex_array_tree_heap(tree, index)) {
		return 0;
	}
	else return 1;
}
void setElementWithIndex_array_tree(element *tree, int index, element e) {
	tree[index] = e;
}
void swapElementWithIndex_array_tree(element *tree, int index1, int index2) {
	element tmpelement;
	tmpelement = tree[index1];
	tree[index1] = tree[index2];
	tree[index2] = tmpelement;
}
void printElements_array_tree_heap(tree_array* tree) {
	int i;
	for (i = 1; i <= tree->currentsize; i++) {
		if ((tree->elementarray)[i].charelement == '#') {
			printf("");
		}
		else {
			printf(" %d", (tree->elementarray)[i]);
		}
	}
}
void insertElementWithIndex_array_tree(tree_array* tree, element e, int index) {

	if (tree->currentsize + 1 == tree->maxsize) {
		printf("fullArrayException");
		return;
	}
	
	if (isParentExist_array_tree(tree, index)) {
//		(tree->elementarray)[index].charelement = '1';
		(tree->elementarray)[index] = e;
		(tree->currentsize)++;
	}
	else if (isRoot_array_tree(index)) {
//		(tree->elementarray)[index].charelement = '1';
		(tree->elementarray)[index] = e;
		(tree->currentsize)++;
	}
	else {
		printf("invalidNodeException_ not exist parent");
		return;
	}
}
void downHeap_array_tree_heap(tree_array* tree, int index, int upsmall_or_upbig) {

	if (isExternalIndex_array_tree_heap(tree, leftChildIndex_array_tree(index))
		&& isExternalIndex_array_tree_heap(tree, rightChildIndex_array_tree(index))) {
		return;
	}

	int smallorbigindex = leftChildIndex_array_tree(index);
	element smallorbigelement = elementInTree_array_tree(tree->elementarray, leftChildIndex_array_tree(index));


	if (upsmall_or_upbig == UPSMALL) {
		if (isInternalIndex_array_tree_heap(tree, rightChildIndex_array_tree(index)))	 {
			if (elementInTree_array_tree(tree->elementarray, rightChildIndex_array_tree(index)).intelement < smallorbigelement.intelement) {
				smallorbigindex = rightChildIndex_array_tree(index);
				smallorbigelement = elementInTree_array_tree(tree->elementarray, smallorbigindex);
			}
		}
		if (smallorbigelement.intelement >= elementInTree_array_tree(tree->elementarray, index).intelement) {
			return;
		}
		swapElementWithIndex_array_tree(tree->elementarray, index, smallorbigindex);
	}
	else {//UPBIG
		if (isInternalIndex_array_tree_heap(tree, rightChildIndex_array_tree(index))) {
			if (elementInTree_array_tree(tree->elementarray, rightChildIndex_array_tree(index)).intelement > smallorbigelement.intelement) {
				smallorbigindex = rightChildIndex_array_tree(index);
				smallorbigelement = elementInTree_array_tree(tree->elementarray, smallorbigindex);
			}
		}
		if (smallorbigelement.intelement <= elementInTree_array_tree(tree->elementarray, index).intelement) {
			return;
		}
		swapElementWithIndex_array_tree(tree->elementarray, index, smallorbigindex);
	}

	downHeap_array_tree_heap(tree, smallorbigindex, upsmall_or_upbig);

}
void expandExternal_array_tree_heap(tree_array* tree) {

}
element retreatLast_array_tree_heap(tree_array* tree) {

	element e = elementInTree_array_tree(tree, lastNodeIndex_array_tree(tree));
	(tree->elementarray)[lastNodeIndex_array_tree(tree)].charelement = '#';
	(tree->currentsize)--;

	return e;
}
element removeMinOrMax_array_tree_heap(tree_array* tree, int upsmall_or_upbig) {

	
	element rootelement = (tree->elementarray)[1];
	element lastelement = (tree->elementarray)[lastNodeIndex_array_tree(tree)];
	
	(tree->elementarray)[1] = lastelement;

	retreatLast_array_tree_heap(tree);

	downHeap_array_tree_heap(tree, 1, upsmall_or_upbig);
	
	return rootelement;
}
void upHeap_array_tree_heap(tree_array* tree, int currentindex, int upsmall_or_upbig) {

	if (isRoot_array_tree(tree->elementarray)) {
		return;
	}

	if (upsmall_or_upbig == UPSMALL) {
		if ((tree->elementarray)[currentindex].intelement >= parentElementInTree_array_tree(tree->elementarray, currentindex).intelement) {
			return;
		}
		swapElementWithIndex_array_tree(tree->elementarray, currentindex, parentIndex_array_tree(currentindex));
	}
	else if (upsmall_or_upbig == UPBIG) {
		if ((tree->elementarray)[currentindex].intelement <= parentElementInTree_array_tree(tree->elementarray, currentindex).intelement) {
			return;
		}
		swapElementWithIndex_array_tree(tree->elementarray, currentindex, parentIndex_array_tree(currentindex));
	}
	else {
		printf("parameter error!");
	}

	upHeap_array_tree_heap(tree, parentIndex_array_tree(currentindex), upsmall_or_upbig);
}
void insertElement_array_tree_heap(tree_array* tree, element e) {
	
	expandExternal_array_tree_heap(tree);

	insertElementWithIndex_array_tree(tree, e, (tree->currentsize)+1);

}



int main() {


	tree_array* tree = NULL;
	tree = get_array_tree(101);
//	element tree[101]; //100 개 최대이므로, 0번 index 비운다면 101 * memory 필요.

	char input;
	int key;
	element tmpelement;
	while (1) {
		scanf("%c", &input);
		if (input == 'i' || input == 'I') {
			scanf("%d", &key);
			
			//set datatype element (init)
			tmpelement.intelement = key;
			tmpelement.charelement = '1';
	
			insertElement_array_tree_heap(tree, tmpelement);
			upHeap_array_tree_heap(tree, tree->currentsize, UPBIG);
			printf("0");
		}

		else if (input == 'd' || input == 'D') {//delete
			printf("%d", removeMinOrMax_array_tree_heap(tree, UPBIG));
		}
		else if (input == 'p' || input == 'P') {//print
			printElements_array_tree_heap(tree);
		}
		else { //input == 'q') : quit!!
			break;
		}
		printf("\n");
		getchar();
	}




	return 0;
}