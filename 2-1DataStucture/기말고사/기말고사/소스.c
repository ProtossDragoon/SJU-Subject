#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//¹®Á¦ 1.
typedef struct stack {
	int arr[100];
	int top;
}st;

void emptyStackException();
void fullStackException();
void printStackDistructive(st* stack);

st* initStack() {

	st* newstack = NULL;
	newstack = (st*)malloc(sizeof(st) * 1);
	if (newstack == NULL) {
		return;
	}

	newstack->top = -1;
	return newstack;
}
void push(st* stack, int elem) {

	if (stack->top == 99) {
		fullStackException();
	}

	stack->top = (stack->top) + 1;
	(stack->arr)[stack->top] = elem;

}
int pop(st* stack) {

	if (stack->top == -1) {
		emptyStackException();
		return;
	}

	stack->top = (stack->top) - 1;
	return (stack->arr)[stack->top + 1];

}
void emptyStackException() {	
	printf("emptystackexception");
}
void fullStackException() {
	printf("fullStackException");
}

st* pushNumberToStack(st *stack, int n) {

	while (n != 0) {
		push(stack, n % 10);
		n = n / 10;	
	}

	return stack;
}
st* pushStackToStack(st* stack) {

	st* newstack;
	newstack = initStack();

	while (stack->top != -1) {
		push(newstack, pop(stack));
	}

	while ((newstack->arr[newstack->top]) == 0) {
		pop(newstack);
	}
	
	printStackDistructive(newstack);
	return newstack;

}

void printStackDistructive(st *stack) {

	int t;
	while (stack->top != -1) {
		t = pop(stack);
		printf("%d", t);
	}
}




int main() {

	st* stack;
	
	stack = initStack();

	int n;
	scanf("%d", &n);

	pushNumberToStack(stack, n);
	pushStackToStack(stack);


	return 0;
}

