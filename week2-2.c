//우선순위 큐 - 제자리 삽입정렬
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

void inPlaceInsertionSort(int *p, int n) {
    int *x, *y;
    for (x = p + 1; x < p + n; x++) {
        int save = *x;
        y = x - 1;
        while ((y >= p) & (save < *y)) {
            *(y + 1) = *y;
            y--;
        }
        *(y + 1) = save;
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    
    int *ar = (int*)malloc(sizeof(int) * n);
    int *p;

    for (p = ar; p < ar + n; p++)
        scanf("%d", p);

    inPlaceInsertionSort(ar, n);

    for (p = ar; p < ar + n; p++)
        printf("% d", *p);
    printf("\n");
    
    return 0;
}
