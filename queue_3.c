/*


// <입력 케이스 a: 무작위 입력 시간 측정>



#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

void selection(int* ar, int n);      // 선택정렬
void insertion(int* ar, int n);      // 삽입정렬

int main() {
	int n;      // 입력받을 정수 개수
	int* A;    // 선택정렬
	int* B;    // 삽입정렬

	LARGE_INTEGER ticksPerSec;       // 시간측정을 위한 변수
	LARGE_INTEGER start, end, diff;

	scanf("%d", &n);      // 입력받을 정수 개수 입력
	A = (int*)malloc(sizeof(int) * n);
	B = (int*)malloc(sizeof(int) * n);

	srand(time(NULL));
	for (int i = 0; i < n; i++) {
		A[i] = rand();             // 난수 생성, 배열 저장
		B[i] = A[i];
	}

	QueryPerformanceFrequency(&ticksPerSec);           // 선택정렬 시간측정
	QueryPerformanceCounter(&start);
	selection(A, n);
	QueryPerformanceCounter(&end);

	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("%fms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);   // ms단위로 시간 출력

	QueryPerformanceFrequency(&ticksPerSec);          // 삽입정렬 시간측정
	QueryPerformanceCounter(&start);
	insertion(B, n);
	QueryPerformanceCounter(&end);

	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("%fms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);   // ms단위로 시간 출력

	free(A);
	free(B);
	return 0;
}

void selection(int* ar, int n) {
	int min_index;

	for (int i = 0; i < n - 1; i++) {       // 선택정렬로 정렬
		min_index = i;
		for (int j = i + 1; j < n; j++) {
			if (ar[min_index] > ar[j]) {       // 최솟값 찾기
				min_index = j;              // 바꿀 위치(최솟값 위치) 저장
			}
		}

		int t = ar[i];             // 최솟값 swap하기
		ar[i] = ar[min_index];
		ar[min_index] = t;
	}

}

void insertion(int* ar, int n) {
	int t;       // 삽입 변수

	for (int i = 1; i < n; i++) {      // 삽입정렬로 정렬
		t = ar[i];
		int j;
		for (j = i - 1; j >= 0, t < ar[j]; j--) {       // 삽입 위치 찾기
			ar[j + 1] = ar[j];      // 삽입위치까지 뒤로 한칸씩 미루기
		}
		ar[j + 1] = t;     // 정수 삽입
	}
}

*/









/*


// <입력 케이스 b: 정렬하여 시간 측정>



#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

void selection(int* ar, int n);      // 선택정렬
void insertion(int* ar, int n);      // 삽입정렬

int main() {
	int n;      // 입력받을 정수 개수
	int* A;    // 선택정렬
	int* B;    // 삽입정렬

	LARGE_INTEGER ticksPerSec;       // 시간측정을 위한 변수
	LARGE_INTEGER start, end, diff;

	scanf("%d", &n);      // 입력받을 정수 개수 입력
	A = (int*)malloc(sizeof(int) * n);
	B = (int*)malloc(sizeof(int) * n);

	srand(time(NULL));
	for (int i = 0; i < n; i++) {
		A[i] = rand();             // 난수 생성, 배열 저장
		B[i] = A[i];
	}
	selection(A, n);     // 정렬
	selection(B, n);     // 정렬

	QueryPerformanceFrequency(&ticksPerSec);           // 선택정렬 시간측정
	QueryPerformanceCounter(&start);
	selection(A, n);
	QueryPerformanceCounter(&end);

	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("%fms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);   // ms단위로 시간 출력

	QueryPerformanceFrequency(&ticksPerSec);          // 삽입정렬 시간측정
	QueryPerformanceCounter(&start);
	insertion(B, n);
	QueryPerformanceCounter(&end);

	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("%fms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);   // ms단위로 시간 출력

	free(A);
	free(B);
	return 0;
}

void selection(int* ar, int n) {
	int min_index;

	for (int i = 0; i < n - 1; i++) {       // 선택정렬로 정렬
		min_index = i;
		for (int j = i + 1; j < n; j++) {
			if (ar[min_index] > ar[j]) {       // 최솟값 찾기
				min_index = j;              // 바꿀 위치(최솟값 위치) 저장
			}
		}

		int t = ar[i];             // 최솟값 swap하기
		ar[i] = ar[min_index];
		ar[min_index] = t;
	}

}

void insertion(int* ar, int n) {
	int t;       // 삽입 변수

	for (int i = 1; i < n; i++) {      // 삽입정렬로 정렬
		t = ar[i];
		int j;
		for (j = i - 1; j >= 0, t < ar[j]; j--) {       // 삽입 위치 찾기
			ar[j + 1] = ar[j];      // 삽입위치까지 뒤로 한칸씩 미루기
		}
		ar[j + 1] = t;     // 정수 삽입
	}
}

*/














/*



// <입력 케이스 c: 역순으로 정렬하여 시간 측정>



#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

void reverse(int* ar, int n);     // 역순 정렬 함수
void selection(int* ar, int n);      // 선택정렬
void insertion(int* ar, int n);      // 삽입정렬

int main() {
	int n;      // 입력받을 정수 개수
	int* A;    // 선택정렬
	int* B;    // 삽입정렬

	LARGE_INTEGER ticksPerSec;       // 시간측정을 위한 변수
	LARGE_INTEGER start, end, diff;

	scanf("%d", &n);      // 입력받을 정수 개수 입력
	A = (int*)malloc(sizeof(int) * n);
	B = (int*)malloc(sizeof(int) * n);

	srand(time(NULL));
	for (int i = 0; i < n; i++) {
		A[i] = rand();             // 난수 생성, 배열 저장
		B[i] = A[i];
	}
	reverse(A, n);      // 역순 정렬
	reverse(B, n);      // 역순 정렬

	QueryPerformanceFrequency(&ticksPerSec);           // 선택정렬 시간측정
	QueryPerformanceCounter(&start);
	selection(A, n);
	QueryPerformanceCounter(&end);

	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("%fms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);   // ms단위로 시간 출력

	QueryPerformanceFrequency(&ticksPerSec);          // 삽입정렬 시간측정
	QueryPerformanceCounter(&start);
	insertion(B, n);
	QueryPerformanceCounter(&end);

	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("%fms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);   // ms단위로 시간 출력

	free(A);
	free(B);
	return 0;
}

void reverse(int* ar, int n) {
	int max_index;

	for (int i = 0; i < n - 1; i++) {        // 선택정렬로 역순으로 정렬
		max_index = i;
		for (int j = i + 1; j < n; j++) {
			if (ar[max_index] < ar[j]) {     // 최댓값 찾기
				max_index = j;         // 바꿀 위치 저장
			}
		}

		int t = ar[i];           // 최댓값 swap하기
		ar[i] = ar[max_index];
		ar[max_index] = t;
	}

}

void selection(int* ar, int n) {
	int min_index;

	for (int i = 0; i < n - 1; i++) {       // 선택정렬로 정렬
		min_index = i;
		for (int j = i + 1; j < n; j++) {
			if (ar[min_index] > ar[j]) {       // 최솟값 찾기
				min_index = j;              // 바꿀 위치(최솟값 위치) 저장
			}
		}

		int t = ar[i];             // 최솟값 swap하기
		ar[i] = ar[min_index];
		ar[min_index] = t;
	}

}

void insertion(int* ar, int n) {
	int t;       // 삽입 변수

	for (int i = 1; i < n; i++) {      // 삽입정렬로 정렬
		t = ar[i];
		int j;
		for (j = i - 1; j >= 0, t < ar[j]; j--) {       // 삽입 위치 찾기
			ar[j + 1] = ar[j];      // 삽입위치까지 뒤로 한칸씩 미루기
		}
		ar[j + 1] = t;     // 정수 삽입
	}
}

*/