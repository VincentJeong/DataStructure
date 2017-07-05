
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

typedef struct ListNode {  //단순연결리스트의 노드 구조 정의
	char data[20];
	struct ListNode* link;
} listNode;

typedef struct {   //리스트의 헤드 노드의 구조 정의
	listNode* head;

} linkedList_h;
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////
listNode pool[10];
listNode*Free = NULL;//자공간 맨앞 널
void init()
{
	int i = 0;
	for (i = 0; i < 9; i++)
	{
		pool[i].link = &pool[i + 1];
	}

	for (i = 0; i < 10; i++)
	{
		strcpy(pool[i].data, "FreeNode"); //주소로하고프면이거지워
	}
	//	pool[i].link = NULL;


	Free = pool;
}

void printSpace()
{
	listNode* p;
	printf("남은 메모리풀 = (");
	p = Free;
	while (p != NULL) {
		printf("%s", p->data); //	printf("%p", p); 메모리로볼때
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
}*///예비용 출력


listNode* getNode(void)// 자유공간 리스트에서의 노드할당
{
	listNode* newnode = Free;
	if (newnode != NULL)
		Free = newnode->link;
	else
		printf("메모리풀에 쓸것이없어서 프로그램이 뻑날것임\n");

	return newnode;
}

void returnNode(listNode* old) {//자유공간 리스트로 노드 반환
	old->link = Free;//반환 노드의 rlink에 자유공간리스트 맨처음을 연결
	Free = old;//Free를 반환노드에 연결
}
/////////////////////////////////////////////////////////////////////////
linkedList_h* createLinkedList_h(void)
{  //공백 연결리스트 생성 연산
	linkedList_h* L;
	L = (linkedList_h*)malloc(sizeof(linkedList_h)); //헤드 노드 할당
	L->head = NULL; //공백 리스트이므로 NULL 설정
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

	newNode = getNode(); //삽입할 새 노드 할당
	strcpy(newNode->data, x);


	newNode->link = L->head;
	L->head = newNode;
}



void deleteFirstNode(linkedList_h * L) //pop
{ //리스트의 마지막 노드 삭제 연산
	listNode* first;

	if (L->head == NULL) return;  //공백 리스트인 경우, 삭제 연산 중단

	if (L->head->link == NULL)
	{  //리스트에 노드가 한 개만 있는 경우,
		returnNode(L->head);             // 첫 번째 노드를 메모리 해제하고
		L->head = NULL;          // 리스트 시작 포인터를 null로 설정한다.
		return;
	}
	else
	{                        //리스트에 노드가 여러 개 있는 경우,
		first = L->head;
		L->head = first->link;
		returnNode(first);
		return;

	}
}

void freeLinkedList_h(linkedList_h* L) {  //리스트 전체 메모리 해제 연산
	listNode* p;
	while (L->head != NULL) {
		p = L->head;
		L->head = L->head->link;
		returnNode(p);
		p = NULL;
	}
}

void printList(linkedList_h* L) {   //노드 순서대로 리스트를 출력하는 연산
	listNode* p;
	printf("리스트목록 = (");
	p = L->head;
	while (p != NULL) {
		printf("%s", p->data);
		p = p->link;

		if (p != NULL) printf(", ");
	}
	printf(") \n");
}








void del(linkedList_h * L)
{ //리스트의 마지막 노드 삭제 연산
	listNode* top;
	top = L->head;

	if (L->head == NULL) return;  //공백 리스트인 경우, 삭제 연산 중단

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
		printf("peek의 메모리주소 [%p]\n", top);
	}
}

int isEmpty(linkedList_h *L)
{
	listNode *top;
	if (L->head == NULL)
	{
		printf("빈 스택 입니다\n");
		return 0;
	}

	else
	{
		printf("스택이 차있습니다\n");
		return 0;
	}
}

int main()
{
	init();
	linkedList_h* L;
	L = createLinkedList_h();
	printf(" ***공백 리스트가 생성되었다!*** \n");
	char x;
	char inputdata[20];
	//char inputdata2[20];


	while (1)
	{
		printf("1.리스트보기     \n");
		printf("2.push \n");
		printf("3.delete \n"); // 미구현
		printf("4.pop \n");
		printf("5. peek \n");
		printf("6.isempty\n");
		printf("0. 프로그램종료\n");
		printf("선택: [   ]\b\b\b");
		scanf(" %c", &x);


		switch (x)
		{
		case '1': printList(L);   printSpace();    break;
		case '2':
		{
			printf("입력할 데이터 입력\n");
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


