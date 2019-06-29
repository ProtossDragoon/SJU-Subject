#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//¹®Á¦ 2.

#define BIG 1
#define SMALL 0

typedef struct Dog dog;
typedef struct queue que;

struct Dog {
	int dogtype;
	int dogid;
};
struct queue {

	dog arr[100];
	int front;
	int rear;

};



que* initQueue() {

	que* newqueue;
	newqueue = (que*)malloc(sizeof(que) * 1);
	if (newqueue == NULL) {
		return;
	}

	newqueue->front = 0;
	newqueue->rear = 100 - 1;

	return newqueue;
}
void* enQueue(que* queue, int dogtype, int dogid) {

	if(isFull(queue)) {
		printf("FullQueueException");
		return;
	}

	(queue->rear) = ((queue->rear) + 1) % 100;
	(queue->arr)[queue->rear].dogid = dogid;
	(queue->arr)[queue->rear].dogtype = dogtype;

}
dog deQueue(que *queue) {

	dog element;
	
	if (isEmpty(queue)) {
		printf("EmtpyQueueException");
		return;
	}

	element = (queue->arr)[queue->front];
	queue->front = queue->front + 1;

	return element;
}

int isFull(que* queue) {

	if (((queue->rear) + 2) % 100 == queue->front) {
		return 1;
	}
	else return 0;

}
int isEmpty(que* queue) {

	if (((queue->rear) + 1) % 100 == queue->front) {
		return 1;
	}
	else return 0;
}


/*
dog* setNewDog(int dogtype, int dogid) {

	dog* newdog;
	newdog = (dog*)malloc(sizeof(dog) * 1);
	if (newdog == NULL) {
		return;
	}

	newdog->dogid = dogid;
	newdog->dogtype = dogtype;

	return newdog;
}

void freeDog(dog* allocateddog) {
	free(allocateddog);
}

*/


int main() {

	int n;
	que* queueBIG;
	que* queueSMALL;
	queueBIG = initQueue();
	queueSMALL = initQueue();

	scanf("%d", &n);
	getchar();

	int i;
	char dogtype;
	int dogid;
	char inputchar;
	dog outputdog;
	for (i = 0; i < n; i++) {
		scanf("%c", &inputchar);
		if (inputchar == 'O') {
			if (!isEmpty(queueBIG)) {
				outputdog = deQueue(queueBIG);
				printf("D");
				printf(" %d\n", outputdog.dogid);
			}
		}
		else if (inputchar == 'o') {
			if (!isEmpty(queueSMALL)) {
				outputdog = deQueue(queueSMALL);
				printf("d");
				printf(" %d\n", outputdog.dogid);
			}
		}
		else {
			dogtype = inputchar;
			scanf("%d", &dogid);
			if (dogtype == 'I') {
				enQueue(queueBIG, BIG, dogid);
			}
			else {
				enQueue(queueSMALL, SMALL, dogid);
			}
		}
		getchar();
	}




	return 0;
}

