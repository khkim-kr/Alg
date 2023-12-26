//이진 탐색 - 비재귀 버전
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

int findElement(int *A, int l, int r, int k) {
    while (l < r) {
        int mid = (l + r) / 2;
        if (k == A[mid])
            return mid;
        else if (k < A[mid])
            r = mid - 1;
        else
            l = mid + 1;
    }
    if (k <= A[l])
        return l;
    else
        return l + 1;
}

int main()
{
    int n, k;
    scanf("%d %d", &n, &k);

    int *A = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);

    printf(" %d\n", findElement(A, 0, n - 1, k));

    return 0;
}
