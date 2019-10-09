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

//#define DEBUG

matrix* newMatrix_square(int size, int type) {

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
				printf("%.3f", mat->floatmatrix[i][j]);
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
				printf("%.3lf", mat->doublematrix[i][j]);
				if (j < mat->col_size) {
					printf(" ");
				}
			}
			printf("\n");
		}
	}


}
void removeMatrix_square(matrix* mat) {

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

matrix* copyMatrix_square(matrix* mat) {

	matrix* newmat = NULL;
	newmat = newMatrix_square(mat->col_size, mat->type);

	int row = mat->row_size;
	int col = mat->col_size;

	int i, j;
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			if (mat->type == INT) newmat->intmatrix[i][j] = mat->intmatrix[i][j];
			if (mat->type == FLOAT) newmat->floatmatrix[i][j] = mat->floatmatrix[i][j];
			if (mat->type == DOUBLE) newmat->doublematrix[i][j] = mat->doublematrix[i][j];
		}
	}

	return newmat;
}


matrix* matmul_square_int(matrix *mat1, matrix* mat2) {

	int i, j;
	int size = mat1->col_size;

	matrix* mat = NULL;
	mat = newMatrix_square(size, INT);

	int sum_tmp = 0;
	int k;

	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {

			for (k = 0; k < size; k++) {
				sum_tmp = sum_tmp + mat1->intmatrix[i][k] * mat2->intmatrix[k][j];
			}

			mat->intmatrix[i][j] = sum_tmp;
			sum_tmp = 0;
		}
	}

	return mat;

}

matrix* matmul_square_double(matrix* mat1, matrix* mat2) {

	int i, j;
	int size = mat1->col_size;

	matrix* mat = NULL;
	mat = newMatrix_square(size, DOUBLE);

	double sum_tmp = 0;
	int k;

	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {

			for (k = 0; k < size; k++) {
				sum_tmp = sum_tmp + mat1->doublematrix[i][k] * mat2->doublematrix[k][j];
			}

			mat->doublematrix[i][j] = sum_tmp;
			sum_tmp = 0;
		}
	}

	return mat;

}

matrix* mul_square_double(double k, matrix* mat) {
	
	int i, j;
	matrix* newmat = NULL;
	newmat = newMatrix_square(mat->col_size, mat->type);
	

	int row = mat->row_size;
	int col = mat->col_size;

	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			newmat->doublematrix[i][j] = mat->doublematrix[i][j] * k;
		}
	}

	return newmat;
}


matrix* select_square(matrix* mat, int row, int col) {

	matrix* newmat = NULL;

	int size = mat->col_size;
	

	if (mat->type == INT)
		newmat = newMatrix_square(size - 1, INT);
	else if (mat->type == DOUBLE)
		newmat = newMatrix_square(size - 1, DOUBLE);
	else if (mat->type == FLOAT)
		newmat = newMatrix_square(size - 1, FLOAT);
	else return;


	int i, j;

	int i_cnt = 0;
	int j_cnt = 0;
	for (i = 0; i < size; i++) { // 전체를 하나씩 도는 놈.
		for (j = 0; j < size; j++) {
			if (i != row && j != col) { // 그 필터조건 row col 에 걸리지 않으면.. 저장하는 것이야!
				if (mat->type == INT)	newmat->intmatrix[i_cnt][j_cnt] = mat->intmatrix[i][j];
				if (mat->type == FLOAT) newmat->floatmatrix[i_cnt][j_cnt] = mat->floatmatrix[i][j];
				if (mat->type == DOUBLE)newmat->doublematrix[i_cnt][j_cnt] = mat->doublematrix[i][j];
				j_cnt++;
				if (j_cnt == size - 1) {
					i_cnt++;
					j_cnt = 0;
				}
			} 
		}
	}
#ifdef DEBUG
	printMatirx(newmat);
#endif // DEBUG
	return newmat;
}


int det_square_int(matrix* mat) {

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

	matrix* tmpmat = NULL;

	if (size == 1) {
#ifdef DEBUG
		printf("answer : ");
		printMatirx(mat);
		printf("\n");
#endif // DEBUG
		int tmp;
		tmp = mat->intmatrix[0][0];
		removeMatrix_square(mat);
		return tmp;
	}

	if (size == 2) {
		int sarrus;
		sarrus = (mat->intmatrix[0][0] * mat->intmatrix[1][1]) - (mat->intmatrix[0][1] * mat->intmatrix[1][0]);
#ifdef DEBUG
		printf("answer : %d\n", sarrus);
#endif // DEBUG
		removeMatrix_square(mat);
		return sarrus;
	}

	else {
		int co_factor = 0;
		int sign_cofactor = -1;
		for (i = 0; i < size; i++) {
			tmpmat = select_square(mat, 0, i);

			if (((0 + 1) + (i + 1)) % 2 == 0) sign_cofactor = 1;
			else sign_cofactor = -1;

			co_factor = sign_cofactor * mat->intmatrix[0][i] * det_square_int(tmpmat);
			answer = answer + co_factor;
#ifdef DEBUG
			printf("---answer : %d*Aij = %d, --> %d\n", mat->intmatrix[0][i], co_factor, answer);

			if (size == 4) {
				printf("========answer cumsum : %d=========\n", answer);
			}
#endif // DEBUG

		}	
		//removeMatrix_square(mat);
		return answer;
	}

}

double det_square_double(matrix* mat) {

	int size = mat->col_size;
	double answer = 0;
	int i, j;

	matrix* tmpmat = NULL;

	if (size == 1) {
#ifdef DEBUG
		printf("answer : ");
		printMatirx(mat);
		printf("\n");
#endif // DEBUG
		float tmp;
		tmp = mat->doublematrix[0][0];
		removeMatrix_square(mat);
		return tmp;
	}

	if (size == 2) {
		double sarrus;
		sarrus = (mat->doublematrix[0][0] * mat->doublematrix[1][1]) - (mat->doublematrix[0][1] * mat->doublematrix[1][0]);
#ifdef DEBUG
		printf("answer : %.3f\n", sarrus);
#endif // DEBUG
		removeMatrix_square(mat);
		return sarrus;
	}

	
	else {
		double co_factor;
		int sign_cofactor = -1;

		for (i = 0; i < size; i++) {
			tmpmat = select_square(mat, 0, i);

			if (((0 + 1) + (i + 1)) % 2 == 0) sign_cofactor = 1;
			else sign_cofactor = -1;

			co_factor = sign_cofactor * mat->doublematrix[0][i] * det_square_double(tmpmat);
			answer = answer + co_factor;
		}
		//removeMatrix_square(mat);
		return answer;
	}
	

}



matrix* transposeMatrix_square(matrix* mat) {

	matrix* newmatrix = NULL;

	int size = mat->col_size;

	if (mat->type == INT) {
		int tmp;
		newmatrix = newMatrix_square(size, INT);

		int i, j;
		for (i = 0; i < size; i++) {
			for (j = 0; j < size; j++) {
				newmatrix->intmatrix[j][i] = mat->intmatrix[i][j];
			}
		}
	}


	else if (mat->type == FLOAT) {
		float tmp;
		newmatrix = newMatrix_square(size, FLOAT);

		int i, j;
		for (i = 0; i < size; i++) {
			for (j = 0; j < size; j++) {
				newmatrix->floatmatrix[j][i] = mat->floatmatrix[i][j];
			}
		}
	}



	else if (mat->type == DOUBLE) {
		double tmp;
		newmatrix = newMatrix_square(size, DOUBLE);

		int i, j;
		for (i = 0; i < size; i++) {
			for (j = 0; j < size; j++) {
				newmatrix->doublematrix[j][i] = mat->doublematrix[i][j];
			}
		}
	}



	else {
		return;
	}




	return newmatrix;
}

matrix* adjugateMatrix_square_double(matrix* mat) {

	matrix* newmatrix = NULL;
	int size = mat->col_size;
	newmatrix = newMatrix_square(size, DOUBLE);

	int i, j;
	int sign_cofactor = 1;

	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {

			if (((i + 1) + (j + 1)) % 2 == 0) sign_cofactor = 1;
			else sign_cofactor = -1;

			newmatrix->doublematrix[i][j] = sign_cofactor * det_square_double(select_square(mat, i, j));

		}
	}

	matrix* answermatrix = NULL;
	answermatrix = transposeMatrix_square(newmatrix);
	removeMatrix_square(newmatrix);
	return answermatrix;
}

matrix* inverseMatrix_square_double(matrix* mat) {

	// inverse matrix 를 만드는 방법

	// augmented matrix 를 만들어 두고 기본 행 연산을 수행한다.
	// adjugate Matrixmatrix 를 만들고, det의 역수를 곱해 준다.

	matrix* newmatrix = NULL;
	double determinant;
	
	newmatrix = adjugateMatrix_square_double(mat);
	determinant = det_square_double(mat);

#ifdef DEBUG
	printf("determinant : %.3f\n", determinant);
#endif // DEBUG

	if (determinant == 0) {
		printf("determinant is not defined!\n");
		return;
	}

	matrix* answermatrix = NULL;
	answermatrix = mul_square_double(1 / determinant, newmatrix);
	removeMatrix_square(newmatrix);

	return answermatrix;
}


int main() {

	matrix *mat1 = NULL, *mat2 = NULL, *mat3 = NULL;
	
	int result1;
	double result2;
	float result3;

	int size;

	size = 8;


	mat1 = newMatrix_square(size, INT);
	mat2 = newMatrix_square(size, DOUBLE);
	mat3 = newMatrix_square(size, FLOAT);

	int i, j;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
//			scanf("%d", &(mat1->intmatrix[i][j]));
			scanf("%lf", &(mat2->doublematrix[i][j]));
//			scanf("%f", &(mat3->floatmatrix[i][j]));
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
	
//	result1 = det_square_int(mat1);
//	printf("%d", result1);
//	result2 = det_square_double(mat2);
//	printf("%.3lf", result2);
//	result3 = det_square_double(mat3);
//	printf("%.3f", result3);

	matrix* tmpmat;
	matrix* printmat;

	tmpmat = inverseMatrix_square_double(mat2);
	printMatirx(tmpmat);

//	printmat = matmul_square_double(mat2, tmpmat);
//	printMatirx(printmat);
//	printf("\n");
//	free(printmat);
//	printmat = matmul_square_double(tmpmat, mat2);
//	printMatirx(printmat);

	return 0;
}