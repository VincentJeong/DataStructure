#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)


typedef struct treeNode {
	int key;                //데이터 필드
	struct treeNode* left;     //왼쪽 서브트리 링크 필드
	struct treeNode* right;    //오른쪽 서브트리 링크 필드
} treeNode;

typedef int element;  //char을 이진 탐색 트리 element의 자료형으로 정의

treeNode* Free = NULL;//자유공간 리스트의 시작노드 포인터
treeNode pool[10];
void init()
{
	int i;
	for (i = 0; i < 9; i++)
		pool[i].right = &pool[i + 1];
	//pool[i].right = NULL;

	Free = pool;
}

void printSpace()
{
	treeNode* p;
	printf("남은 메모리풀 = (");
	p = Free;
	while (p != NULL) {
		printf("%d", p->key);
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
	old->right = Free;//반환 노드의 rlink에 자유공간리스트 맨처음을 연결
	Free = old;//Free를 반환노드에 연결
}


treeNode* insertNode(treeNode *p, int x)
{    //포인터 p가 가리키는 노드와 비교하여 노드 x를 삽입하는 연산
	treeNode *newNode;
	if (p == NULL) {
		//newNode = (treeNode*)malloc(sizeof(treeNode));
		newNode = getNode();
		newNode->key = x;
		newNode->left = NULL;
		newNode->right = NULL;
		return newNode;
	}
	else if (x < p->key)  p->left = insertNode(p->left, x);
	else if (x > p->key)  p->right = insertNode(p->right, x);
	else  printf("\n 이미 같은 키가 있습니다! \n");

	
	return p;
}

void deleteNode(treeNode *root, element key)
{     //root 노드부터 탐색하여 key 값과 같은 노드를 찾아 삭제하는 연산
	treeNode *parent, *p, *succ, *succ_parent;
	treeNode *child;

	parent = NULL;
	p = root;
	while ((p != NULL) && (p->key != key)) 
	{  //삭제할 노드의 위치 탐색
		parent = p;
		if (key < p->key) p = p->left;
		else p = p->right;
	}
	if (p == NULL) {  //삭제할 노드가 없는 경우
		printf("\n 찾는 키가 이진트리에 없습니다!!");
		return;
	}

	// 삭제할 노드가 단말노드인 경우
	if ((p->left == NULL) && (p->right == NULL))
	{
		if (parent != NULL) {
			if (parent->left == p) parent->left = NULL;
			else parent->right = NULL;
		}
		else root = NULL;
	}

	// 삭제할 노드가 한 개의 자식노드를 가진 경우
	else if ((p->left == NULL) || (p->right == NULL)) 
	{
		if (p->left != NULL) child = p->left;
		else child = p->right;

		if (parent != NULL) {
			if (parent->left == p) parent->left = child;
			else parent->right = child;
		}
		else root = child;
	}

	// 삭제할 노드가 두 개의 자식노드를 가진 경우
	else {
		succ_parent = p;
		succ = p->left;
		while (succ->right != NULL) {
			succ_parent = succ;
			succ = succ->right;
		}
		if (succ_parent->left == succ)  succ_parent->left = succ->left;
		else succ_parent->right = succ->left;
		p->key = succ->key;
		p = succ;
	}
	returnNode(p);
}

treeNode* searchBST(treeNode* root, char x)
{    //이진 탐색 트리에서 킷값이 x인 노드의 위치를 탐색하는 연산
	treeNode* p;
	p = root;
	while (p != NULL) 
	{
		if (x < p->key) p = p->left;
		else if (x == p->key) return p;
		else p = p->right;
	}
	printf("\n 찾는 키가 없습니다!");
	return p;
}

void displayInorder(treeNode* root)
{    //이진 탐색 트리를 중위 순회하면서 출력하는 연산
	if (root)
	{
		displayInorder(root->left);
		printf("%d_", root->key);
		displayInorder(root->right);
	}
}

void displayPreorder(treeNode * root)
{
	if (root)
	{
		printf("%d_", root->key);
		displayPreorder(root->left);
		displayPreorder(root->right);
	}
}

void displayPostorder(treeNode* root)
{
	if (root)
	{
		displayPostorder(root->left);
		displayPostorder(root->right);
		printf("%d_", root->key);
		}
	}

int main()
{
	init();
	char x;
	treeNode*root = NULL;
	treeNode*foundedNode = NULL;
	root = insertNode(root, 5);
	int key;

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
			printf("삽입할 문자?\n");
			scanf("%d", &key);
			insertNode(root, key);
			printf("inorder ::  "); displayInorder(root); printf("\n");
			printf("postorder ::  "); displayPostorder(root); printf("\n");
			printf("preorder ::  "); displayPreorder(root); printf("\n");
			printf("\n");
			printSpace();
			break;
		}

		case '3':
		{
			printf("삭제할 문자?\n");
			scanf("%d", &key);
			deleteNode(root, key);
			printf("inorder ::  "); displayInorder(root); printf("\n");
			printf("postorder ::  "); displayPostorder(root); printf("\n");
			printf("preorder ::  "); displayPreorder(root); printf("\n");
			printf("\n");
			printSpace();
			break;

		}

		case '4':
		{
			printf("찾을 문자를 입력하세요 : ");
			scanf("%d", &key);
			foundedNode = searchBST(root, key);
			if (foundedNode != NULL)
				printf("\n %d 를 찾았습니다! \n", foundedNode->key);
			else  printf("\n 문자를 찾지 못했습니다. \n");
			break;
		}





		case '0':               return 0;

		}
		printf("\n");
	}
	return 0;
}