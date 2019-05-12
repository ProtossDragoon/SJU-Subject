#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#define DEBUG
#define SUBMIT
#define SUB1
//#define SUB2

typedef struct stack stack;
typedef struct node node;
typedef struct arrP P;
typedef struct list li;


struct arrP {
	char ope[3];
	int pre;
	int size;
};
struct node {
	int element;
	node* under;
};
struct stack {
	node* headernode;
	node* trailernode;
	node* top;

	int size;
};
struct list {
	node* headernode;
	node* trailernode;
};
//Methods for Subject 1
char* makePostfix(stack* s, char* formula_arr);
void setParr(P* parr, int n);
char* callStringFromChar_andIndexControl(char** cp, char readed_character);
char* callStringFromChar(char readed_character);
int callParrValueFromString(P* parr, char* string, char* formula, char* cp);
int isBinary(char* formula, char* cp);

//Methods for Subject 2
int calculatePostfix(stack* s, char* formula_arr);
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




int main() {

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

#ifdef SUB1
		printf("%s\n", makePostfix(formula, formula_arr));
#endif // SUB1



#ifdef SUB2
		printf("%d\n", calculatePostfix(formula, formula_arr));
#endif // SUB2

	}
	return 0;
}

//Methods for Subject 1
char* makePostfix(stack* s, char* formula_arr) {
	
	int formula_length;
	char* postfix_formula = { 0 };
	postfix_formula = (char*)calloc(101, sizeof(char));
	if (postfix_formula == NULL) {
		printf("postfix_formula malloc error\n");
		return;
	}
	int i = 0;
	char readed_character;
	char* readed_string;
	char* cp;
	P* parr;


	parr = (P*)malloc(sizeof(P) * 12);
	if (parr == NULL) return -1;
	setParr(parr, 12);

	formula_length = strlen(formula_arr);
	for (cp = formula_arr; *cp != 0; cp++) {
		readed_character = getSymbol(cp);
#ifdef DEBUG
printf("read_char : %c\n", readed_character);
#endif // DEBUG

		if (isOperand(readed_character)) {
			//의사코드에서는 write 라고 그냥 바로 print 하라는것같은데
			//string 으로 바꾸려면.. 101짜리 배열을 써서 거기에 저장을 해두거나
			//아니면 연결 리스트를 만들어서 하나씩 뒤에 붙여나가야하는데...
			//일단 배열로 해버리자.
			postfix_formula[i] = readed_character;
			i++;
		}
		else if (readed_character == '(') {
			push(s, readed_character);
		}
		else if (readed_character == ')') {
			while (top(s) != '(') {
				postfix_formula[i] = pop(s);
				i++;
			}
			pop(s);
		}
		else { //If readed_character is operator
			readed_string = callStringFromChar_andIndexControl(&cp, readed_character);

#ifdef DEBUG
printf("string readed : %s\n", readed_string);
#endif //DEBUG


			//Caution!! Parr has type "string"
			int P_value1, P_value2;
			P_value1 = callParrValueFromString(parr, readed_string, formula_arr, cp);
			P_value2 = callParrValueFromString(parr, callStringFromChar(top(s)), formula_arr, cp);

			while ((!isEmpty(s)) && (P_value1 <= P_value2)){

				i = i + strlen(callStringFromChar(top(s)));
				strcat(postfix_formula, callStringFromChar(pop(s)));

#ifdef DEBUG
				printf("s->top : %c\n", top(s), callStringFromChar(top(s)));
				printf("readed Pvalue : %d\n", P_value1);
				printf("Top___ Pvalue : %d\n", P_value2);
#endif // DEBUG

				P_value1 = callParrValueFromString(parr, readed_string, formula_arr, cp);
				P_value2 = callParrValueFromString(parr, callStringFromChar(top(s)), formula_arr, cp);

			}
			
			//Stack save "||" as '|'
			push(s, readed_character);
		}
#ifdef DEBUG
print(s);
printf("%s\n", postfix_formula);
printf("_________________\n");
#endif
	}

	while (!isEmpty(s)) {
		strcat(postfix_formula, callStringFromChar(pop(s)));
	}


	return postfix_formula;
}
void setParr(P* parr, int n) {

	strcpy(&(parr[0].ope[0]), "||");parr[0].pre = 1;
	strcpy(&(parr[1].ope[0]), "&&");parr[1].pre = 2;
	strcpy(&(parr[2].ope[0]), "<"); parr[2].pre = 3;
	strcpy(&(parr[3].ope[0]), ">"); parr[3].pre = 3;
	strcpy(&(parr[4].ope[0]), "-"); parr[4].pre = 4;
	strcpy(&(parr[5].ope[0]), "+"); parr[5].pre = 4;
	strcpy(&(parr[6].ope[0]), "/"); parr[6].pre = 5;
	strcpy(&(parr[7].ope[0]), "*"); parr[7].pre = 5;
	strcpy(&(parr[8].ope[0]), "!"); parr[8].pre = 6;
	strcpy(&(parr[9].ope[0]), "+"); parr[9].pre = 6;
	strcpy(&(parr[10].ope[0]), "-");parr[10].pre = 6;
	strcpy(&(parr[11].ope[0]), "(");parr[11].pre = 0;

	parr->size = n;

}
char* callStringFromChar_andIndexControl(char** cp, char readed_character) {
	//Automatically control character pointer (in for loop) 
	char *readed_string;
	readed_string = (char*)calloc(3, sizeof(char));
	if (readed_string == NULL) {
		printf("method : callStringFromChar_andIndexControl");
		return;
	}
	if (readed_character == '|') {
		(*cp)++;
		strcpy(readed_string, "||");
	}
	else if (readed_character == '&') {
		(*cp)++;
		strcpy(readed_string, "&&");
	}
	else {
		readed_string[0] = readed_character;
	}

	return readed_string;
}
char* callStringFromChar(char readed_character) {
	char* readed_string;
	readed_string = (char*)calloc(3, sizeof(char));
	if (readed_string == NULL) {
		printf("method : callStringFromChar");
		return;
	}	
	if (readed_character == '|') {
		strcpy(readed_string, "||");
	}
	else if (readed_character == '&') {
		strcpy(readed_string, "&&");
	}
	else {
		readed_string[0] = readed_character;
	}
	return readed_string;
}
int callParrValueFromString(P* parr, char* string, char *formula, char *cp) {
	//Use character pointer (in for loop) to make a decision about binary / arithmetic 
	int i, j, k;
	for (i = 0; i < parr->size; i++) {
		if (!strcmp(parr[i].ope, string)) {
			if (!strcmp("-", string)) {			// '-' can be binary operator 
				if (!isBinary(formula, cp)) {
					return parr[i].pre;
				}
				else return parr[i].pre;
			}
			else if (!strcmp("+", string)) {	// '+' can be binary operator too
				if (isBinary(formula, cp)) {
					return parr[i].pre;
				}
				else return parr[i].pre;
			}
			else {
				return parr[i].pre;
			}
		}
	}
}
int isBinary(char *formula, char *cp) {
	
	//case : (binary)(number) "-"3 + 6
	
	//case : (binary)(binary)(binary)... : 5 "+(+(-(+(-"3)))
	//이런 변태같은 경우는 없고..
	//5 __ 연산쟈 __ 부호 __ 숫자
	//내가 위치하고 잇는 곳 앞 방향에 있는 가장 가까운 피연산자에 포인터 두고
	//	만약 내가 위치하고 있는 곳 앞 방향에 가장 가까운 피연산자가 없다면.. 그냥 바로 binary 라고 판단.
	//그 포인터부터 하나씩 넘어가면서 다음에 연산자가 나왔는지 점검하는것이 최선일듯?

	char* tmp_cp = cp;
	int i;
	char *i_cp;
	int cnt = 0;
	char passlist[11] = { '|', '&', '<', '>', '+', '-', '/', '*', '!', '(', ')' };
	while (tmp_cp != formula) {
		for (i = 0 ; i < 10 ; i ++ )
			if (*tmp_cp == passlist[i]) {
				cnt = 1;
				tmp_cp--;
				break;
			}
		if (cnt == 0) break;
		cnt = 0;
	}
	
	if (tmp_cp == formula)
		return 1; //Binary

	for (i_cp = tmp_cp; i_cp < cp; i_cp++) {
		for (i = 0; i < 9; i++) {
			if (*i_cp == passlist[i]) return 1;
		}
	}

	if (i_cp == cp)
		return 0; //Arithmetic
}


//Methods for Subject 2
int calculatePostfix(stack *s, char *formula_arr) {

	int formula_length;
	char readed_character;
	char* cp;
	int answer;

	formula_length = strlen(formula_arr);
	for (cp = formula_arr; *cp != 0; cp++) {
		readed_character = getSymbol(cp);
		if (isOperand(readed_character)) {
			push(s, charToInt(readed_character));
		}
		else {
			int a, b;
			b = (pop(s));
			a = (pop(s));
			push(s, (doOperator(readed_character, a, b)));
		}
	}
#ifdef DEBUG
	printf("formula length : %d\n", formula_length);
	print(s);
#endif // DEBUG
	answer = pop(s);
	return answer;
}

char getSymbol(char* cp) {
	return *cp;
}
int isOperand(char ch) {

	char oper_list[2] = { '<', '>' };
	int i;
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
	else if (ch == '(') {
		return 0;
	}
	else if (ch == ')') {
		return 0;
	}
	else if (ch == '&') {
		return 0;
	}
	else if (ch == '|') {
		return 0;
	}
	else if (ch == '!') {
		return 0;
	}
	else {
		for (i = 0; i < 2; i++) {
			if (oper_list[i] == ch) return 0;
		}
		return 1;
	}
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
stack* __init__() {
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
void push(stack* s, int e) {

	node* np;
	np = getnode();

	np->under = s->headernode->under;
	s->headernode->under = np;
	np->element = e;
	s->top = np;
	(s->size)++;

}
char pop(stack* s) {

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
int size(stack* s) {
	return s->size;
}
int top(stack* s) {
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
void deleteFirst_Node(stack* s) {

	node* np;
	if (isEmpty(s)) {
		emptyStackException();
		return;
	}
	np = s->headernode->under;
	s->headernode->under = np->under;

	free(np);
}

//Sub methods - List ADT
void print(stack* s) {

	node* sp;
	int cnt = 0;
	sp = s->headernode;
	printf("header read _____ : %c\n", sp->element);
	sp = sp->under;
	while (sp != s->trailernode) {
		++cnt;
		printf("%d's node read ___ : %c\n", cnt, sp->element);
		sp = sp->under;
	}
	if (isEmpty(s)) printf("Empty stack!!\n");
	printf("trailer read ____ : %c\n", sp->element);

}


//Errors - Stack ADT
int emptyStackException() {
	printf("emptyStackException\n");
	return -1;
}
int isEmpty(stack* s) {
	if (s->size == 0) {
		return 1;
	}
	else return 0;
}

//Errors - Linked list ADT
int invalidException() {
	printf("invalidException\n");
	return -1;
}

