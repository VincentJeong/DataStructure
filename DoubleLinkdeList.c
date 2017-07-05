#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

typedef struct ListNode {  //�ܼ����Ḯ��Ʈ�� ��� ���� ����
	char data[20];
	struct ListNode* right;
	struct ListNode* left;
} listNode;

typedef struct {   //����Ʈ�� ��� ����� ���� ����
	listNode* head;

} linkedList_h;

/////////////////////////////////////////////////////////////////////////////
linkedList_h* createLinkedList_h(void);
void freeLinkedList_h(linkedList_h*);//�̱���
void reverse(linkedList_h*);//�̱���
void deleteLastNode(linkedList_h*);
void deleteFirstNode(linkedList_h*);
void deleteSearchNode(linkedList_h *, listNode *);
void printList(linkedList_h*);
void insertFirstNode(linkedList_h*, char*);
void insertMiddleNode(linkedList_h*, listNode*, char*);
void addLastNode(linkedList_h*, char*);
listNode* searchNode(linkedList_h*, char *);
/////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
listNode* Free = NULL;//�������� ����Ʈ�� ���۳�� ������
listNode pool[10];
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
	listNode* p;
	printf("���� �޸�Ǯ = (");
	p = Free;
	while (p != NULL) {
		printf("%p", p);
		p = p->right;

		if (p != NULL) printf(", ");
	}
	printf(") \n");
}
listNode* getNode(void)// �������� ����Ʈ������ ����Ҵ�
{
	listNode* newnode = Free;
	if (newnode)
		Free = newnode->right;
	else
		printf("�޸�Ǯ�� �����̾�� ���α׷��� ��������\n");

	return newnode;
}

void returnNode(listNode* old) {//�������� ����Ʈ�� ��� ��ȯ
	old->right = Free;//��ȯ ����� rlink�� ������������Ʈ ��ó���� ����
	Free = old;//Free�� ��ȯ��忡 ����
}
///////////////////////////////////////////////////////////////////////////////////////

void printList(linkedList_h* L) {   //��� ������� ����Ʈ�� ����ϴ� ����
	listNode* p;
	printf("���縮��Ʈ = (");
	p = L->head;
	while (p != NULL) {
		printf("%s", p->data);
		p = p->right;

		if (p != NULL) printf(", ");
	}
	printf(") \n");
}

listNode *searchNode(linkedList_h *L, char *a)
{
	listNode * temp;
	temp = L->head;
	while (temp != NULL)
	{
		if (strcmp(temp->data, a) == 0)
		{
			return temp;
		}
		temp = temp->right;
	}
	return NULL;
}

linkedList_h* createLinkedList_h(void)
{  //���� ���Ḯ��Ʈ ���� ����
	linkedList_h* L;
	L = (linkedList_h*)malloc(sizeof(linkedList_h)); //��� ��� �Ҵ�
	L->head = NULL; //���� ����Ʈ�̹Ƿ� NULL ����
	return L;
}

void insertFirstNode(linkedList_h* L, char* x)
{
	listNode* newNode;
	newNode = getNode(); //������ �� ��� �Ҵ�
	strcpy(newNode->data, x); //�� ����� ������ �ʵ忡 x ����  


	if (L->head == NULL) {  //���� ����Ʈ�� ������ ��� :
		L->head = newNode;
		newNode->right = NULL;
		newNode->left = L->head;
		return;
	}

	else
	{
		newNode->right = L->head;
		L->head->left = newNode;
		L->head = newNode;
	}


}

void addLastNode(linkedList_h* L, char* x) { //����Ʈ�� ������ ��� ���� ����
	listNode* newNode;
	listNode* p; //p�� å���� temp����
	newNode = getNode(); //������ �� ��� �Ҵ�
	strcpy(newNode->data, x); //�� ����� ������ �ʵ忡 x ����  


	if (L->head == NULL) {  //���� ����Ʈ�� ������ ��� :
		L->head = newNode;
		newNode->right = NULL;
		newNode->left = L->head;
	}
	else
	{
		p = L->head;
		while (p->right != NULL) p = p->right;
		p->right = newNode;
		newNode->left = p;
		newNode->right = NULL;
	}
}

void insertMiddleNode(linkedList_h*L, listNode *pre, char*x)
{
	listNode* newNode;

	newNode = getNode(); //������ �� ��� �Ҵ�
	strcpy(newNode->data, x); //�� ����� ������ �ʵ忡 x ����  

	if (L->head == NULL) //��尡 ��������
	{
		L->head = newNode;
		newNode->right = NULL;
		newNode->left = L->head;
	}
	else
	{
		pre->right->left = newNode;
		newNode->right = pre->right;
		pre->right = newNode;
		newNode->left = pre;
	}
}

void deleteFirstNode(linkedList_h * L)
{ //����Ʈ�� ù��°��� ����
	listNode* first;

	if (L->head == NULL) return;  //���� ����Ʈ�� ���, ���� ���� �ߴ�

	if (L->head->right == NULL)
	{
		returnNode(L->head);
		L->head = NULL;
		return;
	}
	else
	{                        //����Ʈ�� ��尡 ���� �� �ִ� ���,
		first = L->head;
		L->head = first->right; //������ �������� ����� �ڸ��� ��
		L->head->left = L->head; // ���� ��尡 �Ⱦ����� ���ʿ��� ���� �־���(��=���)


		returnNode(first);
		return;

	}
}

void deleteLastNode(linkedList_h * L)
{ //����Ʈ�� ������ ��� ���� ����
	listNode* previous;
	listNode* current;
	if (L->head == NULL) return;  //���� ����Ʈ�� ���, ���� ���� �ߴ�

	if (L->head->right == NULL)
	{  //����Ʈ�� ��尡 �� ���� �ִ� ���,
		returnNode(L->head);             // ù ��° ��带 �޸� �����ϰ�
		L->head = NULL;          // ����Ʈ ���� �����͸� null�� �����Ѵ�.
		return;
	}
	else
	{                        //����Ʈ�� ��尡 ���� �� �ִ� ���,
		previous = L->head;
		current = L->head->right;
		while (current->right != NULL)
		{
			previous = current;
			current = current->right;
		}
		returnNode(current);
		previous->right = NULL;
	}
}

void deleteSearchNode(linkedList_h * L, listNode* del)
{ //�˻��� ����
	listNode* previous;
	listNode* current;
	if (L->head == NULL) return;  //���� ����Ʈ�� ���, ���� ���� �ߴ�

	if (L->head->right == NULL) //����Ʈ�� ��尡 �Ѱ��ϰ��
	{
		returnNode(L->head);             // ù ��° ��带 �޸� �����ϰ�
		L->head = NULL;          // ����Ʈ ���� �����͸� null�� �����Ѵ�.
		return;
	}

	else if (L->head == searchNode(L, del)) //��ġ���� ���� ���� ù���̶��
	{
		listNode * first;
		first = L->head;
		L->head = first->right; //������ �������� ����� �ڸ��� ��
		L->head->left = L->head; // ���� ��尡 �Ⱦ����� ���ʿ��� ���� �־���(��=���)


		returnNode(first);
	}

	else if (searchNode(L, del)->right == NULL) //�Է¹������� ����Ʈ�� ���������ϰ��
	{
		previous = del->left;
		current = del;

		returnNode(current);
		previous->right = NULL;
	}

	else
	{
		previous = L->head;
		current = L->head->right;
		while (previous->right != searchNode(L, del))
		{
			previous = current;
			current = current->right;
		}
		previous->right = current->right;
		current->right->left = previous;
		returnNode(current);
	}
}

void freeLinkedList_h(linkedList_h* L) {//�������� ����Ʈ�� ��� ��ü ��ȯ
	listNode* p;//�ӽ����� ������
	while (L->head != NULL) {//��尡 �����ϴµ���
		p = L->head;//�ӽ����������Ϳ� DL->head�� ����
		L->head = L->head->right;//DL->head�� �� ������ ����
		returnNode(p);//p��ȯ
		p = NULL;
	}
}
void deleteNextNode(linkedList_h * L, listNode* del)
{ //�˻��� ����
	listNode* previous;
	listNode* current;

	previous = del;
	current = previous->right;
	if (current->right == NULL)//�����ҳ���� �������� �����������
	{
		del->right = NULL;
		returnNode(current);
		return;

	}

	previous->right = current->right;
	current->right->left = current->left;
	returnNode(current);
}





int main()
{
	init();
	linkedList_h* L;
	L = createLinkedList_h();
	printf(" ***���� ����Ʈ�� �����Ǿ���!*** \n");
	char x;
	char inputdata[20];
	char inputdata2[20];


	while (1)
	{
		printf("1. ����Ʈ����     \n");
		printf("2. insert First Node\n");
		printf("3. insert Middle Node (�Էµ� ����� ������ ����) \n");
		printf("4. insert last Node\n");
		printf("5. delete First Node\n");
		printf("6. delete Last Node\n");
		printf("7. delete searched Node\n");
		printf("8. �Է¹��� ���� ������ ��� ����!!!\n");
		printf("9. free.list!!\n");

		printf("0. ���α׷�����\n");
		printf("����: [   ]\b\b\b");
		scanf(" %c", &x);


		switch (x)
		{
		case '1': printList(L);    printSpace();   break;
		case '2':
		{
			printf("�Է��� ������ �Է�\n");
			scanf("%s", inputdata);
			insertFirstNode(L, inputdata);
			printList(L); printSpace();

			break;
		}

		case '3':
		{
			printf("���� ���� ���ڽ��ϱ�\n");
			scanf("%s", inputdata2);
			printf("�Է��� ������ �Է�\n");
			scanf("%s", inputdata);
			insertMiddleNode(L, searchNode(L, inputdata2), inputdata);
			printList(L); printSpace();

			break;
		}

		case '4':
		{
			printf("�Է��� ������ �Է�\n");
			scanf("%s", inputdata);
			addLastNode(L, inputdata);
			printList(L); printSpace();

			break;
		}

		case '5':
		{

			deleteFirstNode(L);
			printList(L); printSpace();

			break;
		}

		case '6':
		{

			deleteLastNode(L);
			printList(L); printSpace();

			break;
		}

		case '7':
		{
			printf("������ �����Ұų�\n");
			scanf("%s", inputdata2);
			deleteSearchNode(L, searchNode(L, inputdata2));
			printList(L); printSpace();

			break;
		}

		case '8':
		{
			printf("���� ���� �����Ұų�\n");
			scanf("%s", inputdata2);
			deleteNextNode(L, searchNode(L, inputdata2));
			printList(L); printSpace();

			break;
		}

		case '9':
		{
			freeLinkedList_h(L);
			printList(L); printSpace();
			break;
		}

		case '0': return 0;
		}

		printf("\n");
	}

	return 0;
}