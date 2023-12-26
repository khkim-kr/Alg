//우선순위 큐 1번
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

void inPlaceSelectionSort(int *p, int n) {
    int *x, *y;
    for (x = p; x > p - n + 1; x--) {
        int *maxLoc = x;
        for (y = x - 1; y > p - n; y--)
            if (*y > *maxLoc)
                maxLoc = y;
        int tmp = *x;
        *x = *maxLoc;
        *maxLoc = tmp;
    }
}

int main()
{
    int N;
    scanf("%d", &N);

    int *arr = (int*)malloc(N * sizeof(int));
    int *p;
    
    for (p = arr; p < arr + N; p++)
        scanf("%d", p);

    inPlaceSelectionSort(arr + N - 1, N);

    for (p = arr; p < arr + N; p++)
        printf(" %d", *p);
    printf("\n");
    
    return 0;
}
