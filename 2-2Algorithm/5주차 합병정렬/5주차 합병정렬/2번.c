#include<stdio.h>
#include<stdlib.h>

#include<time.h>



// 배열을 이용한 퀵 정렬 문제
typedef struct arraylist arraylist;
struct arraylist {
	int* arr;
	int totalsize;
	int startindex;
	int lastindex;
};

void freeArraylists_arraylist(arraylist** arrlist, int partitionsize) {

	int i;
	for (i = 0; i < partitionsize; i++) {
		free(arrlist[i]);
	}
	free(arrlist);

}
void freeArraylistAndElements_arraylist(arraylist *arrlist) {

	free(arrlist->arr);
	free(arrlist);

}

arraylist* init_arraylist(int size) {
	
	int* arr = NULL;
	arr = (int*)malloc(sizeof(int) * size);
	if (arr == NULL) return;

	arraylist* arrlist = NULL;
	arrlist = (arraylist*)malloc(sizeof(arraylist) * 1);
	if (arrlist == NULL) return;

	//init arraylist sturcture
	arrlist->arr = arr;
	arrlist->totalsize = size;
	arrlist->startindex = 0;
	arrlist->lastindex = size-1;

	return arrlist;

}
arraylist* shareArray_arraylist(int *arr, int startindex, int endindex) {

	if (startindex == -1 && endindex == -1) {
		return NULL;
	}

	arraylist* arrlist = NULL;
	arrlist = (arraylist*)malloc(sizeof(arraylist) * 1);
	if (arrlist == NULL) return;

	//init arraylist sturcture
	arrlist->arr = arr;
	arrlist->totalsize = endindex - startindex + 1;
	arrlist->startindex = startindex;
	arrlist->lastindex = endindex;

	return arrlist;

}

void swap_array(int* arr, int index1, int index2) {

	int tmp;
	tmp = arr[index1];
	arr[index1] = arr[index2];
	arr[index2] = tmp;

}


#define FIRSTSMALL 0
#define FIRSTBIG 1

arraylist** inplacePartition_arraylist(arraylist** arrlists, arraylist* arrlist, int pivot_index) {

	arraylist *LT = NULL, *EQ = NULL, *GT = NULL;

	
	int startindex = arrlist->startindex;
	int lastindex = arrlist->lastindex;
	int pivot_num = arrlist->arr[pivot_index];


	//swap pivot
	swap_array(arrlist->arr, pivot_index, lastindex);


	//pivot 과 동등한 것이 있으면, 뒷쪽으로 몰아줌. (swap pivots)
	int i = arrlist->startindex, j = arrlist->lastindex - 1;
	int same_cnt = 1;

	while (i < j) {
		while (i <= j && arrlist->arr[i] != pivot_num) {
			i++;
		}
		while (i <= j && arrlist->arr[j] == pivot_num) {
			same_cnt++;
			j--;
		}
		if (i < j) {
			swap_array(arrlist->arr, i, j);
			same_cnt++;
			i++;
			j--;
		}
	}



	//pivot 과 다른 것들이 존재하는 앞부분을 swap swap swap 함
	int s, r;
	s = arrlist->startindex;
	r = arrlist->lastindex - same_cnt;
	if (s >= r) { // 특수한 경우
		if (s == r) { // [2, 5, 5]
			if (arrlist->arr[s] > pivot_num)
				swap_array(arrlist->arr, startindex, lastindex);

			LT = shareArray_arraylist(arrlist->arr, startindex, startindex);
			EQ = shareArray_arraylist(arrlist->arr, startindex + 1, lastindex);
			GT = shareArray_arraylist(arrlist->arr, -1, -1);

		}
		else { // [3, 3, 3]
			LT = shareArray_arraylist(arrlist->arr, -1, -1);
			EQ = shareArray_arraylist(arrlist->arr, startindex, lastindex);
			GT = shareArray_arraylist(arrlist->arr, -1, -1);
		}

		arrlists[0] = LT;
		arrlists[1] = EQ;
		arrlists[2] = GT;

		return arrlists;
	}
	else { // 일반적인 경우
		while (s <= r) {

			while (s <= r && arrlist->arr[s] < pivot_num) {
				// 교안에는 arr[index] <= pivot_num 으로 되어있지만
				// 내가 작성한 알고리즘은 처음에 pivot_num 과 같은 원소들을 뒤로 몰고
				// 기존 알고리즘과 동일한 시간 복잡도를 가지므로, 동등조건을 제거함.
				s++;
			}
			while (s <= r && arrlist->arr[r] > pivot_num) {
				r--;
			}
			if (s < r)
				swap_array(arrlist->arr, s, r);
		}
	}


	//큰 것 또는 작은 것들이 모여있는 부분부터 pivot 과 동등한 숫자들만 다시 넘겨줌
	int	tmp = lastindex;
	int tmp_cnt = 0;
	while (tmp_cnt < same_cnt && arrlist->arr[s] != pivot_num) {
		swap_array(arrlist->arr, s, tmp);
		s++;
		tmp--;
		tmp_cnt++;
	}


	LT = shareArray_arraylist(arrlist->arr, startindex, r);
	EQ = shareArray_arraylist(arrlist->arr, r + 1, r + same_cnt);
	GT = shareArray_arraylist(arrlist->arr, r + same_cnt + 1, lastindex);


	arrlists[0] = LT;
	arrlists[1] = EQ;
	arrlists[2] = GT;

	return arrlists;

}


int medianNumber(int a, int b, int c) {

	if (a == b && a == c && b == c) {
		return a;
	}
	else if (a == b) {
		return a;
	}
	else if (b == c) {
		return b;
	}
	else if (a == c) {
		return c;
	}
	else { //a != b != c
		if (a > b) {
			if (b > c) {
				return b;
			}
			else if (c > b) {
				return c;
			}
			else {
				return a;
			}
		}
		else {
			if (a > c) {
				return a;
			}
			else if (a < c) {
				return c;
			}
			else {
				return b;
			}
		}
	}

}
int findMedianIndex(int* arr, int index1, int index2, int index3) {

	int a, b, c;

	a = arr[index1];
	b = arr[index2];
	c = arr[index3];

	int mid;
	mid = medianNumber(a, b, c);

	if (mid == a) {
		return index1;
	}
	else if (mid == b) {
		return index2;
	}
	else return index3;

}
int selectRandomPivotMedianIndex_arraylist(arraylist *arr) {

	int randomly_selected_index[3];
	srand(time(NULL));



	int i;
	for (i = 0; i < 3; i++) {

		randomly_selected_index[i] = rand() % arr->totalsize + arr->startindex;

	}

	int selected_index;
	selected_index = findMedianIndex(arr->arr, randomly_selected_index[0], randomly_selected_index[1], randomly_selected_index[2]);

	return selected_index;
}


void quickSort_arraylist(arraylist* arrlist) {

	int size = arrlist->totalsize;
	int i;

	if (size > 1) {

		int pivot_index;
		pivot_index = selectRandomPivotMedianIndex_arraylist(arrlist);


		arraylist** arrlists = NULL;
		arrlists = (arraylist * *)malloc(sizeof(arraylist*) * 3);
		if (arrlists == NULL) return;
		arrlists = inplacePartition_arraylist(arrlists, arrlist, pivot_index);
		
		
		// 재귀 호출부
		//index 0 : LT (Less Than)
		//index 1 : EQ (EQual)
		//index 2 : GT (Greater Than)
		for (i = 0; i < 3; i++) {
			if (arrlists[i] != NULL && i != 1) quickSort_arraylist(arrlists[i]);
		}


		// arr 내부에서 정렬이 끝나면 arrlists 에 들어있는 애들 free
		freeArraylists_arraylist(arrlists, 3);

	}

}





int main() {


	int n;

	scanf("%d", &n);

	arraylist* arrlist = NULL;
	arrlist = init_arraylist(n);

	int i;
	int input;
	for (i = 0; i < n; i++) {
		scanf("%d", &input);
		arrlist->arr[i] = input;
	}

	quickSort_arraylist(arrlist);

	for (i = 0; i < n; i++) {
		printf(" %d", arrlist->arr[i]);
	}

	return 0;
}