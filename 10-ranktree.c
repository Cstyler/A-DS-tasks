
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SSIZE 7
#define VSIZE 10
#define ELEM struct elem

ELEM {
        int k, count;
        char *v;
        ELEM *parent, *left, *right;
};

void insert(ELEM *t, int k, ELEM *y)
{
        y->parent = y->left = y->right = NULL;
        ELEM* x = t;
        for(;;) {
                if(k < x->k) {
                        if(x->left == NULL) {
                                ++x->count;
                                x->left = y, y->parent = x;
                                break;
                        }
                        ++x->count;
                        x = x->left;
                } else {
                        if(x->right == NULL) {
                                ++x->count;
                                x->right = y, y->parent = x;
                                break;
                        }
                        ++x->count;
                        x = x->right;
                }
        }
}

ELEM* replaceNode(ELEM *t, ELEM *x, ELEM *y)
{
        ELEM* p;
        if(x == t) {
                t = y;
                if(y != NULL) y->parent = NULL;
        } else {
                p = x->parent;
                if(y != NULL)
                        y->parent = p;
                if(p->left == x)
                        p->left = y;
                else
                        p->right = y;
        }
        return t;
}

ELEM* minimum(ELEM* x)
{
        while(x->left != NULL) {
                x->count--;
                x = x->left;
        }
        return x;
}

ELEM* descend(ELEM* x, int k)
{
        while(x != NULL && x->k != k) {
                --x->count;
                x = k < x->k ? x->left : x->right;
        }
        return x;
}

ELEM* delete(ELEM *t, int k)
{
        ELEM *x = descend(t, k);
        if(x->left == NULL && x->right == NULL) {
                t = replaceNode(t, x, NULL);
        } else if(x->left == NULL) {
                t = replaceNode(t, x, x->right);
        } else if(x->right == NULL) {
                t = replaceNode(t, x, x->left);
        } else {
                ELEM *y = minimum(x->right);
                t = replaceNode(t, y, y->right);
                x->left->parent = y;
                y->left = x->left;
                if(x->right != NULL) x->right->parent = y;
                y->right = x->right;
                t = replaceNode(t, x, y);
                y->count = x->count - 1;
        }
        return t;
}

char* searchByRank(ELEM *t, int rank)
{
        int k = t->left == NULL ? 1 : t->left->count + 1;
        if(k == rank) return t->v;
        else if(rank < k) return searchByRank(t->left, rank);
        else return searchByRank(t->right, rank - k);
}

char* lookup(ELEM* t, int k)
{
        ELEM *x = t;
        while(x != NULL && x->k != k)
                x = k < x->k ? x->left : x->right;
        return x->v;
}

int main() {
        unsigned int n;
        scanf("%d", &n);
        ELEM *t;
        ELEM *a = malloc(n * sizeof(ELEM));
        char s[SSIZE];
        int k;
        unsigned int i, j;
        for(i = 0, j = 0; i < n; i++) {
                scanf("%s", s);
                if(!strcmp("INSERT", s)) {
                        char v[VSIZE];
                        scanf("%d %s", &k, v);
                        a[j].v = malloc((strlen(v) + 1) * sizeof(char));
                        strcpy(a[j].v, v);
                        a[j].k = k;
                        a[j].count = 1;
                        if(!j) {
                                a[j].parent = a[j].left = a[j].right = NULL;
                                t = &a[j++];
                                continue;
                        }
                        insert(t, k, &a[j++]);
                        continue;
                }
                if(!strcmp("LOOKUP", s)) {
                        scanf("%d", &k);
                        printf("%s\n", lookup(t, k));
                        continue;
                }
                if(!strcmp("DELETE", s)) {
                        scanf("%d", &k);
                        t = delete(t, k);
                        continue;
                }
                if(!strcmp("SEARCH", s)) {
                        scanf("%d", &k);
                        printf("%s\n", searchByRank(t, k + 1));
                }
        }
        for(i = 0; i < j; i++) free(a[i].v);
        free(a);
        return 0;
}
