
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SSIZE 7
#define ELEM struct elem

ELEM {
    ELEM *next;
    int k, v;
};

int h(int i, unsigned int m)
{
        return i % m;
}

ELEM *initSingleLinkedList()
{
        ELEM *l = calloc(1, sizeof(ELEM));
        l->next = NULL;
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

void insertAfter(struct elem *x, struct elem *y)
{
	struct elem *z = x->next;
	x->next = y;
	y->next = z;
}

void insert(ELEM **t, int k, int v, unsigned int m, int (*h) (int i, unsigned int m))
{
        int i = h(k, m);
        ELEM *x = initSingleLinkedList();
        x->v = v, x->k = k;
        insertAfter(t[i], x);
}

void deleteAfter(ELEM *x)
{
        ELEM *y = x->next;
        x->next = y->next;
        free(y);
}

void deleteHead(ELEM *l)
{
        ELEM *y = l;
        l = y->next;
        free(y);
}

void searchAndDelete(ELEM *l, int k)
{
        ELEM *y, *x;
        for(y = NULL, x = l; x != NULL; y = x, x = x->next) {
                if(x->k == k) {
                        if(y == NULL) {
                                deleteHead(l);
                        } else {
                                deleteAfter(y);
                        }
                        break;
                }
        }
}

void delete(ELEM **t, int k, unsigned int m, int (*h) (int i, unsigned int m))
{
        searchAndDelete(t[h(k, m)], k);
}

ELEM *listSearch(ELEM *l, int k)
{
        ELEM* x = l;
        while(x != NULL && x->k != k) {
                x = x->next;
        }
        return x;
}

void reassign(ELEM **t, int k, int v, unsigned int m, int (*h) (int i, unsigned int m))
{
        listSearch(t[h(k, m)], k)->v = v;
}

ELEM *lookup(ELEM **t, int k, unsigned int m, int (*h) (int i, unsigned int m))
{
        return listSearch(t[h(k, m)], k);
}

void free_hash_table(ELEM **t, unsigned int m)
{
        unsigned int i;
        for(i = 0; i < m; i++) {
                ELEM *l = t[i]->next;
                free(t[i]);
                while (l != NULL) {
                        ELEM *p = l->next;
                        free(l);
                        l = p;
                }
        }
        free(t);
}

int main()
{
        unsigned int n, m, ind, i;
        scanf("%u %u", &n, &m);
        int v;
        char s[SSIZE];
        ELEM **t = initHashTable(m);
        for (i = 0; i < n; i++) {
                scanf("%s", s);
                if(!(strcmp("AT", s))) {
                        scanf("%d", &ind);
                        ELEM *value = lookup(t, ind, m, h);
                        if(value == NULL) {
                                printf("0\n");
                        } else {
                                printf("%d\n", value->v);
                        }
                }
                if(!(strcmp("ASSIGN", s))) {
                        scanf("%u %d", &ind, &v);
                        if(lookup(t, ind, m, h) == NULL) {
                                if(v == 0) continue;
                                insert(t, ind, v, m, h);
                        } else {
                                if(v == 0) {
                                        delete(t, ind, m, h);
                                } else {
                                        reassign(t, ind, v, m, h);
                                }
                        }
                }
        }
        free_hash_table(t, m);
        return 0;
}
