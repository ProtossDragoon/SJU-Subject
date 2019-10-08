#include<stdio.h>
#include<stdlib.h>


/*

typedef struct matrix matrix;
struct matrix {
	int **intelement;
	float** floatmatrix;
	double** doublematrix;
};

matrix** initmatrix() {

	


}

*/


void int_matmul(int (*matrix1)[10], int (*matrix2)[10], int size) {


	int i, j;

	int **result = NULL;


	//allocation
	result = (int**)malloc(sizeof(int*) * size);
	if (result == NULL)return;
	for (i = 0; i < size; i++) {
		result[i] = (int*)malloc(sizeof(int) * size);
		if (result[i] == NULL)return;
	}


	int tmp = 0;
	int k = 0;

	for (i = 0; i < size; i++) { // i 행
		for (j = 0; j < size; j++) { // j 열

			//1,1 : 1행[열전체] X [행전체]1열
			//n,m : n행[열전체] X [행전체]m열
			for (k = 0; k < size; k++) {

				tmp = tmp + matrix1[i][k] * matrix2[k][j];

			}
			printf("%d", tmp);
			result[i][j] = tmp; // i행 j열 연산 결과
			tmp = 0;

			if (j < size) {
				printf(" ");
			}
		}
		printf("\n");
	}







	//free
	for (i = 0; i < size; i++) 
		free(result[i]);
	free(result);

}



int main() {

	int matrix1[10][10];
	int matrix2[10][10];

	int i;
	int j;

	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			scanf("%d", &matrix1[i][j]);
		}
	}


	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			scanf("%d", &matrix2[i][j]);
		}
	}

	int_matmul(matrix1, matrix2, 10);


	return 0;
}