
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
	}

	for (i = 0; i < 10; i++)
	{
		strcpy(pool[i].data, "FreeNode"); //�ּҷ��ϰ������̰�����
	}
	//	pool[i].link = NULL;


	Free = pool;
}

void printSpace()
{
	listNode* p;
	printf("���� �޸�Ǯ = (");
	p = Free;
	while (p != NULL) {
		printf("%s", p->data); //	printf("%p", p); �޸𸮷κ���
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
	if (newnode != NULL)
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
void insertFirstNode(linkedList_h*L, char* x) //push
{
	listNode* newNode;

	newNode = getNode(); //������ �� ��� �Ҵ�
	strcpy(newNode->data, x);


	newNode->link = L->head;
	L->head = newNode;
}



void deleteFirstNode(linkedList_h * L) //pop
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








void del(linkedList_h * L)
{ //����Ʈ�� ������ ��� ���� ����
	listNode* top;
	top = L->head;

	if (L->head == NULL) return;  //���� ����Ʈ�� ���, ���� ���� �ߴ�

		L->head = top->link;
		free(top);
	
}

void peek(linkedList_h *L)
{
	listNode *top;
	if (L->head == NULL) return 0;

	else
	{
		top = L->head;
		printf("peek : [%s] \n", top);
		printf("peek�� �޸��ּ� [%p]\n", top);
	}
}

int isEmpty(linkedList_h *L)
{
	listNode *top;
	if (L->head == NULL)
	{
		printf("�� ���� �Դϴ�\n");
		return 0;
	}

	else
	{
		printf("������ ���ֽ��ϴ�\n");
		return 0;
	}
}

int main()
{
	init();
	linkedList_h* L;
	L = createLinkedList_h();
	printf(" ***���� ����Ʈ�� �����Ǿ���!*** \n");
	char x;
	char inputdata[20];
	//char inputdata2[20];


	while (1)
	{
		printf("1.����Ʈ����     \n");
		printf("2.push \n");
		printf("3.delete \n"); // �̱���
		printf("4.pop \n");
		printf("5. peek \n");
		printf("6.isempty\n");
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
			del(L);
			printList(L); printSpace();

			break;
		}
		

		case '4':
		{
			deleteFirstNode(L);
			printList(L); printSpace();

			break;
		}
		case '5':
		{
			peek(L);
			printList(L); printSpace();

			break;
		}

		case '6':
		{
			isEmpty(L);
			printList(L); printSpace();

			break;
		}


		case '0':               return 0;

		}
		printf("\n");
	}
	return 0;
}


