//합병 정렬
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

int n = 0;

typedef struct Listnode {
    int elem;
    struct Listnode *next;
} Listnode;

Listnode *makenode(int e) { //새로운 노드를 생성하고 그 주소를 반환
    Listnode *node = (Listnode*)malloc(sizeof(Listnode)); //node포인터:동적할당 메모리의 주소 가리킴
    node->elem = e;
    node->next = NULL;
    return node; //생성 node의 주소 반환
}

//그림으로 그려보면 **list가 *list를 가리키고, *list는 초기상태라면 NULL이 저장되어 있음.
//따라서, **list는 연결리스트 자를 가리킨다고 볼 수 있음.
void addLast(Listnode **list, int e) { // *list(포인터 list)의 주소를 가리키는 포인터(**list)
    Listnode *newnode = makenode(e);
    if (*list == NULL) //초기상태 : list포인터가 가리키는게 없으면
        *list = newnode; //list포인터가 newnode를 가리키게 만들어라
    else { //(*list->next != NULL)꼴이 error인 이유 - *list는 단일 포인터일 뿐(next 자체가 없음)
        Listnode *current = *list; //current포인터와 list포인터가 가리키는 노드가 동일
        while (current->next != NULL) //빈 리스트라면, 둘다 NULL 가리키는 중
            current = current->next;
        current->next = newnode; //마지막 노드 뒤에 추가
    }
}

void partition(Listnode **L, Listnode **L1, Listnode **L2, int k) {
    *L1 = *L;
    Listnode *current = *L;
    for (int i = 0; i < k - 1; i++)
        current = current->next;
    *L2 = current->next;
    current->next = NULL;
    *L = NULL; //current 구하면서 이동한 L을 다시 NULL로 초기화
}

void merge(Listnode **L, Listnode **L1, Listnode **L2) {
    while ((*L1 != NULL) && (*L2 != NULL)) {
        if ((*L1)->elem <= (*L2)->elem) {
            addLast(L, (*L1)->elem);
            *L1 = (*L1)->next;
        }
        else {
            addLast(L, (*L2)->elem);
            *L2 = (*L2)->next;
        }
    }
    while (*L1 != NULL) {
        addLast(L, (*L1)->elem);
        *L1 = (*L1)->next;
        }
    while (*L2 != NULL) {
        addLast(L, (*L2)->elem);
        *L2 = (*L2)->next;
    }
}

void mergeSort(Listnode **L, int k) {
    if (k > 1) {
        Listnode *L1 = NULL;
        Listnode *L2 = NULL;
        partition(L, &L1, &L2, k / 2);
        mergeSort(&L1, k / 2);
        mergeSort(&L2, k - (k / 2));
        merge(L, &L1, &L2);
    }
}

void printmergeSort(Listnode **L, int n) {
    Listnode *current = *L;
    for (int i = 0; i < n; i++) {
        printf(" %d", current->elem);
        current = current->next;
    }
    printf("\n");
}

int main()
{
    Listnode *list = NULL; //연결리스트 시작점을 가리키는 포인터 list선언 (NULL로 초기화)
    //list포인터(*list)는 포인터 자료형이지, {elem, next}꼴의 Listnode 자료형이 아니다!!!
    
    scanf("%d", &n);

    for (int i = 0; i < n; i++) { //저장
        int element;
        scanf("%d", &element);
        addLast(&list, element); //포인터 list의 주소 전달
    }
    mergeSort(&list, n);
    printmergeSort(&list, n);

    return 0;
}
