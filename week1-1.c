//자료구조 복습 1-1
#pragma warning(disable:4996)
#include <stdio.h>

typedef struct DL {
    struct DL* prev;
    int element;
    struct DL* next;
} DoubleListNode;

void init(DoubleListNode* H, DoubleListNode* T)
{
    H->next = T;
    T->prev = H;
    H = NULL;
    T = NULL;
}

void add(DoubleListNode* H, DoubleListNode* T, int r, int e, int cnt)
{
    if (r < 1 || r > cnt + 1) {
        printf("invalid position\n");
        cnt--;
        return;
    }

    DoubleListNode* p = H;
    for (int i = 1; i <= r; i++)
        p = p->next;

    DoubleListNode* q = (DoubleListNode*)malloc(sizeof(DoubleListNode));
    q->element = e;

    q->prev = p->prev;
    q->next = p;
    p->prev->next = q;
    p->prev = q;
}

void delete(DoubleListNode* H, DoubleListNode* T, DoubleListNode* p, int r, int
cnt)
{
    if (r < 1 || r > cnt) {
        printf("invalid position\n");
        return;
    }
    p = H;
    for (int i = 1; i <= r; i++)
        p = p->next;
    int e = p->element;
    p->prev->next = p->next;
    p->next->prev = p->prev;
    free(p);
}

void get(DoubleListNode* H, DoubleListNode* T, int r, int cnt)
{
    if (r < 1 || r > cnt) {
        printf("invalid position\n");
        return;
    }
    DoubleListNode* p = H;
    for (int i = 1; i <= r; i++)
        p = p->next;

    printf("%c\n", p->element);
}

void print(DoubleListNode* H, DoubleListNode* T)
{
    DoubleListNode *p = H;
    while (p->next != T) {
        p = p->next;
        printf("%c", p->element);
    }
    printf("\n");
}

int main()
{
    DoubleListNode list;
    DoubleListNode* H = (DoubleListNode*)malloc(sizeof(DoubleListNode));
    DoubleListNode* T = (DoubleListNode*)malloc(sizeof(DoubleListNode));
    H->prev = NULL;
    T->next = NULL;
    init(&list, &list);

    int n, cnt = 0;
    char tmp;
    scanf("%d%c", &n, &tmp);

    for (int i = 0; i < n; i++) {
        char c1, c2;
        int r;
        scanf("%c%c", &c1, &tmp);

        if (c1 == 'A') {
            scanf("%d %c%c", &r, &c2, &tmp);
            add(&list, &list, r, c2, cnt);
            if (r < 1 || r > cnt + 1)
                cnt--;
            cnt++;
        }
        else if (c1 == 'D') {
            scanf("%d%c", &r, &tmp);
            delete(&list, &list, &list, r, cnt);
            if (r < 1 || r > cnt)
                cnt++;
            cnt--;
        }
        else if (c1 == 'G') {
            scanf("%d%c", &r, &tmp);
            get(&list, &list, r, cnt);
        }
        else
            print(&list, &list);
    }
}
