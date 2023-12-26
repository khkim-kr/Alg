//삽입식 힙 생성
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

int H[100];
int n = 0;

void upHeap(int i) {
    if (i == 1)
        return;
    if (H[i] <= H[i / 2])
        return;
    int tmp = H[i];
    H[i] = H[i / 2];
    H[i / 2] = tmp;
    upHeap(i / 2);
}

void downHeap(int i) {
    if (n < 2 * i)
        return;
    int bigger = 2 * i;
    if ((n >= 2 * i + 1) && (H[(2 * i) + 1] >= H[bigger]))
        bigger = 2 * i + 1;
    if (H[i] <= H[bigger]) {
        int tmp = H[i];
        H[i] = H[bigger];
        H[bigger] = tmp;
    }
    downHeap(bigger);
}

void insertItem(int key) {
    n++;
    H[n] = key;
    upHeap(n);
    printf("0\n");
}

int removeMax() {
    int key = H[1];
    H[1] = H[n];
    n--;
    downHeap(1);
    return key;
}

void printHeap() {
    for (int i = 1; i <= n; i++)
        printf(" %d", H[i]);
    printf("\n");
}

int main()
{
    char ch;

    do {
        scanf("%c", &ch);
        switch (ch) {
            case 'i' : {
                int key;
                scanf("%d", &key);
                insertItem(key);
                break;
            }
            case 'd' : {
                printf("%d\n", removeMax());
                break;
            }
            case 'p' : {
                printHeap();
                break;
            }
        }
    } while (ch != 'q');
    
    return 0;
}
