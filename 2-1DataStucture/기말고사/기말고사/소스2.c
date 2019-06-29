#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct node nd;
typedef struct tree tr;

void addChildsFromArr(char* chararr, char ch, int index, int arrsize, nd* node);


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

int MAX(int a, int b) {

	if (a > b)return a;
	else return b;

}


int height(nd *node) {
	if (isExternal(node)) {
		return 0;
	}
	else {
		int l, r;
		l = height(node->leftChild) + 1;
		r = height(node->rightChild) + 1;
		return MAX(l, r);
	}
}

int isExternal(nd* node) {

	if ((node->leftChild == NULL) && (node->rightChild == NULL)) return 1;
	else return 0;

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

void addRightChild(nd *node, char charelem) {
	node->rightChild = getNode();
	node->rightChild->charelem = charelem;
}
void addLeftChld(nd *node, char charelem) {
	node->leftChild = getNode();
	node->leftChild->charelem = charelem;
}

void changeArrayToTree(char *chararr, int arrsize, tr* tree) {

	tree->rootnode->charelem = chararr[1];
	addChildsFromArr(chararr, chararr[1], 1, arrsize, tree->rootnode);
}

void addChildsFromArr(char *chararr, char ch, int index, int arrsize, nd* node) {

	if (ch == '#' || arrsize < index) {
		return;
	}
	else {
		if (index != 1) {
			if (index % 2 == 0) {
				//Â¦¼ö : Left node
				addLeftChld(node, ch);
				node = node->leftChild;
			}
			else {
				//È¦¼ö : Right node
				addRightChild(node, ch);
				node = node->rightChild;
			}
		}
		addChildsFromArr(chararr, chararr[index * 2], index * 2, arrsize, node);
		addChildsFromArr(chararr, chararr[index * 2 + 1], index * 2 + 1, arrsize, node);
	}


}


nd* inOrder(nd *node) {

	if (!isExternal(node))	inOrder(node->leftChild);
	printf("%c\n", node->charelem);
	if (!isExternal(node))	inOrder(node->rightChild);

}


nd* inOrder_SetID(nd* node, int* k) {

	if (!isExternal(node))	inOrder_SetID(node->leftChild, k);

	*k = *k + 1;
	node->numbering = *k;

	if (!isExternal(node))	inOrder_SetID(node->rightChild, k);

}
void* IOSID(nd* node) {

	int* k;
	k = (int*)malloc(sizeof(int) * 1);
	if (k == NULL)return;
	*k = 0;
	inOrder_SetID(node, k);

	free(k);
}

void IOSID_version2(tr *tree) {

	tree->rootnode->numbering = 1;

	tree->rootnode->leftChild->numbering = 2;
	tree->rootnode->leftChild->leftChild->numbering = 4;

	tree->rootnode->leftChild->rightChild->numbering = 5;
	tree->rootnode->leftChild->rightChild->leftChild->numbering = 10;
	tree->rootnode->leftChild->rightChild->rightChild->numbering = 11;


	tree->rootnode->rightChild->numbering = 3;
	tree->rootnode->rightChild->leftChild->numbering = 6;
	tree->rootnode->rightChild->rightChild->numbering = 1;

}



nd* findNode_byid(nd* node, int id, nd* reminder) {

	if (!isExternal(node))	findNode_byid(node->leftChild, id, reminder);

	if (node->numbering == id) {
		reminder = node;
		return;
	}

	if (!isExternal(node))	findNode_byid(node->rightChild, id, reminder);

}
nd* FNBID(tr* tree, int id) {
	nd* reminder = NULL;
//	reminder = (nd*)malloc(sizeof(nd) * 1);
	findNode_byid(tree->rootnode, id, reminder);
	return reminder;
}




int main() {

	tr* tree;

	tree = initTree();

/*
	int arrsize;
	int n;

	scanf("%d", &arrsize);
	scanf("%d", &n);
	getchar();

	
	char chararr[100];
	char charelem;
	int i;

	for (i = 0; i < arrsize; i++) {
		scanf("%c", &charelem);
		chararr[i+1] = charelem;
		getchar();
	}
*/
	
	char newchararr[12] = {'0', '/', 'x', '+', '2', '-', '3', '1', '#', '#', '7', '1'};


//	changeArrayToTree(chararr, arrsize, tree);

	changeArrayToTree(newchararr, 11, tree);

//	printf("%d\n", height(tree->rootnode));

// inOrder(tree->rootnode);

//	IOSID(tree->rootnode);
	IOSID_version2(tree);

	int idinput;
	nd* tmp;
	scanf("%d", &idinput);
//	printf("%c", FNBID(tree, 2)->charelem);



	tmp = FNBID(tree, idinput);
	if (isExternal(tmp)) {
		printf("%c", tmp->charelem);
	}
	else if (tmp == NULL) {
		printf("N");
	}
	else {
		printf("N");
	}

	return 0;
}