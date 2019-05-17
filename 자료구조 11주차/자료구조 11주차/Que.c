#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct list li;
typedef struct node nd;
typedef struct elem e;
typedef struct Que_linkedlist que_li;

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

struct Que_linkedlist {
	int no_header_and_trailer;
	li* list;
	nd* front;
	nd* rear;
};


