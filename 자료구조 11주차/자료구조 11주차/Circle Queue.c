#include<stdio.h>
#include<stdlib.h>

int flowcount = 0;

typedef struct circle_queue_byarr circle_queue_byarr;
struct circle_queue_byarr {
	int *arr;
	int size;
	int front;
	int rear;
};

void printQueue_byArr(circle_queue_byarr* queue);

void fullQueueException(circle_queue_byarr* queue) {

//	printf("fullQueueException\n");
	printf("overflow");

	printQueue_byArr(queue);

	flowcount = 1;

}

void emptyQueueException(circle_queue_byarr *queue) {

//	printf("emptyQueueException\n");
	printf("underflow");

	flowcount = 1;

}


circle_queue_byarr* initCircleQueue_byArr(int n) {

	circle_queue_byarr* arr;

	arr = (circle_queue_byarr*)malloc(sizeof(circle_queue_byarr) * 1);
	if (arr == NULL) {
		printf("function : initCircleQueue erorr\n");
		return;
	}

	arr->arr = (int*)malloc(sizeof(int) * n);
	if (arr->arr == NULL) {
		printf("funcion : initCircleQueue error\n");
		return;
	}

	int i;
	for (i = 0; i < n; i++) {
		(arr->arr)[i] = 0;
	}

	arr->front = 1;
	arr->rear = 1;
	arr->size = n;

	return arr;
}

int isCircleQueueFull_byArr(circle_queue_byarr *queue) {

	if ( (queue->rear + 1) % queue->size == queue->front) {
		return 1;
	}
	else {
		return 0;
	}
}

int isCircleQueueEmpty_byArr(circle_queue_byarr* queue) {

	if ((queue->front) == queue->rear) {
		return 1;
	}
	else return 0;
}

void enQueue_byArr(circle_queue_byarr* queue, int element) {


	if (isCircleQueueFull_byArr(queue)) {
		
		fullQueueException(queue);
		return;
	}

	(queue->arr)[queue->rear] = element;
	queue->rear = ((queue->rear + 1) % queue->size);


}

int deQueue_byArr(circle_queue_byarr* queue) {

	if (isCircleQueueEmpty_byArr(queue)) {
		emptyQueueException(queue);
		return;

	}
	int e;
	e = queue->arr[queue->front];
	queue->arr[queue->front] = 0;
	queue->front = (queue->front + 1) % (queue->size);

	return e;
}
void printQueue_byArr(circle_queue_byarr* queue) {

	int tmpindex;
	tmpindex = queue->front;

/*	while (tmpindex != queue->rear) {

		printf(" %d", (queue->arr)[tmpindex]);
		tmpindex = (tmpindex + 1) % queue->size;

	}*/
	int i;
	for (i = 0; i < queue->size; i++) {
		printf(" %d", queue->arr[i]);
	}

	printf("\n");
}



int main() {

	//---first line---//
	int q;
	scanf("%d", &q);
	circle_queue_byarr* queue;
	queue = initCircleQueue_byArr(q);

	//---second line---//
	int n;
	scanf("%d", &n);
	getchar();

	//---third line---//
	int i;
	char input;
	int inputelem;
	for (i = 0; i < n; i++) {
		scanf("%c", &input);
		if (input == 'I') {
			scanf("%d", &inputelem);
			enQueue_byArr(queue, inputelem);
			if (flowcount == 1) {
				break;
			}
		}
		else if (input == 'D') { 
			deQueue_byArr(queue);
			if (flowcount == 1) {
				break;
			}
		}
		else { //input == P//
			printQueue_byArr(queue);
		}
		getchar();
	}

}