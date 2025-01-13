#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct edge {     // 간선
	int vertex1;
	int vertex2;
	int label;      // 0이면 fresh, 1이면 tree, 2면 back
	struct edge* next;
}edge;

typedef struct incidence {     // 인접한 정점
	struct incidence* next;
	edge* edge;
	int adjvert;
}incidence;

typedef struct vertex {    // 정점
	int vertnum;
	int label;      // 0이면 fresh, 1이면 visited
	incidence* incidence;
}vertex;

typedef struct graph {   // 그래프
	vertex* vertex;
	edge* edge;
	int edgecount;
}graph;

graph ggraph;   // 그래프 선언

void initgraph(int n, int m);       // 그래프 초기화
void addedge(int a, int b);     // 간선 추가
void rdfs(int s);     // dfs 재귀

int main() {
	int n, m, s;
	scanf("%d %d %d", &n, &m, &s);

	initgraph(n, m);    // 그래프 초기화 함수

	rdfs(s);     // 깊이우선탐색

	return 0;
}

void initgraph(int n, int m) {
	ggraph.edgecount = 0;     // 간선 수 초기화
	ggraph.vertex = (vertex*)malloc(n * sizeof(vertex));    // 정점 메모리 할당
	ggraph.edge = (edge*)malloc(sizeof(edge));     // 간선 메모리 할당

	for (int i = 0; i < n; i++) {     // 정점 초기화
		ggraph.vertex[i].vertnum = i + 1;
		ggraph.vertex[i].label = 0;
		ggraph.vertex[i].incidence = (incidence*)malloc(sizeof(incidence));    // incidence 메모리 할당
		ggraph.vertex[i].incidence->edge = NULL;
		ggraph.vertex[i].incidence->next = NULL;    // 초기화
		ggraph.vertex[i].incidence->adjvert = -1;
	}

	ggraph.edge->vertex1 = -1;    // 간선 초기화
	ggraph.edge->vertex2 = -1;
	ggraph.edge->label = 0;
	ggraph.edge->next = NULL;

	for (int i = 0; i < m; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		if (x > y) {     // 크기 비교. 더 작은값 x에 저장
			int t = x;
			x = y;
			y = t;
		}
		addedge(x, y);     // 간선 추가
	}
}

void addedge(int a, int b) {
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
	new->label = 0;
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

void rdfs(int s) {
	ggraph.vertex[s - 1].label = 1;   // 정점에 방문한 걸로 표시
	printf("%d\n", s);       // 방문한 정점 출력

	incidence* p = ggraph.vertex[s - 1].incidence->next;
	while (1) {
		if (p->edge->label == 0) {    // 지난 적이 없는 간선인가
			if (ggraph.vertex[p->adjvert - 1].label == 0) {    // 방문한 적이 없는 간선인가
				p->edge->label = 1;     // 간선 지난 걸로 표시
				rdfs(p->adjvert);    // 재귀
			}
			else {
				p->edge->label = 2;     // 간선 지난 걸로 표시
			}
		}
		p = p->next;
		if (p == NULL) {     // 인접한 정점이 더 없으면 종료
			break;
		}
	}

}