#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int e;
	int h;
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

int updateHeight(node* w);
int isBalanced(node* w);
node* restructure(Tree* T, node* x, node* y, node* z);
void searchAndFixAfterInsertion(Tree* T, node* w);
void searchAndFixAfterRemoval(Tree* T, node* z);

int main() {
	char m;
	int key;

	Tree* T = (Tree*)malloc(sizeof(Tree));    // 트리 초기화
	T->root = (node*)malloc(sizeof(node));
	T->root->h = 0;
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
		l->h = 0;

		r->lchild = NULL;
		r->rchild = NULL;    // 초기화
		r->parent = x;
		r->h = 0;

		x->lchild = l;    // 연결
		x->rchild = r;    // 연결
		x->h = 1;

		searchAndFixAfterInsertion(T, x);
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
	searchAndFixAfterRemoval(T, ys->parent);
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

int updateHeight(node* w) {
	int ht = 1;    // 높이 초기화
	if (w->lchild->h > w->rchild->h) {   // 왼쪽 자식노드의 높이가 더 클때
		ht += w->lchild->h;   // 더 큰 높이만큼 더함
	}
	else {   // 오른쪽 자식노드의 높이가 더 클때
		ht += w->rchild->h;   // 더 큰 높이만큼 더함
	}

	if (ht != w->h) {
		w->h = ht;    // 계산한 높이가 다르면 저장
		return 1;
	}
	else {
		return 0;
	}
}

int isBalanced(node* w) {
	int t = w->lchild->h - w->rchild->h;   // 두 자식노드의 높이 차 구하기
	if (t < 0) {
		t *= -1;
	}
	if (t < 2) {    // 높이 차가 2보다 작으면 1 반환
		return 1;
	}
	else {          // 높이 차가 2 이상이면 0 반환
		return 0;
	}
}

node* restructure(Tree* T, node* x, node* y, node* z) {   // 트리 재구성
	node* a = NULL;
	node* b = NULL;
	node* c = NULL;
	node* t0 = NULL;
	node* t1 = NULL;
	node* t2 = NULL;
	node* t3 = NULL;
	if (z->e < y->e  && y->e < x->e) {
		a = z;      // 키가 가장 작은 노드
		b = y;      // 키 중간 노드
		c = x;      // 키가 가장 큰 노드
		t0 = a->lchild;
		t1 = b->lchild;
		t2 = c->lchild;    // x노드의 왼쪽자식노드 저장
		t3 = c->rchild;    // x노드의 오른쪽자식노드 저장
	}
	else if (x->e < y->e  && y->e < z->e) {
		a = x;      // 키가 가장 작은 노드
		b = y;      // 키 중간 노드
		c = z;      // 키가 가장 큰 노드
		t0 = a->lchild;    // x노드의 왼쪽자식노드 저장
		t1 = a->rchild;    // x노드의 오른쪽자식노드 저장
		t2 = b->rchild;
		t3 = c->rchild;
	}
	else if (z->e < x->e && x->e < y->e) {
		a = z;      // 키가 가장 작은 노드
		b = x;      // 키 중간 노드
		c = y;      // 키가 가장 큰 노드
		t0 = a->lchild;
		t1 = b->lchild;    // x노드의 왼쪽자식노드 저장
		t2 = b->rchild;    // x노드의 오른쪽자식노드 저장
		t3 = c->rchild;
	}
	else if (y->e < x->e && x->e < z->e) {
		a = y;      // 키가 가장 작은 노드
		b = x;      // 키 중간 노드
		c = z;      // 키가 가장 큰 노드
		t0 = a->lchild;
		t1 = b->lchild;    // x노드의 왼쪽자식노드 저장
		t2 = b->rchild;    // x노드의 오른쪽자식노드 저장
		t3 = c->rchild;
	}

	if (T->root == z) {   // z가 루트 노드였을 때
		T->root = b;
		b->parent = NULL;
	}
	else if (z->parent->lchild == z) {     // z가 왼쪽 자식노드 였을 때
		z->parent->lchild = b;
		b->parent = z->parent;
	}
	else if (z->parent->rchild == z) {     // z가 오른쪽 자식노드 였을 때
		z->parent->rchild = b;
		b->parent = z->parent;
	}

	a->lchild = t0;    // a의 왼쪽 자식노드에 t0 저장
	a->rchild = t1;    // a의 오른쪽 자식노드에 t1 저장
	t0->parent = a;
	t1->parent = a;
	updateHeight(a);

	c->lchild = t2;    // a의 왼쪽 자식노드에 t2 저장
	c->rchild = t3;    // a의 오른쪽 자식노드에 t3 저장
	t2->parent = c;
	t3->parent = c;
	updateHeight(c);

	b->lchild = a;    // b의 왼쪽 자식노드에 a 저장
	b->rchild = c;    // b의 오른쪽 자식노드에 c 저장
	a->parent = b;
	c->parent = b;
	updateHeight(b);

	return b;
}

void searchAndFixAfterInsertion(Tree* T, node* w) {
	w->lchild->h = 0;    // 자식노드 높이 0
	w->rchild->h = 0;
	w->h = 1;     // w 높이 1로 저장
	if (w == T->root) {
		return;
	}

	node* z = w->parent;
	while (updateHeight(z) && isBalanced(z)) {
		if (z == T->root) {      // z가 루트노드일 때까지 반복
			return;
		}
		z = z->parent;
	}
	if (isBalanced(z)) {
		return;
	}

	node* y = NULL;
	if (z->lchild->h > z->rchild->h) {
		y = z->lchild;    // 높이가 더 높은 왼쪽 자식노드를 y에 저장
	} 
	else {
		y = z->rchild;    // 높이가 더 높은 오른쪽 자식노드를 y에 저장
	}

	node* x = NULL;
	if (y->lchild->h > y->rchild->h) {
		x = y->lchild;    // 높이가 더 높은 왼쪽 자식노드를 x에 저장
	}
	else {
		x = y->rchild;    // 높이가 더 높은 오른쪽 자식노드를 x에 저장
	}
	restructure(T, x, y, z);    // 트리 재구성
	return;
}

void searchAndFixAfterRemoval(Tree* T, node* z) {
	while (updateHeight(z) && isBalanced(z)) {
		if (z == T->root) {      // z가 루트노드일 때까지 반복
			return;
		}
		z = z->parent;
	}
	if (isBalanced(z)) {
		return;
	}

	node* y = NULL;
	if (z->lchild->h > z->rchild->h) {
		y = z->lchild;    // 높이가 더 높은 왼쪽 자식노드를 y에 저장
	}
	else {
		y = z->rchild;    // 높이가 더 높은 오른쪽 자식노드를 y에 저장
	}

	node* x = NULL;
	if (y->lchild->h > y->rchild->h) {
		x = y->lchild;    // 높이가 더 높은 왼쪽 자식노드를 x에 저장
	}
	else if (y->lchild->h < y->rchild->h) {
		x = y->rchild;    // 높이가 더 높은 오른쪽 자식노드를 x에 저장
	}
	else {
		if (z->lchild == y) {
			x = y->lchild;    // y가 왼쪽 자식노드면 y의 왼쪽 자식노드를 x에 저장
		}
		else {
			x = y->rchild;    // y가 오른쪽 자식노드면 y의 오른쪽 자식노드를 x에 저장
		}
	}

	node* t = restructure(T, x, y, z);    // 트리 재구성
	if (t == T->root) {
		return;
	}
	searchAndFixAfterRemoval(T, t->parent);
}

