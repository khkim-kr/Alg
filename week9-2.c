//해시테이블 - 선형조사법
//개방주소법 - 선형조사법
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

void inithash(int *A, int M) {
    for (int i = 0; i < M; i++)
        A[i] = 0;
}

int hashfunc(int k, int M) {
    return k % M;
}

int getNextBucket(int v, int i, int M) {
    return (v + i) % M;
}

int insertItem(int *A, int k, int M) {
    int v = hashfunc(k, M);
    while (A[v] != 0) {
        printf("C");
        v = getNextBucket(v, 1, M);
    }
    A[v] = k;
    return v;
}
int findElement(int *A, int k, int M) {
    int v = hashfunc(k, M);
    while (A[v] != 0) {
        if (A[v] == k)
            return v;
        v = getNextBucket(v, 1, M);
    }
    return -1;
}

int main()
{
    int M, n;
    scanf("%d %d", &M, &n);
    getchar();

    int *A = (int*)malloc(sizeof(int) * M);
    inithash(A, M);

    char c;
    int x;
    do {
        scanf("%c", &c);
        if (c == 'i') {
            scanf("%d", &x);
            getchar();
            printf("%d\n", insertItem(A, x, M));
        }
        else if (c == 's') {
            scanf("%d", &x);
            getchar();
            int index = findElement(A, x, M);
            if (index == -1)
                printf("%d\n", index);
            else
                printf("%d %d\n", index, A[index]);
        }
    } while (c != 'e');

    return 0;
}
