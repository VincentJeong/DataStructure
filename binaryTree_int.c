#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)


typedef struct treeNode {
	int key;                //������ �ʵ�
	struct treeNode* left;     //���� ����Ʈ�� ��ũ �ʵ�
	struct treeNode* right;    //������ ����Ʈ�� ��ũ �ʵ�
} treeNode;

typedef int element;  //char�� ���� Ž�� Ʈ�� element�� �ڷ������� ����

treeNode* Free = NULL;//�������� ����Ʈ�� ���۳�� ������
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
	printf("���� �޸�Ǯ = (");
	p = Free;
	while (p != NULL) {
		printf("%d", p->key);
		p = p->right;

		if (p != NULL) printf(", ");
	}
	printf(") \n");
}
treeNode* getNode(void)// �������� ����Ʈ������ ����Ҵ�
{
	treeNode* newnode = Free;
	if (newnode)
		Free = newnode->right;
	else
		printf("�޸�Ǯ�� �����̾�� ���α׷��� ��������\n");

	return newnode;
}

void returnNode(treeNode* old) {//�������� ����Ʈ�� ��� ��ȯ
	old->right = Free;//��ȯ ����� rlink�� ������������Ʈ ��ó���� ����
	Free = old;//Free�� ��ȯ��忡 ����
}


treeNode* insertNode(treeNode *p, int x)
{    //������ p�� ����Ű�� ���� ���Ͽ� ��� x�� �����ϴ� ����
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
	else  printf("\n �̹� ���� Ű�� �ֽ��ϴ�! \n");

	
	return p;
}

void deleteNode(treeNode *root, element key)
{     //root ������ Ž���Ͽ� key ���� ���� ��带 ã�� �����ϴ� ����
	treeNode *parent, *p, *succ, *succ_parent;
	treeNode *child;

	parent = NULL;
	p = root;
	while ((p != NULL) && (p->key != key)) 
	{  //������ ����� ��ġ Ž��
		parent = p;
		if (key < p->key) p = p->left;
		else p = p->right;
	}
	if (p == NULL) {  //������ ��尡 ���� ���
		printf("\n ã�� Ű�� ����Ʈ���� �����ϴ�!!");
		return;
	}

	// ������ ��尡 �ܸ������ ���
	if ((p->left == NULL) && (p->right == NULL))
	{
		if (parent != NULL) {
			if (parent->left == p) parent->left = NULL;
			else parent->right = NULL;
		}
		else root = NULL;
	}

	// ������ ��尡 �� ���� �ڽĳ�带 ���� ���
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

	// ������ ��尡 �� ���� �ڽĳ�带 ���� ���
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
{    //���� Ž�� Ʈ������ Ŷ���� x�� ����� ��ġ�� Ž���ϴ� ����
	treeNode* p;
	p = root;
	while (p != NULL) 
	{
		if (x < p->key) p = p->left;
		else if (x == p->key) return p;
		else p = p->right;
	}
	printf("\n ã�� Ű�� �����ϴ�!");
	return p;
}

void displayInorder(treeNode* root)
{    //���� Ž�� Ʈ���� ���� ��ȸ�ϸ鼭 ����ϴ� ����
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

		printf("1. Ʈ����� \n");
		printf("2. Ʈ�������ͻ��� \n");
		printf("3. ����\n");
		printf("4. ã��\n");


		printf("����: [   ]\b\b\b");
		scanf(" %c", &x);



		switch (x)
		{


		case '1':
		{

			printf("Ʈ�����\n");
			printf("inorder ::  "); displayInorder(root); printf("\n");
			printf("postorder ::  "); displayPostorder(root); printf("\n");
			printf("preorder ::  "); displayPreorder(root); printf("\n");
			printSpace();
			break;


		}
		case '2':
		{
			printf("������ ����?\n");
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
			printf("������ ����?\n");
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
			printf("ã�� ���ڸ� �Է��ϼ��� : ");
			scanf("%d", &key);
			foundedNode = searchBST(root, key);
			if (foundedNode != NULL)
				printf("\n %d �� ã�ҽ��ϴ�! \n", foundedNode->key);
			else  printf("\n ���ڸ� ã�� ���߽��ϴ�. \n");
			break;
		}





		case '0':               return 0;

		}
		printf("\n");
	}
	return 0;
}