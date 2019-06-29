#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct st {

	char* chararr;
	int top;
	int indexof_maxstack;

}stack;

int isEmpty(stack* S);
int size(stack* S);
char top(stack* S);
void fullStackException();
void emptyStackException();


void push(stack* S, char c);
stack* initStack(stack* S, int n, int top);
char pop(stack* S);
void peek(stack* S);
void duplicate(stack* S);
void upRotate(stack* S, int n);
void downRotate(stack* S, int n);
void print(stack* S);


char getSymbol(char symbol, int* cnt);
int isOpenSymbol(char symbol);
int isCloseSymbol(char symbol);
int isCounterPart(char symbol1, char symbol2);

int main() {

	char string[1001] = { 0 } ;
	char symbol;
	char top_symbol;

	int len;

	stack st1;
	stack* p_st1 = NULL;
	
	int i, j;
	int boolean = 1;
	int cnt = 0;


	//__init__
	p_st1 = initStack(&st1, 1001, -1);


	gets(string);
	len = strlen(string);

	for (i = 0; i < len; i++) {

		symbol = getSymbol(string[i], &cnt);
		if (symbol) {
//			printf("%c", symbol);
			if (isOpenSymbol(symbol)) {
				push(p_st1, symbol);
			}
			if (isCloseSymbol(symbol)) {
				if (isEmpty(p_st1)) boolean = 0;
				else {
					top_symbol = pop(p_st1);

					if (!isCounterPart(top_symbol, symbol)) {
						boolean = 0;
					}
					else {
//						printf("%c -- %c counterpart!\n", top_symbol, symbol);
					}
				}
			}
//			print(p_st1);
		}
	
	}
	if (p_st1->top != -1) boolean = 0;


	if (boolean == 1) {
		printf("OK_");
	}
	else printf("Wrong_");
	printf("%d", cnt);

	return 0;
}


//----methods
//Sub methods
int isEmpty(stack* S) {
	if (S->top == -1) {
		return 1;
	}
	else return 0;
}
int size(stack* S) {
	return (S->top) + 1;
}
char top(stack* S) {
	if (isEmpty(S)) {
		emptyStackException();
	}
	return (S->chararr[S->top]);
}
void fullStackException() {
	printf("Stack FULL\n");
}
void emptyStackException() {
	printf("Stack Empty\n");
}
void invalidException() {
	printf("");
}

//Main methods
stack* initStack(stack* S, int n, int top) {

	S->top = top;
	S->chararr = (char*)malloc(sizeof(char) * n);
	S->indexof_maxstack = n - 1;

	return S;
}
void push(stack* S, char c) {

	(S->top)++;
	if (S->indexof_maxstack < S->top) {
		(S->top)--;
		fullStackException();
		return;
	}
	S->chararr[S->top] = c;

}
char pop(stack* S) {

	if (isEmpty(S)) {
		emptyStackException();
		return;
	}
	(S->top)--;
	return S->chararr[(S->top) + 1];

}
void peek(stack* S) {

	printf("%c\n", top(S));

}
void duplicate(stack* S) {

	char ch;

	ch = pop(S);
	push(S, ch);
	push(S, ch);

}
void print(stack* S) {

	int i;
	i = S->top;
	while (i != -1) {
		printf("%c", S->chararr[i]);
		i--;
	}

	printf("\n");
}

//Unused methods
/*
void downRotate(stack* S, int n) {

	if (S->top < n - 1) {
		invalidException();
		return;
	}
	else {
		int i;
		char tmp;
		for (i = S->top - n + 1; i <= S->top; i++) {
			if (i == S->top - n + 1) tmp = S->chararr[i];
			else if (i == S->top) {
				S->chararr[i - 1] = S->chararr[i];
				S->chararr[i] = tmp;
			}
			else {
				S->chararr[i - 1] = S->chararr[i];
			}
		}
	}

}

void upRotate(stack* S, int n) {

	if (S->top < n - 1) {
		invalidException();
		return;
	}
	else {
		int i;
		char tmp;
		for (i = S->top; i >= S->top - n; i--) {
			if (i == S->top - n) {
				S->chararr[i + 1] = tmp;
			}
			else if (i == S->top) tmp = S->chararr[i];
			else {
				S->chararr[i + 1] = S->chararr[i];
			}
		}
	}

}
*/

//Methods for Subject2
char getSymbol(char symbol, int* cnt) {

	if (symbol == '[' ||
		symbol == '{' ||
		symbol == '(' ||
		symbol == ']' ||
		symbol == '}' ||
		symbol == ')') {
		(*cnt)++;
		return symbol;
	}
	else {
		return 0;
	}

}
int isOpenSymbol(char symbol) {
	if (symbol == '{') {
		return 1;
	}
	if (symbol == '[') {
		return 1;
	}	
	if (symbol == '(') {
		return 1;
	}
	return 0;
}
int isCloseSymbol(char symbol) {
	if (symbol == '}') {
		return 1;
	}
	if (symbol == ']') {
		return 1;
	}
	if (symbol == ')') {
		return 1;
	}
	return 0;
}
int isCounterPart(char symbol1, char symbol2) {
	//symbol1 : open symbol
	//symbol2 : close symbol
	if (symbol1 == '[' && symbol2 == ']') {
		return 1;
	}
	if (symbol1 == '{' && symbol2 == '}') {
		return 1;
	}
	if (symbol1 == '(' && symbol2 == ')') {
		return 1;
	}
	return 0;

}