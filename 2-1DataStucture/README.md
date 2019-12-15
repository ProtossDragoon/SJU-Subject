## example code

### 14주차 : Tree

```C

//***STRUCTURE EXAMPLE***
//tr_nd_bylist*
//tr 	 : This structure is for "TREE" data structure
//nd 	 : This structrue is about "NODE"
//bylist : This structure was implemented "BY (Linked)LIST"

//***FUNCTION EXAMPLE***
//tr_nextNodeByPreorder_byList
//tr	 		: This function is for "TREE" data structure
//nextNodeByPreorder	: This function returns "NEXT NODE" by "PREORDER"
//byList		: This function was implemented "BY (linked)LIST" ADT too.

tr_nd_bylist* tr_nextNodeByPreorder_byList(tr_nd_bylist *node) {

	if (tr_bi_isInternal_byList(node)) {

		if (tr_bi_isLeftChildExist_byList(node)) return tr_bi_leftChild_byList(node);
		else 					 return tr_bi_rightChild_byList(node);
	}	
	
	tr_nd_bylist* tmpnode;
	tmpnode = node->parent;
	if (tmpnode == NULL)return;

	while (1) {
		while (node != tr_bi_leftChild_byList(tmpnode)) {

			if (tr_bi_isRootNode_byList(tmpnode)) {
				//한바퀴 돌아 다시 root node 로 돌아오는 케이스.
				return NULL;
			}
			node = tmpnode;
			tmpnode = tmpnode->parent;
		}
		if (tr_bi_isRightChildExist_byList(tmpnode)) return tr_bi_rightChild_byList(tmpnode);

		node = tmpnode;
		tmpnode = tmpnode->parent;
		if (tmpnode == NULL)return;
	}
}
```

### HW5 : Tree

```C
int tr_bi_findSizeOfSubTree(tr_nd_bylist* node) {
	
	int k = 0;
	return tr_bi_eulerTour_byList(node, &k);
}

int tr_bi_eulerTour_byList(tr_nd_bylist *node, int *k) {


	tr_bi_visitLeft(node, k);
	if (tr_bi_isLeftChildExist_byList(node)) {
		tr_bi_eulerTour_byList(node->children_list->left, k);
	}
	tr_bi_visitBelow(node, k);
	if (tr_bi_isRightChildExist_byList(node)) {
		tr_bi_eulerTour_byList(node->children_list->right, k);
	}
	tr_bi_visitRight(node, k);

	return node->euler_size;
}

int tr_bi_visitLeft(tr_nd_bylist *node, int *k) {
	*k = *k + 1;
	node->euler_left = *k;
}

void tr_bi_visitBelow(tr_nd_bylist *node) {

}

int tr_bi_visitRight(tr_nd_bylist *node, int *k) {
	node->euler_size = *k - node->euler_left + 1;
	return node->euler_size;

}
```
