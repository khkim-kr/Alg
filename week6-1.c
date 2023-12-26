//이진 탐색 - 재귀 버전
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

int rFE(int *A, int l, int r, int k) {
    if (l >= r) {
        if (k < A[l])
            return l - 1;
        else
            return l;
    }
    int mid = (l + r) / 2;
    if (k == A[mid])
        return mid;
    else if (k < A[mid])
        return rFE(A, l, mid - 1, k);
    else
        return rFE(A, mid + 1, r, k);
}

int main()
{
    int n, k;
    scanf("%d %d", &n, &k);

    int *A = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);

    printf(" %d\n", rFE(A, 0, n - 1, k));

    return 0;
}
