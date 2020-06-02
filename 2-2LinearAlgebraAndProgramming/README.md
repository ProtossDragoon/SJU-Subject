# Example Code

<br>

**구조체 정의**
``` C
typedef struct matrix matrix;
struct matrix {
	int **intmatrix;
	float **floatmatrix;
	double **doublematrix;
	int type;
	int row_size;
	int col_size;
};
```

<br>
<br>


**메소드 정의**
``` C
matrix* newMatrix_square(int size, int type);
void removeMatrix_square(matrix* mat);
matrix* copyMatrix_square(matrix* mat);
// matrix 생성과 소멸과 복사 메모리 관리를 위해 사용. 이것때문에 개고생했네...

matrix* matmul_square_int(matrix *mat1, matrix* mat2);
matrix* matmul_square_double(matrix* mat1, matrix* mat2);
// matrix 곱을 반환함. mat1, mat2 는 훼손되지 않음.
 
matrix* mul_square_double(double k, matrix* mat);
// 상수 * matrix 곱을 반환함. mat 는 훼손되지 않음.

int det_square_int(matrix* mat);
double det_square_double(matrix* mat);
// determinant(행렬식) 를 [cofactor 을 이용하여] 구할때 사용. 기존 mat 은 훼손되지 않음.

matrix* transposeMatrix_square(matrix* mat);
// transpose matrix (전치행렬) 을 만들 때 사용. 기존 mat 은 훼손되지 않음.

matrix* adjugateMatrix_square_double(matrix* mat);
// adjugate matrix (수반행렬) 을 만들 때 사용. 기존 mat 은 훼손되지 않음.

matrix* inverseMatrix_square_double(matrix* mat);
// inverse matrix (역행렬) 을 [determine, adjugate matrix 를 이용하여] 만들 때 사용. 기존 mat 은 훼손되지 않음.

matrix* select_square(matrix* mat, int row, int col);
// cofactor 을 만들 때 사용. 특정 row 와 특정 col 을 제거한 matrix 를 새로 만들어서 반환함.

void printMatirx(matrix* mat);
// matrix 구조체를 print 할 때 사용
```
