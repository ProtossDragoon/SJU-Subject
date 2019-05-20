#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define NO_HEADER_AND_TRAILER 1
#define WITH_HEADER_AND_TRAILER 0

//____________________________________
//To.professor
	//이 부분은 아직 구현되지 않았습니다.
	//이미 함수를 Header 과 Trailer 을 모두 포함시키고 짜버려서
	//시간 주시면 Header과 Trailer 없이 컴파일되도록 짜겠습니다.
//____________________________________


//____________________________________
//Submit, Debug Settings
//Can use SUBMIT, DEBUG define setting simultaneously
	#define SUBMIT 
	//#define DEBUG


//Element data type settings
//Cannot use INT, CHAR define setting simultaneously

//#define CHAR
	#define INT
	//#define CHAR

	#ifdef INT
	#define INPUT "%d"
	#endif
	#ifdef CHAR
	#define INPUT "%c"
	#endif
//____________________________________


//List structure
typedef struct list li;
typedef struct node nd;
typedef struct elem e;
struct list {
	nd* header;
	nd* trailer;
	int size;
};
struct node {
	nd* prev_node;
	e* element;
	nd* next_node;
};
struct elem {
	char charelem;
	int intelem;
};

//Que structure
typedef struct Que_linkedlist que_li;
struct Que_linkedlist {
	int no_header_and_trailer;
	li* list;
	nd* front;
	nd* rear;
};


//No Deque structure



//Function original form
void invalidRankException();
void emptyQueReception();
nd* getNewNode();


//Global variable
int breakcount = 0;


//List ADT
li* initList() {

	li* newlist;
	newlist = (li*)malloc(sizeof(li) * 1);
	if (newlist == NULL) {
		printf("function : initList error\n");
		return;
	}

	newlist->header = getNewNode();
	newlist->trailer = getNewNode();
	newlist->size = 0;

	newlist->header->next_node = newlist->trailer;
	newlist->trailer->prev_node = newlist->header;
	newlist->header->prev_node = NULL;
	newlist->trailer->next_node = NULL;

	return newlist;
}
int size(li* list) {
	return list->size;
}
int isEmpty(li* list) {
	if (size(list) == 0) {
		return 1;
	}
	else return 0;
}
nd* getNewNode() {

	nd* newnode;
	newnode = (nd*)malloc(sizeof(nd) * 1);
	if (newnode == NULL) {
		printf("function : getNewNode error\n");
		return;
	}

	newnode->element = (e*)malloc(sizeof(e) * 1);
	if (newnode->element == NULL) {
		printf("function : getNewNode error\n");
		return;
	}

	newnode->element->charelem = '0';
	newnode->element->intelem = 0;

	return newnode;
}
e removeNode(li* list, nd* node) {

	e tmpe = *(node->element);

	if ((node == list->header) || (node == list->trailer)) {
		invalidRankException();
		return;
	}

	nd* tmpprevnode = node->prev_node;
	nd* tmpnextnode = node->next_node;

	tmpprevnode->next_node = tmpnextnode;
	tmpnextnode->prev_node = tmpprevnode;

	list->size -= 1;

	free(node->element);
	free(node);

	return tmpe;
}
nd* selectNodeByRank(li* list, int rank) {
	//rank는 header이 0번째 node 라고 하고
	//trailer 이 n+1번째 node 라고 하자.


	nd* node;

	if (rank <= 0 || rank > list->size) {
		invalidRankException();
	}


	int i;
	if (rank < list->size / 2) {
		node = list->header;
		for (i = 0; i < rank; i++) {
			node = node->next_node;
		}
	}
	else {
		node = list->trailer;
		for (i = 0; i <= list->size - rank; i++) {
			node = node->prev_node;
		}
	}

	return node;

}
nd* selectLastNode(li *list) {
	int rank = list->size;
	return selectNodeByRank(list, rank);
}
nd* selectFirstNode(li *list) {
	return selectNodeByRank(list, 1);
}
nd* setElementByRank(li* list, int rank, e* elem) {


	nd* np;

	np = selectNodeByRank(list, rank);

	np->element = elem;
	return np;

};
nd* setElementByNode(nd* node, e* elem) {

	node->element = elem;

	return node;
}
nd* addNode(li* list, e* element, int rank) {

	nd* newnode;
	int i;
	
	if (rank < 0 || rank > list->size) {
		invalidRankException();
		return;
	}

	newnode = getNewNode();
	newnode->element = element;
	
	nd* np;

	if (rank < list->size / 2) {
		np = list->header;
		for (i = 0; i < rank; i++) {
			np = np->next_node;
		}
	}
	else {
		np = list->trailer;
		for (i = 0; i < list->size - rank; i++) {
			np = np->prev_node;
		}
		np = np->prev_node;
	}

	np->next_node->prev_node = newnode;
	newnode->next_node = np->next_node;

	np->next_node = newnode;
	newnode->prev_node = np;

	newnode->element = element;
	list->size += 1;

	return newnode;
}
nd* addLastNode(li* list, e* element) {
	int rank;
	rank = list->size;
	return addNode(list, element, rank);
}
nd* addFirstNode(li* list, e* element) {
	int rank;
	rank = 0;
	return addNode(list, element, rank);
}
void printList(li* list) {

	nd* np;
	np = list->header->next_node;
#ifdef DEBUG
	printf("Front______________\n");
#endif // DEBUG

	while (np != list->trailer) {
#ifdef DEBUG
		printf("char: %c int: %d\n", np->element->charelem, np->element->intelem);
#endif

#ifndef DEBUG
		printf("%d ", np->element->intelem);
#endif //DEBUG
		np = np->next_node;
	}

#ifndef DEBUG
	printf("\n");
#endif

#ifdef DEBUG
	printf("Rear_______________\n\n");
#endif // DEBUG

}
void invalidRankException() {
	printf("invalidRankException\n");
}
e* setElement(int intinput, char charinput) {

	e* elem;
	elem = (e*)malloc(sizeof(e) * 1);
	if (elem == NULL) {
		print("funcion : setElement error\n");
		return;
	}
	(elem->intelem) = intinput;
	(elem->charelem) = charinput;

	return elem;
}
void reverseListDirectionComponent(li *list) { //역대급 리버스 모드
	
	nd* np_header = list->header;
	nd* np_trailer = list->trailer;
	nd* np_tmp;
	
	nd* np_i = list->trailer;

	list->trailer->next_node = list->trailer->prev_node;
	list->trailer->prev_node = NULL;
	while (np_i->next_node != NULL) {
		np_i = np_i->next_node;
		np_tmp = np_i->prev_node;
		np_i->prev_node = np_i->next_node;
		np_i->next_node = np_tmp;
	}

	list->header = np_trailer;
	list->trailer = np_header;
	

}


//Que ADT
que_li* initQue_linkedlist(int i) {


	li* list_for_que;
	list_for_que = initList();

	que_li* newque;
	newque = (que_li*)malloc(sizeof(que_li) * 1);
	if (newque == NULL) {
		printf("function : initQue error\n");
		return;
	}

	newque->front = (nd*)malloc(sizeof(nd) * 1);
	newque->rear = (nd*)malloc(sizeof(nd) * 1);
	if (newque->front == NULL || newque->rear == NULL) {
		printf("function : initQue error\n");
		return;
	}
	
	newque->list = list_for_que;
	newque->front = list_for_que->header;
	newque->rear = list_for_que->trailer;
	newque->no_header_and_trailer = i;

	return newque;
}
nd* enqueue_linkedlist(que_li *que, e* element) {


	nd* lastnode;
	if (isQueEmpty_linkedlist(que)) {
		lastnode = addLastNode(que->list, element);
		que->front = lastnode;
		que->rear = lastnode;
	}
	else {
		lastnode = addLastNode(que->list, element);
		que->rear = lastnode;
	}

	return lastnode;
}
e dequeue_linkedlist(que_li *que) {

	if (isQueEmpty_linkedlist(que)) {
		emptyQueReception();
		return;
	}

	//강의 교안에 나온 Que 초기화, Que 관리 방법과는 다소 다른 부분이 존재함.

	if (que->front->next_node == que->list->trailer) { //when size == 1 ( deleting node is last node)
		que->front = que->list->header;
		que->rear = que->list->trailer;
	}
	else que->front = que->front->next_node;

	e element;
	element = removeNode(que->list, selectFirstNode(que->list));
	
	return element;
}
e queFront_linkedlist(que_li *que) {

	if (isQueEmpty_linkedlist(que)) {
		emptyQueReception();
		return;
	}
	return *(que->front->element);
}
int queSize_linkedlist(que_li *que) {
	return que->list->size;
}
int isQueEmpty_linkedlist(que_li *que) {
	if (queSize_linkedlist(que) == 0) {
		return 1;
	}
	else return 0;
}
void emptyQueReception() {
#ifdef DEBUG
	printf("emptyQueReception\n");
#endif // DEBUG

#ifdef SUBMIT
	printf("underflow\n");
	breakcount = 1;
#endif // SUBMIT
}
void fullQueReception() {
	printf("fullQueReception\n");
}
void queReverseListDirectionComponent_linkedlist(que_li* que) {

	reverseListDirectionComponent(que->list);
	
	nd* np_switch_front_rear_tmp;
	np_switch_front_rear_tmp = que->front;

	que->front = que->rear;
	que->rear = np_switch_front_rear_tmp;

}

//Deque ADT
nd* deque_Add_Front(que_li *que, e *element) {

	nd* firstnode;
	if (isQueEmpty_linkedlist(que)) {
		firstnode = addFirstNode(que->list, element);
		que->front = firstnode;
		que->rear = firstnode;
	}
	else {
		firstnode = addFirstNode(que->list, element);
		que->front = firstnode;
	}

	return firstnode;
}
nd* deque_Add_Rear(que_li *que, e *element) {
	return enqueue_linkedlist(que, element);
}
e deque_delete_Front(que_li* que) {
	return dequeue_linkedlist(que);
}
void deque_delete_Rear(que_li *que) {
	
	if (isQueEmpty_linkedlist(que)) {
		emptyQueReception();
		return;
	}
	
	queReverseListDirectionComponent_linkedlist(que);

	e element;
	element = dequeue_linkedlist(que);

	queReverseListDirectionComponent_linkedlist(que);

	return element;

}
void deque_print(que_li *que) {
#ifdef DEBUG
	printf("front : %d\n", que->front->element->intelem);
	printf("rear- : %d\n", que->rear->element->intelem);
#endif // DEBUG
	printList(que->list);
}



int main() {

	que_li* que;
	li* list;
	e* element;

	int n;
	int i;
	char input_string[11] = { 0 };
#ifdef CHAR
	char input_data;
#endif // CHAR
#ifdef INT
	int input_data;
#endif //INT

	que = initQue_linkedlist(WITH_HEADER_AND_TRAILER);

	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%s", input_string);
		if (strcmp(input_string, "AF") == 0) {
			scanf(INPUT, &input_data);
			getchar();
			element = setElement(input_data, '1');
			deque_Add_Front(que, element);
		}
		else if(strcmp(input_string, "AR") ==0) {
			scanf(INPUT, &input_data);
			getchar();
			element = setElement(input_data, '1');
			deque_Add_Rear(que, element);
		}
		else if(strcmp(input_string, "DF") == 0) {
			deque_delete_Front(que);
		}
		else if (strcmp(input_string, "DR") == 0) {
			deque_delete_Rear(que);
		}
		else {
			deque_print(que);
		}
#ifdef DEBUG
		deque_print(que);
		printf("\n");
#endif
		if (breakcount == 1) {
			break;
		}
	}

	return 0;

}

