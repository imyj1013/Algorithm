#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct edge {     // 간선
	int vertex1;
	int vertex2;
	int weight;
	struct edge* next;
}edge;

typedef struct incidence {     // 인접한 정점
	struct incidence* next;
	edge* edge;
	int adjvert;
}incidence;

typedef struct vertex {    // 정점
	int vertnum;
	struct vertax* next;
	incidence* incidence;
}vertex;

typedef struct graph {   // 그래프
	vertex* vertex;
	edge* edge;
	int edgecount;
}graph;

graph ggraph;   // 그래프 선언

void initgraph();       // 그래프 초기화
void searchadj(int a);    // 인접 정점 찾아서 출력
void addedge(int a, int b, int w);     // 간선 추가
void removeedge(int a, int b);     // 간선 삭제

int main() {
	char menu;   // 입력 명령어
	int a, b, w;    // 정점, 가중치

	initgraph();    // 그래프 초기화 함수

	while (1) {
		scanf("%c", &menu);
		if (menu == 'a') {     // a가 입력됐을 때
			scanf("%d", &a);     // 정점 입력
			getchar();

			if (a >= 7 || a <= 0) {
				printf("-1\n");      // 정점이 유효한지 확인
				continue;
			}
			else {
				searchadj(a);     // 인접한 정접 찾아서 출력
			}
		}
		else if (menu == 'm') {      // m이 입력됐을 때
			scanf("%d %d %d", &a, &b, &w);    // 정점, 가중치 입력
			getchar();

			if (a > b) {      // 크기 비교
				int t = a;
				a = b;
				b = t;
			}

			if (a >= 7 || a <= 0 || b >= 7 || b <= 0) {
				printf("-1\n");       // 정점이 유효한지 확인
				continue;
			}
			else {
				edge* p = ggraph.edge->next;
				for (int i = 0; i < ggraph.edgecount; i++) {
					if (a == p->vertex1 && b == p->vertex2) {    // a,b를 지나는 간선이 존재하면
						if (w != 0) {
							p->weight = w;    // 가중치 바꿈
							break;
						}
						else {
							removeedge(a, b);    // w가 0이면 간선 삭제
							break;
						}
					}
					if (i == ggraph.edgecount - 1) {
						addedge(a, b, w);     // 간선이 없으면 간선 추가
						break;
					}
					p = p->next;
				}
			}
		}
		else if (menu == 'q') {    // 종료
			break;
		}
	}

	return 0;
}

void initgraph() {
	ggraph.edgecount = 0;     // 간선 수 초기화
	ggraph.vertex = (vertex*)malloc(6 * sizeof(vertex));    // 정점 메모리 할당
	ggraph.edge = (edge*)malloc(sizeof(edge));     // 간선 메모리 할당

	for (int i = 0; i <= 5; i++) {     // 정점 초기화
		ggraph.vertex[i].vertnum = i + 1;
		ggraph.vertex[i].incidence = (incidence*)malloc(sizeof(incidence));    // incidence 메모리 할당
		ggraph.vertex[i].incidence->edge = NULL;
		ggraph.vertex[i].incidence->next = NULL;    // 초기화
		ggraph.vertex[i].incidence->adjvert = -1;
	}

	ggraph.edge->vertex1 = -1;    // 간선 초기화
	ggraph.edge->vertex2 = -1;
	ggraph.edge->weight = -1;
	ggraph.edge->next = NULL;

	addedge(1, 2, 1);   // 간선 추가
	addedge(1, 3, 1);
	addedge(1, 4, 1);
	addedge(1, 6, 2);
	addedge(2, 3, 1);
	addedge(3, 5, 4);
	addedge(5, 5, 4);
	addedge(5, 6, 3);
}

void searchadj(int a) {
	incidence* p = ggraph.vertex[a - 1].incidence;

	while (1) {
		if (p->next == NULL) {
			break;                // 인접한 정점 더 없으면 종료
		}
		printf(" %d %d", p->next->adjvert, p->next->edge->weight);    // 인접 정점, 가중치 출력
		p = p->next;
	}
	printf("\n");
}

void addedge(int a, int b, int w) {
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
	new->weight = w;
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

void removeedge(int a, int b) {
	edge* p = ggraph.edge;
	incidence* q = ggraph.vertex[a - 1].incidence;
	while (1) {     // a에 인접한 b를 지나는 incidence 찾아서 삭제
		if (q->next == NULL) {
			break;       // 인접 정점 더 없으면 종료
		}
		if (q->next->adjvert == b) {     // b 정점 지나는 incidence 찾기
			q->next = q->next->next;      // incidence 삭제
			break;
		}
		q = q->next;
	}

	if (a != b) {      // a,b가 다를 때
		q = ggraph.vertex[b - 1].incidence;
		while (1) {     // b에 인접한 a를 지나는 incidence 찾아서 삭제
			if (q->next == NULL) {
				break;       // 인접 정점 더 없으면 종료
			}
			if (q->next->adjvert == a) {     // a 정점 지나는 incidence 찾기
				q->next = q->next->next;     // incidence 삭제
				break;
			}
			q = q->next;
		}
	}

	while (1) {
		if (p->next == NULL) {
			break;     // 간선이 더 없으면 종료
		}
		if (p->next->vertex1 == a && p->next->vertex2 == b) {
			p->next = p->next->next;    // a,b를 지나는 간선 삭제
			break;
		}
		p = p->next;
	}
	ggraph.edgecount--;    // 총 간선 수 줄이기
}