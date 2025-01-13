#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct node {         // 노드 구조체
	int e;
	struct node* next;
}node;

typedef struct llist {        // 단일 연결리스트
	node* head;
	int size;
}llist;

void mergeSort(llist* list);       // 합병정렬 함수
void merge(llist* L1, llist* L2, llist* list);       // 두 리스트 합병 함수
void partition(llist* list, int k, llist* L1, llist* L2);       // 리스트 분할 함수
void addLast(llist* list, int el);      // 노드 추가 함수
int removeFirst(llist* list);       //노드 삭제 함수


int main() {
	llist* list = (llist*)malloc(sizeof(llist));    // 단일연결 리스트 선언
	list->head = (node*)malloc(sizeof(node));
	list->head->next = NULL;
	list->size = 0;

	int n;                // 입력받을 정수 갯수
	scanf("%d", &n);
	list->size = n;
	scanf("%d", &list->head->e);

	node* p = list->head;
	for (int i = 0; i < n - 1; i++) {           // 정수 입력받아 리스트에 저장
		node* newnode = (node*)malloc(sizeof(node));
		newnode->next = NULL;
		scanf("%d", &newnode->e);

		p->next = newnode;
		p = p->next;
	}

	mergeSort(list);        // 합병정렬 함수 호출

	p = list->head;
	for (int i = 0; i < n; i++) {      // 정렬한 정수 출력
		printf(" %d", p->e);
		p = p->next;
	}

	return 0;
}

void mergeSort(llist* list) {
	if (list->size > 1) {
		llist* L1 = (llist*)malloc(sizeof(llist));    // 리스트 선언
		llist* L2 = (llist*)malloc(sizeof(llist));     // 리스트 선언
		partition(list, list->size, L1, L2);     // 리스트 분할함수 호출
		mergeSort(L1);     // L1 합병정렬 함수 호출
		mergeSort(L2);     // L2 합병정렬 함수 호출

		merge(L1, L2, list);     // 합병 함수 호출
	}
}

void addLast(llist* list, int el) {
	node* newnode = (node*)malloc(sizeof(node));    // 새로운 노드 생성

	newnode->e = el;       // 정수 저장
	newnode->next = NULL;

	if (list->head == NULL) {
		list->head = newnode;    // 합병한 리스트에 추가
	}
	else {
		node* p = list->head;
		while (p->next) {      // 가장 마지막 노드까지 이동
			p = p->next;
		}
		p->next = newnode;    // 합병한 리스트에 추가
	}
}

int removeFirst(llist* list) {
	int e = list->head->e;
	node* p = list->head;

	list->head = p->next;   // 헤드노드에 다음 노드 저장
	free(p);     // 메모리 해제

	return (e);     // 저장된 정수 반환
}

void merge(llist* L1, llist* L2, llist* list) {

	list->head = NULL;

	while (L1->head != NULL && L2->head != NULL) {     // 두 리스트가 모두 비어있지 않을 때
		if (L1->head->e < L2->head->e) {
			addLast(list, removeFirst(L1));       // 두 리스트 중 더 작은 값을 저장
		}
		else {
			addLast(list, removeFirst(L2));
		}
	}

	while (L1->head != NULL) {          // L1만 남았을 때
		addLast(list, removeFirst(L1));     // L1 남은 노드 추가
	}

	while (L2->head != NULL) {          // L2만 남았을 때
		addLast(list, removeFirst(L2));     // L2 남은 노드 추가
	}

}

void partition(llist* list, int k, llist* L1, llist* L2) {
	node* p = list->head;

	L1->head = p;    // 앞부분 리스트 저장
	L1->size = k / 2;

	for (int i = 0; i < k / 2 - 1; i++) {     // 중간까지 이동
		p = p->next;
	}

	L2->head = p->next;  // 뒷부분 리스트 저장
	L2->size = k - k / 2;

	p->next = NULL;    // 분할
}

