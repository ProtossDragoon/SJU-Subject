#include<stdio.h>
#include<stdlib.h>


//define structure
typedef struct element element;
typedef struct node node;
typedef struct list list;

struct element {
	int intelement;
	char charelement;
};
struct node {
	node* nextnode;
	node* prevnode;
	element e;
};
struct list {
	node* header;
	node* trailer;
	int size;
};


node* newnode() {

	node* nd = NULL;
	nd = (node*)malloc(sizeof(node));

	return nd;

}

//list adt
list* newlist() {

	list* newlist;
	newlist = (list*)malloc(sizeof(list) * 1);

	newlist->header = newnode();
	newlist->trailer = newnode();

	newlist->header->nextnode = newlist->trailer;
	newlist->trailer->prevnode = newlist->header;

	newlist->header->prevnode = NULL;
	newlist->trailer->nextnode = NULL;
	newlist->size = 0;

	return newlist;
}


node* findnodeByRank(list *li, int rank) {

	node* np;
	int i;
	np = li->header;
	for (i = 0; i < rank; i++) {
		np = np->nextnode;
	}
	return np;

}



//define function
void list_add(list *li, int rank, element e) {

	node* targetnode;
	node* target_previous_node;

	targetnode = findnodeByRank(li, rank);
	//target node 앞에 추가해야함.

	target_previous_node = targetnode->prevnode;

	node* nd;
	nd = newnode();

	target_previous_node->nextnode = nd;
	targetnode->prevnode = nd;
	nd->nextnode = targetnode;
	nd->prevnode = target_previous_node;
	nd->e = e;

	li->size++;

}

element list_delete(list *li, int rank) {

	node* targetnode;
	node* target_previous_node;
	node* target_next_node;

	targetnode = findnodeByRank(li, rank);
	target_previous_node = targetnode->prevnode;
	target_next_node = targetnode->nextnode;

	target_previous_node->nextnode = target_next_node;
	target_next_node->prevnode = target_previous_node;

	element tmpelement;
	tmpelement = targetnode->e;

	free(targetnode);

	li->size--;

	return tmpelement;
}

element list_get(list *li, int rank) {

	node* targetnode;

	targetnode = findnodeByRank(li, rank);

	return targetnode->e;
}

void list_print(list *li) {
	node* np;
	np = li->header->nextnode;
	while (np != li->trailer) {
		printf("%c", (np->e).charelement);
		np = np->nextnode;
	}
	printf("\n");
}



int main() {

	list* li;
	li = newlist();
	
	int count;

	scanf("%d", &count);
	getchar();

	int i;
	char command;
	for (i = 0; i < count; i++) {
		scanf("%c", &command);
		if (command == 'P') {
			//print

			list_print(li);
			getchar();

		}
		else {
			int rank;
			scanf("%d", &rank);
			//check rank exception
			

			if (command == 'A') {
				//command == A add
				getchar();

				element e;
				scanf("%c", &(e.charelement));
				getchar();
				if (rank > (li->size) + 1) {
					printf("invalid position\n");
				}
				else {
					list_add(li, rank, e);
				}
			}
			else if (command == 'G') {
				//command == G get
				if (rank > li->size) {
					printf("invalid position\n");
				}
				else {
					printf("%c", list_get(li, rank).charelement);
				}
				getchar();
			}
			else {
				//command == D delete

				if (rank > (li->size) + 1) {
					printf("invalid position\n");
				}
				else {
					list_delete(li, rank);
				}
				getchar();
			}
		}
	}




	return 0;
}

