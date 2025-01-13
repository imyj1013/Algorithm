#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>

int main() {
	int n, max_index;            // 입력받을  정수 개수, 바꿀 위치 변수
	int* ar;              // 배열

	scanf("%d", &n);              // 입력받을 정수 개수 입력받음
	ar = (int*)malloc(sizeof(int) * n);      // 메모리 할당
	for (int i = 0; i < n; i++) {
		scanf("%d", &ar[i]);         // 정수 n개 입력
	}

	for (int i = n - 1; i >= 1; i--) {       // 선택정렬로 정렬
		max_index = i;
		for (int j = i - 1; j >= 0; j--) {
			if (ar[max_index] < ar[j]) {       // 최대값 찾기
				max_index = j;              // 바꿀 위치(최대값 위치) 저장
			}
		}

		int t = ar[i];             // 최대값 swap하기
		ar[i] = ar[max_index];
		ar[max_index] = t;
	}

	for (int i = 0; i < n; i++) {
		printf(" %d", ar[i]);         // 정렬된 배열 출력
	}

	free(ar);        // 메모리 해제
	return 0;
}

