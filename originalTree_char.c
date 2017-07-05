#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)


typedef struct treeNode {
	char key;                //데이터 필드
	struct treeNode* left;     //왼쪽 서브트리 링크 필드
	struct treeNode* right;    //오른쪽 서브트리 링크 필드
} treeNode;

typedef char element;  //char을 이진 탐색 트리 element의 자료형으로 정의

treeNode* Free = NULL;//자유공간 리스트의 시작노드 포인터
treeNode pool[10];
treeNode* paren = NULL;

void init() //자유공간 초기화
{
	int i;
	for (i = 0; i < 9; i++)
		pool[i].right = &pool[i + 1];
	

	Free = pool;
}

void printSpace()
{
	treeNode* p;
	printf("남은 메모리풀 = (");
	p = Free;
	while (p != NULL) {
		printf("%p", p);
		p = p->right;

		if (p != NULL) printf(", ");
	}
	printf(") \n");
}
treeNode* getNode(void)// 자유공간 리스트에서의 노드할당
{
	treeNode* newnode = Free;
	if (newnode)
		Free = newnode->right;
	else
		printf("메모리풀에 쓸것이없어서 프로그램이 뻑날것임\n");

	return newnode;
}

void returnNode(treeNode* old) {//자유공간 리스트로 노드 반환
	old->right = Free;//
	Free = old;//
}




void displayInorder(treeNode* root)
{    //이진 탐색 트리를 중위 순회하면서 출력하는 연산
	if (root) {
		displayInorder(root->left);
		
		printf("%c_", root->key);
		displayInorder(root->right);
	}
}

void displayPreorder(treeNode * root) //전위
{
	if (root)
	{
		printf("%c_", root->key);
		displayPreorder(root->left);
		displayPreorder(root->right);
	}
}

void displayPostorder(treeNode* root) //후위
{
	if (root)
	{
		displayPostorder(root->left);
		displayPostorder(root->right);
		printf("%c_", root->key);
	}
}
treeNode * makeRootNode(char data, treeNode*leftNode, treeNode*rightNode)
{
	treeNode* root = getNode();
	root->key = data;
	root->left = leftNode;
	root->right = rightNode;
	return root;
}

void insertNode(treeNode* p, char x, char y) {
	if (p) {
		if (p->key == x) {
			treeNode* newNode = getNode();
			newNode->key = y;
			newNode->left = NULL;
			newNode->right = NULL;

			if (p->left == NULL)
				p->left = newNode;
			else if (p->right == NULL)
				p->right = newNode;
			else {
				//newNode->left = p->left;
				//p->left = newNode;
				printf("꽉차서 삽입을 못합니다. \n");
				returnNode(newNode); //삽입을못했으니깐 강퇴당함
			}
		}
		insertNode(p->left, x, y);
		insertNode(p->right, x, y);
	}
}



// 삭제 할 노드의 부모노드를 찾는 함수
void searchDeleteNodeParent(treeNode* root, char data)
{
	if (root) {
		treeNode* p;
		if (root->left != NULL)
		{
			p = root->left;
			if (data == p->key) 
			{
				paren = root;
			}
		}
		if (root->right != NULL)
		{
			p = root->right;
			if (data == p->key)
			{
				paren = root;
			}
		}
		searchDeleteNodeParent(root->left, data);
		searchDeleteNodeParent(root->right, data);
	}
}

void deleteNode(treeNode* root, treeNode* par, char data) 
{

	treeNode* parent, *p, *succ, *succ_parent;
	treeNode* child;
	parent = par;

	if (par->left->key == data)
		p = par->left;
	else
		p = par->right;

	// 삭제할 노드가 없는 경우
	if (p == NULL) {
		printf("\n 찾는 데이터가 이진 트리에 없습니다!!\n");
		return;
	}
	// 삭제할 노드가 Leaf 노드인 경우
	if ((p->left == NULL) && (p->right == NULL)) {
		if (parent != NULL) {
			if (parent->left == p)
				parent->left = NULL;
			else
				parent->right = NULL;
		}
		else
			root = NULL;
		//free(p);
		returnNode(p);
	}
	// 삭제할 노드가 한 개의 자식 노드를 가진 경우
	else if ((p->left == NULL) || (p->right == NULL)) {
		if (p->left != NULL)
			child = p->left;
		else
			child = p->right;

		if (parent != NULL) {
			if (parent->left == p)
				parent->left = child;
			else
				parent->right = child;
		}
		else
			root = child;
		//free(p);
		returnNode(p);
	}
	// 삭제할 노드가 두 개의 자식 노드를 가진 경우
	else {
		succ_parent = p;
		succ = p->left;
		while (succ->right != NULL) {
			succ_parent = succ;
			succ = succ->right;
		}
		if (succ_parent->left == succ)
			succ_parent->left = succ->left;
		else
			succ_parent->right = succ->left;

		succ_parent->key = succ->key;
		//p->data = succ->data;
		p = succ;
		returnNode(p);
	}
}


void searchNode(treeNode* root, char x)
{
	if (root) {
		treeNode* p = root->left;
		if (p == NULL)
			goto here;
		if (p->key == x) {
			if (p->key != NULL && p->left != NULL && p->right != NULL)
				printf("%c를 찾았습니다.\n부모노드는 %c, 왼쪽노드는 %c, 오른쪽 노드는 %c\n", root->key, p->left->key, p->right->key);
			else if (p->key != NULL && p->left != NULL && p->right == NULL)
				printf("%c를 찾았습니다.\n부모노드는 %c, 왼쪽노드는 %c\n", root->key, p->left->key);
			else if (p->key != NULL && p->left == NULL && p->right != NULL)
				printf("%c를 찾았습니다.\n부모노드는 %c, 오른쪽노드는 %c\n", root->key, p->right->key);
			else
				printf("%c를 찾았습니다.\n부모노드는 %c, %c는 리프노드입니다.\n", p->key, root->key, p->key);
		}
	here:
		p = root->right;
		if (p == NULL)
			goto next;
		if (p->key == x) {
			if (p->key != NULL && p->left != NULL && p->right != NULL)
				printf("%c를 찾았습니다.\n부모노드는 %c, 왼쪽노드는 %c, 오른쪽 노드는 %c\n", root->key, p->left->key, p->right->key);
			else if (p->key != NULL && p->left != NULL && p->right == NULL)
				printf("%c를 찾았습니다.\n부모노드는 %c, 왼쪽노드는 %c\n", root->key, p->left->key);
			else if (p->key != NULL && p->left == NULL && p->right != NULL)
				printf("%c를 찾았습니다.\n부모노드는 %c, 오른쪽노드는 %c\n", root->key, p->right->key);
			else
				printf("%c를 찾았습니다.\n부모노드는 %c, %c는 리프노드입니다.\n", p->key, root->key, p->key);
		}
	next:
		searchNode(root->left, x);
		searchNode(root->right, x);

	}
}



int main()
{
	init();
	char x;
	//treeNode*root = NULL;
	treeNode*foundedNode = NULL;
	treeNode *root;
	
	treeNode*n5 = makeRootNode('D', NULL, NULL);
	treeNode*n4 = makeRootNode('E', NULL, NULL);
	treeNode*n3 = makeRootNode('C', n5, n4);
	treeNode*n2 = makeRootNode('B', NULL, NULL);
	treeNode*n1 = makeRootNode('A', n2, n3);

	root = n1;



	//root = insertNode(root, 'G');
	char key;
	char input;

	while (1)
	{

		printf("1. 트리출력 \n");
		printf("2. 트리데이터삽입 \n");
		printf("3. 삭제\n");
		printf("4. 찾기\n");


		printf("선택: [   ]\b\b\b");
		scanf(" %c", &x);



		switch (x)
		{


		case '1':
		{

			printf("트리출력\n");
			printf("inorder ::  "); displayInorder(root); printf("\n");
			printf("postorder ::  "); displayPostorder(root); printf("\n");
			printf("preorder ::  "); displayPreorder(root); printf("\n");
			
			printSpace();
			break;


		}
		case '2':
		{
			printf("누구의 자녀로?\n");
			scanf(" %c", &input);
			printf("삽입할 문자?\n");
			scanf(" %c", &key);
			insertNode(root, input, key);
			
			printf("inorder ::  "); displayInorder(root); printf("\n");
			printf("postorder ::  "); displayPostorder(root); printf("\n");
			printf("preorder ::  "); displayPreorder(root); printf("\n");
			printSpace();
			break;
		}

		case '3':
		{
			printf("삭제할 문자?\n");
			scanf(" %c", &key);
			searchDeleteNodeParent(root, key);
			deleteNode(root, paren, key);

			printf("inorder ::  "); displayInorder(root); printf("\n");
			printf("postorder ::  "); displayPostorder(root); printf("\n");
			printf("preorder ::  "); displayPreorder(root); printf("\n");
			printSpace();
			break;

		}

		case '4':
		{
			printf("찾을 문자를 입력하세요 : ");
			scanf(" %c", &key);
			searchNode(root, key);
			
			break;
		}





		case '0':               return 0;

		}
		printf("\n");
	}
	return 0;
}