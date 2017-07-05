#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

typedef struct ListNode {  //�ܼ����Ḯ��Ʈ�� ��� ���� ����
	char data[20];
	struct ListNode* link;
} listNode;

typedef struct {   //����Ʈ�� ��� ����� ���� ����
	listNode* head;

} linkedList_h;
/////////////////////////////////////////////////////////////////////////////
linkedList_h* createLinkedList_h(void);
void freeLinkedList_h(linkedList_h*);
void reverse(linkedList_h*);
void deleteLastNode(linkedList_h*);
void deleteFirstNode(linkedList_h*);
void deleteSearchNode(linkedList_h *, listNode *);
void printList(linkedList_h*);
void insertFirstNode(linkedList_h*, char*);//ù��° ���� ����
void insertMiddleNode(linkedList_h*, listNode*, char*);//�˻��� �� �ڿ� �ֱ�
void addLastNode(linkedList_h*, char*); //==insertLastNode
listNode* searchNode(linkedList_h*, char *);
/////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////
listNode pool[10];
listNode*Free = NULL;//�ڰ��� �Ǿ� ��
void init()
{
	int i = 0;
	for (i = 0; i < 9; i++)
	{
		 
		pool[i].link = &pool[i + 1];
		//strcpy(pool[i].data, "FreeNode");
		
	}

	//pool[i].link = NULL;
	

	Free = pool;
}

void printSpace()
{ 
	listNode* p;
	printf("���� �޸�Ǯ = (");
	p = Free;
	while (p != NULL) {
		printf("%p", p->data); //	printf("%p", p); �޸𸮷κ���
		p = p->link;

		if (p != NULL) printf(", ");
	}
	printf(") \n");
}

/*void printSpace()
{
	int count = 0;
	listNode* node;

	printf("free : ");
	for (node = Free; node; node = node->link)
	{
		printf("%p ", node);
		++count;
	}

	printf("count=%d\n", count);
}*///����� ���


listNode* getNode(void)// �������� ����Ʈ������ ����Ҵ�
{
	listNode* newnode = Free;
	if (newnode!=NULL)
		Free = newnode->link;
	else
		printf("�޸�Ǯ�� �����̾�� ���α׷��� ��������\n");

	return newnode;
}

void returnNode(listNode* old) {//�������� ����Ʈ�� ��� ��ȯ
	old->link = Free;//��ȯ ����� rlink�� ������������Ʈ ��ó���� ����
	Free = old;//Free�� ��ȯ��忡 ����
}
/////////////////////////////////////////////////////////////////////////
linkedList_h* createLinkedList_h(void)
{  //���� ���Ḯ��Ʈ ���� ����
	linkedList_h* L;
	L = (linkedList_h*)malloc(sizeof(linkedList_h)); //��� ��� �Ҵ�
	L->head = NULL; //���� ����Ʈ�̹Ƿ� NULL ����
	return L;
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
void insertFirstNode(linkedList_h*L, char* x)
{
	listNode* newNode;

	newNode = getNode(); //������ �� ��� �Ҵ�
	strcpy(newNode->data, x);


	newNode->link = L->head;
	L->head = newNode;
}

void insertMiddleNode(linkedList_h*L, listNode *pre, char*x)
{
	listNode* newNode;

	newNode = getNode(); //������ �� ��� �Ҵ�
	strcpy(newNode->data, x); //�� ����� ������ �ʵ忡 x ����  

	if (L->head == NULL)
	{
		L->head = newNode;
		newNode->link = NULL;
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

	newNode->link = NULL;//������ ����̴ϱ�
	if (L->head == NULL) {  //���� ����Ʈ�� ������ ��� :
		L->head = newNode;
		return;
	}
	p = L->head;
	while (p->link != NULL) p = p->link;
	p->link = newNode;
}

void reverse(linkedList_h * L) {  //����Ʈ�� ��� ������ �������� �ٲٴ� ����
	listNode* p;
	listNode* q;
	listNode* r;

	p = L->head;
	q = NULL;
	r = NULL;

	while (p != NULL) { //����� ������ �ݴ�� �ٲٱ�
		r = q;
		q = p;
		p = p->link;
		q->link = r;
	}
	L->head = q;

}


void deleteSearchNode(linkedList_h * L, listNode* del)
{ //�˻��� ����
	listNode* previous;
	listNode* current;
	if (L->head == NULL) return;  //���� ����Ʈ�� ���, ���� ���� �ߴ�

	if (L->head->link == NULL)
	{  //����Ʈ�� ��尡 �� ���� �ִ� ���,
		returnNode(L->head);             // ù ��° ��带 �޸� �����ϰ�
		L->head = NULL;          // ����Ʈ ���� �����͸� null�� �����Ѵ�.
		return;
	}

	else if (searchNode(L, del) == L->head) //��ġ�ι�����尡 ù��° ���̸�
	{
		listNode *first;
		first = L->head;
		L->head = first->link;
		returnNode(first);
		return;
	}
	else
	{
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


void deleteLastNode(linkedList_h * L)
{ //����Ʈ�� ������ ��� ���� ����
	listNode* previous;
	listNode* current;
	if (L->head == NULL) return;  //���� ����Ʈ�� ���, ���� ���� �ߴ�

	if (L->head->link == NULL)
	{  //����Ʈ�� ��尡 �� ���� �ִ� ���,
		returnNode(L->head);             // ù ��° ��带 �޸� �����ϰ�
		L->head = NULL;          // ����Ʈ ���� �����͸� null�� �����Ѵ�.
		return;
	}
	else
	{                        //����Ʈ�� ��尡 ���� �� �ִ� ���,
		previous = L->head;
		current = L->head->link;
		while (current->link != NULL)
		{
			previous = current;
			current = current->link;
		}
		returnNode(current);
		previous->link = NULL;
	}
}

void deleteFirstNode(linkedList_h * L)
{ //����Ʈ�� ������ ��� ���� ����
	listNode* first;

	if (L->head == NULL) return;  //���� ����Ʈ�� ���, ���� ���� �ߴ�

	if (L->head->link == NULL)
	{  //����Ʈ�� ��尡 �� ���� �ִ� ���,
		returnNode(L->head);             // ù ��° ��带 �޸� �����ϰ�
		L->head = NULL;          // ����Ʈ ���� �����͸� null�� �����Ѵ�.
		return;
	}
	else
	{                        //����Ʈ�� ��尡 ���� �� �ִ� ���,
		first = L->head;
		L->head = first->link;
		returnNode(first);
		return;

	}
}

void freeLinkedList_h(linkedList_h* L) {  //����Ʈ ��ü �޸� ���� ����
	listNode* p;
	while (L->head != NULL) {
		p = L->head;
		L->head = L->head->link;
		returnNode(p);
		p = NULL;
	}
}

void printList(linkedList_h* L) {   //��� ������� ����Ʈ�� ����ϴ� ����
	listNode* p;
	printf("����Ʈ��� = (");
	p = L->head;
	while (p != NULL) {
		printf("%s", p->data);
		p = p->link;

		if (p != NULL) printf(", ");
	}
	printf(") \n");
}



void deleteNextNode(linkedList_h * L, listNode* del)
{
	listNode* previous;
	listNode* current;

	previous = del;
	current = previous->link;
	if (current->link == NULL)//�����ҳ���� �������� �����������
	{
		previous->link = NULL;
		free(current);
		return;

	}

	previous->link = current->link;
	returnNode(current);
}

/*
listNode* freeSpace(listNode* ptr)
{
	listNode* temp = NULL;
	while (ptr != NULL)
	{
		temp = ptr;
		ptr = ptr->link;
		returnNode(temp);
	}

	return NULL;
}*/


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
		printf("1.����Ʈ����     \n");
		printf("2.insert First Node\n");
		printf("3.insert Middle Node\n");
		printf("4.insert Last Node\n");
		printf("5.delete First Node\n");
		printf("6.delete last Node\n");
		printf("7. search Delete\n");
		printf("8. �Է¹����� �����ʳ�����\n");

		printf("9. free linked list\n");
		printf("[z].reverse List\n");
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
			printList(L);
			printSpace();

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
			printf("������ ����ڽ��ϱ� \n");
			scanf("%s", inputdata2);

			deleteSearchNode(L, searchNode(L, inputdata2));
			printList(L); printSpace();

			break;


		}

		case 'z':
		{
			reverse(L);
			printList(L); printSpace();

			break;
		}

		

		case '8':
		{
			printf("���� ���� �� ����ڽ��ϱ� \n");
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


		case '0':               return 0;

		}
		printf("\n");
	}
	return 0;
}


