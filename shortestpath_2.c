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
int D[101];     // 정점까지 최단거리

void initgraph(int n, int m);       // 그래프 초기화
void addedge(int a, int b, int c);     // 간선 추가
void bellmanfordshortestpath(int n, int s);    // bellmanfordshortestpath 알고리즘

int main() {
	int n, m, s;
	scanf("%d %d %d", &n, &m, &s);

	initgraph(n, m);    // 그래프 초기화 함수
	bellmanfordshortestpath(n, s);      // bellmanfordshortestpath

	for (int i = 1; i <= n; i++) {
		if (D[i] < 200000 && i != s) {
			printf("%d %d\n", i, D[i]);    // 최단거리 출력
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
	}

	ggraph.edge->vertex1 = -1;    // 간선 초기화
	ggraph.edge->vertex2 = -1;
	ggraph.edge->weight = -1;
	ggraph.edge->next = NULL;

	for (int i = 0; i < m; i++) {
		int x, y, z;
		scanf("%d %d %d", &x, &y, &z);
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
}

void bellmanfordshortestpath(int n, int s) {
	for (int i = 1; i <= n; i++) {
		D[i] = 200000;      // 최단거리 무한대값 설정
	}

	D[s] = 0;
	for (int i = 1; i <= n - 1; i++) {
		edge* p = ggraph.edge->next;
		while (p != NULL) {        // 모든 간선에 대해 완화시도
			int u = p->vertex1;
			int v = p->vertex2;
			if (D[u] != 200000 && D[v] > D[u] + p->weight) {    // 최단거리 갱신
				D[v] = D[u] + p->weight;
			}
			p = p->next;
		}
	}
}
