#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
int H[100];               // 힙
int n;                // 힙의 크기

void insertItem(int key);   // 삽입 함수
int removeMax();           //삭제 함수
void upHeap(int i);         // 상향이동 함수
void downHeap(int i);        // 하향이동 함수
void printHeap();         // 출력 함수

int main() {
	int key;     // 키 저장 변수
	char menu;     // i,d, p, q 저장 변수
	scanf("%c", &menu);
	n = 0;              // 힙 크기 초기화

	while (menu != 'q') {
		if (menu == 'i') {      // i 입력받았을 때
			scanf("%d", &key);    // 키 입력받음
			getchar();

			insertItem(key);      // 삽입함수 호출
			printf("0\n");
		}
		else if (menu == 'd') {      // d 입력받았을 때
			int t = removeMax();    // 삭제함수 호출
			printf("%d\n", t);
		}
		else if (menu == 'p') {      // p 입력받았을 때
			printHeap();            // 출력함수 호출
		}
		else if (menu == 'q') {      // q 입력받았을 때
			break;
		}

		scanf("%c", &menu);
	}

	return 0;
}

void insertItem(int key) {
	n++;          // 힙 크기 증가
	H[n] = key;     // 제일 끝에 저장

	upHeap(n);    // 상향이동 함수 호출
}

int removeMax() {
	int removekey = H[1];      // 반환할 값 저장
	H[1] = H[n];          // 제일 끝에 저장된 값 제일 처음으로 이동
	n--;         // 힙 크기 감소

	downHeap(1);      // 하향이동 함수 호출
	return removekey;
}

void upHeap(int i) {
	while (i > 1) {      // 루트노드까지 올라가면 멈춤
		if (H[i] > H[i / 2]) {       // 부모노드보다 클때
			int ttt = H[i];
			H[i] = H[i / 2];     // swap
			H[i / 2] = ttt;
			i = i / 2;
		}
		else {         // 부모노드보다 작으면 멈춤
			break;
		}
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