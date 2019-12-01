#include<stdio.h>
#include<stdlib.h>

typedef struct tree tree;
typedef struct treenode treenode;
struct treenode {

	treenode* lchild;
	treenode* rchild;
	treenode* parent;
	int key;
	int height;

};
struct tree {
	treenode* root;
};

treenode* getNode() {

	treenode* newnode = NULL;
	newnode = (treenode*)malloc(sizeof(treenode) * 1);
	if (newnode == NULL) return;
	
	newnode->lchild = NULL;
	newnode->rchild = NULL;
	newnode->parent = NULL;
	newnode->height = 0;
	newnode->key = -1;

	return newnode;

}

int isExternal(treenode* node) {
	if (node->lchild == NULL) return 1;
	else return 0;
}
int isInternal(treenode* node) {
	return !isExternal(node);
}
void expandExternal(treenode* externalnode) {

	externalnode->lchild = getNode();
	externalnode->rchild = getNode();
	externalnode->lchild->parent = externalnode;
	externalnode->rchild->parent = externalnode;
}
int isRoot(treenode* node) {

	if (node->parent == NULL) 
		return 1;
	else return 0;
}


int updateHeight(treenode* innernode) {

	// select child - who has higher height
	treenode* bigger;
	bigger = innernode->lchild;
	if (innernode->rchild->height > bigger->height) {
		bigger = innernode->rchild;
	}

	// if not updated height
	if (innernode->height == (bigger->height + 1)) {
		return 0;
	}
	// updated
	else {
		innernode->height = bigger->height + 1;
		return 1;
	}
}
int isBalanced(treenode* innernode) {

	int lh, rh;
	lh = innernode->lchild->height;
	rh = innernode->rchild->height;

	if (lh - rh <= -2) {
		return 0;
	}
	else if (lh - rh >= 2) {
		return 0;
	}
	else return 1;
}
void setABC(treenode* x, treenode* y, treenode* z, treenode** a, treenode** b, treenode** c) {

	// x, z, y
	// x, y, z
	// z, x, y
	if (x->key > y->key) {

		if (z->key > x->key) { // z, x, y
			*c = z;
			*b = x;
			*a = y;
		}
		else if (z->key > y->key){ // x, z, y
			*c = x;
			*b = z;
			*a = y;
		}
		else { // x, y, z
			*c = x;
			*b = y;
			*a = z;
		}
	}
	// y, x, z
	// y, z, x
	// z, y, x
	else {

		if (z->key > y->key) { // z, y, x
			*c = z;
			*b = y;
			*a = x;
		}
		else if (z->key > x->key) { // y, z, x
			*c = y;
			*b = z;
			*a = x;
		}
		else { // y, x, z
			*c = y;
			*b = x;
			*a = z;
		}
	}

	
}
void setT(treenode* a, treenode* b, treenode* c, treenode** T1, treenode** T2, treenode** T3, treenode** T4) {

	treenode* I[3] = { a, b, c };
	treenode** T[4] = {T1, T2, T3, T4};
	
	treenode* Q[6] = { a->lchild, a->rchild, b->lchild, b->rchild, c->lchild, c->rchild };

	int i, j;
	int index = 0;

	for (i = 0; i < 4; i++) {
		// loop until find rootnode of subtree that is not a, b, c
		for (j = 0; j < 3; j++) {
			if (Q[index] == I[j]) {
				index++;
				j = -1;
			}
		}
		*T[i] = Q[index];
		index++;
	}


}
treenode* restructure(treenode* x, treenode* y, treenode* z) {

	treenode* a = NULL, * b = NULL, * c = NULL;
	treenode* T1 = NULL, * T2 = NULL, * T3 = NULL, * T4 = NULL;
	treenode* parent;



	setABC(x, y, z, &a, &b, &c);
	setT(a, b, c, &T1, &T2, &T3, &T4);


	parent = z->parent;

	
	if (!isRoot(z)) {
		if (parent->lchild == z) {
			parent->lchild = b;
		}
		else {
			parent->rchild = b;
		}
	}

	a->lchild = T1;
	a->rchild = T2;
	T1->parent = a;
	T2->parent = a;
	a->parent = b;
	updateHeight(a);

	c->lchild = T3;
	c->rchild = T4;
	T3->parent = c;
	T4->parent = c;
	c->parent = b;
	updateHeight(c);

	b->lchild = a;
	b->rchild = c;
	b->parent = parent;
	updateHeight(b);
	

	return b;
}
void searchAndFixAfterInsertion(treenode* final_innernode) {

	final_innernode->height++;

	treenode* p, *w;
	treenode* x, *y, *z;

	p = final_innernode->parent;
	w = final_innernode;

	while (!isRoot(w)) {
		if (!isBalanced(p)) {

			z = p;
			y = p->lchild;
			if (p->lchild->height < p->rchild->height) {
				y = p->rchild;
			}

			x = y->lchild;
			if (y->lchild->height < y->rchild->height) {
				x = y->rchild;
			}

			restructure(x, y, z);
			break;
		}
		updateHeight(p);
		w = p;
		p = p->parent;
	}


}

treenode* treeSearch(treenode* root, int key) {

	treenode* node = root;
	
	while (!isExternal(node)) {

		if (node->key < key) {
			node = node->rchild;
		}
		else if (node->key > key) {
			node = node->lchild;
		}
		else {
			return node;
		}
	}

	return node;

}
void insertItem(treenode* root, int key) {
	// interface

	treenode* node;
	node = treeSearch(root, key);

	if (isInternal(node)) {
		// no duplication
	}
	else {
		expandExternal(node);
		node->key = key;
		searchAndFixAfterInsertion(node);
	}
}
void searchItem(treenode* tree, int key) {
	// interface

	treenode* node;
	node = treeSearch(tree, key);

	if (isExternal(node)) {
		printf("X\n");
	}
	else printf("%d\n", node->key);
}



treenode* inOrderSucc(treenode* node) {

	treenode* w;
	if (isInternal(node)) {
		w = node->rchild;
		while (!isExternal(w)) {
			w = w->lchild;
		}
		return w;
	}

	treenode* p;
	p = node->parent;
	while (p->rchild == node) {
		if (isRoot(p)) {
			printf("invalid node exception\n");
			return;
		}
		node = p;
		p = p->parent;
	}
	return p->rchild;
}
treenode* sibling(treenode* node) {
	
	if (isRoot(node)) {
		return;
	}

	treenode* p;
	p = node->parent;

	if (p->lchild == node) {
		return p->rchild;
	}
	else {
		return p->lchild;
	}
}
void searchAndFixAfterRemoval(treenode* innernode) {

	if (innernode == NULL) {
		return;
	}

	treenode* p, * w;
	treenode* x, * y, * z;

	w = innernode;
	p = innernode->parent;

	while (w != NULL) {
		updateHeight(w);
		if (!isBalanced(w)) {

			z = w;
			y = w->lchild;
			if (w->lchild->height < w->rchild->height) {
				y = w->rchild;
			}

			x = y->lchild;
			if (y->lchild->height < y->rchild->height) {
				x = y->rchild;
			}
			if (y->lchild->height == y->rchild->height) {
				if (w->lchild == y) {
					x = y->lchild;
				}
				else {
					x = y->rchild;
				}
			}
			w = restructure(x, y, z);
			updateHeight(w);
		}
		w = w->parent;
	}

}
treenode* reduceExternal(tree *treeroot, treenode* externalnode) {

	treenode* p, *gp;
	treenode* sib;
	p = externalnode->parent;
	sib = sibling(externalnode);	
	
	if (isRoot(p)) {
		sib->parent = NULL;
		treeroot->root = sib;
	}
	else {
		gp = p->parent;
		sib->parent = gp;
		if (p == gp->lchild) {
			gp->lchild = sib;
		}
		else {
			gp->rchild = sib;
		}
	}

	free(externalnode);
	free(p);
	
	return sib;
}
int removeItem(tree *treeroot, int key) {

	treenode* root = treeroot->root;
	treenode* node;
	treenode* ext, *suc;

	node = treeSearch(root, key);
	if (isExternal(node)) {
		printf("X\n");
		return -1;
	}

	int e;
	treenode* sib = NULL;

	e = node->key;
	ext = node->lchild;
	if (!isExternal(ext)) {
		ext = node->rchild;
	}
	if (isExternal(ext)) {
		sib = reduceExternal(treeroot, ext);
	}
	else {
		ext = inOrderSucc(node);
		suc = ext->parent;
		node->key = suc->key;
		sib = reduceExternal(treeroot, ext);
	}

	searchAndFixAfterRemoval(sib->parent);
	printf("%d\n", e);
	return e;
}


void visitForPrint(treenode* root) {
	
	if (isExternal(root)) {
		// external
	}
	else {
		printf(" %d", root->key);
	}
}
void preOrder(treenode* root) {
	
	visitForPrint(root);
	if (isInternal(root)) {
		preOrder(root->lchild);
		preOrder(root->rchild);
	}
}
void printItem(treenode* root) {
	//interface

	preOrder(root);
	printf("\n");
}
void visitForRemove(treenode* node) {

	free(node);
}
void postOrder(treenode* node) {

	if (isInternal(node)) {
		postOrder(node->lchild);
		postOrder(node->rchild);
	}
	visitForRemove(node);
}
void removeTree(treenode* root) {

	postOrder(root);
}





int updateFromLeaf(treenode* final_innernode) {

	treenode* w = final_innernode;
	(w->height)++;

	treenode* p = w->parent;
	treenode* bigger;
	while (!isRoot(w)) {
		
		bigger = p->lchild;
		if (bigger->key < p->rchild->key) {
			bigger = p->rchild;
		}
		p->height = bigger->key;
		
		w = p;
		w = w->parent;
	}

}

treenode* initroot(tree* treeroot) {

	while (!isRoot(treeroot->root)) {
		treeroot->root = treeroot->root->parent;
	}
	return treeroot->root;
}

int main() {

	char input;
	int key;
	tree newtree;
	treenode* root = NULL;
	root = getNode();
	newtree.root = root;

	while (1) {

		scanf("%c", &input);
		newtree.root = initroot(&newtree);

		if (input == 'i') {

			scanf("%d", &key);
			insertItem(newtree.root, key);
		}
		else if (input == 's') {

			scanf("%d", &key);
			searchItem(newtree.root, key);
		}
		else if (input == 'p') {

			printItem(newtree.root);
		}
		else if (input == 'd') {

			scanf("%d", &key);
			removeItem(&newtree, key);
		}
		else { // input == 'q'

			break;
		}
		getchar();
	}

	// free
	removeTree(newtree.root);

	return 0;
}