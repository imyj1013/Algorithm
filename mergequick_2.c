#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void inPlaceQuickSort(int* ar, int l, int r);     // 퀵정렬 함수
int findpivot(int* ar, int l, int r);       // pivot 찾기 함수
int* inPlacePartition(int* ar, int l, int r, int piv);      // pivot 이용한 정렬함수

int main() {
    int n;
    scanf("%d", &n);      // 입력 받을 정수 갯수 입력

    int* ar = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {      // n개의 정수 입력받아  배열에 저장
        scanf("%d", &ar[i]);
    }

    inPlaceQuickSort(ar, 0, n - 1);  // 퀵정렬함수 호출

    for (int i = 0; i < n; i++) {
        printf(" %d", ar[i]);    // 정렬한 배열 출력
    }
    return 0;
}

int* inPlacePartition(int* ar, int l, int r, int piv) {
    int i = l, j = r-1, t, pivot = ar[piv];
    int* result = (int*)malloc(2 * sizeof(int));

    t = ar[piv];
    ar[piv] = ar[r];
    ar[r] = t;

    while (i <= j) {
        while (ar[i] < pivot && i <= j) {
            i++;      // i가 j 이하이고 ar[i]이 pivot보다 작을 때까지 i 증가
        }
        while (ar[j] >= pivot && i <= j) {
            j--;      // i가 j 이하이고 ar[i]이 pivot 이상일 때까지 j 감소
        }

        if (i < j) {
            t = ar[i];        // ar[i], ar[j] 스왑
            ar[i] = ar[j];
            ar[j] = t;
        }
    }
    result[0] = i;
    j = r - 1;

    while (i <= j) {
        while (ar[i] == pivot && i <= j) {
            i++;      // i가 j 이하이고 ar[i]이 pivot보다 작을 때까지 i 증가
        }
        while (ar[j] > pivot && i <= j) {
            j--;     // i가 j 이하이고 ar[i]이 pivot 이상일 때까지 j 감소
        }

        if (i < j) {
            t = ar[i];        // ar[i], ar[j] 스왑
            ar[i] = ar[j];
            ar[j] = t;
        }
    }

    result[1] = i;

    t = ar[i];      // ar[i], ar[r] 스왑
    ar[i] = ar[r];
    ar[r] = t;

    return result;      // result 반환


}

int findpivot(int* ar, int l, int r) {
    int piv[3];         // 3개의 난수 저장할 배열
    srand(time(NULL));
    piv[0] = rand() % (r - l + 1) + l;
    piv[1] = rand() % (r - l + 1) + l;       // 3개의 난수 저장
    piv[2] = rand() % (r - l + 1) + l;

    for (int i = 0; i < 2; i++) {          // 난수 3개 정렬
        for (int j = i + 1; j < 3; j++) {
            if (piv[i] > piv[j]) {
                int t = piv[i];
                piv[i] = piv[j];
                piv[j] = t;
            }
        }
    }
    return piv[1];        // 난수 3개 중 중앙값 반환
}

void inPlaceQuickSort(int* ar, int l, int r) {
    if (l >= r) {
        return;
    }

    int piv = findpivot(ar, l, r);     // pivot 찾기 함수 호출

    int* x = inPlacePartition(ar, l, r, piv);    // pivot 이용한 정렬 함수 호출
    inPlaceQuickSort(ar, l, x[0]-1);      // 앞부분 배열 정렬하기 위해 퀵정렬 함수 호출
    inPlaceQuickSort(ar, x[1] + 1, r);      // 뒷부분 배열 정렬하기 위해 퀵정렬 함수 호출
}