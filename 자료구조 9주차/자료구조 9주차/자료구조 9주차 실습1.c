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

void ______downRotate(stack* S, int n);
void hanoiWithStacks(stack* mainstack, stack* substack, stack* gotostack, int n);


int main() {

	stack st1;
	stack* p_st1 = NULL;

	int n;
	int count_of_function;
	int i;
	char inputstring[10] = { 0 };
	char inputchar;
	int inputnum;

	scanf("%d%d", &n, &count_of_function);
	p_st1 = initStack(&st1, n, -1);

	for (i = 0; i < count_of_function; i++) {
		
		scanf("%s", inputstring);
//		printf("%s\n", inputstring);
		getchar();

		if (strcmp(inputstring, "POP") == 0) {
			pop(p_st1);
		}
		else if (strcmp(inputstring, "PUSH") == 0) {
			scanf("%c", &inputchar);
			push(p_st1, inputchar);
		}
		else if (strcmp(inputstring, "PEEK") == 0) {
			peek(p_st1);
		}
		else if (strcmp(inputstring, "DUP") == 0) {
			duplicate(p_st1);
		}
		else if (strcmp(inputstring, "UpR") == 0) {
			scanf("%d", &inputnum);
			upRotate(p_st1, inputnum);
		}
		else if (strcmp(inputstring, "DownR") == 0) {
			scanf("%d", &inputnum);
			downRotate(p_st1, inputnum);
		}
		else if (strcmp(inputstring, "PRINT") == 0) {
			print(p_st1);
		}
		else {
			break;
		}
//		print(p_st1);
	}



	return 0;
}

//----methods
//Sub methods
int isEmpty(stack *S) {
	if (S->top == -1) {
		return 1;
	}
	else return 0;
}
int size(stack *S) {
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
void ______downRotate(stack *S , int n) {

	if (S->top < n - 1) {
		invalidException();
		return;
	}
	else {
		int i;
		char tmp;
		for (i = S->top - n + 1 ; i <= S-> top ; i++) {
			if (i == S->top - n + 1) tmp = S->chararr[i];
			else if (i == S->top) {
				S->chararr[i - 1] = S->chararr[i];
				S->chararr[i] = tmp;
			}
			else {
				S->chararr[i-1] = S->chararr[i];
			}
		}
	}

}


void upRotate(stack *S, int n) {
	
	if (S->top < n - 1) {
		invalidException();
		return;
	}
	else {
		int i;
		char tmp;

		//___________make a new tmp stack , initialize_____________//
		stack tmpstack;
		tmpstack.chararr = (char*)malloc(sizeof(char) * n);
		if (tmpstack.chararr == NULL) return -1;
		initStack(&tmpstack, n, -1);

		//_______get elements from top and save to tmpstack________//
		tmp = pop(S); //elem1
		for (i = 0; i < n - 1; i++) {
			push(&tmpstack, pop(S));
		}
		push(&tmpstack, tmp);

		//_______from : tmpstack, to : mainstack, and free_________//
		for (i = 0; i < n; i++) {
			push(S, pop(&tmpstack));
		}
		free(tmpstack.chararr);
	}

}
void downRotate(stack* S, int n) {
	if (S->top < n - 1) {
		invalidException();
		return;
	}
	else {
		int i;
		char tmp;

		//___________make a new tmp stack , initialize_____________//
		//Hanoi...?

		stack substack1;
		stack substack2;

		substack1.chararr = (char*)malloc(sizeof(char) * n);
		if (substack1.chararr == NULL) return -1;
		initStack(&substack1, n, -1);
		substack2.chararr = (char*)malloc(sizeof(char) * n);
		if (substack2.chararr == NULL) return -1;
		initStack(&substack2, n, -1);


		//________n번째 스택 가져가기위해 n-1번째까지의 스택을 보조스택1로 옮긴다._______//
		hanoiWithStacks(S, &substack2, &substack1, n-1);

		//________n번째 스택을 가져간다. == 밑장빼기________//
		tmp = pop(S);
		
		//________보조스택1로 옮겨두었던 스택들을 다시 메인 스택으로 옮긴다.________//
		hanoiWithStacks(&substack1, &substack2, S, n - 1);
		push(S, tmp); //밑장뺀거 얹어주기.
	
	}

}


void hanoiWithStacks(stack *mainstack, stack *substack, stack *gotostack, int n) {
		
	if (n == 2) {
		push(substack, pop(mainstack));
		push(gotostack, pop(mainstack));
		push(gotostack, pop(substack));
	}
	else {
		hanoiWithStacks(mainstack, gotostack, substack, n - 1);
		push(gotostack, pop(mainstack));
		hanoiWithStacks(substack, mainstack, gotostack, n - 1);
	}
	
	printf("clear\n");

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

