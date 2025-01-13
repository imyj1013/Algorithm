#pragma warning(disable: 4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int search(char* arar, int l, int r);   // 이진탐색 재귀버전 함수

int main() {
	int a, b, len;    // 두 개의 정수와 문자열 길이
	char* answer;     // 문자열

	scanf("%d %d %d", &a, &b, &len);    // 두 개의 정수와 문자열 길이 입력
	getchar();
	answer = (char*)malloc((len+1) * sizeof(char));    // 동적할당

	scanf("%s", answer);      // 문자열 입력

	printf("%d", search(answer, a, b));     // 정답 출력

	free(answer);     // 메모리 해제
	return 0;
}

int search(char* answer, int a, int b) {
	if (b - a <= 0) {
		return b;     // 정답 반환
	}

	if (*answer == 'Y') {      // 정답이 중앙값보다 클 때
		answer = answer + 1;
		return search(answer, (a+b)/2+1, b);    // 중앙값보다 큰 수들을 다시 탐색
	}
	else if (*answer == 'N') {      // 정답이 중앙값 이하일 때
		answer = answer + 1;
		return search(answer, a, (a + b) / 2);    // 중앙값 이하인 수들을 다시 탐색
	}

}