#include<stdio.h>
#include<stdlib.h>

typedef struct matrix matrix;
struct matrix {
	int **intmatrix;
	float **floatmatrix;
	double **doublematrix;
	int type;
	int row_size;
	int col_size;
};

#define INT 0
#define FLOAT 1
#define	DOUBLE 2

matrix* newMatrix_square_int(int size, int type) {

	matrix* mat = NULL;
	mat = (matrix*)malloc(sizeof(matrix) * 1);
	if (mat == NULL)return;


	//init
	mat->col_size = size;
	mat->row_size = size;
	mat->type = type;
	mat->intmatrix = NULL;
	mat->floatmatrix = NULL;
	mat->doublematrix = NULL;


	int i;


	if (type == INT) {
		//memory allocation
		int** result = NULL;
		result = (int**)malloc(sizeof(int*) * size);
		if (result == NULL)return;
		for (i = 0; i < size; i++) {
			result[i] = (int*)malloc(sizeof(int) * size);
			if (result == NULL)return;
		}
		mat->intmatrix = result;
	}

	if (type == FLOAT) {
		//memory allocation
		float** result = NULL;
		result = (float**)malloc(sizeof(float*) * size);
		if (result == NULL)return;
		for (i = 0; i < size; i++) {
			result[i] = (float*)malloc(sizeof(float) * size);
			if (result == NULL)return;
		}
		mat->floatmatrix = result;
	}


	if (type == DOUBLE) {
		//memory allocation
		double** result = NULL;
		result = (double**)malloc(sizeof(double*) * size);
		if (result == NULL)return;
		for (i = 0; i < size; i++) {
			result[i] = (double*)malloc(sizeof(double) * size);
			if (result == NULL)return;
		}
		mat->doublematrix = result;
	}



	return mat;
}
void printMatirx(matrix* mat) {
	
	int i, j;

	if (mat->type == INT) {
		for (i = 0; i < mat->row_size; i++) {
			for (j = 0; j < mat->col_size; j++) {
				printf("%d", mat->intmatrix[i][j]);
				if (j < mat->col_size) {
					printf(" ");
				}
			}
			printf("\n");
		}
	}

	if (mat->type == FLOAT) {
		for (i = 0; i < mat->row_size; i++) {
			for (j = 0; j < mat->col_size; j++) {
				printf("%f", mat->floatmatrix[i][j]);
				if (j < mat->col_size) {
					printf(" ");
				}
			}
			printf("\n");
		}
	}

	if (mat->type == DOUBLE) {
		for (i = 0; i < mat->row_size; i++) {
			for (j = 0; j < mat->col_size; j++) {
				printf("%lf", mat->doublematrix[i][j]);
				if (j < mat->col_size) {
					printf(" ");
				}
			}
			printf("\n");
		}
	}


}
void removeMatrix_square_int(matrix* mat) {

	int i;
	
	if (mat->type == INT) {
		for (i = 0; i < mat->col_size; i++) {
			free(mat->intmatrix[i]);
		}
		free(mat->intmatrix);
	}

	else if (mat->type == FLOAT) {
		for (i = 0; i < mat->col_size; i++) {
			free(mat->floatmatrix[i]);
		}
		free(mat->floatmatrix);
	}

	else if (mat->type == DOUBLE) {
		for (i = 0; i < mat->col_size; i++) {
			free(mat->doublematrix[i]);
		}
		free(mat->doublematrix);
	}

	else return;


	free(mat);

}
matrix* matmul_square_int(matrix *mat1, matrix* mat2) {

	int i, j;
	int size = mat1->col_size;

	matrix* mat = NULL;
	int** result = NULL;
	int** matrix1 = NULL, ** matrix2 = NULL;
	mat = newMatrix_square_int(size, INT);
	result = mat->intmatrix;
	matrix1 = mat1->intmatrix;
	matrix2 = mat2->intmatrix;

	int sum_tmp = 0;
	int k;

	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {

			for (k = 0; k < size; k++) {
				sum_tmp = sum_tmp + matrix1[i][k] * matrix2[k][j];
			}

			result[i][j] = sum_tmp;
			sum_tmp = 0;
		}
	}

	return mat;

}

matrix* cofactor_int(matrix *mat, int row, int col) {


}

matrix* select_square_int(matrix* mat, int row, int col) {

	matrix* newmat = NULL;

	int size = mat->col_size;
	newmat = newMatrix_square_int(size - 1, INT);

	int i, j;


	for (i = 0; i < size; i++) { // 전체를 하나씩 도는 놈.
		for (j = 0; j < size; j++) {

			newmat->intmatrix[][];
			if () { // 그 필터조건 row col 에 걸리지 않으면.. 저장하는 것이야!

			} 
		}
	}


	return newmat;
}

matrix* det_square_int(matrix* mat) {

	// with cofactor

	// theorem
	// det(A^T) 와 det(A) 는 같다.
	// A의 한 행 또는 한 열을 바꾸어서 만들어진 행렬 B 는 det(A) = - det(B) 이다.
	// det(AB) = det(A) * det(B)
	// A의 한 행 또는 한 열의 원소가 전부 0 이면 det(A) 는 0이다
	// 상부삼각행렬 또는 하부삼각행렬이라면 행렬식은 주대각선의 원소 곱이다.
	// A의 한 행 또는 한 열의 원소에 k 를 곱한 행렬 B 의 det(B) 는 k * det(A) 이다.

	int size = mat->col_size;
	int answer = 0;
	int i, j;

	int co_factor;


	matrix* tmpmat = NULL;

	if (size == 1) {
		return mat->intmatrix[0][0];
	}

	if (size == 2) {
		return (mat->intmatrix[0][0] * mat->intmatrix[1][1]) - (mat->intmatrix[0][1] * mat->intmatrix[1][0]);
	}

	for (i = 0; i < size; i++) {
	
		tmpmat = select_square_int(mat, 0, i);
		answer = answer + det_square_int(tmpmat);

	}

	return answer;
}

int** inverseMatrix_square_int(int** matrix) {



}


int main() {

	matrix *mat1, *mat2;
	matrix* result;

	int size;

	size = 3;


	mat1 = newMatrix_square_int(size, INT);
	mat2 = newMatrix_square_int(size, INT);


	int i, j;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			scanf("%d", &(mat1->intmatrix[i][j]));
		}
	}

	/*
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			scanf("%d", &(mat2->intmatrix[i][j]));
		}
	}
	result = matmul_square_int(mat1, mat2);
	*/

	result = det_square_int(mat1);
	printf("%d", result);
//	printMatirx(result);

	return 0;
}