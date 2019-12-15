### 구현연습2

- 실행시간을 준수하는 것은 기본으로 하며, 의사코드의 형태를 최대한 유지해서 쉽게 읽을 수 있는 코드를 작성하고자 하였음.


```C
// MSTKruskal algorithm
void KruskalMST(graph* G) {

	// Queue
	p_queue Q;
	getQueue(&Q, G->num_edge);
	for (int i = 0; i < G->num_edge; i++) {
		enQueue(&Q, G->edges[i].weight, i);
	}
	
	// Set
	set *S;
	S = getSet(G->num_vertices, G->num_vertices);
	for (int i = 1; i < G->num_vertices; i++) {
		S->setdata[i] = i;
	}

	int index_edge;
	int a, b;
	int sum = 0;
	while (!isQueueEmpty(&Q)) {
		index_edge = deQueue(&Q);
		a = G->edges[index_edge].index_vert_a;
		b = G->edges[index_edge].index_vert_b;
		if (setFind(S, a) != setFind(S, b)) {
			// add this edge to MST bag
			sum = sum + G->edges[index_edge].weight;
			printf(" %d", G->edges[index_edge].weight);
			setUnion(S, setFind(S,a), setFind(S, b));
		}
	}
	printf("\n%d", sum);
}
```
