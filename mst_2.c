#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct edge {     // 간선
	int vertex1;
	int vertex2;
	int weight;
	struct edge* next;
}edge;

typedef struct vertex {    // 정점
	int vertnum;
	int distance;
}vertex;

typedef struct graph {   // 그래프
	vertex* vertex;
	edge* edge;
	int edgecount;
}graph;

graph ggraph;   // 그래프 선언
int sum;
int D[101];     // 분리집합

void initgraph(int n, int m);       // 그래프 초기화
void addedge(int a, int b, int c);     // 간선 추가
void kruskal(int n);    // kruskal 알고리즘
int find(int t);       // 소속 집합 반환
void uunion(int u, int v);     // 집합 갱신

int main() {
	int n, m;
	sum = 0;
	scanf("%d %d", &n, &m);

	initgraph(n, m);    // 그래프 초기화 함수
	kruskal(n);      // 크루스칼

	return 0;
}

void initgraph(int n, int m) {
	ggraph.edgecount = 0;     // 간선 수 초기화
	ggraph.vertex = (vertex*)malloc(n * sizeof(vertex));    // 정점 메모리 할당
	ggraph.edge = (edge*)malloc(sizeof(edge));     // 간선 메모리 할당

	for (int i = 0; i < n; i++) {     // 정점 초기화
		ggraph.vertex[i].vertnum = i + 1;
		ggraph.vertex[i].distance = 99999999999;
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
		if (p->next->weight > c) {     // 간선 삽입 위치까지 이동, 무게 순으로 정렬
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
}

void kruskal(int n) {
	for (int i = 1; i <= n; i++) {
		D[i] = i;      // 트리에 기초한 분리집합
	}
	edge* p = ggraph.edge->next;
	int i = 1;
	while (i < n) {
		int u = p->vertex1;
		int v = p->vertex2;
		if (find(u) != find(v)) {     // 소속 집합 찾기
			printf(" %d", p->weight);     // 무게 출력
			sum += p->weight;     // 무게 갱신
			uunion(u, v);      // 집합 갱신
			i++;
		}
		p = p->next;
	}
	printf("\n%d", sum);    // 무게 출력
}

int find(int t) {
	if (D[t] == t) {
		return t;
	}
	return find(D[t]);    // 소속 집합 찾기
}

void uunion(int u, int v) {
	D[find(v)] = find(u);    // 집합 갱신
}