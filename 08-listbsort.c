
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SSIZE 50
#define WSIZE 10
#define OUT 0
#define IN 1

typedef struct elem {
    struct elem *next;
    char *word;
    unsigned int len;
} elem_t;

elem_t *initSingleLinkedList()
{
        elem_t *l = calloc(1, sizeof(elem_t));
        return l;
}

void insertAfter(elem_t *x, elem_t *y)
{
	elem_t *z = x->next;
	x->next = y;
	y->next = z;
}

char compare(elem_t *x, elem_t *y)
{
	return x->len > y->len ? 1 : 0;
}

void swap(elem_t* x)
{
	elem_t *a = x->next;
	elem_t *b = a->next;
	a->next = b->next;
	x->next = b;
	b->next = a;
}

elem_t *bsort(elem_t *list)
{
	elem_t *t = NULL, *bound = t, *i, *j;
	while(t != list) {
		bound = t, t = list, i = list, j = list->next;
		while(j->next != bound) {
			if(compare(j, j->next)) {
				swap(i);
				t = j;
			}
			i = i->next, j = i->next;
		}
	}
	return list;
}

int wcount(char *s)
{
	int i, n = 0, flag = OUT;
	for(i = 0; s[i]; i++) {
		if(flag == OUT && s[i] != ' ') n++;
		if(s[i] == ' ') flag = OUT;
		else flag = IN;
        }
	return n;
}

int main()
{
	char*s = malloc(SSIZE * sizeof(char));
	gets(s);
	int n = wcount(s);
	char **ss = (char**)malloc(n * sizeof(char*));
    char *sss = (char*)calloc(n * WSIZE, sizeof(char));
    int i, k, j;
    for(i = 0; i < n; i++)
        ss[i] = sss + i * WSIZE;
    char flag = OUT;
    for(i = 0, j = 0, k = 0; s[i]; i++) {
		if(flag == IN && s[i] == ' ') ++j, k = 0;
		if(s[i] == ' ') flag = OUT;
			else {
				ss[j][k] = s[i];
				++k;
				flag = IN;
			}
		}
	free(s);

	elem_t *list = initSingleLinkedList();
	elem_t *a = malloc(n * sizeof(elem_t));
	for(i = n - 1; i >= 0; i--) {
		a[i].word = ss[i];
                a[i].len = strlen(ss[i]);
		insertAfter(list, &a[i]);
	}

	list = bsort(list);

	elem_t *el = list->next;
	while(el != NULL) {
		printf("%s ", el->word);
		el = el->next;
	}
	printf("\n");

	free(list);
	free(a);
	free(ss);
	free(sss);
	return 0;
}
