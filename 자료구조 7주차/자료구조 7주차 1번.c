#include<stdio.h>
#include<stdlib.h>
#include<string.h>


//LINKED LIST METHOD BELOW HERE
typedef struct list_for_set li;
typedef struct node_for_set nd;
typedef struct elem_for_set e;
typedef struct group gr;

struct list_for_set {
	nd* header;
    nd* noheader;
	int size;
	int existheader;
};
struct node_for_set {
	e* element;
	nd* next_node;
};
struct elem_for_set {
	char charelem;
	int intelem;
};
struct group {
    li* grouplist;
};


e   set_getElement_byLinkedList(gr *group);
e   set_removeFirstElement_byLinkedList(gr *group);
void set_addLastElement_byLinkedList(gr* group, e element);
nd* singleLinkedList_addNode(li* list, e* element, int rank);

void invalidRankException();
nd* singleLinkedList_getNewNode();


//List ADT
li* singleLinkedList_init(int existheader) {

    li *newlist;
    newlist = (li*)malloc(sizeof(li) * 1);
    if (newlist == NULL){
        printf("function : singleLinkedList_init error\n");
        return;
    }

    if (existheader == 1){
        newlist->header         = singleLinkedList_getNewNode();
        newlist->existheader    = existheader;
        newlist->noheader       = NULL;
    }
    else {
        newlist->header         = NULL;
        newlist->existheader    = existheader;
        newlist->noheader       = NULL;
    }

	newlist->size = 0;
    return newlist;

}
int singleLinkedList_size(li* list) {
	return list->size;
}
int singleLinkedList_isEmpty(li* list) {
	if (list->size == 0) {
		return 1;
	}
	else return 0;
}
nd* singleLinkedList_getNewNode() {

	nd* newnode;
	newnode = (nd*)malloc(sizeof(nd) * 1);
	if (newnode == NULL) {
		printf("function : getNewNode error\n");
		return;
	}

	newnode->element = (e*)malloc(sizeof(e) * 1);
	if (newnode->element == NULL) {
		printf("function : getNewNode error\n");
		return;
	}

	newnode->element->charelem = '0';
	newnode->element->intelem = 0;

    newnode->next_node = NULL;

	return newnode;
}
e   singleLinkedList_removeNode(li* list, nd* node) {

    nd *node_post;
    nd *node_pointer;
    e   returnelement = *(node->element);

    if (list->existheader == 1) { //header exist, trailer not-exist
        node_pointer = list->header;
        while (node_pointer->next_node != node){
            node_pointer = node_pointer->next_node;
        }

        node_pointer->next_node = node->next_node;
        free(node->element);
        free(node);
    }    
    else { //header and trailer : not-exist
        if (list->size == 1){
            free(node->element);
            free(node);
            list->noheader = NULL;
        }
        else {
            node_pointer = list->noheader;

			if (node_pointer == node) {
				list->noheader = node->next_node;
			}
			else {
				while (node_pointer->next_node != node) {
					node_pointer = node_pointer->next_node;
				}
				node_pointer->next_node = node->next_node;
			}
            free(node->element);
            free(node);
        }
    }

	list->size -= 1;
    return returnelement;

}
nd* singleLinkedList_selectNodeByRank(li* list, int rank) {

	nd* node = NULL;

	if (rank <= 0 || rank > list->size) {
		invalidRankException();
	}


	int i;

	
    if (list->existheader == 1){
      	node = list->header;
        for (i = 0; i < rank; i++) {
            node = node->next_node;
        }
    }
    else {
        node = list->noheader;
        for ( i = 0 ; i < rank-1 ; i++) {
            node = node->next_node;
        }
    }
	

	return node;

}
nd* singleLinkedList_selectLastNode(li* list) {
	int rank = list->size;
	return singleLinkedList_selectNodeByRank(list, rank);
}
nd* singleLinkedList_selectFirstNode(li* list) {
	return singleLinkedList_selectNodeByRank(list, 1);
}
nd* singleLinkedList_setElementByRank(li* list, int rank, e* elem) {

	nd* np;
	np = singleLinkedList_selectNodeByRank(list, rank);
    free(np->element);
	np->element = elem;
	return np;

};
nd* singleLinkedList_setElementByNode(nd* node, e* elem) {

    free(node->element);
	node->element = elem;

	return node;
}
nd* singleLinkedList_addNode(li* list, e* element, int rank) {


	if (rank < 0 || rank > list->size) {
		invalidRankException();
		return;
	}

	
	nd* newnode;
    newnode = singleLinkedList_getNewNode();
    newnode->element = element;

	nd* np;

    if (rank == 0){
        if (list->existheader == 1){
            np                    = list->header;
            newnode->next_node    = np->next_node;
            np->next_node         = newnode;

        }
        else {
            newnode->next_node    = list->noheader;
            list->noheader        = newnode;
        }
    }
    else {
        np                        = singleLinkedList_selectNodeByRank(list, rank);            newnode->next_node        = np->next_node;
        np->next_node             = newnode;

    }

	list->size            = list->size + 1;

	return newnode;
}
nd* singleLinkedList_addLastNode(li* list, e* element) {
	int rank;
	rank = list->size;
	return singleLinkedList_addNode(list, element, rank);
}
nd* singleLinkedList_addFirstNode(li* list, e* element) {
	int rank;
	rank = 0;
	return singleLinkedList_addNode(list, element, rank);
}
void singleLinkedList_print(li *list){
    nd *np;
    if(list->existheader == 1){
        np = list->header->next_node;
        while(np != NULL){
            printf(" %d", np->element->intelem);
			np = np->next_node;
        }
    }
    else{
        np = list->noheader;
        while(np != NULL){
            printf(" %d", np->element->intelem);
			np = np->next_node;
        }
    }
}

void invalidRankException() {
	printf("invalidRankException\n");
}




//SET MEHTHOD BELOW HERE
//main method
gr* set_initGroup_byLinkedList(int existheader){
    gr* group;
    group = (gr*)malloc(sizeof(gr) * 1);
    if (group == NULL){
        printf("funciton : set_initGroup_byLinkedList error\n");
        return;
    }

    group->grouplist = singleLinkedList_init(existheader);
    return group;
}

gr* set_union_byLinkedList(gr *A, gr *B, int existheader){

    gr *C;    
    C = set_initGroup_byLinkedList(existheader);

    int c1, c2;
    while (!set_isEmpty_byLinkedList(A) && !set_isEmpty_byLinkedList(B)){
        c1 = set_getElement_byLinkedList(A).intelem;
        c2 = set_getElement_byLinkedList(B).intelem;
        if (c1 > c2) {
            set_addLastElement_byLinkedList(C, set_getElement_byLinkedList(B));
            set_removeFirstElement_byLinkedList(B);
        }
        else if (c1 < c2){
            set_addLastElement_byLinkedList(C, set_getElement_byLinkedList(A));
            set_removeFirstElement_byLinkedList(A);
        }
        else {
            set_addLastElement_byLinkedList(C, set_getElement_byLinkedList(A));
            set_removeFirstElement_byLinkedList(A);
            set_removeFirstElement_byLinkedList(B);
        }
    }
    while(!set_isEmpty_byLinkedList(A)){

        c1 = set_getElement_byLinkedList(A).intelem;
        set_addLastElement_byLinkedList(C, set_removeFirstElement_byLinkedList(A));
    }
    while(!set_isEmpty_byLinkedList(B)){

        c2 = set_getElement_byLinkedList(B).intelem;
        set_addLastElement_byLinkedList(C, set_removeFirstElement_byLinkedList(B));
    }

    return C;
}
gr* set_intersect_byLinkedList(gr* A, gr* B, int existheader){

	gr* C;
	C = set_initGroup_byLinkedList(existheader);

	int c1, c2;
	while (!set_isEmpty_byLinkedList(A) && !set_isEmpty_byLinkedList(B)) {
		c1 = set_getElement_byLinkedList(A).intelem;
		c2 = set_getElement_byLinkedList(B).intelem;
		if (c1 > c2) {
			set_removeFirstElement_byLinkedList(B);
		}
		else if (c1 < c2) {
			set_removeFirstElement_byLinkedList(A);
		}
		else {
			set_addLastElement_byLinkedList(C, set_getElement_byLinkedList(A));
			set_removeFirstElement_byLinkedList(A);
			set_removeFirstElement_byLinkedList(B);
		}
	}
	while (!set_isEmpty_byLinkedList(A)) {
		set_removeFirstElement_byLinkedList(A);
	}
	while (!set_isEmpty_byLinkedList(B)) {
		set_removeFirstElement_byLinkedList(B);
	}

	return C;
}
void set_subtract_byLinkedList(){

}

//normal method
int set_size_byLinkedList(gr *group){
    return group->grouplist->size;
}
int set_isEmpty_byLinkedList(gr *group){
    if (set_size_byLinkedList(group) == 0){
        return 1;
    }
    else return 0;
}
void set_print_byLinkedList(gr *group){
	if (set_isEmpty_byLinkedList(group)) {
		printf(" 0");
	}
    else singleLinkedList_print(group->grouplist);
}

//question method
int set_members_byLinkedList(){
    //개체 e가 집합의 원소인지를 반환
}
int set_subset_byLinkedList(){
    //집합 a가 집합 b의 부분집합인지를 반환
}

//update method
void set_addLastElement_byLinkedList(gr *group, e element){
    //집합의 맨 뒤에 원소 e를 추가
    e *elementpointer;
    elementpointer = (e *)malloc(sizeof(e)*1);
	*elementpointer = element;

    singleLinkedList_addLastNode(group->grouplist, elementpointer);
}
e   set_removeFirstElement_byLinkedList(gr *group){
    //집합의 맨 앞 원소 e를 삭제
    nd *tmpnode;
    tmpnode = singleLinkedList_selectFirstNode(group->grouplist);
    return singleLinkedList_removeNode(group->grouplist, tmpnode);
}
e   set_getElement_byLinkedList(gr *group){
    //집합으로부터 첫 번째 원소를 가져옴
    return *(singleLinkedList_selectFirstNode(group->grouplist)->element);
}

//exception
void set_emptySetException_byLinkedList(){
    printf("emptySetException");
}






int main() {

    int n1, n2;
    int i;
    int tmpnum;
    e element;
    gr *group1;
    gr *group2;
    gr *group3;
	gr* group1_2;
	gr* group2_2;
	gr* group3_2;


	group1 = set_initGroup_byLinkedList(0);
	group2 = set_initGroup_byLinkedList(0);

	group1_2 = set_initGroup_byLinkedList(0);
	group2_2 = set_initGroup_byLinkedList(0);
	
	scanf("%d", &n1);
    for ( i = 0 ; i < n1; i++){
        scanf("%d", &tmpnum);
        element.intelem = tmpnum;
        set_addLastElement_byLinkedList(group1, element);
		set_addLastElement_byLinkedList(group1_2, element);
	}

    scanf("%d", &n2);
    for (i = 0 ; i < n2 ; i++ ){
		scanf("%d", &tmpnum);
        element.intelem = tmpnum;
        set_addLastElement_byLinkedList(group2, element);
		set_addLastElement_byLinkedList(group2_2, element);
    }

    group3 = set_union_byLinkedList(group1, group2, 0);
	group3_2 = set_intersect_byLinkedList(group1_2, group2_2, 0);
    set_print_byLinkedList(group3);
	printf("\n");
	set_print_byLinkedList(group3_2);


    return 0;
}

