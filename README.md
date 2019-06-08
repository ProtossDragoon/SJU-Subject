# SJU-Subject <br>
Eng : Repository for recording Assignment and Homework from Sejong University <br>

Kor : 이 저장소는 세종대학교에서 이루어지는 수업에서 작성한 코드들을 보관합니다.


<h1>Grade 2 (2019)</h1>

<h2>Data Structure</h2>

| Semester | Professor | Lecture Name | Language | Lecture Hours / week | Credit | GradePoint (A~D,F) |
|:--------|:--------|:--------|:--------|:---------|:---------|:---------|
| Spring | ys Cho | Data Structure  | Korean | 5hours / week | 4 | A+ (4.5) |
| 1학기 | 조윤식 | 자료구조 및 실습  | 한국어 | 5시간 / 주 | 4 | A+ (4.5)|



| Editing Period | File Main Title | File Sub Title | Environment | Contents | Focus On & Main issue |
|:--------|:--------|:--------|:--------|:---------|:---------|
|| 자료구조 | 9주차 |  C / VS2019 | | |
|| 자료구조 | 10주차 |  C / VS2019 | | |
|| 자료구조 | 11주차 |  C / VS2019 | Make Capsulized Queue ADT method & bug fix | ADT Capsulization <br> *significant error (find 2019/05/28) : element pointer sometimes grab unnecessary memories and don't free flexibly. My big mistake. This error will be fixed after this week's solutions* |
|~2019/<br>05/30| 자료구조 | 12주차 |  C / VS2019 | Tree | Make Capsulized Tree ADT method <br> 기존에 사용했던 element를 유연한 적용을 위해 element 구조체를 새로 정의하고, binary tree 메소드를 모두 정의해 보았다. |
|~2019/<br>05/31| 자료구조 | 13주차 |  C / VS2019 | Tree | Make Capsulized Tree ADT method & bug fix <br> upgrade function : more parameter and more option. 어떻게 오버로딩 없이 함수를 깔끔하게 구성할 수 있을까에 대한 고민. 전역변수도 사용해 보고 했지만 무엇보다 함수 파라미터를 일일이 다 바꾸어 주어야 한다는 것은 너무 귀찮았음. 그런데 오버로딩이나 오버라이딩이 금지되어 있기 때문에 더욱 깔끔한 코드를 작성하는 방법에 대한 고민을 많이 하게 되는 것 같음. |
|~2019/<br>06/02| 자료구조 | HW 3 4 | C / VS2019 | Deque by Stack, Stack by Queue | Make complicated data structure ADT methods like Deque and Stack implemented by simple data structure ADT mehtods |
|| 자료구조 | 13주차 |  C / VS2019 | | Install GCC compiler & VS code|


<h4>example code</h4>

```python
print("hello world")
```

<h5>14주차 : Tree</h5>

```C
//현재 위치에서 전위순회 기준 다음 노드를 반환하는 함수를 작성한다.
tr_nd_bylist* tr_nextNodeByPreorder_byList(tr_nd_bylist *node) {

	if (tr_bi_isInternal_byList(node)) {

		if (tr_bi_isLeftChildExist_byList(node)) return tr_bi_leftChild_byList(node);
		else 					 return tr_bi_rightChild_byList(node);
	}	
	
	tr_nd_bylist* tmpnode;
	tmpnode = node->parent;
	if (tmpnode == NULL)return;

	while (1) {
		while (node != tr_bi_leftChild_byList(tmpnode)) {

			if (tr_bi_isRootNode_byList(tmpnode)) {
				//한바퀴 돌아 다시 root node 로 돌아오는 케이스.
				return NULL;
			}
			node = tmpnode;
			tmpnode = tmpnode->parent;
		}
		if (tr_bi_isRightChildExist_byList(tmpnode)) return tr_bi_rightChild_byList(tmpnode);

		node = tmpnode;
		tmpnode = tmpnode->parent;
		if (tmpnode == NULL)return;
	}
}
```


<br>
<h2>Basic of Data Analysis</h2>

| Semester | Professor | Lecture Name | Language | Lecture Hours / week | Credit | GradePoint (A~D,F) |
|:--------|:--------|:--------|:--------|:---------|:---------|:---------|
| Spring | jw Song | Basic of <br>Data Analysis  | Kor, Eng | 3hours / week | 3 |B+ (3.5)|
| 1학기 | 송재욱 | 데이터분석개론  | 한국어, 영어 | 3시간 / 주 | 3 |B+ (3.5)|


