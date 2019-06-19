#include<stdio.h>
#include<stdlib.h>
#include<string.h>


//function original form and structure for...

//0. Linked List
//__0-1. Singly Linked List
//_____0-1-1. No-header & No-trailer
typedef struct node Nd;
struct node {
	E* element;
	Nd* nextnode;
};

typedef struct element E;
struct element {
	int intelem;
	char charelem;
	char* stringelem;
};

//__0-2. Doubly Linked List
typedef struct double_linked_list DLL;
struct double_linked_list {
	Nd* prevnode;
	E* element;
	Nd* nextnode;
};


//1. Stack
//__1-1. Stack with Array
typedef struct stack_by_array St_Arr;
struct stack_by_array {
	E *arr;
	int top;
};


//__1-2. Stack with 0-2 : Singly Linked List

//2. Queue
//__2-1. 



int main() {







	return 0;
}


//function list
Nd* LL_getNode() {

	Nd* newnode;
	
	newnode = (Nd*)malloc(sizeof(Nd) * 1);
	if (newnode == NULL) {
		printf("function : LL_getNode error\n");
	}

	return newnode;

}



//1.Stack
St_Arr* ST_initStack_Arr(int size) {

	St_Arr* arr;

	arr = (St_Arr*)malloc(sizeof(St_Arr) * 1);


	arr->arr = (E*)malloc(sizeof(E) * size);

	
	arr->top = -1;


	return arr;
}