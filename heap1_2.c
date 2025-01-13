#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
int H[100];               // 힙
int n;                // 힙의 크기

void rBuildHeap(int i);        // 재귀 상향 함수
void buildHeap();            // 비재귀 상향 함수
void downHeap(int i);        // 하향이동 함수
void printHeap();         // 출력 함수

int main() {
	int key;     // 키 저장 변수
	n = 0;              // 힙 크기 초기화

	scanf("%d", &n);     // 힙 크기 입력
	for (int i = 1; i <= n; i++) {    // 키 입력
		scanf("%d", &H[i]);
	}

	rBuildHeap(1);    // 재귀 상향식 힙 생성 함수 호출
	printHeap();     // 출력함수 호출
	return 0;
}

void rBuildHeap(int i) {
	if (i > n) {    // 외부노드까지 내려가서 정렬
		return;
	}
	rBuildHeap(2 * i);     // 왼쪽 자식노드
	rBuildHeap(2 * i + 1);      // 오른쪽 자식 노드
	downHeap(i);
	return;
}

void buildHeap() {
	for (int i = n / 2; i >= 1; i--) {    // 하향이동하면서 루트노드까지 올라감
		downHeap(i);
	}
}

void downHeap(int i) {
	while (i * 2 <= n) {     // 외부노드까지 내려가면 멈춤
		int target = 2 * i;
		if (i * 2 + 1 <= n && H[i * 2 + 1] > H[target]) {   // 자식노드 중 큰 값 찾기
			target = 2 * i + 1;
		}

		if (H[i] < H[target]) {       // 자식노드가 더 크면 swap
			int ttt = H[target];
			H[target] = H[i];     // swap
			H[i] = ttt;
			i = target;
		}
		else {
			return;
		}
	}
}

void printHeap() {
	for (int i = 1; i <= n; i++) {     // 힙 출력
		printf(" %d", H[i]);
	}
	printf("\n");
}