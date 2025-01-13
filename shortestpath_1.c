#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct edge {     // 간선
	int vertex1;
	int vertex2;
	int weight;
	struct edge* next;
}edge;

typedef struct incidence {     // 인접한 정점 리스트
	struct incidence* next;
	edge* edge;
	int adjvert;
}incidence;

typedef struct vertex {    // 정점
	int vertnum;
	int distance;
	incidence* incidence;
}vertex;

typedef struct graph {   // 그래프
	vertex* vertex;
	edge* edge;
	int edgecount;
}graph;

typedef struct heap {
	int distance;
	int vertnum;
}heap;

graph ggraph;   // 그래프 선언
heap H[101];     // 우선순위 큐

void initgraph(int n, int m);       // 그래프 초기화
void addedge(int a, int b, int c);     // 간선 추가
void dijkstrashortestpath(int n, int s);      // dijkstrashortestpath 알고리즘
void downHeap(int n, int i);        // 하향이동 함수
void upHeap(int i);    // 상향이동함수

int main() {
	int n, m, s;
	scanf("%d %d %d", &n, &m, &s);

	initgraph(n, m);    // 그래프 초기화 함수
	dijkstrashortestpath(n, s);     // 최단경로 찾기

	for (int i = 1; i <= n; i++) {
		if (H[i].distance < 200000 && i != s) {
			printf("%d %d\n", H[i].vertnum, H[i].distance);    // 최단거리 출력
		}
	}

	return 0;
}

void initgraph(int n, int m) {
	ggraph.edgecount = 0;     // 간선 수 초기화
	ggraph.vertex = (vertex*)malloc(n * sizeof(vertex));    // 정점 메모리 할당
	ggraph.edge = (edge*)malloc(sizeof(edge));     // 간선 메모리 할당

	for (int i = 0; i < n; i++) {     // 정점 초기화
		ggraph.vertex[i].vertnum = i + 1;
		ggraph.vertex[i].distance = 200000;
		ggraph.vertex[i].incidence = (incidence*)malloc(sizeof(incidence));    // incidence 메모리 할당
		ggraph.vertex[i].incidence->edge = NULL;
		ggraph.vertex[i].incidence->next = NULL;    // 초기화
		ggraph.vertex[i].incidence->adjvert = -1;
	}

	ggraph.edge->vertex1 = -1;    // 간선 초기화
	ggraph.edge->vertex2 = -1;
	ggraph.edge->weight = -1;
	ggraph.edge->next = NULL;

	for (int i = 0; i < m; i++) {
		int x, y, z;
		scanf("%d %d %d", &x, &y, &z);
		if (x > y) {     // 크기 비교. 더 작은값 x에 저장
			int t = x;
			x = y;
			y = t;
		}
		addedge(x, y, z);     // 간선 추가
	}
}

void addedge(int a, int b, int c) {
	edge* p = ggraph.edge;
	for (int i = 0; i < ggraph.edgecount; i++) {
		if (p->next->vertex1 >= a && p->next->vertex2 > b) {     // 간선 삽입 위치까지 이동
			break;
		}
		p = p->next;
	}

	edge* new = (edge*)malloc(sizeof(edge));    // 추가할 간선 메모리 할당
	new->vertex1 = a;     // 간선 초기화
	new->vertex2 = b;
	new->weight = c;
	new->next = p->next;    // 간선 삽입
	p->next = new;
	ggraph.edgecount++;    // 총 간선 수 증가

	incidence* aincid = (incidence*)malloc(sizeof(incidence));
	incidence* bincid = (incidence*)malloc(sizeof(incidence));
	aincid->next = NULL;
	aincid->edge = new;
	aincid->adjvert = b;       // incidence 초기화
	bincid->next = NULL;
	bincid->edge = new;
	bincid->adjvert = a;


	incidence* q = ggraph.vertex[a - 1].incidence;
	while (1) {
		if (q->next == NULL) {
			break;     // incidence가 더 없으면 종료
		}
		if (q->next->adjvert > b) {
			break;      // 오름차순으로 삽입할 위치 찾기
		}
		q = q->next;
	}
	aincid->next = q->next;     // incidence 삽입
	q->next = aincid;

	if (a != b) {
		q = ggraph.vertex[b - 1].incidence;
		while (1) {
			if (q->next == NULL) {
				break;     // incidence가 더 없으면 종료
			}
			if (q->next->adjvert > a) {
				break;      // 오름차순으로 삽입할 위치 찾기
			}
			q = q->next;
		}
		bincid->next = q->next;     // incidence 삽입
		q->next = bincid;
	}
}

void dijkstrashortestpath(int n, int s) {
	for (int i = 1; i < n + 1; i++) {
		H[i].vertnum = ggraph.vertex[i - 1].vertnum;    // 우선순위큐(힙)에 정점 저장
		H[i].distance = ggraph.vertex[i - 1].distance;     // 우선순위큐(힙)에 키 저장
	}

	ggraph.vertex[s-1].distance = 0;    // 정점 s에서 부터 시작
	H[s].distance = 0;
	upHeap(s);
	int heapsize = n;   // 힙 크기 변수

	for (int i = 0; i < n; i++) {
		heap u = H[1];
		H[1] = H[heapsize];     // removemin
		H[heapsize] = u;
		heapsize--;
		downHeap(heapsize, 1);

		incidence* p = ggraph.vertex[u.vertnum - 1].incidence->next;   // 인접 정점들 확인하기 위한 포인터
		while (p != NULL) {
			int z = p->adjvert;

			for (int j = 1; j <= heapsize; j++) {    // 최단 경로 찾기
				if (H[j].vertnum == z && H[heapsize+1].distance + p->edge->weight < H[j].distance) {
					H[j].distance = H[heapsize + 1].distance + p->edge->weight;   // 최단경로로 갱신
					upHeap(j);    // 최소힙으로 정렬
					break;
				}
			}
			p = p->next;
		}
	}

	for (int i = 1; i < n; i++) {      // 정점 번호의 오름차순으로 정렬
		for (int j = i; j <= n; j++) {
			if (H[i].vertnum > H[j].vertnum) {
				heap t = H[i];
				H[i] = H[j];
				H[j] = t;
			}
		}
	}
	
}

void downHeap(int n, int i) {
	while (i * 2 <= n) {     // 외부노드까지 내려가면 멈춤
		int target = 2 * i;
		if (i * 2 + 1 <= n && H[i * 2 + 1].distance < H[target].distance) {   // 자식노드 중 작은 값 찾기
			target = 2 * i + 1;
		}

		if (H[i].distance > H[target].distance) {       // 자식노드가 더 작으면 swap
			heap ttt = H[target];
			H[target] = H[i];     // swap
			H[i] = ttt;
			i = target;
		}
		else {
			return;
		}
	}
}

void upHeap(int i) {
	while (i > 1) {      // 루트노드까지 올라가면 멈춤
		if (H[i].distance < H[i / 2].distance) {       // 부모노드보다 작을때
			heap ttt = H[i];
			H[i] = H[i / 2];     // swap
			H[i / 2] = ttt;
			i = i / 2;
		}
		else {         // 부모노드보다 크면 멈춤
			break;
		}
	}
}