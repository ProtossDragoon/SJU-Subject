#ifndef BASIC_HEADER
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#endif // !BASIC_HEADER



#ifndef STRUCTURE
typedef struct element e;
struct element {
	char charelem;
	int intelem;
	char* string;
};

typedef struct node nd;
struct node{
	nd * prev_node;
	e* element;
	nd* next_node;
};
#endif // !STRUCTURE


#ifndef LINKEDLIST
typedef struct linkedlist li;
struct linkedlist{
	int size_of_list;
	nd* header;
	nd* trailer;
	int single_or_double;
	int header_and_trailer;
};
#endif // !LINKEDLIST



//지난번에 하다 보니까, 구조체 이름이랑 함수 이름을 계속 존나 까먹음
//그러지 않도록 standard 를 정해놓고 해야겠다 싶었음.
//[자료구조]_____[자료구조의 부품]______[어떤 자료구조로 구현했는지]
#ifndef TREE
#define BINARY 1
typedef struct tree_______bylist		 tr____bylist;
typedef struct tree_node__bylist		 tr_nd_bylist;
typedef struct tree_binarylist__bylist	 tr_bili_bylist;

struct tree_______bylist {
	tr_nd_bylist* rootnode;
};
struct tree_node__bylist {
	tr_nd_bylist* parent;
	e* element;
	tr_bili_bylist* children_list;
};
struct tree_binarylist__bylist {
	tr_nd_bylist* left;
	tr_nd_bylist* right;
	int treetype_isbinary;
};
#endif // !TREE



//funciton original form
tr_bili_bylist* tr_initBinaryList_byList(int isbinary);
tr_nd_bylist* tr_parent_byList(tr_nd_bylist* node);
int	int_Max(int a, int b) {
	if (a > b) {
		return a;
	}
	else return b;
}


//패치 : element 포인터를 input 으로 받아야겠음.
//그렇지 않으면 element가 free가 안된채로 막 돌아다님.
e*				readyElement() {
	e* element;
	element = (e*)malloc(sizeof(e) * 1);
	return element;
}
e				readySetElement(e* elem, int intinput, char charinput) {

	(elem->intelem) = intinput;
	(elem->charelem) = charinput;

	return *elem;
}
e				readySetElement_string(e* elem, char* string) {

	char* cp = string;
	int string_length = 0;
	while (*cp != 0) {
		string_length++;
		cp++;
	}
	elem->string = (char*)malloc(sizeof(char) * string_length + 1);
	strcpy((elem->string), string);
	return *elem;

}


//function reading example : tr_bi_isExternal_byList
//tr_			: Data Structure - Tree ADT
//bi_			: Tree ADT, only for binary tree
//isExternal_	: function name
//byList		: implemented with Linked List
tr_nd_bylist*	tr_getNode_bylist(int isbinary) {

	tr_nd_bylist* newnode;
	newnode = (tr_nd_bylist*)malloc(sizeof(tr_nd_bylist) * 1);
	if (newnode == NULL) {
		printf("funciton : tr_getNode_bylist error\n");
		return;
	}

	newnode->children_list = tr_initBinaryList_byList(isbinary);

	newnode->element = readyElement();
	*(newnode->element) = readySetElement(newnode->element, -1, '1');
	newnode->parent = NULL;

	return newnode;

}
tr_nd_bylist*	tr_initRoot_byList(int isbinary) {

	tr_nd_bylist* newrootnode;
	tr____bylist* newroot;

	newroot = (tr____bylist*)malloc(sizeof(tr____bylist) * 1);
	if (newroot == NULL) {
		printf("function : tr_initRoot_byList error");
		return;
	}

	newrootnode = tr_getNode_bylist(isbinary);

	//init list first!
	
	readySetElement(newrootnode->element, 0, '0');
	newroot->rootnode = newrootnode;

	return newroot;
}
tr_bili_bylist* tr_initBinaryList_byList(int isbinary) {

	tr_bili_bylist* newlist;
	newlist = (tr_bili_bylist*)malloc(sizeof(tr_bili_bylist) * 1);
	if (newlist == NULL) {
		printf("function : tr_initList_byList error\n");
		return;
	}
	newlist->treetype_isbinary = isbinary;
	newlist->left = NULL;
	newlist->right = NULL;

	return newlist;
}
e				tr_element_byList(tr_nd_bylist *node) {
	return *(node->element);
}
tr_nd_bylist*	tr_root_byList(tr_nd_bylist *node) {
	if (tr_parent_byList(node) == NULL) {
		return node;
	}
	else {
		tr_nd_bylist* tmp_parent_node;
		tmp_parent_node = node->parent;
		while (tr_parent_byList(tmp_parent_node) == NULL ) {
			tmp_parent_node = tr_parent_byList(tmp_parent_node);
		}
		return tmp_parent_node;
	}
}
tr_nd_bylist*	tr_parent_byList(tr_nd_bylist *node) {
	return node->parent;
}
tr_nd_bylist*	tr_bi_leftChild_byList(tr_nd_bylist *node) {
	return node->children_list->left;
}
tr_nd_bylist*	tr_bi_rightChild_byList(tr_nd_bylist *node) {
	return node->children_list->right;
}
tr_nd_bylist*	tr_bi_anotherSibling_byList(tr_nd_bylist* node) {
	tr_nd_bylist* current_node, * tmp_parent_node;
	current_node = node;
	tmp_parent_node = tr_parent_byList(node);

	if (tr_bi_leftChild_byList(tmp_parent_node) == current_node)
		return tr_bi_rightChild_byList(tmp_parent_node);
	else 
		return tr_bi_leftChild_byList(tmp_parent_node);

}

tr_nd_bylist*	tr_bi_addNodeRightChild(tr_nd_bylist* node) {
	tr_nd_bylist* newnode;
	newnode = tr_getNode_bylist(BINARY);
	node->children_list->right = newnode;
	return newnode;
}
tr_nd_bylist*	tr_bi_addNodeLeftChild(tr_nd_bylist* node) {
	tr_nd_bylist* newnode;
	newnode = tr_getNode_bylist(BINARY);
	node->children_list->left = newnode;
	return newnode;
}


int				tr_bi_size_byList(tr_nd_bylist *node) {

}
int				tr_dept_byList(tr_nd_bylist *node) {
	if (tr_isRoot_byList(node)) {
		return 0;
	}
	else {
		return 1 + tr_dept_byList(tr_parent_byList(node));
	}
}	 
int				tr_bi_height_byList(tr_nd_bylist* node) {
	if (tr_bi_isExternal_byList(node)) {
		return 0;
	}
	else {
		tr_nd_bylist* tmp1, * tmp2;
		int height = 0;

		height = int_Max(height, tr_bi_size_byList(tr_bi_leftChild_byList(node))),
		height = int_Max(height, tr_bi_size_byList(tr_bi_rightChild_byList(node)));

		return 1 + height;
	}

}



int				tr_isRoot_byList(tr_nd_bylist *node) {
	if (tr_root_byList(node) == node) {
		return 1;
	}
	else {
		return 0;
	}
}
int				tr_bi_isInternal_byList(tr_nd_bylist *node) {
	if (tr_bi_leftChild_byList(node) == NULL
		&&
		tr_bi_rightChild_byList(node) == NULL) {
		return 0;
	}
	return 1;
}
int				tr_bi_isExternal_byList(tr_nd_bylist *node) {
	if (tr_bi_leftChild_byList(node) == NULL
		&&
		tr_bi_rightChild_byList(node) == NULL) {
		return 1;
	}
	return 0;
}
void			tr_readySetElement_byList(tr_nd_bylist *node, e element) {
	*(node->element) = element;
}
void			tr_swapElement_byList(tr_nd_bylist *v, tr_nd_bylist *w) {
	e* tmp;
	tmp = v->element;
	v->element = w->element;
	w->element = tmp;
}




int main() {


	tr____bylist* root;
	tr____bylist* tmp;
	e* element;

	element = readyElement();

	//F1
	root = tr_initRoot_byList(BINARY);
	*element = readySetElement(element, 20, '1');
	tr_readySetElement_byList(root->rootnode, *element);


	//F2
	tmp = tr_bi_addNodeLeftChild(root->rootnode);
	*element = readySetElement(element, 30, '2');
	tr_readySetElement_byList(tmp, *element);
	//	F4
		tmp = tr_bi_addNodeLeftChild(root->rootnode->children_list->left);
		*element = readySetElement(element, 70, '4');
		tr_readySetElement_byList(tmp, *element);
	//	F5
		tmp = tr_bi_addNodeLeftChild(root->rootnode->children_list->left);
		*element = readySetElement(element, 90, '5');
		tr_readySetElement_byList(tmp, *element);


	//F3
	tmp = tr_bi_addNodeRightChild(root->rootnode);
	*element = readySetElement(element, 50, '3');
	tr_readySetElement_byList(tmp, *element);
	//	F6
		tmp = tr_bi_addNodeRightChild(root->rootnode->children_list->right);
		*element = readySetElement(element, 120, '6');
		tr_readySetElement_byList(tmp, *element);
	//		F7
			tmp = tr_bi_addNodeLeftChild(root->rootnode->children_list->right->children_list->right);
			*element = readySetElement(element, 130, '7');
			tr_readySetElement_byList(tmp, *element);
	//		F8
			tmp = tr_bi_addNodeRightChild(root->rootnode->children_list->right->children_list->right);
			*element = readySetElement(element, 80, '8');
			tr_readySetElement_byList(tmp, *element);

	return 0;
}