#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct edge {    // 간선
	int vertex1;
	int vertex2;
	int label;      // 0이면 fresh, 1이면 tree, 2면 cross
	struct edge* next;
}edge;

typedef struct vertex {    // 정점
	int vertnum;
	int label;      // 0이면 fresh, 1이면 visited
	struct vertax* next;
}vertex;

typedef struct graph {     // 그래프
	vertex* vertex;
	edge* edge;
	int edgecount;
}graph;

graph ggraph;      // 그래프 선언
edge*** matrix;     // 인접행렬

void initgraph(int n, int m);     // 그래프 초기화
void addedge(int a, int b, int n);     // 간선 추가
void rbfs(int s, int n);      // bfs

int main() {
	int n, m, s;
	scanf("%d %d %d", &n, &m, &s);

	initgraph(n, m);    // 그래프 초기화 함수

	rbfs(s, n);     // 너비우선탐색

	return 0;

}

void initgraph(int n, int m) {
	ggraph.edgecount = 0;     // 간선 수 초기화
	ggraph.vertex = (vertex*)malloc(n * sizeof(vertex));    // 정점 메모리 할당
	ggraph.edge = (edge*)malloc(sizeof(edge));     // 간선 메모리 할당
	matrix = (edge***)malloc(n * sizeof(edge**));     // 인접행렬 초기화
	for (int i = 0; i < n; i++) {
		matrix[i] = (edge**)calloc(n, sizeof(edge*));
	}

	for (int i = 0; i < n; i++) {     // 정점 초기화
		ggraph.vertex[i].vertnum = i + 1;
		ggraph.vertex[i].label = 0;
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
		addedge(x, y, n);     // 간선 추가
	}

}

void addedge(int a, int b, int n) {
	edge* p = ggraph.edge;
	for (int i = 0; i < ggraph.edgecount; i++) {
		if (p->next->vertex1 >= a && p->next->vertex2 > b) {     // 간선 삽입 위치까지 이동
			break;
		}
		p = p->next;
	}

	edge* new = (edge*)malloc(sizeof(edge));     // 추가할 간선 메모리 할당
	new->vertex1 = a;       // 간선 초기화
	new->vertex2 = b;
	new->label = 0;
	new->next = p->next;    // 간선 삽입
	p->next = new;
	ggraph.edgecount++;    // 총 간선 수 증가

	matrix[a - 1][b - 1] = new;   // 인접행렬에 간선 추가
	matrix[b - 1][a - 1] = new;
}

void rbfs(int s, int n) {
	int* list = (int*)malloc(n * sizeof(int));    // 탐색할 정점 저장할 리스트
	int index = 0;
	list[0] = s;
	int end = index;

	while (end < n && index != n) {
		printf("%d\n", list[index]);       // 방문한 정점 출력
		for (int i = 0; i < n; i++) {
			if (matrix[list[index] - 1][i] != NULL && matrix[list[index] - 1][i]->label == 0) {
				if (ggraph.vertex[i].label == 0) {
					ggraph.vertex[i].label = 1;   // 정점에 방문한 걸로 표시
					matrix[list[index] - 1][i]->label = 1;    // 간선 지난걸로 표시
					matrix[i][list[index] - 1]->label = 1;

					list[++end] = i + 1;    // 탐색할 정점 저장
				}
				else {
					matrix[list[index] - 1][i]->label = 2;    // 간선 지난걸로 표시
					matrix[i][list[index] - 1]->label = 2;
				}
			}
		}
		index++;
	}
}
