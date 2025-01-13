#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>

int findelement(int* table, int k, int M);     // 탐색함수
int insertitem(int* table, int k, int M);      // 삽입함수

int main() {
	int M, n, x;
	char menu;
	scanf("%d %d", &M, &n);    // 배열크기와 삽입개수 입력
	getchar();

	int* table = (int*)malloc(M * sizeof(int));    // 테이블 초기화
	for (int i = 0; i < M; i++) {
		table[i] = 0;
	}

	while (n > 0) {
		scanf("%c", &menu);

		if (menu == 'i') {
			scanf("%d", &x);
			int t = insertitem(table, x, M);     // 삽입함수 호출
			printf("%d\n", t);     // 주소 출력
		}
		else if (menu == 's') {
			scanf("%d", &x);
			int t = findelement(table, x, M);     // 탐색함수 호출
			if (t == -1) {
				printf("-1\n");      // 해당 키가 없을경우 -1 출력
			}
			else {
				printf("%d %d\n", t, x);    // 주소와 키 출력
			}
		}
		else if (menu == 'e') {
			break;     // 종료
		}
		getchar();
	}

	free(table);    // 메모리해제

	return 0;
}

int findelement(int* table, int k, int M) {
	int v = k % M;
	if (table[v] == k) {
		return v;      // 키 찾으면 주소 반환
	}
	else {
		int result = 1;
		while (1) {
			if (result > M) {
				return -1;     // 키 없으면 -1 반환
			}

			if (table[(v + result) % M] == k) {
				return (v + result) % M;        // 키 찾으면 주소 반환
			}
			else {
				result++;    // 한칸씩 뒤로 이동하며 탐색
			}
		}
	}
}

int insertitem(int* table, int k, int M) {
	int v = k % M;
	if (table[v] == 0) {
		table[v] = k;
		return v;       // 저장할 위치 찾으면 주소 반환
	}
	else {
		int result = 1;
		printf("C");
		while (1) {
			if (result > M) {
				return;     // 배열이 다 찼을때 반환
			}

			if (table[(v+result)%M] == 0) {
				table[(v + result) % M] = k;
				return (v + result) % M;     // 저장한 주소 반환
			}
			else {
				printf("C");    // 충돌일어나면 C 출력
				result++;     // 한칸씩 이동하며 탐색
			}
		}
	}
}