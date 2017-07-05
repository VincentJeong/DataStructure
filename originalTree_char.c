#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)


typedef struct treeNode {
	char key;                //������ �ʵ�
	struct treeNode* left;     //���� ����Ʈ�� ��ũ �ʵ�
	struct treeNode* right;    //������ ����Ʈ�� ��ũ �ʵ�
} treeNode;

typedef char element;  //char�� ���� Ž�� Ʈ�� element�� �ڷ������� ����

treeNode* Free = NULL;//�������� ����Ʈ�� ���۳�� ������
treeNode pool[10];
treeNode* paren = NULL;

void init() //�������� �ʱ�ȭ
{
	int i;
	for (i = 0; i < 9; i++)
		pool[i].right = &pool[i + 1];
	

	Free = pool;
}

void printSpace()
{
	treeNode* p;
	printf("���� �޸�Ǯ = (");
	p = Free;
	while (p != NULL) {
		printf("%p", p);
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
	old->right = Free;//
	Free = old;//
}




void displayInorder(treeNode* root)
{    //���� Ž�� Ʈ���� ���� ��ȸ�ϸ鼭 ����ϴ� ����
	if (root) {
		displayInorder(root->left);
		
		printf("%c_", root->key);
		displayInorder(root->right);
	}
}

void displayPreorder(treeNode * root) //����
{
	if (root)
	{
		printf("%c_", root->key);
		displayPreorder(root->left);
		displayPreorder(root->right);
	}
}

void displayPostorder(treeNode* root) //����
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
				printf("������ ������ ���մϴ�. \n");
				returnNode(newNode); //�������������ϱ� �������
			}
		}
		insertNode(p->left, x, y);
		insertNode(p->right, x, y);
	}
}



// ���� �� ����� �θ��带 ã�� �Լ�
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

	// ������ ��尡 ���� ���
	if (p == NULL) {
		printf("\n ã�� �����Ͱ� ���� Ʈ���� �����ϴ�!!\n");
		return;
	}
	// ������ ��尡 Leaf ����� ���
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
	// ������ ��尡 �� ���� �ڽ� ��带 ���� ���
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
	// ������ ��尡 �� ���� �ڽ� ��带 ���� ���
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
				printf("%c�� ã�ҽ��ϴ�.\n�θ���� %c, ���ʳ��� %c, ������ ���� %c\n", root->key, p->left->key, p->right->key);
			else if (p->key != NULL && p->left != NULL && p->right == NULL)
				printf("%c�� ã�ҽ��ϴ�.\n�θ���� %c, ���ʳ��� %c\n", root->key, p->left->key);
			else if (p->key != NULL && p->left == NULL && p->right != NULL)
				printf("%c�� ã�ҽ��ϴ�.\n�θ���� %c, �����ʳ��� %c\n", root->key, p->right->key);
			else
				printf("%c�� ã�ҽ��ϴ�.\n�θ���� %c, %c�� ��������Դϴ�.\n", p->key, root->key, p->key);
		}
	here:
		p = root->right;
		if (p == NULL)
			goto next;
		if (p->key == x) {
			if (p->key != NULL && p->left != NULL && p->right != NULL)
				printf("%c�� ã�ҽ��ϴ�.\n�θ���� %c, ���ʳ��� %c, ������ ���� %c\n", root->key, p->left->key, p->right->key);
			else if (p->key != NULL && p->left != NULL && p->right == NULL)
				printf("%c�� ã�ҽ��ϴ�.\n�θ���� %c, ���ʳ��� %c\n", root->key, p->left->key);
			else if (p->key != NULL && p->left == NULL && p->right != NULL)
				printf("%c�� ã�ҽ��ϴ�.\n�θ���� %c, �����ʳ��� %c\n", root->key, p->right->key);
			else
				printf("%c�� ã�ҽ��ϴ�.\n�θ���� %c, %c�� ��������Դϴ�.\n", p->key, root->key, p->key);
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
			printf("������ �ڳ��?\n");
			scanf(" %c", &input);
			printf("������ ����?\n");
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
			printf("������ ����?\n");
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
			printf("ã�� ���ڸ� �Է��ϼ��� : ");
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