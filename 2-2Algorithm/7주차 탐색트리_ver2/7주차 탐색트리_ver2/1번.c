#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct treenode trnd;
struct treenode {

	trnd* leftchild;
	trnd* rightchild;
	trnd* parent;
	int key;

};

int isExternal(trnd* node) {
	//완전 이진 트리를 전제로 하기 때문에..
	if (node->leftchild == NULL) {
		return 1;
	}
	if (node->rightchild == NULL) {
		return 1;
	}
	return 0;
}
trnd* inOrderSuc(trnd* node) {

	//

	//


	//

}
int findelement(trnd* root, int key) {




}
int insertItem(trnd* root, int key) {



}
int treeSearch(trnd* root, int key) {



}
int removeElement(trnd* root, int key) {



}





int main() {


	char input; 

	while (1) {

		scanf("%c", &input);

		if (input == 'i') {


		}
		else if (input == 'd') {



		}
		else if (input == 's') {


		}
		else if (input == 'p') {



		}
		else { // input == 'q'
			return;
		}




	}



	return 0;
}