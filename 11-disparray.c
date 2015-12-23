
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ELEM struct elem

ELEM {
    ELEM *next;
    int k, v;
};

ELEM *initSingleLinkedList()
{
        ELEM *l = calloc(1, sizeof(ELEM));
	return l;
}

ELEM **initHashTable(unsigned int m)
{
        ELEM **t = malloc(m * sizeof(ELEM*));
        unsigned int i;
        for(i = 0; i < m; i++) {
                t[i] = initSingleLinkedList();
        }
        return t;
}

ELEM *insertBeforeHead(ELEM *l, ELEM *x)
{
        x->next = l;
        return l = x;
}

ELEM *listSearch(ELEM *l, int k)
{
        ELEM* x = l;
        while(x != NULL && x->k != k) {
                x = x->next;
        }
        return x;
}

void deleteAfter(ELEM *x)
{
        ELEM *y = x->next;
        x->next = y->next;
        y->next = NULL;
}

ELEM* deleteHead(ELEM *l)
{
        ELEM *y = l;
        l = y->next;
        y->next = NULL;
}

ELEM *searchAndDelete(ELEM *l, int k)
{
        ELEM *y = NULL;
        ELEM *x;
        for(x = l; x != NULL; y = x, x = x->next) {
                if(x->k == k) {
                        deleteHead(l);
                } else {
                        deleteAfter(y);
                }
        }
}

int h(int i, unsigned int m)
{
        return i mod m;
}

void insert(ELEM **t, int k, int v, unsigned int m, int (*h) (int i, unsigned int m))
{
        int i = h(k, m);
        ELEM *x = initSingleLinkedList();
        x->v = v, x->k = k;
        insertBeforeHead(t[i], x);
}

void delete(ELEM **t, int k, unsigned int m, int (*h) (int i, unsigned int m))
{
        searchAndDelete(t[h(k, m)], k);
}

void reassign(ELEM **t, int k, int v, unsigned int m, int (*h) (int i, unsigned int m))
{
        return listSearch(t[h(k, m)], k)->v;
}

int main() {
        unsigned int n, m, ind, i;
        int v;

        // for(i = 0; i < n; i++) {
        //
        // }
        return 0;
}
