//힙 정렬 - 유일 키
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

int H[100];
int n = 0;
int m;

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

void insertItem(int k) {
    n++;
    H[n] = k;
    upHeap(n);
}

void BuildHeap() {
    for (int i = 1; i <= m; i++)
        insertItem(H[i]);
}

void downHeap(int w) {
    if (n < w * 2)
        return;
    int bigger = w * 2;
    if (n >= w * 2 + 1 && H[bigger] < H[bigger + 1])
        bigger = w * 2 + 1;
    if (H[w] >= H[bigger])
        return;
    int tmp = H[w];
    H[w] = H[bigger];
    H[bigger] = tmp;
    downHeap(bigger);
}

void inPlaceHeapSort() {
    BuildHeap(); //phase 1 삽입식 힙 생성 (maxheap생성)
    for (int i = m; i > 1; i--) { //phase 2 정렬 과정 (maxheap root노드가 항상 최대, H[1] <-> H[i])
        int tmp = H[1];
        H[1] = H[i];
        H[i] = tmp;
        n--;
        downHeap(1);
    }
}

void printArray() {
    for (int i = 1; i <= m; i++)
        printf(" %d", H[i]);
    printf("\n");
}

int main()
{
    scanf("%d", &m);
    
    for (int i = 1; i <= m; i++)
        scanf("%d", &H[i]);
    inPlaceHeapSort();
    printArray();
    
    return 0;
}
