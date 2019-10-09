#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int findkey_binarysearch_recursive(int *arr, int key, int left, int right) {

	if (left > right) {
		//printf("No such Key!");
		return right;
	}

	int looking = (left + right) / 2;


	if (arr[looking] < key) {
		return findkey_binarysearch_recursive(arr, key, looking + 1, right);
	}
	else if (arr[looking] > key) {
		return findkey_binarysearch_recursive(arr, key, left, looking - 1);
	}
	else {
		return looking;
	}

}

int findkey_binarysearch(int* arr, int size, int key) {

	int a = 0;
	int b = size - 1;

	int mid;

	while (b > a) {
		mid = (b + a) / 2;
		if (arr[mid] < key) {
			a = mid + 1;
		}
		else if (arr[mid] > key) {
			b = mid;
		}
		else {
			return mid;
		}
	}

	return mid;
}


int main() {

	int n;

	scanf("%d", &n);
	
	int key;
	scanf("%d", &key);

	// 동적 할당
	int* arr = NULL;
	arr = (int*)malloc(sizeof(int) * n);
	if (arr == NULL) return;

	int i, j;
	for (i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}


	//printf(" %d", findkey_binarysearch_recursive(arr, key, 0, n-1));

	printf(" %d", findkey_binarysearch(arr, n, key));


	return 0;
}