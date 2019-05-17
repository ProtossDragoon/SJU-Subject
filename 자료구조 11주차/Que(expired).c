#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Que que;
typedef struct Element e;


struct Que {

	e *elem;
	char* elemtype;
};
struct Element {
	//element
	char stringelem[101];
	char *charelem;
	int *intelem;

};




que* initQue(char *elemtype, char *datatype) {

	que *newque = (que*)malloc(sizeof(que) *1 );
	e* newelement = (e*)malloc(sizeof(e) * 1);

	if (newque == NULL) {
		printf("function : initque error\n");
		return;
	}
	

	if (strcmp("string", elemtype) == 0) {
	

#ifdef DEBUG
		printf("element type : string\n");
#endif // DEBUG

	}


	else if (strcmp("int", elemtype) == 0) {


#ifdef DEBUG
		printf("element type : integer\n");
#endif // DEBUG

	}


	else if (strcmp("char", elemtype) == 0) {

#ifdef DEBUG
		printf("element type : character\n");
#endif // DEBUG

	}


	else {
		printf("function : initque error\n");
		return;
	}

	return newque;


}

void enqueue() {



}
