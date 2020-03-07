# SJU-Subject <br>
Eng : Repository for recording Assignment and Homework from Sejong University <br>

Kor : 이 저장소는 세종대학교에서 이루어지는 수업에서 작성한 코드들을 보관합니다.


<h1>Grade 2 (2019)</h1>

<h2>Data Structure</h2>

| Semester | Professor | Lecture Name | Language | Lecture Hours / week | Credit | GradePoint (A~D,F) |
|:--------|:--------|:--------|:--------|:---------|:---------|:---------|
| Spring | ys Cho | Data Structure  | Korean | 5hours / week | 4 | B+ (3.5) |
| 1학기 | 조윤식 | 자료구조 및 실습  | 한국어 | 5시간 / 주 | 4 | B+ (3.5)|



| Editing Period | File Main Title | File Sub Title | Environment | Contents | Focus On & Main issue |
|:--------|:--------|:--------|:--------|:---------|:---------|
|| 자료구조 | 9주차 |  C / VS2019 | Stack | |
|| 자료구조 | 10주차 |  C / VS2019 | Stack | |
|~2019/<br>06/15| 자료구조 | 11주차 |  C / VS2019 | Queue | ADT Capsulization, make Cricle queue methods<br> *significant error (find 2019/05/28) : element pointer sometimes grab unnecessary memories and not be free flexibly. My big mistake. This error will be fixed after this week's solutions* |
|~2019/<br>05/30| 자료구조 | 12주차 |  C / VS2019 | Tree | Make Capsulized Tree ADT method <br> 기존에 사용했던 element를 유연한 적용을 위해 element 구조체를 새로 정의하고, binary tree 메소드를 모두 정의해 보았다. |
|~2019/<br>05/31| 자료구조 | 13주차 |  C / VS2019 | Binary Tree | 어떻게 오버로딩 없이 함수를 깔끔하게 구성할 수 있을까에 대한 고민. 전역변수도 사용해 보고 했지만 무엇보다 함수 파라미터를 일일이 다 바꾸어 주어야 한다는 것은 너무 귀찮았음. 그런데 오버로딩이나 오버라이딩이 금지되어 있기 때문에 더욱 깔끔한 코드를 작성하는 방법에 대한 고민을 많이 하게 되는 것 같음. |
|~2019/<br>06/02| 자료구조 | HW 3 4 | C / VS2019 | Deque by Stack, Stack by Queue | Make complicated data structure ADT methods like Deque and Stack implemented by simple data structure ADT mehtods |
|~2019/<br>06/10| 자료구조 | 14주차 |  C / VS2019 | Binary Tree | Bug fix from week 13, add some function : Example Code |
|~2019/<br>06/10| 자료구조 | 7주차 |  C / VS2019 | Destructive Set | Make Capsulized Set ADT method |
|~2019/<br>06/18| 자료구조 | HW 5 |  C / VS2019 | Binary Tree | 현재 위치에서 전위순회 기준 다음 노드를 반환하는 함수를 작성한다. 그리고, 전위순회하여 input 과 일치하는 원소를 가진 node를 찾아내는 함수를 제작함.|





<br>
<h2>Basic of Data Analysis</h2>

| Semester | Professor | Lecture Name | Language | Lecture Hours / week | Credit | GradePoint (A~D,F) |
|:--------|:--------|:--------|:--------|:---------|:---------|:---------|
| Spring | jw Song | Basic of <br>Data Analysis  | Kor, Eng | 3hours / week | 3 |A+ (4.5)|
| 1학기 | 송재욱 | 데이터분석개론  | 한국어, 영어 | 3시간 / 주 | 3 |A+ (4.5)|




| Editing Period | File Main Title | File Sub Title | Environment | Contents | Focus On & Main issue |
|:--------|:--------|:--------|:--------|:---------|:---------|
|| BasicOfDataAnalysis | 1st assignment |  python / Jupyter notebook | Data pre processing<br> PCA <br> Simple data Visuallization |  |
|| BasicOfDataAnalysis | 3rd assignment |  python / Jupyter notebook | Final Project - Free Topic | Titanic, Machine Learning From Disaster. Focused on "Study" about "Real Titanic" (Domain Knoledge Study) |

<br>
[기말고사 과제]https://github.com/ProtossDragoon/SJU-Subject/blob/master/2-1BasicOfDataAnalysis/3rd%20Assignment/IDA_A3_%EC%9D%B4%EC%9E%A5%ED%9B%84_18011573.ipynb


<br>
<h2>Algorithm</h2>

| Semester | Professor | Lecture Name | Language | Lecture Hours / week | Credit | GradePoint (A~D,F) |
|:--------|:--------|:--------|:--------|:---------|:---------|:---------|
| Summer |  | Algorithm  | Kor | 5hours / week | 4 | A0 |
| 2학기 | 나중채 | 알고리즘및실습  | 한국어 | 5시간 / 주 | 4 | A0 |

<br>

| Editing Period | File Main Title | File Sub Title | Environment | Contents | Focus On & Main issue |
|:--------|:--------|:--------|:--------|:---------|:---------|
|| Algorithm | 자료구조 복습 |  C / VS2019 | linked list, binary tree |  |
|~2019/09/11| Algorithm | Priority Queue |  C / VS2019 | Priority Queue and Selection/Insertion sorting | Capsulization |




<br>
<h2>Linear Algebra with Programming</h2>

| Semester | Professor | Lecture Name | Language | Lecture Hours / week | Credit | GradePoint (A~D,F) |
|:--------|:--------|:--------|:--------|:---------|:---------|:---------|
| Second |  | Linear Algebra  | Kor | 3hours / week | 3 | - |
| 2학기 | 이영렬 | 선형대수및프로그래밍 | 한국어 | 3시간 / 주 | 3 |-|

- 아파서 시험못봄 ㅠㅠ



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



<br>
<h2>Computer Organization And Design</h2>

| Semester | Professor | Lecture Name | Language | Lecture Hours / week | Credit | GradePoint (A~D,F) |
|:--------|:--------|:--------|:--------|:---------|:---------|:---------|
| Second | Gi-Ho Park | Computer Structure  | Kor | 3hours / week | 3 | B+ |
| 2학기 | 박기호 | 컴퓨터구조 | 한국어 | 3시간 / 주 | 3 | B+ |

<br>

| Editing Period | File Main Title | File Sub Title | Environment | Contents | Focus On & Main issue |
|:--------|:--------|:--------|:--------|:---------|:---------|
| 1/4 | Computer Organization ... | mars | Assembly / Mars | understand ISA with Assembly | program pointer, stack pointer 로 재귀함수 구현 등 |
| 2/4 | Computer Organization ... | cahcesim |  C / VS2019 | Cahce simulator |  |
| 3/4 | Computer Organization ... | mipscpu |  C / VS2019 | cpu datapath | make cpu datapath with capsulized function |



<br>
