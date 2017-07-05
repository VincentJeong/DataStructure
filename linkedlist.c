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
linkedList_h* createLinkedList_h(void);
void freeLinkedList_h(linkedList_h*);
void reverse(linkedList_h*);
void deleteLastNode(linkedList_h*);
void deleteFirstNode(linkedList_h*);
void deleteSearchNode(linkedList_h *, listNode *);
void printList(linkedList_h*);
void insertFirstNode(linkedList_h*, char*);//첫번째 노드로 삽입
void insertMiddleNode(linkedList_h*, listNode*, char*);//검색후 그 뒤에 넣기
void addLastNode(linkedList_h*, char*); //==insertLastNode
listNode* searchNode(linkedList_h*, char *);
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
		//strcpy(pool[i].data, "FreeNode");
		
	}

	//pool[i].link = NULL;
	

	Free = pool;
}

void printSpace()
{ 
	listNode* p;
	printf("남은 메모리풀 = (");
	p = Free;
	while (p != NULL) {
		printf("%p", p->data); //	printf("%p", p); 메모리로볼때
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
	if (newnode!=NULL)
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
void insertFirstNode(linkedList_h*L, char* x)
{
	listNode* newNode;

	newNode = getNode(); //삽입할 새 노드 할당
	strcpy(newNode->data, x);


	newNode->link = L->head;
	L->head = newNode;
}

void insertMiddleNode(linkedList_h*L, listNode *pre, char*x)
{
	listNode* newNode;

	newNode = getNode(); //삽입할 새 노드 할당
	strcpy(newNode->data, x); //새 노드의 데이터 필드에 x 저장  

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


void addLastNode(linkedList_h* L, char* x) { //리스트의 마지막 노드 삽입 연산
	listNode* newNode;
	listNode* p; //p가 책에서 temp더라
	newNode = getNode(); //삽입할 새 노드 할당
	strcpy(newNode->data, x); //새 노드의 데이터 필드에 x 저장  

	newNode->link = NULL;//마지막 노드이니까
	if (L->head == NULL) {  //현재 리스트가 공백인 경우 :
		L->head = newNode;
		return;
	}
	p = L->head;
	while (p->link != NULL) p = p->link;
	p->link = newNode;
}

void reverse(linkedList_h * L) {  //리스트의 노드 순서를 역순으로 바꾸는 연산
	listNode* p;
	listNode* q;
	listNode* r;

	p = L->head;
	q = NULL;
	r = NULL;

	while (p != NULL) { //노드의 연결을 반대로 바꾸기
		r = q;
		q = p;
		p = p->link;
		q->link = r;
	}
	L->head = q;

}


void deleteSearchNode(linkedList_h * L, listNode* del)
{ //검색후 삭제
	listNode* previous;
	listNode* current;
	if (L->head == NULL) return;  //공백 리스트인 경우, 삭제 연산 중단

	if (L->head->link == NULL)
	{  //리스트에 노드가 한 개만 있는 경우,
		returnNode(L->head);             // 첫 번째 노드를 메모리 해제하고
		L->head = NULL;          // 리스트 시작 포인터를 null로 설정한다.
		return;
	}

	else if (searchNode(L, del) == L->head) //써치로받은노드가 첫번째 값이면
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
{ //리스트의 마지막 노드 삭제 연산
	listNode* previous;
	listNode* current;
	if (L->head == NULL) return;  //공백 리스트인 경우, 삭제 연산 중단

	if (L->head->link == NULL)
	{  //리스트에 노드가 한 개만 있는 경우,
		returnNode(L->head);             // 첫 번째 노드를 메모리 해제하고
		L->head = NULL;          // 리스트 시작 포인터를 null로 설정한다.
		return;
	}
	else
	{                        //리스트에 노드가 여러 개 있는 경우,
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



void deleteNextNode(linkedList_h * L, listNode* del)
{
	listNode* previous;
	listNode* current;

	previous = del;
	current = previous->link;
	if (current->link == NULL)//삭제할노드의 오른족이 마지막노드라면
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
	printf(" ***공백 리스트가 생성되었다!*** \n");
	char x;
	char inputdata[20];
	char inputdata2[20];


	while (1)
	{
		printf("1.리스트보기     \n");
		printf("2.insert First Node\n");
		printf("3.insert Middle Node\n");
		printf("4.insert Last Node\n");
		printf("5.delete First Node\n");
		printf("6.delete last Node\n");
		printf("7. search Delete\n");
		printf("8. 입력받은값 오른쪽노드삭제\n");

		printf("9. free linked list\n");
		printf("[z].reverse List\n");
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
			printf("누구 옆에 놓겠습니까\n");
			scanf("%s", inputdata2);
			printf("입력할 데이터 입력\n");
			scanf("%s", inputdata);
			insertMiddleNode(L, searchNode(L, inputdata2), inputdata);
			printList(L); printSpace();

			break;
		}
		case '4':
		{
			printf("입력할 데이터 입력\n");
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
			printf("누구를 지우겠습니까 \n");
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
			printf("누구 옆을 를 지우겠습니까 \n");
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


