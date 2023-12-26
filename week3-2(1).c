//상향식 힙 생성 (재귀 버전 - 좌측하단 start -> 우상향)
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

void rBuildHeap(int i) {
    if (i > n)
        return;
    rBuildHeap(2 * i); //좌하단에서 start
    rBuildHeap(2 * i + 1); //우측 전진 후 최종적으로 root로 복귀귀
    downHeap(i);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &H[i]);

    rBuildHeap(1);
    printHeap();
    return 0;
}
