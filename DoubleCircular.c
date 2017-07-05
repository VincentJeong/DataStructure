#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

typedef struct ListNode {  //단순연결리스트의 노드 구조 정의
	char data[20];
	struct ListNode* right;
	struct ListNode* left;
} listNode;

typedef struct {   //리스트의 헤드 노드의 구조 정의
	listNode* head;

} linkedList_h;

/////////////////////////////////////////////////////////////////////////////
linkedList_h* createLinkedList_h(void);
void freeLinkedList_h(linkedList_h*);//미구현
void reverse(linkedList_h*);//미구현
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
listNode* Free = NULL;//자유공간 리스트의 시작노드 포인터
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
	//pool[i].right = NULL; 지렷다 ㅇㅈ? ㅇㅋ ㄳ;

	Free = pool;
}

void printSpace()
{
	listNode* p;
	printf("남은 메모리풀 = (");
	p = Free;
	while (p != NULL) {
		printf("%s", p->data); // %p, p 하면 주소
		p = p->right;

		if (p != NULL) printf(", ");
	}
	printf(") \n");
}
listNode* getNode(void)// 자유공간 리스트에서의 노드할당
{
	listNode* newnode = Free;
	if (newnode)
		Free = newnode->right;
	else
		printf("메모리풀에 쓸것이없어서 프로그램이 뻑날것임\n");

	return newnode;
}

void returnNode(listNode* old) {//자유공간 리스트로 노드 반환
	old->right = Free;//반환 노드의 rlink에 자유공간리스트 맨처음을 연결
	Free = old;//Free를 반환노드에 연결
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
{  //공백 연결리스트 생성 연산
	linkedList_h* L;
	L = (linkedList_h*)malloc(sizeof(linkedList_h)); //헤드 노드 할당
	L->head = NULL; //공백 리스트이므로 NULL 설정
	return L;
}

void insertFirstNode(linkedList_h* L, char* x)
{
	listNode* newNode;
	listNode* temp;//순회용노드
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

void addLastNode(linkedList_h* L, char* x) { //리스트의 마지막 노드 삽입 연산
	listNode* newNode;
	listNode* p; //p가 책에서 temp더라
	newNode = getNode(); //삽입할 새 노드 할당
	strcpy(newNode->data, x); //새 노드의 데이터 필드에 x 저장  

							  //newNode->link = NULL;//마지막 노드이니까
	if (L->head == NULL) {  //현재 리스트가 공백인 경우 :
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

	if (L->head == NULL) return;  //공백 리스트인 경우, 삭제 연산 중단

	if (L->head->right == L->head)
	{  //리스트에 노드가 한 개만 있는 경우,

		returnNode(L->head);             // 첫 번째 노드를 메모리 해제하고
		L->head = NULL;          // 리스트 시작 포인터를 null로 설정한다.
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
{ //리스트의 마지막 노드 삭제 연산
	listNode* previous;
	listNode* current;
	if (L->head == NULL) return;  //공백 리스트인 경우, 삭제 연산 중단

	if (L->head->right == L->head)
	{  //리스트에 노드가 한 개만 있는 경우,
		returnNode(L->head);             // 첫 번째 노드를 메모리 해제하고
		L->head = NULL;          // 리스트 시작 포인터를 null로 설정한다.
		return;
	}
	else
	{                        //리스트에 노드가 여러 개 있는 경우,
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
{ //검색후 삭제

	if (L->head == NULL) return;  //공백 리스트인 경우, 삭제 연산 중단

	if (L->head->right == L->head)
	{  //리스트에 노드가 한 개만 있는 경우,
		returnNode(L->head);             // 첫 번째 노드를 메모리 해제하고
		L->head = NULL;          // 리스트 시작 포인터를 null로 설정한다.
		return;
	}

	else if (searchNode(L, del) == L->head)//써치노드값이 리스트의 첫번째값이면
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
		L->head = L->head->right; /* free 함수로 메모리 해제*/
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
	if (current->right == L->head)//삭제할노드의 오른족이 마지막노드라면
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
	printf(" ***공백 리스트가 생성되었다!*** \n");
	char x;
	char inputdata[20];
	char inputdata2[20];


	while (1)
	{
		printf("1. 리스트보기     \n");
		printf("2. insert First Node\n");
		printf("3. insert Middle Node (입력된 노드의 오른쪽 삽입) \n");
		printf("4. insert last Node\n");
		printf("5. delete First Node\n");
		printf("6. delete Last Node\n");
		printf("7. delete searched Node\n");
		printf("8. 입력받은 것의 오른쪽 노드 삭제!!!\n");
		printf("9. free.list!!\n");

		printf("0. 프로그램종료\n");
		printf("선택: [   ]\b\b\b");
		scanf(" %c", &x);


		switch (x)
		{
		case '1': printList(L);    printSpace();   break;
		case '2':
		{
			printf("입력할 데이터 입력\n");
			scanf("%s", inputdata);
			insertFirstNode(L, inputdata);
			printList(L); printSpace();

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
			printf("누구를 삭제할거냐\n");
			scanf("%s", inputdata2);
			deleteSearchNode(L, searchNode(L, inputdata2));
			printList(L); printSpace();

			break;
		}

		case '8':
		{
			printf("누구 옆을 삭제할거냐\n");
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