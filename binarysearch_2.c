#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>

int search(int* arar, int l, int r, int k);   // 이진탐색 비재귀버전 함수

int main() {
	int* arar;     // 정수 키 저장 변수
	int n, k;      // 정수 키 갯수, 탐색할 키

	scanf("%d %d", &n, &k);      // 정수 키 갯수, 탐색할 키 입력
	arar = (int*)malloc(n * sizeof(int));     // 동적할당

	for (int i = 0; i < n; i++) {
		scanf("%d", &arar[i]);        // n개의 정수 키 입력
	}

	printf("%d", search(arar, 0, n - 1, k));    // 위치 출력

	free(arar);    // 메모리 해제
	return 0;
}

int search(int* arar, int l, int r, int k) {
	int result = 0;    // 반환할 위치 저장
	int left = l;
	int right = r;

	while (1) {

		if (right - left < 0) {
			result = left;     // 탐색할 키보다 크면서 가장 작은 수 위치 저장
			break;
		}

		if (arar[(left + right) / 2] == k) {    // 탐색할 키 찾은 경우
			result = (left + right) / 2;      // 위치 저장
			break;
		}
		else if (arar[(left + right) / 2] > k) {      // 탐색할 키가 중앙값보다 더 작은 경우
			right = (left + right) / 2 - 1;      // 중앙값보다 작은 키들을 다시 탐색하기 위해 right 변경
		}
		else if (arar[(left + right) / 2] < k) {      // 탐색할 키가 중앙값보다 더 큰 경우
			left = (left + right) / 2 + 1;      // 중앙값보다 큰 키들을 다시 탐색하기 위해 left 변경
		}

	}

	return result;    // 위치 반환
}