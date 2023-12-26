//자료구조 복습 1-2
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode {
    struct TreeNode *left;
    int data;
    struct TreeNode *right;
} TreeNode;

void makeNode(TreeNode *root, int x, int y, int z)
{
    TreeNode *v = root;
    TreeNode *l = (TreeNode*)malloc(sizeof(TreeNode));
    TreeNode *r = (TreeNode*)malloc(sizeof(TreeNode));
    l->data = y;
    l->left = NULL;
    l->right = NULL;
    r->data = z;
    r->left = NULL;
    r->right = NULL;

    if (v->data == x) {
        if (y != 0)
            v->left = l;
        else {
            free(l);
            v->left = NULL;
        }
        if (z != 0)
            v->right = r;
        else {
            free(r);
            v->right = NULL;
        }
        return;
    }
    else {
        free(l);
        free(r);
    }

    if (v->left != NULL)
        makeNode(v->left, x, y, z);
    if (v->right != NULL)
        makeNode(v->right, x, y, z);
}

void searchTree(TreeNode *v, char search[100], int n)
{
    printf(" %d", v->data);
    for (int i = 0; i < n; i++) {
        if (search[i] == 'L')
            v = v->left;
        else if (search[i] == 'R')
            v = v->right;
        else
            return;
        printf(" %d", v->data);
    }
    printf("\n");
}

int main()
{
    int n;
    scanf("%d", &n);

    TreeNode *treenode = (TreeNode*)malloc(sizeof(TreeNode));
    TreeNode *root = treenode;

    int x, y, z;

    for (int i = 0; i < n; i++) {
        scanf("%d%d%d", &x, &y, &z);

        if (i == 0)
            treenode->data = x;
        makeNode(root, x, y, z);
    }

    int s;
    scanf("%d", &s);
    getchar();

    for (int i = 0; i < s; i++) {
        char search[100];
        scanf("%s", search);
        searchTree(root, search, strlen(search));
    }
}
