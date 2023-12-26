//이진탐색트리 구현
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    struct node *parent;
    struct node *left;
    int key;
    struct node *right;
} node;

void initnode(node **head) {
    node *newnode = (node*)malloc(sizeof(node));
    newnode->parent = NULL;
    newnode->left = NULL;
    newnode->right = NULL;
    *head = newnode;
}

int isInternal(node *w) {
    return (w->left != NULL || w->right != NULL);
}

int isExternal(node *w) {
    return (w->left == NULL && w->right == NULL);
}

node *treeSearch(node *w, int k) {
    if (isExternal(w)) //최하단까지 하향경로 이동
        return w;
    if (k == w->key)
        return w;
    else if (k < w->key)
        return treeSearch(w->left, k);
    else
        return treeSearch(w->right, k);
}

void expandExternal(node *w) {
    node *l = (node*)malloc(sizeof(node));
    node *r = (node*)malloc(sizeof(node));
    l->parent = w;
    l->left = NULL;
    l->right = NULL;
    r->parent = w;
    r->left = NULL;
    r->right = NULL;
    w->left = l;
    w->right = r;
}

void insertItem (node *head, int k) {
    node *w = treeSearch(head, k);
    if (isInternal(w))
        return;
    w->key = k;
    expandExternal(w);
}

node *sibling(node *z) {
    return z->parent->left == z ? z->parent->right : z->parent->left;
}
//head 변경 후 호출 함수(removeElemnt)도 적용돼야함, 이중포인터
void reduceExternal(node **head, node *z) {
    node *w = z->parent;
    node *zs = sibling(z);
    if (w == *head) {
        *head = zs;
        zs->parent = NULL;
    }
    else {
        node *g = w->parent;
        zs->parent = g;
        if (w == g->left)
            g->left = zs;
        else
            g->right = zs;
    }
    free(z);
    free(w);
}

node *inOrderSucc(node *w) {
    node *y = w->right;
    while (isInternal(y->left))
        y = y->left;
    return y;
}
//head 변경 후 호출함수(main)도 적용돼야함, 이중포인터
int removeElement(node **head, int k) {
    node *w = treeSearch(*head, k); //*head 주의
    if (isExternal(w))
        return -1;
    int e = w->key;
    node *z = w->left;
    if (isInternal(z))
        z = w->right;
    if (isExternal(z))
        reduceExternal(head, z); //이중포인터 넘길때 head
    else {
        node *y = inOrderSucc(w);
        node *z = y->left;
        w->key = y->key;
        reduceExternal(head, z);
    }
    return e;
}

int findElement(node *head, int k) {
    node *w = treeSearch(head, k);
    if (isExternal(w))
        return -1;
    return w->key;
}

void printBST(node *w) {
    if (isExternal(w))
        return;
    printf(" %d", w->key);
    printBST(w->left);
    printBST(w->right);
}

int main()
{
    node *head = NULL;
    initnode(&head);

    char c;
    int k;
    do {
        scanf("%c", &c);
        if (c == 'i') {
            scanf("%d", &k);
            getchar();
            insertItem(head, k);
        }
        else if (c == 'd') {
            scanf("%d", &k);
            getchar();
            int e = removeElement(&head, k); //단일 포인터 head의 주소 넘김, 이중포인터 **head로 받아야 수정 및 적용 가능
            if (e == -1)
                printf("X\n");
            else
                printf("%d\n", e);
        }
        else if (c == 's') {
            scanf("%d", &k);
            getchar();
            int e = findElement(head, k);
            if (e == -1)
                printf("X\n");
            else
                printf("%d\n", e);
        }
        else if (c == 'p') {
            printBST(head);
            printf("\n");
        }
    } while (c != 'q');
}
