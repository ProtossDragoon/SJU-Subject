#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define RIGHT 0
#define LEFT 1

typedef struct node nd;
typedef struct tree tr;

struct node { 
	// Node 에는 int 형 데이터를 받을 수 있는 intelem 과 char 형 데이터를 받을 수 있는 charelem 이 존재함. 
	nd* parent;
	int intelem;
	char charelem;
	nd* leftchild;
	nd* rightchid;
};
struct tree {
	nd rootnode;
};

nd* getNode() { // 새 노드를 할당하고 초기화해서 반환해주는 함수.
	
	//할당
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

nd* makeChildNode(nd* node, int left_or_right) { // 어떠한 노드의 자손노드를 만들어 반환하는 함수
		
	nd* childnode = NULL;

	//자손노드를 위한 메모리 할당
	childnode = getNode();
	childnode->parent = node;


	//좌측 자손으로 만들기
	if (left_or_right == LEFT) {
		node->leftchild = childnode;
	}
	//우측 자손으로 만들기
	if (left_or_right == RIGHT) {
		node->rightchid = childnode;
	}

	return childnode;
}
void setElement(nd* node, int intelement) { // 어떠한 노드의 element 를 setting 해주는 함수

	node->intelem = intelement;

}

void visitWithId(nd* node, int current_node_number, nd** savingnode) { // 순회하는 도중 id 값이 같은 노드의 주소를 저장함.
	if (current_node_number == node->intelem) {
		*savingnode = node;
	}
}
void preorderAndId(nd* node, int current_node_number, nd** savingnode) { // O(n) 시간에 선위순회하는 알고리즘

	visitWithId(node, current_node_number, savingnode); // visit
	if (isLeftChildExist(node))
		preorderAndId(node->leftchild, current_node_number, savingnode);
	if (isRightChildExist(node))
		preorderAndId(node->rightchid, current_node_number, savingnode);

}
nd* findNodeById(tr* tree, int current_node_number, nd** savingnode) { // id 가 같은 노드를 찾아내는 함수. 선위순회 알고리즘을 이용
	preorderAndId(&(tree->rootnode), current_node_number, savingnode);
	return *savingnode;
}


int isLeftChildExist(nd* node);
int isRightChildExist(nd* node);

int main() {


	tr tree;

	int i = 0, j = 0;

	int current_node_number;
	int left_node_number;
	int right_node_number;

	int count_of_node;

	scanf("%d", &count_of_node); // 노드 개수
	/* 
	
	흐름 설명

	어떤 노드에 id 를 달아주고
	(1) 그 id 를 기준으로 선위순회를 통해 노드를 찾고,
	(2) 그것의 좌측 자손, 우측 자손을 달아줌
	

	하지만 내 생각에 굉장히 비효율적임
	왜냐하면, 일단 처음에 count of node 를 왜 받는지 모르겠음.
	어차피 선위순회 순서대로 노드를 입력받으니까, 탐색과정을 거치지 않고 
	적절한 위치에 그냥 하나씩 노드를 달아주고, 알아서 마지막 노드를 인식하고 자동적으로 멈추게 할수도 있겠다는 생각이 들었음.
	그런데 문제에서 Node 의 개수를 입력받으라고 했기 때문에 의도가 그것은 아닐 것 같다는 생각이 들어 이렇게 코딩했음.
	
	*/

	// 입력 페이즈
	for (i = 0; i < count_of_node; i++) {
		scanf("%d %d %d", &current_node_number, &left_node_number, &right_node_number);
		if (i == 0) { // 한번도 노드를 만든 적 없는 경우
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



	// 탐색 페이즈
	int count_of_order;
	char order[101] = { 0 };
	nd* tmpnode;
	scanf("%d", &count_of_order); // 탐색 횟수
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

