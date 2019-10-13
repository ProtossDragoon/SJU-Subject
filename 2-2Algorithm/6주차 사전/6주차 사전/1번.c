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

	int left = 0;
	int right = size - 1;

	int mid;

	while (right >= left) {
		mid = (left + right) / 2;
		if (arr[mid] < key) {
			left = mid + 1;
		}
		else if (arr[mid] > key) {
			right = mid - 1;
		}
		else {
			return mid;
		}
	}

	return left;
}


typedef struct minmax {

	int min;
	int max;

}minmax;

minmax find_minmax(minmax data, int M, char YoN) {

	minmax newdata = data;

	// 내가 짐작한 수 M 이
	// 너가 생각한 수 보다 크니?

	if (YoN == 'Y') {
		// 네 커요
		// data.min < M < K < data.max
		newdata.min = M + 1;

		return newdata;
	}
	if (YoN == 'N') {
		// 아뇨 작거나 같아요
		// data.min < K < M < data.max
		newdata.max = M;

		return newdata;
	}

	return newdata;
}




int main() {

	int a, b;
	scanf("%d", &a);
	scanf("%d", &b);

	int n;
	scanf("%d", &n);

	char yes_or_yes[101];

	scanf("%s", yes_or_yes);
	int len = strlen(yes_or_yes);
	
	int i;
	int M;


	int *arr = NULL;
	int size = b - a + 1;
	arr = (int*)malloc(sizeof(int) * (size));
	if (arr == NULL) return;

	minmax finaldata;
	finaldata.max = b;
	finaldata.min = a;

	for (i = 0; i < n; i++) {
		
		M = (finaldata.max + finaldata.min) / 2;

		finaldata = find_minmax(finaldata, M, yes_or_yes[i]);

	}

	printf("%d", finaldata.max);

	return 0;
}