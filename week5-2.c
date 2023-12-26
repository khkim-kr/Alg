//퀵 정렬
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int findPivot(int *L, int l, int r) {
    srand(time(NULL));
    return rand() % (r - l + 1) + l;
}

int inPlacePartition(int *L, int l, int r, int k) {
    int p = L[k]; //pivot 저장 (p <- A[k])
    
    int tmp = L[k]; //pivot 맨 뒤로 이동 (A[k] <-> A[r])
    L[k] = L[r];
    L[r] = tmp;
    
    int i = l; //i, j 설정 (i <- l, j <- r - 1)
    int j = r - 1;

    while (i <= j) { //LT, GT (EQ) 설정 과정
        while ((i <= j) && (L[i] <= p)) //pivot보다 작은 수 지나침 (LT)
            i++;
        while ((j >= i) && (L[j] >= p)) //pivot보다 큰 수 지나침 (GT)
            j--;
        if (i < j) { //작은 수, 큰 수 조건 만족 X인 두 수 swap
            tmp = L[i];
            L[i] = L[j];
            L[j] = tmp;
        }
    }
    tmp = L[i]; //적절위치에 pivot 재이동
    L[i] = L[r];
    L[r] = tmp;

    return i; //pivot의 위치 반환
}

void inPlaceQuickSort(int *L, int l, int r) {
    if (l < r) {
        int k = findPivot(L, l, r); //pivot 위치 선정
        int a = inPlacePartition(L, l, r, k); //분할 후 pivot 위치 받아서 a에 저장
        inPlaceQuickSort(L, l, a - 1); //(l ~ a - 1) = LT
        inPlaceQuickSort(L, a + 1, r); //(a + 1 ~ r) = GT
    }
}

void printinPlaceQuickSort(int *L, int n) {
    for (int i = 0; i < n; i++)
        printf(" %d", L[i]);
    printf("\n");
}

int main()
{
    int n;
    scanf("%d", &n);

    int *a = (int*)malloc(sizeof(int) * n); //크기 n인 배열 동적할당

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    inPlaceQuickSort(a, 0, n - 1);
    printinPlaceQuickSort(a, n);

    return 0;
}
