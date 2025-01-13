#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>

int main() {
	int n, t;       // 입력받을 정수 개수, 삽입 위치 변수
	int* ar;        // 배열

	scanf("%d", &n);        // 입력받을 정수 입력받음
	ar = (int*)malloc(sizeof(int) * n);      // 메모리 할당
	for (int i = 0; i < n; i++) {
		scanf("%d", &ar[i]);      // 정수 n개 입력받음
	}

	for (int i = 1; i < n; i++) {      // 삽입정렬로 정렬
		t = ar[i];
		int j;
		for (j = i - 1; j >= 0, t < ar[j]; j--) {       // 삽입 위치 찾기
			ar[j + 1] = ar[j];      // 삽입위치까지 뒤로 한칸씩 미루기
		}
		ar[j + 1] = t;     // 정수 삽입
	}

	for (int i = 0; i < n; i++) {
		printf(" %d", ar[i]);        // 정렬된 배열 출력
	}

	free(ar);     // 메모리 해제
	return 0;
}