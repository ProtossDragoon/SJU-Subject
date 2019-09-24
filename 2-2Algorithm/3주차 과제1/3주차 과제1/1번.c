#include<stdio.h>
#include<string.h>
#include<stdlib.h>


typedef struct Node {
	char elem;
	struct Node* prev;
	struct Node* next;
}Node; // 노드 정의


typedef struct List {
	struct Node* header;
	struct Node* trailer;
}List; // 리스트 정의


void init_list(List* list) {

	//헤더와 트레일러 할당
	list->header = (Node*)malloc(sizeof(Node) * 1);
	list->trailer = (Node*)malloc(sizeof(Node) * 1);

	//헤더와 트레일러 초기화
	list->header->next = list->trailer;
	list->trailer->prev = list->header;
	list->header->prev = NULL;
	list->trailer->next = NULL;
}


Node* getNode() {

	Node* newnode = NULL; // 새로운 노드 포인터 생성
	newnode = (Node*)malloc(sizeof(Node) * 1);
	if (newnode == NULL)return;

	newnode->elem = '0';
	newnode->next = NULL;
	newnode->prev = NULL;


	return newnode; // 새로 메모리를 할당받은 노드 반환
}
void linkNode(Node *prevnode, Node* newnode, Node* nextnode) { // add 함수에서 호출되는 함수
	prevnode->next = newnode;
	newnode->next = nextnode;
	newnode->prev = prevnode;
	nextnode->prev = newnode;
}
void unlinkNode(Node* prevnode, Node* currentnode, Node* nextnode) { // delete 함수에서 호출되는 함수
	prevnode->next = nextnode;
	nextnode->prev = prevnode;
}


#define SELECT 0
#define INSERT 1
int isInvalidRankException(List list, int select_or_insert, int position) { // input 의 position 이 invalid 한지 알아보는 함수

	Node* np = list.header;
	int cnt = 0;
	while (np->next != list.trailer) { // 최대 개수를 count 합니다. Trailer 이 나타날때까지 개수를 세어 position 과 비교하기 위함
		np = np->next;
		cnt++;
	}

	if (select_or_insert == INSERT) { // 만약, 노드 삽입 시 invalid 을 검사하다면 INSERT 모드로 실행
		if (cnt + 1 < position || position < 0) {
			printf("invalid position\n");
			return 1;
		}
		else return 0;
	}
	else { // 만약, 노드를 선택해서 처리해야 하는 상황 invalid 을 검사한다면 SELECT 모드로 실행
		if (cnt < position || position <= 0) {
			printf("invalid position\n");
			return 1;
		}
	}
	return 0;
}

void add(List list, int position, char item) {

	if (isInvalidRankException(list, INSERT, position)) return;
	
	Node* prevnode = list.header;
	Node* nextnode = list.header->next;

	Node* newnode = NULL; // 새로 할당받은 노드 메모리
	newnode = getNode();
	newnode->elem = item;

	int i; // 위치 찾아가는 for loop
	for (i = 1; i < position; i++, 
		prevnode = prevnode->next,
		nextnode = nextnode->next) {
	}
	// 내가 추가할 위치의 전, 후를 골라냄.

	linkNode(prevnode, newnode, nextnode); // 이전 노드, 현재 노드, 다음 노드를 연결해주는 함수
}

int delete(List list, int position) {

	if (isInvalidRankException(list, SELECT, position)) return;

	Node* currentnode = list.header;
	Node* nextnode = list.header->next;

	int i; // 위치 찾아가는 for loop
	for (i = 0; i < position; i++,
		currentnode = currentnode->next,
		nextnode = nextnode->next) {
	}
	// 내가 제거할 노드의 뒷쪽 노드를 골라냄.
	
	unlinkNode(currentnode->prev, currentnode, nextnode); // 이전 노드, 현재 노드, 다음 노드를 끊어주는 함수
	int e = currentnode->elem;
	free(currentnode);
	return e;
}

int get_entry(List list, int position) { 

	if (isInvalidRankException(list, SELECT, position)) return;



	Node* currentnode = list.header;
	Node* nextnode = list.header->next;

	int i; // 위치 찾아가는 for loop
	for (i = 0; i < position; i++,
		currentnode = currentnode->next,
		nextnode = nextnode->next) {
	}
	// 내가 읽을 노드의 뒷쪽 노드를 골라냄.

	char e = currentnode->elem;
	printf("%c\n", e);
	return e;
}

void print(List list) {

	Node* np = list.header;
	np = np->next;

	while (np != list.trailer) {
		printf("%c", np->elem);
		np = np->next;
	}
	printf("\n");

}

void free_list(List list) {


	Node* currentnode = list.header->next; // 값이 들어있는 노드 : currentnode
	Node* nextnode = list.header->next->next; // 값이 들어있는 다음 노드 : currentnode->next

	while (currentnode != list.trailer) {

		unlinkNode(currentnode->prev, currentnode, nextnode); // 링크 해제
		free(currentnode); // 타겟 노드 제거

		currentnode = nextnode;
		nextnode = currentnode->next;

	}

	free(list.header);
	free(list.trailer);
}


int main(void) {

	List list;			// 리스트 선언
	char op, item;		// 입력 연산의 종류, 아이템
	int position;		// 입력 위치
	int num_op;			// 연산의 개수
	

	init_list(&list);		// 리스트 초기화 (헤더, 트레일러 노드 할당 및 초기화)
	scanf("%d", &num_op);	// 연산 개수 입력
	

	
	for (int i = 0; i < num_op; ++i) {
		getchar();			// 공백 또는 개행문자 읽기
		scanf("%c", &op);	// 연산 종류
		switch (op) {

		case 'A': // 삽입
			scanf("%d %c", &position, &item);
			add(list, position, item);
			break;

		case 'D': // 삭제
			scanf("%d", &position);
			delete(list, position);
			break;

		case 'G': // 참조
			scanf("%d", &position);
			get_entry(list, position);
			break;

		case 'P': // 출력
			print(list);
			break;
		}
	}


	free_list(list); // 리스트의 노드 해제


	return 0;
}