#include<stdio.h>
#include<stdlib.h>

// #define number1
#define number2
// #define number3

typedef struct bucket_array bucket_array;
typedef struct linked_list linked_list;
typedef struct node node;

struct bucket_array {
	linked_list* li;
	int item;
};
struct linked_list {
	node* header;
	node* trailer;
};
struct node {
	node* next;
	node* perv;
	int item;
};

node* get_node(int item) {

	node* newnode = NULL;
	newnode = (node*)malloc(sizeof(node) * 1);
	if (newnode == NULL) return NULL;

	newnode->item = item;
	newnode->next = NULL;
	newnode->perv = NULL;

	return newnode;
}
linked_list* get_linked_list() {

	linked_list* newlist = NULL;
	
	newlist = (linked_list*)malloc(sizeof(linked_list) * 1);
	if (newlist == NULL) return NULL;

	newlist->header = get_node(-1);
	newlist->trailer = get_node(-1);
	newlist->header->next = newlist->trailer;
	newlist->trailer->perv = newlist->header;

	return newlist;
}
bucket_array* get_bucket_array(int size) {

	bucket_array* newarray = NULL;

	newarray = (bucket_array*)malloc(sizeof(bucket_array) * size);
	if (newarray == NULL) return NULL;

	int i;
	for (i = 0; i < size; i++) {
		newarray[i].li = get_linked_list();
		newarray[i].item = 0;
	}
	return newarray;
}
void put_linked_list(linked_list *li) {

	node* np;
	np = li->header;

	if (np->next != li->trailer)
		while (np != li->trailer) {
			np = np->next;
			free(np->perv);
		}

	free(li->header);
	free(li->trailer);
	free(li);
}
void put_bucket_array(bucket_array *x, int size) {
	
	int i;
	for (i = 0; i < size; i++) {
		put_linked_list(x[i].li);
	}

	free(x);
}

int hash(int item, int param) {

	int return_index;
	return_index = item % param;

	return return_index;
}
int hash_prime(int item, int param) {
	return param - (item % param);
}
int hash_linearSearch(int item, int param, int i) {
	return hash(item + i, param);
}
int hash_doubleHashing(int item, int param1, int param2, int i) {
	int a, b;
	a = hash(item, param1);
	b = i * hash_prime(item, param2);
	return (a + b) % param1;
}
void addFirst_linked_list(linked_list *list, int item) {

	node *node_before, *node_after;
	node_before = list->header;
	node_after = node_before->next;

	node* newnode = NULL;
	newnode = get_node(item);
	node_before->next = newnode;
	newnode->perv = node_before;
	newnode->next = node_after;
	node_after->perv = newnode;

}
void addFirst_bucket_array(bucket_array* x, int index, int item, int param) {

	// --- linked list ---
#ifdef number1
	addFirst_linked_list(x[index].li, item);
#endif // number1

	

	// --- linear search ---
#ifdef number2
	int hash_index = index;
	int cnt = 1;
	while (x[hash_index].item != 0) {
		hash_index = hash_linearSearch(item, param, cnt);
		cnt++;
		printf("C");
	}
	x[hash_index].item = item;
	printf("%d\n", hash_index);
#endif // number2

}
void insertItem(bucket_array* x, int item, int param) {
	//interface

	int hash_index;
	hash_index = hash(item, param);

	addFirst_bucket_array(x, hash_index, item, param);

}
int insertItem_doublehashing(bucket_array* x, int item, int param1, int param2) {

	int cnt;
	int hash_index;

	cnt = 0;
	hash_index = hash_doubleHashing(item, param1, param2, cnt);
	while (x[hash_index].item != 0) {
		cnt++;
		hash_index = hash_doubleHashing(item, param1, param2, cnt);
		printf("C");
	}
	x[hash_index].item = item;

	return hash_index;
}


int searchItem_linked_list(linked_list* li, int item) {

	node* np;
	int count = 1;
	np = li->header->next;

	while (np != li->trailer) {

		if (np->item == item) {
			return count;
		}
		np = np->next;
		count++;
	}

	return 0;
}
int searchItem(bucket_array* x, int item, int param) {
	//interface

	int hash_index;
	hash_index = hash(item, param);

	int returnval = 0;
	

	// --- linked list ---
#ifdef number1
	returnval = searchItem_linked_list(x[hash_index].li, item);
#endif // number1

	// --- linear search ---
#ifdef number2
	int cnt = 1;
	while (x[hash_index].item != 0) {
		if (x[hash_index].item == item) {
			printf("%d %d\n", hash_index, x[hash_index].item);
			return hash_index;
		}
		hash_index = hash_linearSearch(item, param, cnt);
		cnt++;
	}
	returnval = -1;
	printf("%d\n", returnval);
#endif // number2

	return returnval;
}
int searchItem_doublehashing(bucket_array* x, int item, int param1, int param2) {
	// interface

	int cnt;
	int hash_index;

	cnt = 0;
	hash_index = hash_doubleHashing(item, param1, param2, cnt);
	while (x[hash_index].item != 0) {
		if (x[hash_index].item == item) {
			printf("%d %d\n", hash_index, x[hash_index].item);
			return hash_index;
		}
		cnt++;
		hash_index = hash_doubleHashing(item, param1, param2, cnt);
	}

	printf("-1\n");
	return -1;
}


int deleteItem_linked_list(linked_list* li, int item) {

	node* np;
	node* tmpnode1, *tmpnode2;
	int count = 1;
	np = li->header->next;

	while (np != li->trailer) {

		if (np->item == item) {
			tmpnode1 = np->perv;
			tmpnode2 = np->next;

			tmpnode1->next = tmpnode2;
			tmpnode2->perv = tmpnode1;

			free(np);
			return count;
		}
		np = np->next;
		count++;
	}

	return 0;
}
int deleteItem(bucket_array* x, int item, int param) {
	//interface

	int hash_index;
	hash_index = hash(item, param);

	return deleteItem_linked_list(x[hash_index].li, item);
}


void printItem_linked_list(linked_list* li) {

	node* np;
	np = li->header->next;
	while (np != li->trailer) {
		printf(" %d", np->item);
		np = np->next;
	}
}
void printItem(bucket_array* x, int size) {
	//interface

#ifdef number1
	int i;
	for (i = 0; i < size; i++) {
		printItem_linked_list(x[i].li);
	}
#endif // number1


#ifdef number3
	int i;
	for (i = 0; i < size; i++) {
		printf(" %d", x[i].item);
	}
#endif // number3

	printf("\n");
}



int number_1() {


	//scan size of bucket array
	int m;
	scanf("%d", &m);
	getchar();

	//init bucket array
	bucket_array* x = NULL;
	x = get_bucket_array(m);


	char input;
	int item;
	int output;

	while (1) {

		scanf("%c", &input);
		getchar();

		if (input == 'i') {
			scanf("%d", &item);
			getchar();
			insertItem(x, item, m);
		}

		else if (input == 's') {
			scanf("%d", &item);
			getchar();
			output = searchItem(x, item, m);
			printf("%d\n", output);
		}

		else if (input == 'd') {
			scanf("%d", &item);
			getchar();
			output = deleteItem(x, item, m);
			printf("%d\n", output);
		}

		else if (input == 'p') {
			printItem(x, m);
		}

		else {

			break;
		}
	}

	//free
	put_bucket_array(x, m);
	//----

	return 0;

}
int number_2() {


	//scan size of bucket array
	int m, n;
	scanf("%d %d", &m, &n);
	getchar();

	//init bucket array
	bucket_array* x = NULL;
	x = get_bucket_array(m);


	char input;
	int item;
	int output;
	int n_cnt = 0;

	while (1) {

		scanf("%c", &input);
		getchar();

		if (input == 'i') {
			scanf("%d", &item);
			getchar();
			if (n_cnt >= n) {
				break;
			}
			insertItem(x, item, m);
			n_cnt++;
		}

		else if (input == 's') {
			scanf("%d", &item);
			getchar();
			searchItem(x, item, m);
		}

		else if (input == 'e') {

			break;
		}

		else if (input == 'p') {
			printItem(x, m);
		}

		else {

			break;
		}
	}

	//free
	put_bucket_array(x, m);
	//----


	return 0;

}
int number_3() {


	//scan size of bucket array
	int m, n, q;
	scanf("%d %d %d", &m, &n, &q);
	getchar();

	//init bucket array
	bucket_array* x = NULL;
	x = get_bucket_array(m);


	char input;
	int item;
	int output;
	int n_cnt = 0;

	while (1) {

		scanf("%c", &input);
		getchar();

		if (input == 'i') {
			scanf("%d", &item);
			getchar();
			if (n_cnt >= n) {
				break;
			}
			output = insertItem_doublehashing(x, item, m, q);
			printf("%d\n", output);
			n_cnt++;
		}

		else if (input == 's') {
			scanf("%d", &item);
			getchar();
			searchItem_doublehashing(x, item, m, q);
		}

		else if (input == 'e') {
			printItem(x, m);
			break;
		}

		else if (input == 'p') {
			printItem(x, m);
		}

		else {

			break;
		}
	}

	//free
	put_bucket_array(x, m);
	//----


	return 0;

}



int main() {

#ifdef number1
	number_1();
#endif // number1


#ifdef number2
	number_2();
#endif // number2


#ifdef number3
	number_3();
#endif // number3

	return 0;
}