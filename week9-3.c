//해시테이블 - 이중해싱
//개방주소법 - 이중해싱
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

void inithash(int *A, int M) {
    for (int i = 0; i < M; i++)
        A[i] = 0;
}

int hashfunc1(int k, int M) {
    return k % M;
}

int hashfunc2(int k, int q) {
    return q - (k % q);
}

int getNextBucket(int v, int i, int M) {
    return (v + i) % M;
}

int insertItem(int *A, int k, int M, int q) {
    int v = hashfunc1(k, M);
    while (A[v] != 0) {
        printf("C");
        int i = hashfunc2(k, q);
        v = getNextBucket(v, i, M);
    }
    A[v] = k;
    return v;
}
int findElement(int *A, int k, int M, int q) {
    int v = hashfunc1(k, M);
    while (A[v] != 0) {
        if (A[v] == k)
            return v;
        int i = hashfunc2(k, q);
        v = getNextBucket(v, i, M);
    }
    return -1;
}

void printHash(int *A, int M) {
    for (int i = 0; i < M; i++)
        printf(" %d", A[i]);
    printf("\n");
}

int main()
{
    int M, n, q;
    scanf("%d %d %d", &M, &n, &q);
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
            printf("%d\n", insertItem(A, x, M, q));
        }
        else if (c == 's') {
            scanf("%d", &x);
            getchar();
            int index = findElement(A, x, M, q);
            if (index == -1)
                printf("%d\n", index);
            else
                printf("%d %d\n", index, A[index]);
        }
        else if (c == 'p' || c == 'e') {
            getchar();
            printHash(A, M);
        }
    } while (c != 'e');
    free(A);

    return 0;
}
