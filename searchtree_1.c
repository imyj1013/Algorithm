#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int e;
	struct node* parent, * lchild, * rchild;
}node;

typedef struct {
	node* root;
} Tree;

int findelement(Tree* T, int key);     // 탐색 함수
void insertitem(Tree* T, int key);     // 삽입 함수
node* treesearch(node* vvv, int key);    // 위치 찾기
int removeelement(Tree* T, int key);     // 삭제 함수
node* reduceexternal(Tree* T, node* y);     // 외부노드 삭제 함수
int isexternal(node* w);      // 외부노드 인가
int isinternal(node* w);      // 내부노드 인가
node* inordersucc(node* w);    // 다음 탐색 노드 찾기
void printtree(node* v);    // 트리 출력 함수
node* sibling(node* w);     // 형제노드 찾기

int main() {
	char m;
	int key;

	Tree* T = (Tree*)malloc(sizeof(Tree));    // 트리 초기화
	T->root = (node*)malloc(sizeof(node));
	T->root->parent = NULL;
	T->root->lchild = NULL;
	T->root->rchild = NULL;

	while (1) {
		scanf("%c", &m);
		getchar();

		if (m == 'i') {      // i 입력받았을 때
			scanf("%d", &key);    // 키 입력받음
			getchar();

			insertitem(T, key);      // 삽입함수 호출
		}
		else if (m == 'd') {      // d 입력받았을 때
			scanf("%d", &key);    // 키 입력받음
			getchar();

			int t = removeelement(T, key);    // 삭제함수 호출
			if (t == -1) {
				printf("X\n");     // 없으면 x 출력
			}
			else {
				printf("%d\n", t);    // 키 출력
			}
		}
		else if (m == 's') {
			scanf("%d", &key);    // 키 입력받음
			getchar();

			int x = findelement(T, key);    // 탐색 함수 호출
			if (x == -1) {
				printf("X\n");    // 없으면 x 출력
			}
			else {
				printf("%d\n", x);     // 키 출력
			}
		}
		else if (m == 'p') {      // p 입력받았을 때

			printtree(T->root);    // 출력 함수 호출
			printf("\n");

		}
		else if (m == 'q') {      // q 입력받았을 때
			break;
		}
	}
	return 0;
}

int findelement(Tree* T, int key) {
	node* w = treesearch(T->root, key);   // 위치 찾기 함수 호출

	if (isexternal(w)) {
		return -1;
	}
	else {
		return w->e;   // 위치 반환
	}

}

void insertitem(Tree* T, int key) {
	node* x = treesearch(T->root, key);   // 삽입 위치 찾기

	if (isinternal(x)) {
		return;
	}
	else {
		x->e = key;   // 키 저장

		node* l = (node*)malloc(sizeof(node));   // 왼쪽 자식노드 
		node* r = (node*)malloc(sizeof(node));    // 오른쪽 자식 노드

		l->lchild = NULL;
		l->rchild = NULL;   // 초기화
		l->parent = x;

		r->lchild = NULL;
		r->rchild = NULL;    // 초기화
		r->parent = x;

		x->lchild = l;    // 연결
		x->rchild = r;    // 연결

	}

}

node* treesearch(node* vvv, int key) {
	if (isexternal(vvv)) {
		return vvv;
	}

	if (vvv->e == key) {      // 키 찾으면 위치 반환
		return vvv;
	}
	else if (vvv->e > key) {
		return treesearch(vvv->lchild, key);     // 키가 더 작으면 왼쪽 자식노드 탐색
	}
	else {
		return treesearch(vvv->rchild, key);    // 키가 더 크면 오른쪽 자식노드 탐색
	}
}

int removeelement(Tree* T, int key) {
	node* x = treesearch(T->root, key);    // 위치 찾기

	if (isexternal(x)) {
		return -1;
	}

	int result = x->e;   // 반환할 삭제 키
	node* y = x->lchild;

	if (!isexternal(y)) {
		y = x->rchild;
	}
	node* ys = NULL;
	if (isexternal(y)) {
		ys = reduceexternal(T, y);   // 외부노드 삭제 함수 호출
	}
	else {
		node* z = inordersucc(x);    // 다음 탐색 노드 찾기
		y = z->lchild;
		x->e = z->e;
		ys = reduceexternal(T, y);   // 외부노드 삭제 함수 호출
	}
	return result;    // 키 반환
}

node* reduceexternal(Tree* T, node* y) {
	node* w = y->parent;
	node* ys = sibling(y);    // 형제 노드 찾기

	if (T->root == w) {
		T->root = ys;      // 부모노드가 루트노드면 형제노드를 루트노드로 저장
		ys->parent = NULL;
	}
	else {
		node* x = w->parent;
		ys->parent = x;
		if (w == x->lchild) {
			x->lchild = ys;     // 부모노드가 왼쪽 자식노드면 그 위치에 형제노드 저장
		}
		else {
			x->rchild = ys;     // 부모노드가 오른쪽 자식노드면 그 위치에 형제노드 저장
		}
	}
	free(w);    // 메모리해제
	free(y);

	return ys;
}

int isexternal(node* w) {     // 외부노드인가
	if (w->lchild == NULL && w->rchild == NULL) {
		return 1;     // 외부노드인 경우
	}
	else {
		return 0;   // 아닌경우
	}
}

int isinternal(node* w) {      // 내부노드인가
	if (w->lchild != NULL || w->rchild != NULL) {
		return 1;     // 내부노드인 경우
	}
	else {
		return 0;     // 아닌경우
	}
}

node* inordersucc(node* w) {    // 중위순회 다음 탐색 노드 찾기
	w = w->rchild;
	while (isinternal(w->lchild)) {
		w = w->lchild;    // 왼쪽 자식 노드따라 내려감
	}
	return w;   // 다음 탐색 노드 반환
}

void printtree(node* v) {
	printf(" %d", v->e);    // 전위순회로 키 출력
	if (isinternal(v->lchild)) {
		printtree(v->lchild);    // 왼쪽 자식 노드 출력 함수 호출
	}
	if (isinternal(v->rchild)) {
		printtree(v->rchild);    // 오른쪽 자식 노드 출력 함수 호출
	}
}

node* sibling(node* w) {    // 형제노드 찾기
	if (w->parent->lchild == w) {
		return w->parent->rchild;     // 왼쪽 자식 노드일 경우 오른쪽 자식노드 반환
	}
	else {
		return w->parent->lchild;     // 오른쪽 자식 노드일 경우 왼쪽 자식노드 반환
	}
}
