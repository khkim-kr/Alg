//상향식 힙 생성 (비재귀 버전 - 우측 중간 start->후진 탐색)
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

int H[100];
int n = 0;

void downHeap(int i) {
    if (n < 2 * i)
        return;
    int bigger = 2 * i;
    if ((n >= bigger + 1) && (H[bigger] <= H[bigger + 1]))
        bigger++;
    if (H[i] < H[bigger]) {
        int tmp = H[i];
        H[i] = H[bigger];
        H[bigger] = tmp;
    }
    downHeap(bigger);
}

void printHeap() {
    for (int i = 1; i <= n; i++)
        printf(" %d", H[i]);
    printf("\n");
}

void BuildHeap() {
    for (int i = n / 2; i > 0; i--) //last의 부모노드 start-> i = n/2
        downHeap(i);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &H[i]);

    BuildHeap();
    printHeap();
    return 0;
}
