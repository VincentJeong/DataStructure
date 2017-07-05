#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)
typedef struct ListNode
{
	char data[20];
	struct ListNode* link;
} listNode;


typedef struct
{
	listNode* head;
} linkedList_h;

///////////////////////////////////////////////////////////////////////
linkedList_h* createLinkedList_h(void);
void insertFirstNode(linkedList_h*, char*);
void insertMiddleNode(linkedList_h*, listNode*, char*);
void addLastNode(linkedList_h* L, char* x);
void deleteFirstNode(linkedList_h * L);
void deleteLastNode(linkedList_h * L);
void deleteSearchNode(linkedList_h * L, listNode*);
void printList(linkedList_h*);
void freeLinkedList_h(linkedList_h* L);


listNode* searchNode(linkedList_h*, char *);
////////////////////////////////////////////////////////////////////////
listNode* Free = NULL;//�������� ����Ʈ�� ���۳�� ������
listNode pool[10];
void init()
{
	int i;
	for (i = 0; i < 9; i++)
		pool[i].link = &pool[i + 1];
	pool[i].link = NULL;

	Free = pool;
}

void printSpace()
{
	listNode* p;
	printf("���� �޸�Ǯ = (");
	p = Free;
	while (p != NULL) {
		printf("%p", p);
		p = p->link;

		if (p != NULL) printf(", ");
	}
	printf(") \n");
}
listNode* getNode(void)// �������� ����Ʈ������ ����Ҵ�
{
	listNode* newnode = Free;
	if (newnode)
		Free = newnode->link;
	else
		printf("�޸�Ǯ�� �����̾�� ���α׷��� ��������\n");

	return newnode;
}

void returnNode(listNode* old) {//�������� ����Ʈ�� ��� ��ȯ
	old->link = Free;//��ȯ ����� rlink�� ������������Ʈ ��ó���� ����
	Free = old;//Free�� ��ȯ��忡 ����
}


/////////////////////////////////////////////////////////////////


linkedList_h* createLinkedList_h(void)
{
	linkedList_h* L;
	L = (linkedList_h*)malloc(sizeof(linkedList_h));
	L->head = NULL;
	return L;
}


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
		p = p->link;
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
		temp = temp->link;
	}
	return NULL;
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
		newNode->link = newNode;
	}
	else
	{
		temp = L->head;
		while (temp->link != L->head)
			temp = temp->link;


		newNode->link = temp->link;
		temp->link = newNode;
		L->head = newNode;

	}
}

void insertMiddleNode(linkedList_h* L, listNode* pre, char* x)
{
	listNode* newNode;
	newNode = getNode();
	strcpy(newNode->data, x);

	if (L->head == NULL)
	{
		L->head = newNode;
		newNode->link = newNode;
	}

	else
	{
		newNode->link = pre->link;
		pre->link = newNode;
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
		newNode->link = newNode;
		return;
	}
	p = L->head;
	while (p->link != L->head) p = p->link;
	p->link = newNode;
	newNode->link = L->head;
}

void deleteFirstNode(linkedList_h * L)
{
	listNode* first;
	listNode* p;

	if (L->head == NULL) return;  //���� ����Ʈ�� ���, ���� ���� �ߴ�

	if (L->head->link == L->head)
	{  //����Ʈ�� ��尡 �� ���� �ִ� ���,

		returnNode(L->head);             // ù ��° ��带 �޸� �����ϰ�
		L->head = NULL;          // ����Ʈ ���� �����͸� null�� �����Ѵ�.
		return;
	}
	else
	{
		p = L->head;
		while (p->link != L->head) p = p->link;
		first = L->head;
		L->head = first->link;
		p->link = first->link;
		returnNode(first);
		return;

	}
}

void deleteLastNode(linkedList_h * L)
{ //����Ʈ�� ������ ��� ���� ����
	listNode* previous;
	listNode* current;
	if (L->head == NULL) return;  //���� ����Ʈ�� ���, ���� ���� �ߴ�

	if (L->head->link == L->head)
	{  //����Ʈ�� ��尡 �� ���� �ִ� ���,
		returnNode(L->head);             // ù ��° ��带 �޸� �����ϰ�
		L->head = NULL;          // ����Ʈ ���� �����͸� null�� �����Ѵ�.
		return;
	}
	else
	{                        //����Ʈ�� ��尡 ���� �� �ִ� ���,
		previous = L->head;
		current = L->head->link;
		while (current->link != L->head)
		{
			previous = current;
			current = current->link;
		}
		previous->link = current->link;

		returnNode(current);

	}
}

void deleteSearchNode(linkedList_h * L, listNode* del)
{ //�˻��� ����

	if (L->head == NULL) return;  //���� ����Ʈ�� ���, ���� ���� �ߴ�

	if (L->head->link == L->head)
	{  //����Ʈ�� ��尡 �� ���� �ִ� ���,
		returnNode(L->head);             // ù ��° ��带 �޸� �����ϰ�
		L->head = NULL;          // ����Ʈ ���� �����͸� null�� �����Ѵ�.
		return;
	}

	else if (searchNode(L, del) == L->head)//��ġ��尪�� ����Ʈ�� ù��°���̸�
	{
		listNode *p;
		listNode *first;
		p = L->head;
		while (p->link != L->head) p = p->link;
		first = L->head;
		L->head = first->link;
		p->link = first->link;
		returnNode(first);
		return;
	}
	else
	{
		listNode* previous;
		listNode* current;
		previous = L->head;
		current = L->head->link;
		while (previous->link != searchNode(L, del))
		{
			previous = current;
			current = current->link;
		}

		previous->link = current->link;
		returnNode(current);

	}
}

void reverse(linkedList_h* L) { /* �����ͷ� �հ��� ������ ������ �κ� */
	listNode* p;
	listNode* q;
	listNode* r;
	listNode* s;
	p = L->head;
	q = NULL;
	r = NULL;
	while (p->link != L->head)
	{
		p = p->link;
	}

	p->link = NULL;
	s = L->head;

	while (s != NULL) {
		r = q;
		q = s;
		s = s->link;
		q->link = r;
	}
	L->head = q;

	p = L->head;

	while (p->link != NULL)
	{
		p = p->link;
	}
	p->link = L->head;

}

void freeLinkedList_h(linkedList_h* L) {
	listNode* p;

	p = L->head;
	while (L->head != p->link)
	{
		p = p->link;
	}

	p->link = NULL;

	while (L->head != NULL) {
		p = L->head;
		L->head = L->head->link; /* free �Լ��� �޸� ����*/
		returnNode(p);
		p = NULL;
	}

}
void deleteNextNode(linkedList_h * L, listNode* del)
{
	listNode* previous;
	listNode* current;

	previous = del;
	current = previous->link;
	if (current->link == L->head)//�����ҳ���� �������� �����������
	{
		previous->link = L->head;
		returnNode(current);
		return;

	}
	previous->link = current->link;
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
		printf("8. ������!!!\n");
		printf("9. free.list!!\n");
		printf("zŰ . ���õ� ���� ������ ����\n");

		printf("0. ���α׷�����\n");
		printf("����: [   ]\b\b\b");
		scanf(" %c", &x);


		switch (x)
		{
		case '1': printList(L);   printSpace();    break;
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
			printf("���� �����ʿ� �Ѱ��ΰ�\n");
			scanf("%s", inputdata2);
			printf("�Է��� �����ʹ�?\n");
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

			reverse(L);
			printList(L); printSpace();

			break;
		}

		case '9':
		{
			freeLinkedList_h(L);
			printList(L); printSpace();
			break;
		}

		case 'z':
		{
			printf("������ �������� �����Ұų�\n");
			scanf("%s", inputdata2);
			deleteNextNode(L, searchNode(L, inputdata2));
			printList(L); printSpace();
			break;
		}

		case '0': return 0;
		}

		printf("\n");
	}

	return 0;
}