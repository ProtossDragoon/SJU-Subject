//1. List
//2. Queue (by list)
//3. Deque (by list)
//4. Stack (by list)
//5. Stack (by Array)

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

//Que structure
typedef struct Que_linkedlist que_li;
struct Que_linkedlist {
	int no_header_and_trailer;
	li* list;
	nd* front;
	nd* rear;
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
e stack_Top_array(st_arr *stack) {

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






/*
st_li* addTwoStacksForHomework(st_li* stack1, st_li* stack2) {

	st_li* stack_result;
	e* tmpelem;
	char num1, num2;
	int uppercount = 0;

	stack_result = initStack_linkedlist();

	while (!stack_IsEmpty_linkedlist(stack1) && !stack_IsEmpty_linkedlist(stack2)) {
		num1 = charToInt(stack_Pop_linkedlist(stack1).charelem) + charToInt(stack_Pop_linkedlist(stack2).charelem);
		if (uppercount == 1) {
			num1++;
			uppercount = 0;
		}

		if (num1 == 10) {
			num2 = 0;

			tmpelem = setElement(num2, intToChar(num2));
			stack_Push_linkedlist(stack_result, tmpelem);
			uppercount = 1;
		}
		else if (num1 > 10) {
			num2 = num1 % 10;

			tmpelem = setElement(num2, intToChar(num2));
			stack_Push_linkedlist(stack_result, tmpelem);
			uppercount = 1;
		}
		else {
			tmpelem = setElement(num1, intToChar(num1));
			stack_Push_linkedlist(stack_result, tmpelem);
		}
	}

	while (stack_IsEmpty_linkedlist(stack1) && !stack_IsEmpty_linkedlist(stack2)) {
		num1 = charToInt(stack_Pop_linkedlist(stack2).charelem);
		if (uppercount == 1) {
			num1++;
			uppercount = 0;
		}

		if (num1 == 10) {
			num2 = 0;

			tmpelem = setElement(num2, intToChar(num2));
			stack_Push_linkedlist(stack_result, tmpelem);
			uppercount = 1;
		}
		else {
			tmpelem = setElement(num1, intToChar(num1));
			stack_Push_linkedlist(stack_result, tmpelem);
		}
	}

	while (stack_IsEmpty_linkedlist(stack2) && !stack_IsEmpty_linkedlist(stack1)) {
		num1 = charToInt(stack_Pop_linkedlist(stack1).charelem);
		if (uppercount == 1) {
			num1++;
			uppercount = 0;
		}

		if (num1 == 10) {
			num2 = 0;

			tmpelem = setElement(num2, intToChar(num2));
			stack_Push_linkedlist(stack_result, tmpelem);
			uppercount = 1;
		}
		else {
			tmpelem = setElement(num1, intToChar(num1));
			stack_Push_linkedlist(stack_result, tmpelem);
		}
	}

	if (uppercount == 1) {
		tmpelem = setElement(1, '1');
		stack_Push_linkedlist(stack_result, tmpelem);
		uppercount--;
	}


	return stack_result;
}
*/


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



/* Checking Palindrome 
영문으로 된 문자열을 입력받아 문자열이 대소문자 및 공란을 무시하여 Palindrome 인지 아닌지 True/False 로 출력하시오. 
*주의 Stack나 Queue를  활용하지 않으면 0점 처리됨. 
* Stack , Queue 두개 활용 가능함


ABBA => True
aBba => True 
Rats Live on No Evil Star => True 
Smashing Pumkins => False 
Cold Play => False 

재미있는 읽을거리:  Palindrome musician들   http://rateyourmusic.com/list/ssorcd/band_name_palindromes/
더 읽고싶다면,  읽을거리 : https://en.wikipedia.org/wiki/Palindrome */

int main() {



	char input;
	e* element;

	char string[101] = { 0 };
	char *cp = string;

//	st_li* stack;
//	stack = initStack_array();

	que_li* deque;
	deque = initQue_linkedlist(DOUBLE_LINKED_LIST);


	gets(string);
	while (*cp != 0) {
		input = *cp;
		element = setElement(input, input);

		deque_Add_Rear(deque, element);
		cp++;
	}
	
	if (strlen(string) == 1 || strlen(string) == 0) {
		printf("True");
		return 0;
	}

	int cnt = 1;
	while (cnt == 1) {
		cnt = 0;


		//error case : aAbBcC : True
		//error case : aabbcc : True
		//error case : 112233 : False
		if (isIdenticalForHomework(deque_Rear(deque).charelem , deque_Front(deque).charelem)) {
			deque_delete_Front(deque);
			deque_delete_Rear(deque);
			cnt = 1;
		}
		else {
			printf("False");
			return 0;
		}

		if (queSize_linkedlist(deque) == 0 || queSize_linkedlist(deque) == 1) {
			printf("True");
			return 0;
		}
	}

	printf("False");



	return 0;
}