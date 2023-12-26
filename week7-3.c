//AVL 트리 삭제
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct node { //구조체 정의 - 이진탐색트리에 높이 정보(height)만 추가
    struct node *parent;
    struct node *left;
    int key;
    int height;
    struct node *right;
} node;

void initnode(node **head) { //이진트리 초기화 (이중포인터 사용하여 함수 원형에서 tree 수정 시 호출한 함수에서도 수정되도록)
    node *newnode = (node*)malloc(sizeof(node));
    newnode->parent = NULL;
    newnode->left = NULL;
    newnode->right = NULL;
    *head = newnode; //헤더 노드를 해당 빈 노드에 연결 (초기화)
}

int isInternal(node *w) { //w가 내부노드인가를 반환
    return (w->left != NULL || w->right != NULL);
}

int isExternal(node *w) { //w가 외부노드인가를 반환
    return (w->left == NULL && w->right == NULL);
}

node *treeSearch(node *w, int k) { //이진트리 내 key값으로 k를 갖는 노드 있는지 탐색
    if (isExternal(w)) //최하단까지 하향경로 이동
        return w;
    if (k == w->key) //찾으면 해당 노드 반환
        return w;
    else if (k < w->key) //이진탐색트리 성질 (key(u) < key(v) <= key(w))이용, 왼쪽 자식, 오른쪽 자식으로 경우에 따라 이동
        return treeSearch(w->left, k);
    else
        return treeSearch(w->right, k);
}

void expandExternal(node *w) { //외부노드에 key값 삽입 후 내부노드로 전환 및 외부노드 자식 갖도록 설정
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

int max(int lh, int rh) { //w의 왼쪽, 오른쪽 자식의 height 중 높은 것 반환
    return lh >= rh ? lh : rh;
}

int updateHeight(node *w) { //w의 height 멤버 갱신 및 갱신 여부 반환
    int h = max(w->left->height, w->right->height) + 1;
    if (h != w->height) {
        w->height = h;
        return 1;
    }
    else
        return 0;
}

int isBalanced(node *w) { //왼쪽, 오른쪽 자식의 height 차이가 2 미만인지 여부 (2 미만 : 높이 균형 O - 1, 2 이상 : 높이 균형 X - 0)
    int diff = w->left->height - w->right->height;
    if (diff < 0)
        diff *= -1;
    return diff < 2 ? 1 : 0;
}

node *restructure(node *x, node *y, node *z, node **head) { //개조
    node *a, *b, *c, *T0, *T1, *T2, *T3;
    if (z->key < y->key && y->key < x->key) { //single rotation의 case 1
        a = z, b = y, c = x;
        T0 = a->left, T1 = b->left, T2 = c->left, T3 = c->right;
    }
    else if (x->key < y->key && y->key < z->key) { //single rotation의 case 2
        a = x, b = y, c = z;
        T0 = a->left, T1 = a->right, T2 = b->right, T3 = c->right;
    }
    else if (z->key < x->key && x->key < y->key) { //double rotation의 case 1
        a = z, b = x, c = y;
        T0 = a->left, T1 = b->left, T2 = b->right, T3 = c->right;
    }
    else { //double rotation의 case 2
        a = y, b = x, c = z;
        T0 = a->left, T1 = b->left, T2 = b->right, T3 = c->right;
    }

    if (z == *head) { //isRoot(z) : rotation후 b를 root로
        *head = b;
        b->parent = NULL;
    }
    else if (z->parent->left == z) { //z가 왼쪽 자식이면 b를 왼쪽 자식으로
        z->parent->left = b;
        b->parent = z->parent;
    }
    else { //z가 오른쪽 자식이면 b를 오른쪽 자식으로
        z->parent->right = b;
        b->parent = z->parent;
    }

    a->left = T0, a->right = T1; //부트리 T0, T1과 a 연결
    T0->parent = a, T1->parent = a;
    updateHeight(a); //a->height 갱신

    c->left = T2, c->right = T3; //부트리 T2, T3와 c 연결
    T2->parent = c, T3->parent = c;
    updateHeight(c); //c->height 갱신

    b->left = a, b->right = c; //a, c와 b 연결
    a->parent = b, c->parent = b;
    updateHeight(b); //b->height 갱신
    return b; //rotation(restructure) 후의 node b를 반환
}

void searchAndFixAfterInsertion(node *w, node **head) { //삽입 후 AVL 트리의 높이균형 속성 맞는지 확인
    w->left->height = 0;
    w->right->height = 0;
    w->height = 1;
    if (w == *head)
        return;
    node *z = w->parent;
    while (updateHeight(z) & isBalanced(z)) { //높이 갱신 & 균형 유지중일 경우 부모노드로 이동
        if (z == *head)
            return;
        z = z->parent;
    }
    if (isBalanced(z)) //높이 균형 속성 만족 - return
        return;
    node *y; //y : z의 자식 중 height가 더 큰 자식 노드
    if (z->left->height > z->right->height)
        y = z->left;
    else
        y = z->right;
    node *x; //x : y의 자식 중 height가 더 큰 자식 노드
    if (y->left->height > y->right->height)
        x = y->left;
    else
        x = y->right;
    node *b = restructure(x, y, z, head); //높이 균형 속성 만족하도록 개조
}

void insertItem (node **head, int k) { //key값 삽입
    node *w = treeSearch(*head, k); //이진트리 탐색
    if (isInternal(w)) //w가 내부노드일 경우 (이미 k가 삽입된 적이 있음) return
        return;
    w->key = k; //key값 삽입
    expandExternal(w); //내부노드 전환 및 외부노드의 자식 갖도록 확장
    searchAndFixAfterInsertion(w, head); //높이 균형 속성 만족하는지, 만족 X - 개조
}

node *sibling(node *z) { //z의 반대편 자식
    return z->parent->left == z ? z->parent->right : z->parent->left;
}
//head 변경 후 호출 함수(removeElemnt)도 적용돼야함, 이중포인터
node *reduceExternal(node **head, node *z) { //삭제 후 외부노드 지우기
    node *w = z->parent;
    node *zs = sibling(z);
    if (w == *head) { //isRoot(w) : zs를 root로
        *head = zs;
        zs->parent = NULL;
    }
    else { //그 외
        node *g = w->parent; //g와 zs연결 (왼쪽, 오른쪽 자식 판별 후 연결)
        zs->parent = g;
        if (w == g->left)
            g->left = zs;
        else
            g->right = zs;
    }
    free(z); //동적할당 메모리 해제
    free(w);
    return zs; //zs반환
}

node *inOrderSucc(node *w) { //중위순회 후계자 반환
    node *y = w->right; //오른쪽 자식으로 한 번 이동
    while (isInternal(y->left)) //내부노드인 동안 왼쪽 자식으로 이동
        y = y->left;
    return y; //중위순회 후계자 y 반환
}

//재귀 함수 - 삭제 후 개조한 이진트리가, 그 부모 노드에 대해 높이 균형 속성 만족하지 못할 수 있으므로
void searchAndFixAfterRemoval(node *z, node **head) { //삭제 후 높이 균형 속성 만족 여부에 따라 개조
    while (updateHeight(z) && isBalanced(z)) { //height 갱신 및 높이 균형 속성 만족인 동안 부모노드로 이동
        if (z == *head)
            return;
        z = z->parent;
    }
    if (isBalanced(z)) //높이 균형속성 만족 시 return
        return;
    node *y; //y : z의 자식 중 height가 더 큰 자식 노드
    if (z->left->height > z->right->height)
        y = z->left;
    else
        y = z->right;
    node *x; //x : y의 자식 중 height가 더 큰 자식 노드
    if (y->left->height > y->right->height)
        x = y->left;
    else if (y->left->height < y->right->height)
        x = y->right;
    else { //자식 둘의 높이가 동일하면 둘 중 y와 같은 쪽의 자식을 x로
        if (z->left == y)
            x = y->left;
        else
            x = y->right;
    }
    node *b = restructure(x, y, z, head); //개조 후 b 갱신
    if (b == *head)
        return;
    searchAndFixAfterRemoval(b->parent, head); //b의 부모노드에 대해 높이 균형 속성 만족하는 지 재귀적으로 실행
}

//head 변경 후 호출함수(main)도 적용돼야함, 이중포인터
int removeElement(node **head, int k) { //key값 삭제
    node *w = treeSearch(*head, k);
    if (isExternal(w)) //찾는 key값 없을 경우 -1 반환
        return -1;
    int e = w->key; //key값 저장
    node *z = w->left; //왼쪽 자식이 외부노드라면 z는 왼쪽 자식, 내부노드라면 z는 오른쪽 자식
    if (isInternal(z))
        z = w->right;
    node *zs;
    if (isExternal(z))
        zs = reduceExternal(head, z); //z가 외부노드 : (w,z) node 삭제 및 이진트리 갱신
    else {
        node *y = inOrderSucc(w); //중위 순회 후계자 찾기
        node *z = y->left; //z는 중위 순회 후계자 y의 leftchild
        w->key = y->key; //key값 옮기기
        zs = reduceExternal(head, z); //(w, z) node 삭제 및 이진트리 갱신
    }
    searchAndFixAfterRemoval(zs->parent, head); //삭제 후 높이 균형 속성 만족하도록 개조
    return e; //삭제 한 key값 반환
}

int findElement(node *head, int k) { //탐색
    node *w = treeSearch(head, k);
    if (isExternal(w))
        return -1;
    return w->key; //찾는 key값 k가 있으면 반환, 없으면 -1 반환
}

void printBST(node *w) { //전위순회로 인쇄
    if (isExternal(w))
        return;
    printf(" %d", w->key);
    printBST(w->left);
    printBST(w->right);
}

void freeAll(node *w) { //동적 메모리 해제를 위한 함수 - 후위순회 방법으로 메모리 전체 해제
    if (isExternal(w))
        return;
    freeAll(w->left);
    freeAll(w->right);
    free(w);
}

int main()
{
    node *head = NULL; //헤더노드 선언 및 NULL로 초기화
    initnode(&head); //이진트리 : 빈 연결리스트로 초기화

    char c;
    int k;
    do {
        scanf("%c", &c);
        if (c == 'i') { //key값 입력받고 삽입 실행
            scanf("%d", &k);
            getchar();
            insertItem(&head, k);
        }
        else if (c == 'd') { //key값 입력받고 삭제 실행
            scanf("%d", &k);
            getchar();
            int e = removeElement(&head, k); //단일 포인터 head의 주소 넘김, 이중포인터 **head로 받아야 수정 및 적용 가능
            if (e == -1) //입력받은 key값이 이진트리에 없는 경우(-1), X 출력
                printf("X\n");
            else
                printf("%d\n", e);
        }
        else if (c == 's') { //key값 입력받고 탐색 실행
            scanf("%d", &k);
            getchar();
            int e = findElement(head, k);
            if (e == -1) //이진트리에 key값 없는 경우(-1), X 출력
                printf("X\n");
            else
                printf("%d\n", e);
        }
        else if (c == 'p') { //전위순회로 이진트리 출력
            printBST(head);
            printf("\n");
        }
    } while (c != 'q'); //'q'입력 시 종료

    freeAll(head); //동적할당 메모리 해제 (후위순회 방식으로 전체 순회하며 free)
    
    return 0;
}
