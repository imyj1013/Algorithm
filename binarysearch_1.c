#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>

int search(int* arar, int l, int r, int k);   // 이진탐색 재귀버전 함수

int main() {
	int* arar;     // 정수 키 저장 변수
	int n, k;      // 정수 키 갯수, 탐색할 키

	scanf("%d %d", &n, &k);      // 정수 키 갯수, 탐색할 키 입력
	arar = (int*)malloc(n*sizeof(int));     // 동적할당

	for (int i = 0; i < n; i++) {
		scanf("%d", &arar[i]);        // n개의 정수 키 입력
	}

	printf("%d", search(arar, 0, n-1, k));    // 위치 출력

	free(arar);    // 메모리 해제
	return 0;
}

int search(int* arar, int l, int r, int k) {
	if (r - l < 0) {
		return r;     // 탐색할 키보다 작으면서 가장 큰 수 위치 반환
	}

	if (arar[(l + r) / 2] == k) {    // 탐색할 키 찾은 경우
		return (l + r) / 2;      // 위치 반환
	}
	else if (arar[(l + r) / 2] > k) {      // 탐색할 키가 중앙값보다 더 작은 경우
		return search(arar, l, (l + r) / 2 - 1, k);      // 중앙값보다 작은 키들을 다시 탐색
	}
	else if (arar[(l + r) / 2] < k) {       // 탐색할 키가 중앙값보다 더 큰 경우
		return search(arar, (l + r) / 2 + 1, r, k);       // 중앙값보다 큰 키들을 다시 탐색
	}
}