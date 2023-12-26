//해시테이블 - 분리연쇄법
//분리연쇄법 - 해시테이블 충돌처리 case 1
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    struct node *next;
} node;

typedef struct hashtable {
    node **bucket;
} hashtable;

void inithash(hashtable *A, int M) {
    A->bucket = (node**)malloc(sizeof(node*) * M);
    for (int i = 0; i < M; i++)
        A->bucket[i] = NULL;
}

int hashfunc(int k, int M) {
    return k % M;
}

void insertItem(hashtable *A, int k, int M) {
    int v = hashfunc(k, M); //삽입할 배열의 index
    node *newnode = (node*)malloc(sizeof(node));
    newnode->key = k;
    newnode->next = NULL;
    if (A->bucket[v] == NULL)
        A->bucket[v] = newnode;
    else {
        newnode->next = A->bucket[v];
        A->bucket[v] = newnode; //bucket list 맨 앞에 삽입
    }
}

int findElement(hashtable *A, int k, int M) {
    int v = hashfunc(k, M);
    node *current = A->bucket[v];
    int r = 1;
    while (current != NULL) {
        if (current->key == k)
            return r;
        current = current->next;
        r++;
    }
    return 0; //NoSuchKey
}

int removeElement(hashtable *A, int k, int M) {
    int v = hashfunc(k, M);
    node *current = A->bucket[v];
    node *prev = NULL;
    int r = 1;
    while (current != NULL) {
        if (current->key == k) {
            if (prev == NULL)
                A->bucket[v] = current->next;
            else
                prev->next = current->next;
            free(current);
            return r;
        }
        prev = current;
        current = current->next;
        r++;
    }
    return 0;
}

void printHash(hashtable *A, int M) {
    for (int i = 0; i < M; i++) {
        node *current = A->bucket[i];
        while (current != NULL) {
            printf(" %d", current->key);
            current = current->next;
        }
    }
    printf("\n");
}

int main()
{
    int M;
    scanf("%d", &M);
    getchar();

    hashtable *A = (hashtable*)malloc(sizeof(hashtable));
    inithash(A, M);

    char c;
    int x;
    do {
        scanf("%c", &c);
        if (c == 'i') {
            scanf("%d", &x);
            getchar();
            insertItem(A, x, M);
        }
        else if (c == 's') {
            scanf("%d", &x);
            getchar();
            printf("%d\n", findElement(A, x, M));
        }
        else if (c == 'd') {
            scanf("%d", &x);
            getchar();
            printf("%d\n", removeElement(A, x, M));
        }
        else if (c == 'p') {
            printHash(A, M);
        }
    } while (c != 'e');
    
    return 0;
}
