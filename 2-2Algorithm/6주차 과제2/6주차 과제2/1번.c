#include<stdio.h>
#include<stdlib.h>
#include<time.h>
// #include<Windows.h>

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

	<-------중요 개정------>
	- firstnode 사용을 피해 주세요.



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


<!> heap sort 에 관하여
	- upheap, downheap 는 모두 재귀방식으로 이루어집니다.


<!> 주의
	- 일반 node 와 treenode 는 구조적으로 다릅니다. tree 를 구현할 때에는 treenode 를 사용해야 합니다.
	- 반드시 linked list 의 맨 앞 노드의 prevnode, 맨 뒤 노드의 nextnode 는 NULL 로 초기화되어있어야 합니다.
	- 이것이 옳은 방법인지는 모르겠으나, 트리가 배열로 구현될 때에는 널문자로 초기화함.
	- 어떤 자료구조를 생성한 후에는 반드시 remove 함수를 호출해서 사용할 것.

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
typedef struct doublelinkedlist_stack doublelinkedlist_stack;
typedef struct doublelinkedlist_queue doublelinkedlist_queue;
typedef struct doublelinkedlist_priorityqueue doublelinkedlist_priorityqueue;

typedef struct binarytree binarytree;
typedef struct treenode treenode;
typedef struct tree_array tree_array;



struct element {
	int intelement;
	char charelement;
	char* stringelement;
	treenode* treenodepointer;
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
struct doublelinkedlist_queue {

	doublelinkedlist* list;
	node* front;
	node* rear;

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
struct binarytree{
	treenode* root;
	int treesize;
};
struct treenode {
	treenode* parent;
	treenode* leftchild;
	treenode* rightchild;
	int height;
	element e;
};

struct doublelinkedlist_stack {
	doublelinkedlist* list;
	node* top;
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

//--------------------------------
//linked list ADT

void init_element(element* e) {
	e->charelement = '0';
	e->intelement = -1;
	e->stringelement = NULL;
	e->treenodepointer = NULL;
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
element removeFromList_doubleLinkedList(node* currentnode) {
	
	element e;

	node* np1, *np2;
	np1 = currentnode->prevnode;
	np2 = currentnode->nextnode;
	
	np1->nextnode = np2;
	np2->prevnode = np1;

	e = remove_node(currentnode);
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
void remove_doubleLinkedList(doublelinkedlist *list) {

	node* tmpnode = list->header->nextnode;
	while (list->header->nextnode != list->trailer) {
		tmpnode = tmpnode->nextnode;
		removeFromList_doubleLinkedList(tmpnode->prevnode);
	}

	remove_node(list->header);
	remove_node(list->trailer);
	free(list);

}
node* addLast_doubleLinkedList(doublelinkedlist* list, element e) {

	node* np;
	np = list->trailer->prevnode;

	node* newnode;
	newnode = get_node();

	np->nextnode = newnode;
	newnode->prevnode = np;
	newnode->nextnode = list->trailer;
	list->trailer->prevnode = newnode;
	newnode->e = e;

	return newnode;
}

//--------------------------------
//stack with linked list ADT

doublelinkedlist_stack* get_doubleLinkedList_stack() {

	doublelinkedlist_stack* newstack = NULL;
	newstack = (doublelinkedlist_stack*)malloc(sizeof(doublelinkedlist_stack) * 1);
	if (newstack == NULL)return;

	newstack->list = get_doubleLinkedList();
	newstack->top = NULL;

	return newstack;
}
int isEmpty_doubleLinkedList_stack(doublelinkedlist_stack* stack) {

	if (stack->top == NULL) {
		return 1;
	}
	else if (stack->list->header == stack->top) {
		return 1;
	}
	else {
		return 0;
	}
}
void push_doubleLinkedList_stack(doublelinkedlist_stack* stack, element e) {

	doublelinkedlist* list;

	list = stack->list;
	addLast_doubleLinkedList(list, e);

	if (stack->top == NULL) 
		stack->top = stack->list->trailer->prevnode;
	else stack->top = 
		stack->top->nextnode;

}
element pop_doubleLinkedList_stack(doublelinkedlist_stack* stack) {

	if (isEmpty_doubleLinkedList_stack(stack))
		return;

	node* removingnode;
	removingnode = stack->top;

	element e;
	e = removingnode->e;

	//만약 마지막 스택이면 다시 NULL 로 바꿔 놓기
	if (stack->top->prevnode == stack->list->header) {
		stack->top = NULL;
	}
	else {
		stack->top = stack->top->prevnode;
	}
	
	//메모리 free 하기 는 알아서됨.
	removeFromList_doubleLinkedList(removingnode);

	return e;
}
void remove_doubleLinkedList_stack(doublelinkedlist_stack* stack) {

	remove_doubleLinkedList(stack->list);
	free(stack);

}


//--------------------------------
//queue with linked list ADT

doublelinkedlist_queue* get_doubleLinkedList_queue() {

	doublelinkedlist_queue* newqueue = NULL;
	newqueue = (doublelinkedlist_queue*)malloc(sizeof(doublelinkedlist_queue) * 1);
	if (newqueue == NULL) return;
	
	newqueue->list = get_doubleLinkedList();
	newqueue->front = newqueue->list->header->nextnode;
	newqueue->rear = newqueue->list->trailer->prevnode;

}
int isEmpty_doubleLinkedList_queue(doublelinkedlist_queue* queue) {

	if (queue->front == NULL) {
		return 1;
	}
	else if (queue->front == queue->list->trailer) {
		return 1;
	}

	else return 0;
}
void enqueue_doubleLinkedList_queue(doublelinkedlist_queue* queue, element e) {


	node* newnode = NULL;
	newnode = addLast_doubleLinkedList(queue->list, e);

	if (isEmpty_doubleLinkedList_queue(queue)) {
		queue->front = queue->list->header->nextnode;
	}

	queue->rear = newnode;

}
element dequeue_doubleLinkedList_queue(doublelinkedlist_queue* queue) {

	if (isEmpty_doubleLinkedList_queue(queue)) {
		emptyQueueException();
		return;
	}

	queue->front = queue->front->nextnode;
	element e;
	e = removeFromList_doubleLinkedList(queue->list->header->nextnode);

	return e;
}
void remove_doubleLinkedList_queue(doublelinkedlist_queue* queue) {
	
	remove_doubleLinkedList(queue->list);
	free(queue);
}


//--------------------------------
//priority queue ADT

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


//--------------------------------
//binary tree with linked list ADT



//--------------------------------
//binary tree with array ADT


//--------------------------------
//heap ADT

#define UPSMALL 0
#define UPBIG 1

#define UPPER 0 //상향식 힙
#define DOWNER 1


int isExternal_treenode_binarytree(treenode* node) {

	if (node->leftchild == NULL && node->rightchild == NULL) {
		return 1;
	}
	else {
		return 0;
	}
}
treenode* leftChild_treenode_binarytree(treenode* node) {

	return node->leftchild;

}
treenode* rightChild_treenode_binarytree(treenode* node) {

	return node->rightchild;

}
void binaryExpansion(doublelinkedlist_stack* stack, int n) {

	element e;
	e.intelement = n % 2;
	while (n >= 2) {
		e.intelement = n % 2;
		push_doubleLinkedList_stack(stack, e);
		n = n / 2;
	}
	e.intelement = n;
	push_doubleLinkedList_stack(stack, e);

}

treenode* get_treenode_binarytree() {

	treenode* newnode = NULL;
	newnode = (treenode*)malloc(sizeof(treenode) * 1);
	if (newnode == NULL) return;

	//init
	element e;
	init_element(&e);
	newnode->e = e;
	newnode->height = 0;
	newnode->leftchild = NULL;
	newnode->rightchild = NULL;
	newnode->parent = NULL;


	return newnode;

}
element remove_treenode_binarytree(treenode *node) {
	
	element e;

	if (node->parent != NULL) {
		
		if (node->parent->leftchild == node) {
			node->parent->leftchild = NULL;
		}

		if (node->parent->rightchild == node) {
			node->parent->rightchild = NULL;
		}

	}


	e = node->e;
	free(node);

	return e;

}
binarytree* get_binarytree() {

	binarytree* newtree = NULL;
	
	newtree = (binarytree*)malloc(sizeof(binarytree) * 1);
	if (newtree == NULL) return;

	treenode* newnode = NULL;
	newnode = get_treenode_binarytree();

	//init tree
	newtree->root = newnode;
	newtree->treesize = 0;
	

	return newtree;

}


//후위순회 visit
void visitPostOrder_treenode_binarytree(treenode* node) {

	remove_treenode_binarytree(node);

}
//후위순회
treenode* postOrder_treenode_binarytree(treenode* node) {

	if (!isExternal_treenode_binarytree(node)) {
		postOrder_treenode_binarytree(leftChild_treenode_binarytree(node));
		postOrder_treenode_binarytree(rightChild_treenode_binarytree(node));
	}
	
	visitPostOrder_treenode_binarytree(node);

}
//중위순회 visit
void visitInOrder_treenode_binarytree(treenode* node) {

	if (!isExternal_treenode_binarytree(node)) {
		printf(" %d", node->e.intelement);
	}

}
//중위순회
treenode* inOrder_treenode_binarytree(treenode* node) {

	if (!isExternal_treenode_binarytree(node))
		inOrder_treenode_binarytree(leftChild_treenode_binarytree(node));

	visitInOrder_treenode_binarytree(node);

	if (!isExternal_treenode_binarytree(node))
		inOrder_treenode_binarytree(rightChild_treenode_binarytree(node));

}
void printElementsInOrder_treenode_binarytree(treenode* root) {

	inOrder_treenode_binarytree(root);

}



void visitLevelOrder_treenode_binarytree(treenode* node) {

	if (!isExternal_treenode_binarytree(node)) {
		printf(" %d", node->e.intelement);
	}

}
treenode* levelOrder_treenode_binarytree(treenode* node){

	doublelinkedlist_queue* queue = NULL;
	
	queue = get_doubleLinkedList_queue();


	element e, el, er;
	init_element(&e);
	init_element(&el);
	init_element(&er);

	e.treenodepointer = node;
	enqueue_doubleLinkedList_queue(queue, e);

	while (!isEmpty_doubleLinkedList_queue(queue)) {

		e = dequeue_doubleLinkedList_queue(queue);
		
		visitLevelOrder_treenode_binarytree(e.treenodepointer);
		if (!isExternal_treenode_binarytree(e.treenodepointer)) {
			el.treenodepointer = e.treenodepointer->leftchild;
			enqueue_doubleLinkedList_queue(queue, el);
			er.treenodepointer = e.treenodepointer->rightchild;
			enqueue_doubleLinkedList_queue(queue, er);
		}

	}

}
void printElements_treenode_binarytree(treenode* root) {

	levelOrder_treenode_binarytree(root);

}
int isRoot_treenode_binarytree(treenode* node) {
	if (node->parent == NULL) {
		return 1;
	}
	else return 0;
}
void remove_binarytree(binarytree* tree) {

	// 후위순회 하면서 visit 한 것 제거
	postOrder_treenode_binarytree(tree->root);

}
int isRoot_binarytree(treenode* node) {

	if (node->parent == NULL) {
		return 1;
	}
	else return 0;

	}
treenode* parent_treenode_binarytree(treenode* node) {

	return node->parent;

}
void expandExternal_treenode_binarytree(treenode* node) {

	node->leftchild = get_treenode_binarytree();
	node->rightchild = get_treenode_binarytree();
	node->leftchild->parent = node;
	node->rightchild->parent = node;

}
treenode* findLastNode_treenode_binarytree_heap(binarytree* tree) {

	int size = tree->treesize;

	doublelinkedlist_stack* stack = NULL;
	stack = get_doubleLinkedList_stack();

	binaryExpansion(stack, size);
	pop_doubleLinkedList_stack(stack);

	element bit;
	treenode* returnnode = tree->root;


	while (!isEmpty_doubleLinkedList_stack(stack)) {
		
		bit = pop_doubleLinkedList_stack(stack);
		if (bit.intelement == 0) {
			returnnode = leftChild_treenode_binarytree(returnnode);
		}
		else returnnode = rightChild_treenode_binarytree(returnnode);

	}

	remove_doubleLinkedList_stack(stack);

	return returnnode;

}
treenode* findAdvanceNode_treenode_binarytree_heap(binarytree* tree) {

	int size = tree->treesize;

	doublelinkedlist_stack* stack = NULL;
	stack = get_doubleLinkedList_stack();

	binaryExpansion(stack, size + 1);
	pop_doubleLinkedList_stack(stack);

	element bit;
	treenode* returnnode = tree->root;


	while (!isEmpty_doubleLinkedList_stack(stack)) {

		bit = pop_doubleLinkedList_stack(stack);
		if (bit.intelement == 0) {
			returnnode = leftChild_treenode_binarytree(returnnode);
		}
		else returnnode = rightChild_treenode_binarytree(returnnode);

	}

	remove_doubleLinkedList_stack(stack);

	return returnnode;
}
void swapElements_treenode_binarytree_heap(treenode* node1, treenode* node2) {

	element e;
	e = node1->e;
	node1->e = node2->e;
	node2->e = e;

}
void upHeap_treenode_binarytree_heap(treenode* node, int upsmall_or_upbig) {

	if (upsmall_or_upbig == UPSMALL) {
		if (isRoot_binarytree(node)) {
			return;
		}
		else {
			if (node->e.intelement < parent_treenode_binarytree(node)->e.intelement) {
				swapElements_treenode_binarytree_heap(node, parent_treenode_binarytree(node));
				upHeap_treenode_binarytree_heap(parent_treenode_binarytree(node), upsmall_or_upbig);
			}
			else {
				return;
			}
		}
	}

	else if (upsmall_or_upbig == UPBIG) {
		if (isRoot_binarytree(node)) {
			return;
		}
		else {
			if (node->e.intelement > parent_treenode_binarytree(node)->e.intelement) {
				swapElements_treenode_binarytree_heap(node, parent_treenode_binarytree(node));
				upHeap_treenode_binarytree_heap(parent_treenode_binarytree(node), upsmall_or_upbig);
			}
			else {
				return;
			}
		}
	}

	else return;
}
treenode* insertItem_treenode_binarytree_heap(binarytree* tree, element e, int upsmall_or_upbig) {

	treenode* node = NULL;
	if (tree->treesize == 0) {
		node = tree->root;
		node->e = e;
		expandExternal_treenode_binarytree(node);
		tree->treesize ++;
		return;
	}

	node = findAdvanceNode_treenode_binarytree_heap(tree);
	node->e = e;
	expandExternal_treenode_binarytree(node);
	upHeap_treenode_binarytree_heap(node, upsmall_or_upbig);
	tree->treesize++;

	return node;

}
treenode* downHeap_treenode_binarytree_heap(treenode* node, int upbig_or_upsmall) {


	if (upbig_or_upsmall == UPBIG) {

		if (isExternal_treenode_binarytree(leftChild_treenode_binarytree(node)) &&
			isExternal_treenode_binarytree(rightChild_treenode_binarytree(node)))
			return;

		treenode* biggernode = NULL;
		biggernode = leftChild_treenode_binarytree(node);

		if (!isExternal_treenode_binarytree(rightChild_treenode_binarytree(node))) {
			if (biggernode->e.intelement < rightChild_treenode_binarytree(node)->e.intelement) {
				biggernode = rightChild_treenode_binarytree(node);
			}
		}
		
		if (biggernode->e.intelement < node->e.intelement) {
			return;
		}

		swapElements_treenode_binarytree_heap(biggernode, node);
		downHeap_treenode_binarytree_heap(biggernode, upbig_or_upsmall);

	}

	if (upbig_or_upsmall == UPSMALL) {




	}


	return;

}
element removeMinOrMax_treenode_binarytree_heap(binarytree* tree, int upbig_or_upsmall) {

	element e;
	e = tree->root->e;

	treenode* finalnode = NULL;
	finalnode = findLastNode_treenode_binarytree_heap(tree);
	swapElements_treenode_binarytree_heap(tree->root, finalnode);


	remove_treenode_binarytree(finalnode->leftchild);
	remove_treenode_binarytree(finalnode->rightchild);
	tree->treesize--;

	downHeap_treenode_binarytree_heap(tree->root, upbig_or_upsmall);

	return e;

}




int isRoot_array_tree(int index) {
	if (index == 1) {
		return 1;
	}
	else return 0;
}
element elementInTree_array_tree(element* tree, int index) {
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
int isInternalIndex_array_tree(element* tree, int arraysize, int index) {
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
void setElementWithIndex_array_tree(element* tree, int index, element e) {
	tree[index] = e;
}
void swapElementWithIndex_array_tree(element* tree, int index1, int index2) {
	element tmpelement;
	tmpelement = tree[index1];
	tree[index1] = tree[index2];
	tree[index2] = tmpelement;
}
void printElementsWithRoot_array_tree_heap(tree_array* tree, int rootindex) {
	int i;
	for (i = rootindex; i < rootindex + tree->currentsize; i++) {
		if ((tree->elementarray)[i].charelement == '#') {
			printf("");
		}
		else {
			printf(" %d", (tree->elementarray)[i].intelement);
		}
	}
}
void printElements_array_tree_heap(tree_array* tree) {
	printElementsWithRoot_array_tree_heap(tree, 1);
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
		if (isInternalIndex_array_tree_heap(tree, rightChildIndex_array_tree(index))) {
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
void downHeapForInPlace_array_tree_heap(tree_array* tree, int index, int upsmall_or_upbig) {

	int smallorbigindex = leftChildIndex_array_tree(index);
	element smallorbigelement = elementInTree_array_tree(tree->elementarray, leftChildIndex_array_tree(index));
	int last = tree->maxsize - 1;

	if (last < smallorbigindex) return;

	if (upsmall_or_upbig == UPSMALL) {
		if (last >= rightChildIndex_array_tree(index)) {
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
		if (last >= rightChildIndex_array_tree(index)) {
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

	downHeapForInPlace_array_tree_heap(tree, smallorbigindex, upsmall_or_upbig);

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

	insertElementWithIndex_array_tree(tree, e, (tree->currentsize) + 1);

}
void buildInPlaceHeap_array_tree_heap(tree_array* tree, int upsmall_or_upbig) {

}
void buildUpperHeap_array_tree_heap(tree_array* tree, int upsmall_or_upbig) {
	int i;
	tree->currentsize = ((tree->maxsize - 1) / 2) + ((tree->maxsize - 1) % 2);
	for (i = ((tree->maxsize - 1) / 2); i >= 1; i--) {
		tree->currentsize++;
		//			printf("start : %d :: number : %d\n", i, tree->elementarray[i]);
		downHeapForInPlace_array_tree_heap(tree, i, upsmall_or_upbig);
		//			printElementsWithRoot_array_tree_heap(tree, i);
		//			printf("\ncurrentsize : %d\n", tree->currentsize);
	}
}
void inPlaceHeapSort_array_tree_heap(tree_array* tree, int upsmall_or_upbig, int upper_or_downer) {

	//제자리 힙정렬

	if (upper_or_downer == UPPER) {
		// 힙 생성
		buildUpperHeap_array_tree_heap(tree, upsmall_or_upbig);
		// 2기 작업
		while (tree->currentsize != 0) {
			printf(" %d", removeMinOrMax_array_tree_heap(tree, upsmall_or_upbig).intelement);
		}
	}
	else { //downer , 하향식 힙

		// upheap 이후 downheap
	}

}









int main() {



	binarytree* tree = NULL;
	tree = get_binarytree();


	char input;
	int key;
	element tmpelement;
	treenode* node;

	while (1) {
		scanf("%c", &input);
		if (input == 'i' || input == 'I') {
			scanf("%d", &key);

			//set datatype element (init)
			tmpelement.intelement = key;
			tmpelement.charelement = '1';

			node = insertItem_treenode_binarytree_heap(tree, tmpelement, UPBIG);
//			upHeap_array_tree_heap(tree, tree->currentsize, UPBIG);
			printf("0");
		}

		else if (input == 'd' || input == 'D') {//delete
//			printf("%d", removeMinOrMax_array_tree_heap(tree, UPBIG));
			printf("%d", removeMinOrMax_treenode_binarytree_heap(tree, UPBIG).intelement);
		}
		else if (input == 'p' || input == 'P') {//print
//			printElements_array_tree_heap(tree);
			levelOrder_treenode_binarytree(tree->root);
		}
		else { //input == 'q') : quit!!
			break;
		}
		printf("\n");
		getchar();
	}

// 이거 고치기!
	remove_binarytree(tree);

	return 0;
}