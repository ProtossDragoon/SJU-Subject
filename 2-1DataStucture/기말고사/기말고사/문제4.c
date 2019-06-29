#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct node nd;
typedef struct tree tr;



struct node {

	nd* parent;
	int numbering;
	int intelem;
	char charelem;
	nd* leftChild;
	nd* rightChild;
};

struct tree {

	nd* rootnode;

};



nd* getNode() {

	nd* newnode;
	newnode = (nd*)malloc(sizeof(nd) * 1);
	if (newnode == NULL) return;

	newnode->parent = NULL;
	newnode->leftChild = NULL;
	newnode->rightChild = NULL;
	newnode->charelem = '~';
	newnode->intelem = -1;
	newnode->numbering = 0;

	return newnode;

}


tr* initTree() {

	tr* newtree;
	newtree = (tr*)malloc(sizeof(tr) * 1);
	if (newtree == NULL) {
		return;
	}

	newtree->rootnode = getNode();

	return newtree;
}






int main() {

	tr* tree;
	int tmp;
	scanf("%d", &tmp);
	tree = initTree();



	return 0;
}