#include<stdio.h>
#include<stdlib.h>

//연결 리스트
typedef struct ll ll;
typedef struct node_ll node_ll;
struct ll {
	node_ll* header;
	node_ll* trailer;
	int size;
};
struct node_ll{
	int key;
	node_ll* next;
	node_ll* prev;
};
node_ll* getNode() {

	node_ll* newnode = NULL;
	newnode = (node_ll*)malloc(sizeof(node_ll) * 1);
	if (newnode == NULL) return;
	newnode->key = -1;
	newnode->next = NULL;
	newnode->prev = NULL;
	return newnode;
}
void putList(ll * list) {
	
	node_ll* np = NULL;
	np = list->trailer->prev;

	while (np != list->header) {
		np = np->prev;
		free(np->next);
	}

	free(list->trailer);
	free(list->header);
	free(list);

}
ll* getLinkedList() {

	ll* newlist = NULL;
	newlist = (ll*)malloc(sizeof(ll) * 1);
	if (newlist == NULL) return;

	newlist->header = getNode();
	newlist->trailer = getNode();
	newlist->header->next = newlist->trailer;
	newlist->trailer->prev = newlist->header;
	newlist->size = 0;

	return newlist;

}
void addLast(ll* list, int key) {

	node_ll *np1 = NULL, *np2 = NULL;
	np1 = list->trailer->prev;
	np2 = list->trailer;

	node_ll* newnode = NULL;
	newnode = getNode();
	newnode->key = key;
	
	np1->next = newnode;
	np2->prev = newnode;
	newnode->prev = np1;
	newnode->next = np2;
	list->size++;
}
void printList(ll* list) {

	node_ll* np;
	np = list->header->next;

	while (np != list->trailer) {
		printf(" %d", np->key);
		np = np->next;
	}
	printf("\n");

}
node_ll* select_nIndex_node(ll *list, int index) {

	node_ll* np;
	np = list->header->next;

	int i;
	for (i = 0; i < index; i++) {
		if (np == list->trailer) {
			printf("invalidNodeException\n");
			return;
		}
		np = np->next;
	}


	return np;
}

//이진 트리
typedef struct node_tr node_tr;
struct node_tr {
	node_tr* parent;
	int key;
	node_tr* leftchild;
	node_tr* rightchild;
};


//우선순위 큐 (선택 정렬, 삽입 정렬)
void swapelement(int *arr, int index1, int index2) {

	int tmp;
	tmp = arr[index1];
	arr[index1] = arr[index2];
	arr[index2] = tmp;

}
int* insertionSort_inplace(int *arr, int size) {
	
	int i;
	int save;
	int j;
	int loc;

	for (i = 1; i < size; i++) {
		save = arr[i];
		loc = i;
		for (j = i - 1; j >= 0; j--) {
			if (save < arr[j]) {
				arr[j + 1] = arr[j];
				loc = j;
			}
		}
		arr[loc] = save;
	}

	return arr;
}
int* selectionSort_inplace(int *arr, int size) {

	int pass;
	int i;
	int changable;
	int loc;

	for (pass = 0; pass < size - 1; pass++) {
		loc = pass;
		for (i = pass + 1; i < size; i++) {
			if (arr[loc] > arr[i]) {
				loc = i;				
			}
		}
		swapelement(arr, loc, pass);
	}

	return arr;
}

//힙
//--시도해보지 않은것 : 연결힙, 최종노드 등...
//--상향식힙 연결힙으로 짜기
int heapsize_2 = 0;
int heap_2[100];
void printarrayheap(int *arr, int heapsize) {

	int i;
	for (i = 1; i <= heapsize; i++) {
		printf(" %d", arr[i]);
	}
	printf("\n");
}
void upheap(int *heap, int index) {

	if (index == 1) return;

	if (heap[index] > heap[index / 2]) {
		swapelement(heap, index, index / 2);
		upheap(heap, index / 2);
	}

}
void insertItem(int* arr, int input) {

	if (heapsize_2 == 100) {
		printf("fullHeapException\n");
		return;
	}

	heap_2[heapsize_2 + 1] = input; //insert
	upheap(arr, heapsize_2 + 1); //upheap
	
	heapsize_2++;

}
void downheap(int *arr, int index) {

	int left = index * 2;
	int right = index * 2 + 1;

	if (left > heapsize_2) {
		return;
	}

	int bigger_index;
	bigger_index = left;
	if (right <= heapsize_2 && arr[bigger_index] < arr[right]) 
		bigger_index = right;

	if (arr[bigger_index] > arr[index]) {
		swapelement(arr, bigger_index, index);
		downheap(arr, bigger_index);
	}

}
void inplaceSort(int* heap, int heapsize) {
	
	while (heapsize != 0) {
		heap[heapsize] = removeFirst(heap, heapsize);
		heapsize--;
	}
}
int removeFirst(int* heap, int heapsize) {

	if (heapsize == 0) {
		printf("EmptyheapException\n");
		return;
	}

	int returnelement = heap[1];
	heap[1] = heap[heapsize];

	downheap(heap, 1);

	heapsize_2--;
	return returnelement;
}
void buildUpperHeap(int *fullheap, int heapsize) {

	int i;
	for (i = heapsize / 2; i >= 1; i--) {
		downheap(heap_2, i);
	}

}

//합병 정렬
void merge() {


}
ll** partition(ll *list, int size) {

	if (size <= 1) {

	}

	//make two lists
	ll** lists = NULL;
	lists = (ll**)malloc(sizeof(ll*) * 2);
	if (lists == NULL) return;
	
	lists[0] = (ll*)malloc(sizeof(ll) * 1);
	lists[1] = (ll*)malloc(sizeof(ll) * 1);
	if (lists[0] == NULL)return;
	if (lists[1] == NULL)return;

	lists[0] = getLinkedList();
	lists[1] = getLinkedList();
	
	//list.size control
	int partitionsize = size / 2;



	//lists
	return lists;
}
void mergeSort(ll *list) {
	
	int size;
	size = list->size;
	//partition
	//merge

}



//퀵 정렬
//


//순서 사전 (이진탐색 재귀버전, 이진탐색 비재귀버전)
//--시도해보지 않은 것 : 교차 선분, 단일모드 배열의 최대원소, 배열의 두 수 덧셈, k번째 작은 key
#define num2
int binarySearch(int* arr, int key, int left, int right) {

#ifdef num1
	if (right < left) {
		return right;
	}
#endif // num1

#ifdef num2
	if (right < left) {
		return left;
	}
#endif // num2


	int mid = (left + right) / 2;

	if (arr[mid] < key) {
		binarySearch(arr, key, mid + 1, right);
	}
	else if (arr[mid] > key) {
		binarySearch(arr, key, left, mid - 1);
	}
	else return mid;

}
int findElement(int *arr, int key, int size) {

	int index;
	
	index = binarySearch(arr, key, 0, size - 1);

	return index;
}



//탐색 트리
//--시도해보지 않은 것 : 중복 키를 가진 이진탐색트리 메소드, 주어진 키 범위 내의 원소들, 주어진 키 범위 내의 원소수
int isExternal(node_tr* node) {

	if (node->leftchild == NULL || node->rightchild == NULL) return 1;
	else return 0;

}
int isInternal(node_tr* node) {
	if (isExternal(node) == 1) {
		return 0;
	}
	else return 1;
}
node_tr* newNode() {

	node_tr* newnode = NULL;
	newnode = (node_tr*)malloc(sizeof(node_tr) * 1);
	if (newnode == NULL)return;

	newnode->leftchild = NULL;
	newnode->rightchild = NULL;
	newnode->key = 0;
	newnode->parent = NULL;

	return newnode;
}
node_tr* sibling(node_tr* node) {

	if (node->parent == NULL) { // root
		return;
	}
	node_tr* w;
	w = node->parent;
	if (node == w->rightchild) {
		return w->leftchild;
	}
	else {
		return w->rightchild;
	}
}
node_tr* treeSearch(node_tr* node, int key) {

	if (isExternal(node)) return node;

	if (node->key > key) {
		return treeSearch(node->leftchild, key);
	}
	else if (node->key < key) {
		return treeSearch(node->rightchild, key);
	}
	else {
		return node;
	}

}
node_tr* findKey(node_tr* node, int key) {

	if (isExternal(node)) {
		printf("already external node!\n");
		return node;
	}

	node_tr* w;

	w = treeSearch(node, key);
	if (isExternal(w)) {
		printf("X");
		return w;
	}
	printf("%d", w->key);
	return w;
}
node_tr* inOrderSuccessor(node_tr* node) {

	node_tr* np;
	if (!isExternal(node)) {
		np = node->rightchild;
		while (!isExternal(np)) {
			np = np->leftchild;
		}
		return np;
	}
	else { //node is External
		np = node->parent;
		if (node == np->leftchild) {
			return np;
		}
		else {
			while (np->rightchild == node) {
				if (np->parent == NULL) {
					printf("invalid node exception - no inordersucessor exist, find root before searching end\n");
					return;
				}
				node = np;
				np = np->parent;
			}
			return np;
		}
	}


}
void expandExternal(node_tr* node) {

	node->leftchild = newNode();
	node->rightchild = newNode();
	node->leftchild->parent = node;
	node->rightchild->parent = node;

}
void reduceExternal(node_tr* externalnode) {

	node_tr* w, * sib;

	w = externalnode->parent;

	sib = sibling(externalnode);

	sib->parent = w->parent;

	if (w->parent->rightchild == w) {
		w->parent->rightchild = sib;
	}
	else {
		w->parent->leftchild = sib;
	}

	free(externalnode);
	free(w);

}
void removeAllItem(node_tr* root, int key) {

	node_tr* w;
	w = treeSearch(root, key);
	if (isExternal(w)) {
		printf("X\n");
		return;
	}

	node_tr *succ, *z;
	while (isInternal(w)) {
		printf("%d\n", w->key);
		z = w->leftchild;
		if (!isExternal(z)) {
			z = w->rightchild;
		}
		if (isExternal(z)) {
			reduceExternal(z);
		}
		else {
			z = inOrderSuccessor(w);
			succ = z->parent;
			w->key = succ->key;
			reduceExternal(z);
		}
		w = treeSearch(w->rightchild, key);
	}

}
void insertItem_searchTree(node_tr* root, int key) {

	node_tr* node;

	node = treeSearch(root, key);
	while (isInternal(node)) {
		node = treeSearch(node->rightchild, key);
	}
	expandExternal(node);	//node 에 expand 해주고
	node->key = key;		//node 에 키 값 넣어줌


}
void visit(node_tr* root) {

	if (!isExternal(root))
		printf(" %d", root->key);

}
#define INORDER 1
#define PREORDER 2
void printTree(node_tr* root, int order) {


	if (order == INORDER) {
		if (!isExternal(root)) {
			printTree(root->leftchild, order);
		}
		visit(root);
		if (!isExternal(root)) {
			printTree(root->rightchild, order);
		}
	}
	else if(order == PREORDER) {
		visit(root);
		if (!isExternal(root->leftchild)) {
			printTree(root->leftchild, order);
		}
		if (!isExternal(root->rightchild)) {
			printTree(root->rightchild, order);
		}
	}
	else {
		return;
	}

}

//문제
void priorityQueue_number1() {
	int n;
	scanf("%d", &n);

	int* arr = NULL;
	arr = (int*)malloc(sizeof(int) * n);
	if (arr == NULL) return;

	int i;
	for (i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}

	insertionSort_inplace(arr, n);


	for (i = 0; i < n; i++) {
		printf(" %d", arr[i]);
	}

	free(arr);
}
void priorityQueue_number2() {

	int n;
	scanf("%d", &n);

	int* arr = NULL;
	arr = (int*)malloc(sizeof(int) * n);
	if (arr == NULL) return;

	int i;
	for (i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}

	selectionSort_inplace(arr, n);


	for (i = 0; i < n; i++) {
		printf(" %d", arr[i]);
	}

	free(arr);
}
void heap1_number1() {

	char input;
	int inputnum;
	while (1) {

		scanf("%c", &input);

		if (input == 'i') {

			scanf("%d", &inputnum);
			insertItem_searchTree(heap_2, inputnum);
			printf("0\n");
			getchar();

		}
		else if (input == 'd') {
			printf("%d", removeFirst(heap_2, heapsize_2));
			printf("\n");
			getchar();
		}
		else if (input == 'p') {
			printarrayheap(heap_2, heapsize_2);
			getchar();
		}
		else break;

	}



}
void heap1_number2() {

	int cnt;
	scanf("%d", &cnt);

	heapsize_2 = cnt;

	int i;
	int inputnum;
	for (i = 1; i <= cnt; i++) {
		scanf("%d", &inputnum);
		heap_2[i] = inputnum;
	}

	buildUpperHeap(heap_2, heapsize_2);
	printarrayheap(heap_2, heapsize_2);

}
void heap2_number1() {

	int cnt;
	scanf("%d", &cnt);

	heapsize_2 = cnt;

	int i;
	int inputnum;
	for (i = 1; i <= cnt; i++) {
		scanf("%d", &inputnum);
		heap_2[i] = inputnum;
	}

	buildUpperHeap(heap_2, heapsize_2);
	inplaceSort(heap_2, heapsize_2);


	for (i = 1; i <= cnt; i++) {
		printf(" %d", heap_2[i]);
	}

}
void heap2_number2() {

	int cnt;
	scanf("%d", &cnt);

	heapsize_2 = cnt;

	int i;
	int inputnum;
	for (i = 1; i <= cnt; i++) {
		scanf("%d", &inputnum);
		heap_2[i] = inputnum;
	}

	buildUpperHeap(heap_2, heapsize_2);
	inplaceSort(heap_2, heapsize_2);


	for (i = 1; i <= cnt; i++) {
		printf(" %d", heap_2[i]);
	}


}
void mergequick_number1() {

	int n;
	scanf("%d", &n);

	ll* list = NULL;
	list = getLinkedList();
	int i;
	int input;
	for (i = 0; i < n; i++) {
		scanf("%d", &input);
		addLast(list, input);
	}


	printList(list);

	//	printf("%d", select_nIndex_node(list, 3)->key);

	putList(list);

}
void mergequick_number2() {


}
void dictionary_number1() {

	int n;
	scanf("%d", &n);

	int k;
	scanf("%d", &k);


	int* list;
	list = (int*)malloc(sizeof(int) * n);
	if (list == NULL) return;

	int i;
	for (i = 0; i < n; i++) {
		scanf("%d", &list[i]);
	}

	printf("%d", findElement(list, k, n));

}
void dictionary_number2() {

	dictionary_number1();

}
void searchtree_number1() {


	node_tr* root;
	root = newNode();

	char input;
	int key;
	while (1) {

		scanf("%c", &input);
		if (input == 'i') {

			scanf("%d", &key);
			insertItem_searchTree(root, key);
			getchar();
		}
		else if (input == 'd') {

			scanf("%d", &key);
			removeAllItem(root, key);
			getchar();
		}
		else if (input == 's') {

			scanf("%d", &key);
			findKey(root, key);
			getchar();
		}
		else if (input == 'p') {

			printTree(root, PREORDER);
			getchar();
		}
		else { // quit

			break;
		}
	}

}


int main() {

	searchtree_number1();
	return 0;

}