#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct incidence {     // 인접리스트
	int x;
	struct incidence* next;
}incidence;

typedef struct edge {     // 간선
	int start;
	int end;
}edge;

typedef struct vertex {     // 정점
	char name;
	incidence* out;
	incidence* in;
	int indegree;
}vertex;

typedef struct graph {    // 그래프
	vertex* vertex;
	edge* edge;
}graph;

void buildgraph();
void insertvertex(char vertexname, int i);    // 정점 삽입
void insertdirectededge(char uname, char wname, int i);     // 방향간선 삽입
int index(char vertexname);     // 정점 인덱스 찾기
void addfirst(incidence* head, int i);    // 맨 앞에 삽입
void topologicalsort();     // 위상순서 구하기
int isempty(int* qqq);    // 큐 비었는가
void enqueue(int i);      // 큐 삽입
int dequeue();       // 큐 삭제

graph ggg;     // 방향 그래프
int n, m;     // 정점 수 , 간선 수
int* toporder;       // 위상순서
int* qqq;      // 정점 대기열
int qqqfront, qqqrear;    // 큐 앞, 뒤

int main() {
	buildgraph();

	topologicalsort();     // 위상순서 구하기

	if (toporder[0] == 0) {
		printf("0");     // 방향 싸이클이 존재하면 0 출력
	}
	else {
		for (int i = 1; i <= n; i++) {
			printf("%c ", ggg.vertex[toporder[i]].name);     // 위상순서 출력
		}
	}

	return 0;
}

void buildgraph() {
	scanf("%d", &n);     // 정점 수 입력
	getchar();
	ggg.vertex = (vertex*)malloc(n * sizeof(vertex));

	for (int i = 0; i < n; i++) {
		char vertexname;       // 정점 이름
		scanf("%c", &vertexname);       // 정점 이름 입력
		getchar();
		insertvertex(vertexname, i);       // 정점 삽입
	}

	scanf("%d", &m);     // 간선 수 입력
	getchar();
	ggg.edge = (edge*)malloc(m * sizeof(edge));

	for (int i = 0; i < m; i++) {
		char uname, wname;
		scanf("%c %c", &uname, &wname);     // 방향간선 입력
		getchar();
		insertdirectededge(uname, wname, i);      // 방향간선 삽입
	}

	return;
}

void insertvertex(char vertexname, int i) {
	ggg.vertex[i].name = vertexname;     // 정점 이름 저장
	ggg.vertex[i].out = (incidence*)malloc(sizeof(incidence));     // 진출부 리스트
	ggg.vertex[i].out->next = NULL;
	ggg.vertex[i].in = (incidence*)malloc(sizeof(incidence));    // 진입부 리스트
	ggg.vertex[i].in->next = NULL;
	ggg.vertex[i].indegree = 0;     // 진입차수 초기화
	return;
}

void insertdirectededge(char uname, char wname, int i) {
	int uindex, windex;

	uindex = index(uname);    // 정점 인덱스 찾기
	windex = index(wname);

	ggg.edge[i].start = uindex;    // 시점 저장
	ggg.edge[i].end = windex;       // 종점 저장

	addfirst(ggg.vertex[uindex].out, i);    // 진출부 리스트에 삽입
	addfirst(ggg.vertex[windex].in, i);     // 진입부 리스트에 삽입

	ggg.vertex[windex].indegree++;     // 진입차수 갱신
	return;
}

int index(char vertexname) {
	for (int i = 0; i < n; i++) {
		if (ggg.vertex[i].name == vertexname) {
			return i;     // 정점 인덱스 반환
		}
	}
}

void addfirst(incidence* head, int i) {
	incidence* new = (incidence*)malloc(sizeof(incidence));
	new->x = i;
	new->next = head->next;     // 맨앞에 삽입
	head->next = new;
	return;
}

void topologicalsort() {
	toporder = (int*)malloc((n + 1) * sizeof(int));
	int* in = (int*)malloc(n*sizeof(int));    // 진입차수
	qqq = (int*)malloc(n * sizeof(int));

	qqqfront = 0;      // 큐 초기화
	qqqrear = n-1;

	for (int i = 0; i < n; i++) {
		in[i] = ggg.vertex[i].indegree;     // 진입차수 저장
		if (in[i] == 0) {
			enqueue(i);      // 진입차수가 0인 정점 삽입
		}
	}

	int t = 1;
	int u;
	while (isempty(qqq) != 1) {
		u = dequeue();
		toporder[t] = u;    // 위상순서 저장
		t++;

		incidence* p = ggg.vertex[u].out->next;
		while (1) {
			if (p == NULL) {    // 진출간선 더 없으면 종료
				break;
			}
			int w = ggg.edge[p->x].end;
			in[w] = in[w] - 1;    // in[w] 1만큼 감소
			if (in[w] == 0) {
				enqueue(w);    // in[w]이 0이면 큐에 삽입
			}
			p = p->next;
		}
	}

	if (t <= n) {
		toporder[0] = 0;   // 방향싸이클 존재하면 0 저장
	}
	else {
		toporder[0] = 1;     // 방향싸이클 존재하지 않으면 1 저장
	}
	return;
}

int isempty(int *qqq) {
	if ((qqqrear + 1) % n == qqqfront) {
		return 1;         // 큐가 빈 경우
	}
	else {
		return 0;         // 큐가 비어있지 않은 경우
	}
}

void enqueue(int i) {
	qqqrear = (qqqrear + 1) % n;
	qqq[qqqrear] = i;     // 큐 삽입
	return;
}

int dequeue() {
	int result = qqq[qqqfront];
	qqqfront = (qqqfront + 1) % n;     // 큐 삭제
	return result;    // 삭제 큐 반환
}