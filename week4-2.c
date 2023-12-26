//힙 정렬 - 중복 키
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

int H[100];
int n = 0;

void upHeap(int w) {
    if (w == 1)
        return;
    if (H[w] <= H[w / 2])
        return;
    int tmp = H[w];
    H[w] = H[w / 2];
    H[w / 2] = tmp;
    upHeap(w / 2);
}

void insertItem(int key) {
    n++;
    H[n] = key;
    upHeap(n);
}

void downHeap(int w, int last) { //기존 downHeap의 n = last
    if (last < w * 2) //n < w * 2 와 같은 의미
        return;
    int bigger = w * 2;
    if (last >= w * 2 + 1 && H[bigger] < H[w * 2 + 1])
        bigger = w * 2 + 1;
    if (H[w] >= H[bigger])
        return;
    int tmp = H[w];
    H[w] = H[bigger];
    H[bigger] = tmp;
    downHeap(bigger, last);
}

void inplaceHeapSort() {
    for (int i = n; i > 1; i--) {
        int tmp = H[1];
        H[1] = H[i];
        H[i] = tmp;
        downHeap(1, i - 1); //기존 downHeap에서 last만 추가 (Heap의 크기를 n--로 건드릴 경우 printHeap 정상 수행 불가)
    }
}

void printArray() {
    for (int i = 1; i <= n; i++)
        printf(" %d", H[i]);
    printf("\n");
}

int main()
{
    int N;
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) { //삽입식 힙 생성 (phase 1)
        int k;
        scanf("%d", &k);
        insertItem(k);
    }
    inplaceHeapSort();
    printArray();
    
    
}
