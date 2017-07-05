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

	for (i = 0; i < 10; i++)
	{
		strcpy(pool[i].data, "FreeNode");
	}
	//pool[i].right = NULL; ���Ǵ� ����? ���� ��;

	Free = pool;
}

void printSpace()
{
	listNode* p;
	printf("���� �޸�Ǯ = (");
	p = Free;
	while (p != NULL) {
		printf("%s", p->data); // %p, p �ϸ� �ּ�
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

void printList(linkedList_h* L)
{
	listNode* p;
	printf("L = (");
	p = L->head;
	if (p == NULL)
	{
		printf(") \n");
		return;
	}
	do
	{
		printf("%s", p->data);
		p = p->right;
		if (p != L->head) printf(", ");
	} while (p != L->head);
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
	listNode* temp;//��ȸ����
	newNode = getNode();
	strcpy(newNode->data, x);


	if (L->head == NULL)
	{
		L->head = newNode;
		newNode->right = newNode;
		newNode->left = newNode;
	}
	else
	{
		temp = L->head;
		while (temp->right != L->head)
			temp = temp->right;


		newNode->right = temp->right;
		newNode->right->left = newNode;
		newNode->left = temp;
		temp->right = newNode;
		L->head = newNode;

	}
}

void addLastNode(linkedList_h* L, char* x) { //����Ʈ�� ������ ��� ���� ����
	listNode* newNode;
	listNode* p; //p�� å���� temp����
	newNode = getNode(); //������ �� ��� �Ҵ�
	strcpy(newNode->data, x); //�� ����� ������ �ʵ忡 x ����  

							  //newNode->link = NULL;//������ ����̴ϱ�
	if (L->head == NULL) {  //���� ����Ʈ�� ������ ��� :
		L->head = newNode;
		newNode->right = newNode;
		newNode->left = newNode;
		return;
	}
	p = L->head;
	while (p->right != L->head) p = p->right;
	p->right = newNode;
	newNode->left = p;
	newNode->right = L->head;
	L->head->left = newNode;
}

void insertMiddleNode(linkedList_h* L, listNode* pre, char* x)
{
	listNode* newNode;
	newNode = getNode();
	strcpy(newNode->data, x);

	if (L->head == NULL)
	{
		L->head = newNode;
		newNode->right = newNode;
		newNode->left = newNode;
	}

	else
	{
		newNode->right = pre->right;
		newNode->right->left = newNode;
		newNode->left = pre;
		pre->right = newNode;
	}
}

void deleteFirstNode(linkedList_h * L)
{
	listNode* first;
	listNode* p;

	if (L->head == NULL) return;  //���� ����Ʈ�� ���, ���� ���� �ߴ�

	if (L->head->right == L->head)
	{  //����Ʈ�� ��尡 �� ���� �ִ� ���,

		returnNode(L->head);             // ù ��° ��带 �޸� �����ϰ�
		L->head = NULL;          // ����Ʈ ���� �����͸� null�� �����Ѵ�.
		return;
	}
	else
	{
		p = L->head;
		while (p->right != L->head) p = p->right;
		first = L->head;
		p->right = first->right;
		first->right->left = p;
		L->head = first->right;
		returnNode(first);
		return;

	}
}

void deleteLastNode(linkedList_h * L)
{ //����Ʈ�� ������ ��� ���� ����
	listNode* previous;
	listNode* current;
	if (L->head == NULL) return;  //���� ����Ʈ�� ���, ���� ���� �ߴ�

	if (L->head->right == L->head)
	{  //����Ʈ�� ��尡 �� ���� �ִ� ���,
		returnNode(L->head);             // ù ��° ��带 �޸� �����ϰ�
		L->head = NULL;          // ����Ʈ ���� �����͸� null�� �����Ѵ�.
		return;
	}
	else
	{                        //����Ʈ�� ��尡 ���� �� �ִ� ���,
		previous = L->head;
		current = L->head->right;
		while (current->right != L->head)
		{
			previous = current;
			current = current->right;
		}
		previous->right = current->right;
		previous->right->left = previous;

		returnNode(current);

	}
}

void deleteSearchNode(linkedList_h * L, listNode* del)
{ //�˻��� ����

	if (L->head == NULL) return;  //���� ����Ʈ�� ���, ���� ���� �ߴ�

	if (L->head->right == L->head)
	{  //����Ʈ�� ��尡 �� ���� �ִ� ���,
		returnNode(L->head);             // ù ��° ��带 �޸� �����ϰ�
		L->head = NULL;          // ����Ʈ ���� �����͸� null�� �����Ѵ�.
		return;
	}

	else if (searchNode(L, del) == L->head)//��ġ��尪�� ����Ʈ�� ù��°���̸�
	{
		listNode*p;
		listNode*first;
		p = L->head;
		while (p->right != L->head) p = p->right;
		first = L->head;
		p->right = first->right;
		first->right->left = p;
		L->head = first->right;
		returnNode(first);
		return;
	}
	else
	{
		listNode* previous;
		listNode* current;
		previous = L->head;
		current = L->head->right;
		while (previous->right != searchNode(L, del))
		{
			previous = current;
			current = current->right;
		}

		previous->right = current->right;
		previous->right->left = previous;
		returnNode(current);

	}
}

void freeLinkedList_h(linkedList_h* L) {
	listNode* p;

	p = L->head;
	while (L->head != p->right)
	{
		p = p->right;
	}

	p->right = NULL;

	while (L->head != NULL) {
		p = L->head;
		L->head = L->head->right; /* free �Լ��� �޸� ����*/
		returnNode(p);
		p = NULL;
	}

}
void deleteNextNode(linkedList_h * L, listNode* del)
{
	listNode* previous;
	listNode* current;

	previous = del;
	current = previous->right;
	if (current->right == L->head)//�����ҳ���� �������� �����������
	{
		previous->right = L->head;
		previous->left = L->head;
		returnNode(current);
		return;

	}
	previous->right = current->right;
	previous->right->left = previous;
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