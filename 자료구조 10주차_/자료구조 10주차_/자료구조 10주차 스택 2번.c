#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct stack stack;
typedef struct node node;
struct node{
	int element;
	node* under;
};
struct stack{
	node* headernode;
	node* trailernode;
	node* top;

	int size;
};


//Methods for Subject 2
char getSymbol(char* cp);
int isOperand(char ch);
int charToInt(char ch);
int doOperator(char oper, int a, int b);
char intToChar(int a);
int unImplementedException();

//Main methods - Stack ADT
stack* __init__();
void push(stack* s, int e);
char pop(stack* s);

//Sub methods - Stack ADT
int top(stack* s);
int size(stack* s);


//Main methods - List ADT
node* getnode();

//Sub methods - List ADT
void deleteFirst_Node(stack* s);
void print(stack* s);

//Errors - Stack ADT
int emptyStackException();
int isEmpty(stack* s);

//Errors - Linked list ADT
int invalidException();




int main(){

	stack* formula = NULL;
	char formula_arr[101] = { 0 };
	char* cp;
	int i, j;
	int formula_length;
	char readed_character;

	int count_of_formula;
	scanf("%d", &count_of_formula); getchar();

	formula = __init__();
	
	for (i = 0; i < count_of_formula; i++) {
		gets(formula_arr);

		formula_length = strlen(formula_arr);
		for (cp = formula_arr; *cp != 0; cp++) {
			readed_character = getSymbol(cp);
			if (isOperand(readed_character)) {
				push(formula, charToInt(readed_character));
			}
			else {
				int a, b;
				b = (pop(formula));
				a = (pop(formula));
				push(formula, (doOperator(readed_character, a, b)));
			}
		}
		printf("formula length : %d\n", formula_length);
		print(formula);
		printf("%d\n", pop(formula));
	}
	return 0;
}

//Methods for Subject 2
char getSymbol(char *cp) {
	return *cp;
}
int isOperand(char ch) {
	if (ch == '+') {
		return 0;
	}
	else if (ch == '-') {
		return 0;
	}
	else if (ch == '/') {
		return 0;
	}
	else if (ch == '*') {
		return 0;
	}
	else return 1;
}
int doOperator(char oper, int a, int b) {
	if (oper == '+') {
		return a + b;
	}
	else if (oper == '-') {
		return a - b;
	}
	else if (oper == '*') {
		return a * b;
	}
	else if (oper == '/') {
		return a / b;
	}
	else {
		unImplementedException();
		return;
	}

}
int charToInt(char ch) {
	//input
	//	char
	//return
	//	number that same meaning with character

	return ch - '0';

}
char intToChar(int a) {
	return a + '0';
}

int unImplementedException() {
	printf("unImplementedException\n");
	return -1;
}

//Main methods - Stack ADT
stack *__init__() {
	//Return new stack pointer

	stack* newstack = NULL;
	
	newstack = (stack*)malloc(sizeof(stack) * 1);
	if (newstack == NULL) {
		printf("error method : init\n");
		return;
	}

	newstack->headernode = (node*)malloc(sizeof(node) * 1);
	if (newstack->headernode == NULL) {
		printf("error method : init\n");
		return;
	}

	newstack->trailernode = (node*)malloc(sizeof(node) * 1);
	if (newstack->trailernode == NULL) {
		printf("error method : init\n");
		return;
	}


	newstack->headernode->under = newstack->trailernode;
	newstack->trailernode->element = 'T';
	newstack->headernode->element = 'H';
	newstack->top = newstack->trailernode;
	newstack->trailernode->under = NULL;
	newstack->size = 0;

	//_____Why "top pointer" points trailer node?
	//At first, "top pointer" points stack's (implemented by stack) "trailer node"
	//If new node come in, "top pointer" points header node's "under" node
	//and if some node delete, "top pointer" points deleting node's "under" node

	return newstack;
}
void push(stack *s, int e) {

	node *np;
	np = getnode();

	np->under = s->headernode->under;
	s->headernode->under = np;
	np->element = e;
	s->top = np;
	(s->size)++;

}
char pop(stack *s) {

	int deleted_element;
	node* current_top;

	if (isEmpty(s)) {
		emptyStackException();
		return;
	}
	current_top = s->top;
	deleted_element = current_top->element;
	s->top = current_top->under;
	
	deleteFirst_Node(s);
	(s->size)--;

	return deleted_element;
}

//Sub methods - Stack ADT
int size(stack *s) {
	return s->size;
}
int top(stack *s) {
	return s->top->element;
}

//Main methods - List ADT
node* getnode() {

	node* np = NULL;
	np = (node*)malloc(sizeof(node) * 1);
	if (np == NULL) {
		printf("error method : getnode\n");
		return;
	}

	return np;

}
void deleteFirst_Node(stack *s) {

	node *np;
	if (isEmpty(s)) {
		emptyStackException();
		return;
	}
	np = s->headernode->under;
	s->headernode->under = np->under;

	free(np);
}

//Sub methods - List ADT
void print(stack *s) {
	
	node* sp;
	int cnt = 0;
	sp = s->headernode;
		printf("header read _____ : %c\n", sp->element);
	sp = sp->under;
	while (sp != s->trailernode) {
		++cnt;
		printf("%d's node read ___ : %d\n", cnt, sp->element);
		sp = sp->under;
	}
	if (isEmpty(s)) printf("Empty stack!!\n");
		printf("trailer read ____ : %c\n", sp->element);

}


//Errors - Stack ADT
int emptyStackException() {
	print("emptyStackException\n");
	return -1;
}
int isEmpty(stack *s) {
	if (s->size == 0) {
		return 1;
	}
	else return 0;
}

//Errors - Linked list ADT
int invalidException() {
	print("invalidException\n");
	return -1;
}

