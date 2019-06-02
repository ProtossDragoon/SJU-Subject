//1. List
//2. Queue (by list)
//3. Deque (by list)
//4. Stack (by list)
//5. Stack (by Array)
//6. Queue (by Stack - by list)
//7. Stack (by Queue - by list)

#include<stdio.h>
#include<stdlib.h>
#include<string.h>



#define NO_HEADER_AND_TRAILER 1
#define WITH_HEADER_AND_TRAILER 0
#define SINGLE_LINKED_LIST 0
#define DOUBLE_LINKED_LIST 1

//____________________________________
//To.professor
	//이 부분은 아직 구현되지 않았습니다.
	//이미 함수를 Header 과 Trailer 을 모두 포함시키고 짜버려서
	//시간 주시면 Header과 Trailer 없이 컴파일되도록 짜겠습니다.
#define SINGLE_LINKED_LIST_NOT_READY
//____________________________________


//____________________________________
//Submit, Debug Settings
//Can use SUBMIT, DEBUG define setting simultaneously
#define SUBMIT
//#define DEBUG


//Element data type settings
//Cannot use INT, CHAR define setting simultaneously

//#define INT
#define CHAR

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
	int list_type;
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



//No Deque structure

//Stack structure
typedef struct stack_linkedlist st_li;
typedef struct stack_array st_arr;
struct stack_linkedlist {
	nd* top;
	li* list;
};
struct stack_array {
	int top;
	e stack[100];
};

//Que structure
typedef struct Queue_linkedlist que_li;
struct Queue_linkedlist {
	int no_header_and_trailer;
	li* list;
	nd* front;
	nd* rear;
};

//Stack by Que structure
typedef struct Stack_queue st_que;
struct Stack_queue {

	que_li* inputqueue;
	que_li* outputqueue;

};



//Que by Stack structure
typedef struct Queue_stack que_st;
struct Queue_stack {
	st_li* inputstack;
	st_li* outputstack;
};






//Function original form
void invalidRankException();
void emptyQueReception();
int isQueEmpty_linkedlist(que_li* que);
nd* getNewNode();
void emptyStackException();
char intToChar(int a);
int charToInt(char ch);
st_li* addTwoStacksForHomework(st_li* stack1, st_li* stack2);
int stack_Size_linkedlist(st_li* stack);
e* setElement(int intinput, char charinput) {

	e* elem;
	elem = (e*)malloc(sizeof(e) * 1);
	if (elem == NULL) {
		printf("function : setElement error\n");
		return;
	}
	(elem->intelem) = intinput;
	(elem->charelem) = charinput;

	return elem;
}
void queue_Refill_stack(que_st* que);
nd* stack_Push_linkedlist(st_li* stack, e* element);
void stack_Refill_queue(st_que* stack);

//Global variable
int breakcount = 0;



//List ADT
li* initList(int i) {

	li* newlist;
	newlist = (li*)malloc(sizeof(li) * 1);
	if (newlist == NULL) {
		printf("function : initList error\n");
		return;
	}

	if (i == SINGLE_LINKED_LIST) {
		newlist->header = getNewNode();
		newlist->trailer = getNewNode();
		newlist->size = 0;

		newlist->header->next_node = newlist->trailer;
		newlist->header->prev_node = NULL;
		newlist->trailer->next_node = NULL;
		newlist->trailer->prev_node = NULL;

		newlist->list_type = SINGLE_LINKED_LIST;
	}
	else {
		newlist->header = getNewNode();
		newlist->trailer = getNewNode();
		newlist->size = 0;

		newlist->header->next_node = newlist->trailer;
		newlist->trailer->prev_node = newlist->header;
		newlist->header->prev_node = NULL;
		newlist->trailer->next_node = NULL;

		newlist->list_type = DOUBLE_LINKED_LIST;
	}

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

	if (list->list_type == DOUBLE_LINKED_LIST) {
		nd* tmpprevnode = node->prev_node;
		nd* tmpnextnode = node->next_node;

		tmpprevnode->next_node = tmpnextnode;
		tmpnextnode->prev_node = tmpprevnode;

		list->size -= 1;

		free(node->element);
		free(node);
	}
	else { // If the list is single linked list
		printf("funciton : removenode, error : not implemented\n");
	}

	return tmpe;
}
nd* selectNodeByRank(li* list, int rank) {
	//rank는 header이 0번째 node 라고 하고
	//trailer 이 n+1번째 node 라고 하자.


	nd* node = NULL;

	if (rank <= 0 || rank > list->size) {
		invalidRankException();
	}


	int i;

	if (list->list_type == DOUBLE_LINKED_LIST) {
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
	}
	else { //If the list is single linked list
		printf("funciton : selectNodeByRank, error : not implemented\n");
	}

	return node;

}
nd* selectLastNode(li* list) {
	int rank = list->size;
	return selectNodeByRank(list, rank);
}
nd* selectFirstNode(li* list) {
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


	if (list->list_type == DOUBLE_LINKED_LIST) {
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
	}
	else { //If the list is single linked list
		printf("funciton : addNode, error : not implemented\n");
	}

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
void reverseListDirectionComponent(li* list) { //역대급 리버스 모드

	if (list->list_type == DOUBLE_LINKED_LIST) {
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
	else {
		printf("funciton : reverseListDirectionComponent,\n error : This method cannot implemented with single linked list\n");
	}

}




//Que ADT
que_li* initQue_linkedlist(int i) {

	li* list_for_que;
#ifdef SINGLE_LINKED_LIST_NOT_READY
	list_for_que = initList(DOUBLE_LINKED_LIST);
#endif // SINGLE_LINKED_LIST_NOT_READY
#ifndef SINGLE_LINKED_LIST_NOT_READY
	list_for_que = initList(SINGLE_LINKED_LIST);
#endif // !SINGLE_LINKED_LIST_NOT_READY


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
nd* enqueue_linkedlist(que_li* que, e* element) {


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
e dequeue_linkedlist(que_li* que) {

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
e queFront_linkedlist(que_li* que) {

	if (isQueEmpty_linkedlist(que)) {
		emptyQueReception();
		return;
	}
	return *(que->front->element);
}
int queSize_linkedlist(que_li* que) {
	return que->list->size;
}
int isQueEmpty_linkedlist(que_li* que) {
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
nd* deque_Add_Front(que_li* que, e* element) {

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
nd* deque_Add_Rear(que_li* que, e* element) {
	return enqueue_linkedlist(que, element);
}
e deque_delete_Front(que_li* que) {
	return dequeue_linkedlist(que);
}
e deque_delete_Rear(que_li* que) {

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
e deque_Front(que_li* que) {
	return *(que->front->element);
}
e deque_Rear(que_li* que) {
	return *(que->rear->element);
}
void deque_print(que_li* que) {
#ifdef DEBUG
	printf("front : %d\n", que->front->element->intelem);
	printf("rear- : %d\n", que->rear->element->intelem);
#endif // DEBUG
	printList(que->list);
}




//Stack ADT
void emptyStackException() {
	printf("emptyStackException\n");
}
void fullStackException() {
	printf("fullStackException\n");
}

st_li* initStack_linkedlist() {

	li* newlist;
#ifdef SINGLE_LINKED_LIST_NOT_READY
	newlist = initList(DOUBLE_LINKED_LIST);
#endif // SINGLE_LINKED_LIST_NOT_READY
#ifndef SINGLE_LINKED_LIST_NOT_READY
	newlist = initList(SINGLE_LINKED_LIST);
#endif // !SINGLE_LINKED_LIST_NOT_READY


	st_li* newstack;
	newstack = (st_li*)malloc(sizeof(st_li) * 1);
	if (newstack == NULL) {

		printf("function : initStack_linkedlist\n");
		return;
	}

	newstack->list = newlist;
	newstack->top = newlist->header;

	return newstack;
}
e stack_Pop_linkedlist(st_li* stack) {

	if (stack_Size_linkedlist(stack) == 0) {
		emptyStackException();
		return;
	}

	e element;
	nd* currenttop = stack->top;

	element = *(stack->top->element);

	stack->top = currenttop->prev_node;

	removeNode(stack->list, currenttop);
	return element;

}
e stack_Top_linkedlist(st_li* stack) {
	return *(stack->top->element);
}
nd* stack_Push_linkedlist(st_li* stack, e* element) {

	nd* currenttop = stack->top;

	addLastNode(stack->list, element);

	stack->top = stack->top->next_node;

	return stack->top;
}
int stack_Size_linkedlist(st_li* stack) {
	return stack->list->size;
}
int stack_IsEmpty_linkedlist(st_li* stack) {
	if (stack_Size_linkedlist(stack) == 0) return 1;
	else return 0;
}
void stack_print_linkedlist(st_li* stack) {
	printList(stack->list);
}
void stack_Popping_inkedlist(st_li* stack) {
	e tmpelem;
	while (!stack_IsEmpty_linkedlist(stack)) {
		tmpelem = stack_Pop_linkedlist(stack);
#ifdef CHAR
		printf("%c", tmpelem.charelem);
#endif // CHAR
#ifdef INT
		printf("%d", tmpelem.intelem);
#endif // INT
	}

}
void stack_delete_linkedlist(st_li *stack) {

	while (!stack_IsEmpty_linkedlist(stack)) {
		stack_Pop_linkedlist(stack);
	}
	free(stack);

}


//Queue by Stack ADT
que_st* queue_InitQue_stack() {

	que_st* newque;

	newque = (que_st*)malloc(sizeof(que_st) * 1);
	if (newque == NULL) {
		printf("function : queue_initQue_stack error\n");
		return;
	}

	newque->inputstack = initStack_linkedlist();
	newque->outputstack = initStack_linkedlist();


	return newque;
}
int queue_Size_stack(que_st* que) {
	return stack_Size_linkedlist(que->inputstack) + stack_Size_linkedlist(que->outputstack);
}
int queue_IsEmpty_stack(que_st* que) {
	if (queue_Size_stack(que) == 0) return 1;

	return 0;
}
void queue_Enqueue_stack(que_st* que, e* element) {

	stack_Push_linkedlist(que->inputstack, element);

}
e queue_Dequeue_stack(que_st* que) {

	if (isQueEmpty_linkedlist(que->outputstack)) {
		queue_Refill_stack(que);
		return stack_Pop_linkedlist(que->outputstack);
	}
	else {
		return stack_Pop_linkedlist(que->outputstack);
	}

}
void queue_Refill_stack(que_st* que) {

	if (stack_IsEmpty_linkedlist(que->inputstack)) {
		emptyStackException();
		return;
	}
	else {
		e* element;
		while (!stack_IsEmpty_linkedlist(que->inputstack)) {

			element = (e*)malloc(sizeof(e) * 1);
			if (element == NULL) {
				printf("queue_Refill_stack error\n");
				return;
			}
			*element = stack_Pop_linkedlist(que->inputstack);

			stack_Push_linkedlist(que->outputstack, element);

		}

	}

}

//Stack by Queue ADT
st_que* stack_InitStack_queue() {

	st_que* newstack;

	newstack = (st_que*)malloc(sizeof(st_que) * 1);
	if (newstack == NULL) {
		printf("function : stack_initStack_queue error\n");
		return;
	}

	newstack->inputqueue = initQue_linkedlist(DOUBLE_LINKED_LIST);
	newstack->outputqueue = initQue_linkedlist(DOUBLE_LINKED_LIST);

	return newstack;

}
int stack_Size_queue(st_que* stack) {
	return queSize_linkedlist(stack->inputqueue) + queSize_linkedlist(stack->outputqueue);
}
int stack_IsEmpty_queue(st_que* stack) {
	if (stack_Size_queue(stack) == 0)return 1;
	return 0;
}
void stack_Push_queue(st_que* stack, e* element) {

	enqueue_linkedlist(stack->inputqueue, element);

}
e stack_Pop_queue(st_que* stack) {

	if (stack_IsEmpty_linkedlist(stack->outputqueue)) {

		stack_Refill_queue(stack);
		return dequeue_linkedlist(stack->outputqueue);
	}
	else {
		return dequeue_linkedlist(stack->outputqueue);
	}

}
e stack_Top_queue(st_que* stack) {

	if (stack_IsEmpty_linkedlist(stack->outputqueue)) {
		stack_Refill_queue(stack);

		e* element;
		element = (e*)malloc(sizeof(e) * 1);
		if (element == NULL) {
			printf("function : stack_Refill_queue error\n");
			return;
		}

		*element = dequeue_linkedlist(stack->outputqueue);
		enqueue_linkedlist(stack->inputqueue, element);
		return *element;
	}
	else {
		printf("function : stack_Top_queue error.\n");
		//outputqueue must be empty.
	}

}
void stack_Refill_queue(st_que* stack) {

	if (isQueEmpty_linkedlist(stack->inputqueue)) {
		emptyQueReception();
		return;
	}
	else {
		e* element;
		while (queSize_linkedlist(stack->inputqueue) > 1) {

			element = (e*)malloc(sizeof(e) * 1);
			if (element == NULL) {
				printf("function : stack_Refill_queue error\n");
				return;
			}
			*element = dequeue_linkedlist(stack->inputqueue);

			enqueue_linkedlist(stack->outputqueue, element);
		}

		que_st* tmp;
		tmp = stack->outputqueue;
		stack->outputqueue = stack->inputqueue;
		stack->inputqueue = tmp;

	}

}
void stack_Print_queue(st_que* stack) {

	while (!isQueEmpty_linkedlist(stack->inputqueue)) {
#ifdef CHAR
		printf("%c", stack_Pop_queue(stack).charelem);
#endif // CHAR
#ifdef INT
		printf("%d", stack_Pop_queue(stack).intelem);
#endif // INT

#ifdef DEBUG
		printf(" ");
#endif //DEBUG
	}

}




//Stack_arr ADT
st_arr* initStack_array() {

	st_arr* newstack;
	e* element;
	newstack = (st_arr*)malloc(sizeof(st_arr) * 1);
	if (newstack == NULL) {
		printf("function : initStack_array error\n");
		return;
	}

	newstack->top = -1;


	int i;
	element = setElement(0, '0');
	for (i = 0; i < 100; i++) {
		newstack->stack[i] = *element;
	}

	return newstack;
}
int stack_Size_array(st_arr* stack) {
	return stack->top + 1;
}
e stack_Top_array(st_arr* stack) {

	if (stack_Size_array(stack) == 0) {
		emptyStackException();
		return;
	}
	return stack->stack[stack->top];

}
void stack_Push_array(st_arr* stack, e element) {

	if (stack_Size_array(stack) == 100) {
		fullStackException();
		return;
	}
	(stack->top)++;
	stack->stack[stack->top] = element;

}
e stack_Pop_array(st_arr* stack) {

	if (stack_Size_array(stack) == 0) {
		emptyStackException();
		return;
	}
	stack->top = stack->top - 1;
	return stack->stack[stack->top + 1];
}







//HW 3 numbrer1,2 methods
typedef struct number number;
struct number {
	char* status;
	st_li *number;
};

int numberStack_IsEnd_linkedlist(st_li* stack) {
	
	if (stack_IsEmpty_linkedlist(stack)) {
		return 1;
	}

	if (stack_Top_linkedlist(stack).charelem == '-') {
		return 1;
	}

	return 0;
}

st_li* addTwoStacksForHomework(st_li* stack1, st_li* stack2) {

	st_li* stack_result1;
	st_li* stack_result2;
	st_li* stack_result3;

	e* tmpelem;

	char num1_1, num1_2;		//for stack_result 1
	char num2_1, num2_2;	//for stack_result 2
	char num3_1, num3_2;	//for stack_result 3

	int uppercount1 = 0;		//for stack_result 1
	int downercount2 = 0;		//for stack_result 2
	int downercount3 = 0;		//for stack_result 3

	// Needs			|  funciton |	howto	 |
	// A-B > 0			| f() = A-B |			 |
	// A-B < 0			| f() = B-A | result (-) |
	// B-A > 0 (-A + B)	| f() = B-A |            |
	// B-A < 0 (-A + B)	| f() = A-B | result (-) |

	stack_result1 = initStack_linkedlist();
	stack_result2 = initStack_linkedlist();
	stack_result3 = initStack_linkedlist();


	//calculate 1 of 3
	while ((!numberStack_IsEnd_linkedlist(stack1)) && (!numberStack_IsEnd_linkedlist(stack2))) {

		num1_1 = charToInt(stack_Top_linkedlist(stack1).charelem) + charToInt(stack_Top_linkedlist(stack2).charelem);

		num2_1 = charToInt(stack_Top_linkedlist(stack1).charelem);
		num2_2 = charToInt(stack_Top_linkedlist(stack2).charelem);


		num3_1 = charToInt(stack_Pop_linkedlist(stack1).charelem);
		num3_2 = charToInt(stack_Pop_linkedlist(stack2).charelem);


		//making stack_result 1 : + + or - -
		{
			if (uppercount1 == 1) {
				num1_1++;
				uppercount1 = 0;
			}

			if (num1_1 == 10) {
				num1_2 = 0;

				tmpelem = setElement(num1_2, intToChar(num1_2));
				stack_Push_linkedlist(stack_result1, tmpelem);
				uppercount1 = 1;
			}
			else if (num1_1 > 10) {
				num1_2 = num1_1 % 10;

				tmpelem = setElement(num1_2, intToChar(num1_2));
				stack_Push_linkedlist(stack_result1, tmpelem);
				uppercount1 = 1;
			}
			else {
				tmpelem = setElement(num1_1, intToChar(num1_1));
				stack_Push_linkedlist(stack_result1, tmpelem);
			}
		}

		//making stack_result 2 : + -
		{
			int currentnum2 = num2_1 - num2_2;

			if (currentnum2 > 0) {
				if (downercount2 == 1) {
					currentnum2 = currentnum2 - downercount2;
				}
				downercount2 = 0;
			}
			else if (currentnum2 == 0) {
				if (downercount2 == 1) {
					currentnum2 = 9;
					downercount2 = 1;
				}
				//else current number 0, downercount 0
			}
			else {
				if (downercount2 == 1)
					currentnum2 = (10 + currentnum2) - downercount2;
				else
					currentnum2 = (10 + currentnum2);
				downercount2 = 1;
			}
			tmpelem = setElement(currentnum2, intToChar(currentnum2));
			stack_Push_linkedlist(stack_result2, tmpelem);

		}

		
		//making stack_result 3 : - + 
		{
			int currentnum3 = num3_2 - num3_1;

			if (currentnum3 > 0) {
				if (downercount3 == 1) {
					currentnum3 = currentnum3 - downercount3;
				}
				downercount3 = 0;
			}
			else if (currentnum3 == 0) {
				if (downercount3 == 1) {
					currentnum3 = 9;
					downercount3 = 1;
				}
				//else current number 0, downercount 0
			}
			else {
				if (downercount3 == 1)
					currentnum3 = (10 + currentnum3) - downercount3;
				else
					currentnum3 = (10 + currentnum3);
				downercount3 = 1;
			}
			tmpelem = setElement(currentnum3, intToChar(currentnum3));
			stack_Push_linkedlist(stack_result3, tmpelem);

		}
		

	}

	//calculate 2 of 3
	while (numberStack_IsEnd_linkedlist(stack1) && !numberStack_IsEnd_linkedlist(stack2)) {
		num1_1 = charToInt(stack_Top_linkedlist(stack2).charelem);
		num3_1 = charToInt(stack_Pop_linkedlist(stack2).charelem);


		//making stack_result 1 : + + or - -
		{
			if (uppercount1 == 1) {
				num1_1++;
				uppercount1 = 0;
			}

			if (num1_1 == 10) {
				num1_2 = 0;

				tmpelem = setElement(num1_2, intToChar(num1_2));
				stack_Push_linkedlist(stack_result1, tmpelem);
				uppercount1 = 1;
			}
			else {
				tmpelem = setElement(num1_1, intToChar(num1_1));
				stack_Push_linkedlist(stack_result1, tmpelem);
			}
		}

		//making stack_result 2 : + -
		//생각할 필요가 없다.
		//무조건 stack1 < stack2
		downercount2 = 2;


		//making stack_result 3 : - + 
		num3_1 = num3_1 - downercount3;
		if (num2_1 >= 0) {
			downercount3 = 0;
		}
		else {
			10 + num3_1;
			downercount3 = 1;
		}
		tmpelem = setElement(num3_1, intToChar(num3_1));
		stack_Push_linkedlist(stack_result3, tmpelem);


	}

	//calculate 3 of 3
	while (numberStack_IsEnd_linkedlist(stack2) && !numberStack_IsEnd_linkedlist(stack1)) {
		num1_1 = charToInt(stack_Top_linkedlist(stack2).charelem);
		num2_1 = charToInt(stack_Top_linkedlist(stack2).charelem);


		//making stack_result 1 : + + or - -
		{
			if (uppercount1 == 1) {
				num1_1++;
				uppercount1 = 0;
			}

			if (num1_1 == 10) {
				num1_2 = 0;

				tmpelem = setElement(num1_2, intToChar(num1_2));
				stack_Push_linkedlist(stack_result1, tmpelem);
				uppercount1 = 1;
			}
			else {
				tmpelem = setElement(num1_1, intToChar(num1_1));
				stack_Push_linkedlist(stack_result1, tmpelem);
			}
		}

		//making stack_result 2 : + -
		num2_1 = num2_1 - downercount2;
		if (num2_1 >= 0) {
			downercount2 = 0;
		}
		else {
			10 + num2_1;
			downercount2 = 1;
		}
		tmpelem = setElement(num2_1, intToChar(num2_1));
		stack_Push_linkedlist(stack_result2, tmpelem);

		

		//making stack_result 3 : - + 
		//생각할 필요가 없다.
		//무조건 stack1 > stack2
		downercount3 = 2;

	}







	//making stack_result 1 : + + or - -
	if (uppercount1 == 1) {
			tmpelem = setElement(1, '1');
			stack_Push_linkedlist(stack_result1, tmpelem);
			uppercount1--;
	}

	//
	if (downercount2 == 1) {


	}
	//downercount should not control


	//making stack_result 2,3. delete first 0 while not-empty
	if (!stack_IsEmpty_linkedlist(stack_result2)) {
		while (stack_Size_linkedlist(stack_result2) > 1 && stack_Top_linkedlist(stack_result2).charelem == '0') {
			stack_Pop_linkedlist(stack_result2);
		}
	}
	if (!stack_IsEmpty_linkedlist(stack_result3)) {
		while (stack_Size_linkedlist(stack_result3) > 1 && stack_Top_linkedlist(stack_result3).charelem == '0') {
			stack_Pop_linkedlist(stack_result3);
		}
	}





	// + +
	if (stack_IsEmpty_linkedlist(stack1) && stack_IsEmpty_linkedlist(stack2)) {
		stack_delete_linkedlist(stack_result2);
		stack_delete_linkedlist(stack_result3);
		return stack_result1;
	}
	// - -
	else if (!stack_IsEmpty_linkedlist(stack1) && !stack_IsEmpty_linkedlist(stack2)) {

		stack_Pop_linkedlist(stack1);
		tmpelem = setElement(0, '0');
		*tmpelem = stack_Pop_linkedlist(stack2);
		stack_Push_linkedlist(stack_result1, tmpelem);

		stack_delete_linkedlist(stack_result2);
		stack_delete_linkedlist(stack_result3);

		return stack_result1;

	}
	// + - : result 2 or - + : result 3 
	else {
		//A - B
		if (stack_IsEmpty_linkedlist(stack1) && !stack_IsEmpty_linkedlist(stack2)) {
			if (downercount2 > 0) { // A < B
				tmpelem = setElement(0, '-');
				stack_Push_linkedlist(stack_result3, tmpelem);
				return stack_result3;
			}
			if (downercount3 > 0) { // A > B
				return stack_result2;
			}
			return stack_result2;
		}
		//B - A
		else if (!stack_IsEmpty_linkedlist(stack1) && stack_IsEmpty_linkedlist(stack2)) {
			if (downercount2 > 0) { // A < B
				return stack_result3;
			}
			if (downercount3 > 0) { // A > B
				tmpelem = setElement(0, '-');
				stack_Push_linkedlist(stack_result2, tmpelem);
				return stack_result2;
			}
			return stack_result2;
		}
		else {
			stack_delete_linkedlist(stack_result1);
			stack_delete_linkedlist(stack_result2);
			stack_delete_linkedlist(stack_result3);
			printf("error");
			return;
		}
	}
}



int charToInt(char ch) {
	return ch - '0';
}
char intToChar(int a) {
	return a + '0';
}
int isIdenticalForHomework(char ch1, char ch2) {

	if (ch1 == ch2) return 1;
	else if (ch1 >= 'A' && ch1 <= 'Z') {
		if (ch1 + 'a' - 'A' == ch2) return 1;
	}
	else if (ch1 >= 'a' && ch1 <= 'z') {
		if (ch1 - ('a' - 'A') == ch2) return 1;
	}
	else return 0;

	return 0;

}

void fromStack_MoveToFinal_WithPop_ForHomework(st_que* fromstack, st_que* finalstack, st_que* tmpstack) {

	e* element1;
	e* element2;

	while (!stack_IsEmpty_queue(fromstack)) {
		element1 = (e*)malloc(sizeof(e) * 1);
		if (element1 == NULL) {
			printf("function : fromStack_MoveToFinal_WithPop_ForHomeworkr\n");
			return;
		}

		*element1 = stack_Pop_queue(fromstack);

		if (stack_IsEmpty_queue(finalstack)) {
			stack_Push_queue(finalstack, element1);
		}
		else {
			while (element1->charelem > stack_Top_queue(finalstack).charelem) {

				element2 = (e*)malloc(sizeof(e) * 1);
				if (element2 == NULL) {
					printf("function : fromStack_MoveToFinal_WithPop_ForHomeworkr\n");
					return;
				}
				*element2 = stack_Pop_queue(finalstack);
				stack_Push_queue(tmpstack, element2);


				if (stack_IsEmpty_queue(finalstack)) {
					break;
				}
			}
			stack_Push_queue(finalstack, element1);
		}
	}
}


int main() {


	char number_input_by_string_1[102] = { 0 };
	char number_input_by_string_2[102] = { 0 };
	char* cp;
	st_li* number_stack_1; char status1 = '+';
	st_li* number_stack_2; char status2 = '+';
	st_li* number_stack_sum;
	e* element;




	//stack 1
	number_stack_1 = initStack_linkedlist();

	scanf("%s", number_input_by_string_1);
	cp = number_input_by_string_1;
	while (*cp != 0) {

		element = setElement(0, *cp);
		stack_Push_linkedlist(number_stack_1, element);
		if (cp == number_input_by_string_1) {
			if (stack_Top_linkedlist(number_stack_1).charelem == '-') {
				status1 = '-';
			}
		}

#ifdef DEBUG
		stack_print_linkedlist(number_stack_1);
#endif //DEBUG
		cp++;
	}

	//stack 2
	number_stack_2 = initStack_linkedlist();

	scanf("%s", number_input_by_string_2);
	cp = number_input_by_string_2;
	while (*cp != 0) {

		element = setElement(0, *cp);
		stack_Push_linkedlist(number_stack_2, element);
		if (stack_Top_linkedlist(number_stack_2).charelem == '-') {
			status1 = '-';
		}

#ifdef DEBUG
		stack_print_linkedlist(number_stack_2);
#endif //DEBUG
		cp++;

	}

	number_stack_sum = addTwoStacksForHomework(number_stack_1, number_stack_2);
	stack_Popping_inkedlist(number_stack_sum);


	return 0;

}