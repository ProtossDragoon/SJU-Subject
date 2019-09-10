#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define RIGHT 0
#define LEFT 1

typedef struct node nd;
typedef struct tree tr;

struct node {
	nd* parent;
	int intelem;
	char charelem;
	nd* leftchild;
	nd* rightchid;
};
struct tree {
	nd rootnode;
};

nd* getNode() {

	nd* newnode = NULL;
	newnode = (nd*)malloc(sizeof(nd) * 1);
	if (newnode == NULL) return;

	//init them
	newnode->charelem = '0';
	newnode->intelem = 0;
	newnode->parent = NULL;
	newnode->leftchild = NULL;
	newnode->rightchid = NULL;

	return newnode;

}
nd* makeChildNode(nd* node, int left_or_right) {
	
	nd* childnode = NULL;

	childnode = getNode();
	childnode->parent = node;

	if (left_or_right == LEFT) {
		node->leftchild = childnode;
	}
	if (left_or_right == RIGHT) {
		node->rightchid = childnode;
	}

	return childnode;
}
void setElement(nd* node, int intelement) {

	node->intelem = intelement;

}

void visitWithId(nd* node, int current_node_number, nd** savingnode) {
	if (current_node_number == node->intelem) {
		*savingnode = node;
	}
}
void preorderAndId(nd* node, int current_node_number, nd** savingnode) {

	visitWithId(node, current_node_number, savingnode);
	if (isLeftChildExist(node))
		preorderAndId(node->leftchild, current_node_number, savingnode);
	if (isRightChildExist(node))
		preorderAndId(node->rightchid, current_node_number, savingnode);

}
nd* findNodeById(tr* tree, int current_node_number, nd** savingnode) {
	preorderAndId(&(tree->rootnode), current_node_number, savingnode);
	return *savingnode;
}



void preorder(nd* node);
int isLeftChildExist(nd* node);
int isRightChildExist(nd* node);

int main() {


	tr tree;

	int i = 0, j = 0;

	int current_node_number;
	int left_node_number;
	int right_node_number;

	int count_of_node;
	scanf("%d", &count_of_node);
	for (i = 0; i < count_of_node; i++) {
		scanf("%d %d %d", &current_node_number, &left_node_number, &right_node_number);
		if (i == 0) {
			setElement(&(tree.rootnode), current_node_number);
			setElement(makeChildNode(&(tree.rootnode), LEFT), left_node_number);
			setElement(makeChildNode(&(tree.rootnode), RIGHT), right_node_number);
		}
		else {
			nd* savingnode = NULL;
			setElement(makeChildNode(findNodeById(&(tree), current_node_number, &savingnode), LEFT), left_node_number);
			setElement(makeChildNode(findNodeById(&(tree), current_node_number, &savingnode), RIGHT), right_node_number);
		}
	}


	int count_of_order;
	char order[101] = { 0 };
	nd* tmpnode;
	scanf("%d", &count_of_order);
	getchar();
	for (i = 0; i < count_of_order; i++) {
		gets(order);
		tmpnode = &(tree.rootnode);
		printf(" %d", tree.rootnode.intelem);
		for (j = 0; j < strlen(order); j++) {
			if (order[j] == 'L') {
				tmpnode = tmpnode->leftchild;
			}
			else { // R
				tmpnode = tmpnode->rightchid;
			}
			printf(" %d", tmpnode->intelem);
		}
		printf("\n");
	}


	return 0;
}


void visit(nd *node) {
	
	printf("visit! %d", node->intelem);
}

//불완전 이진 트리에서 preorder 이란..
void preorder(nd *node) {

	visit(node);
	if (isLeftChildExist(node))
		preorder(node->leftchild);
	if (isRightChildExist(node))
		preorder(node->rightchid);

}

int isLeftChildExist(nd* node) {
	if (node->leftchild == NULL) {
		return 0;
	}
	else {
		return 1;
	}
}
int isRightChildExist(nd* node) {
	if (node->rightchid == NULL) {
		return 0;
	}
	else {
		return 1;
	}
}

