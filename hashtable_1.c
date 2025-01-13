#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int e;
	struct node* next;
}node;

int findelement(node** table, int k, int M);     // 탐색 함수
void insertitem(node** table, int k, int M);     // 삽입 함수
int removeelement(node** table, int k, int M);    // 삭제 함수
void initbucketarray(node** table, int M);      // 초기화 함수
void print(node** table, int M);      // 출력 함수

int main() {
	int M, x;
	char menu;
	scanf("%d", &M);
	getchar();

	node** table = (node**)malloc(M*sizeof(node*));    // 해쉬테이블 메모리 할당
	initbucketarray(table, M);    // 테이블 초기화

	while (1) {
		scanf("%c", &menu);

		if (menu == 'i') {
			scanf("%d", &x);
			insertitem(table, x, M);    //  삽입함수 호출
		}
		else if (menu == 's') {
			scanf("%d", &x);
			int t = findelement(table, x, M);    // 탐색함수 호출
			printf(" %d\n", t);    // 키 순위 출력
		}
		else if (menu == 'd') {
			scanf("%d", &x);
			int t = removeelement(table, x, M);    // 삭제함수 호출
			printf(" %d\n", t);     // 순위 출력
		}
		else if (menu == 'p') {
			print(table, M);    // 출력함수 호출
		}
		else if (menu == 'e') {
			break;    // 종료
		}
		getchar();
	}
}

void insertitem(node** table, int k, int M) {
	node* new = (node*)malloc(sizeof(node));    // 새로운 노드 초기화
	new->e = k;
	int v = k % M;    // 삽입 리스트 위치 계산
	new->next = table[v];
	table[v] = new;    // 리스트 맨앞에 삽입
}

int findelement(node** table, int k, int M) {
	int result = 0;
	int v = k % M;      // 순위 찾기
	node* p = table[v];
	while (p != NULL) {
		result++;
		if (p->e == k) {     // 키 찾으면 브레이크
			break;
		}
		if (p->next == NULL) {
			result = 0;       // 해당 키가 없다면 0 반환
			break;
		}
		p = p->next;
	}
	return result;      // 순위 반환
}

int removeelement(node** table, int k, int M) {
	int result = 1;
	int v = k % M;
	node* p = table[v];
	if (p == NULL) {
		return 0;     // 리스트에 저장된 값이 없으면 0 반환
	}
	if (p->e == k) {
		table[v] = p->next;    // 키 찾으면 삭제
	}
	else {
		result++;
		if (p->next == NULL) {
			result = 0;     // 해당 키가 없으면 0 반환
			return result;
		}
		while (p != NULL) {
			if (p->next->e == k) {
				p->next = p->next->next;    // 키 찾으면 순위 반환, 반복 종료
				break;
			}
			if (p->next->next == NULL) {
				result = 0;     // 해당 키가 없으면 0 반환
				break;
			}
			result++;
			p = p->next;
		}
	}
	return result;      // 순위 반환
}

void initbucketarray(node** table, int M) {
	for (int i = 0; i < M; i++) {
		table[i] = NULL;     // 초기화
	}
	return;
}

void print(node** table, int M) {
	for (int i = 0; i < M; i++) {
		node* p = table[i];    // 리스트별로 출력
		while (p) {
			printf(" %d", p->e);    // 키 출력
			p = p->next;
		}
	}
}