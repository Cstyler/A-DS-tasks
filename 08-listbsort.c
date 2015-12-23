
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SSIZE 50
#define WSIZE 10
#define OUT 0
#define IN 1

struct elem {
    struct elem *next;
    char *word;
};

struct elem *initSingleLinkedList()
{
        struct elem *l = calloc(1, sizeof(struct elem));
	return l;
}

void insertAfter(struct elem *x, struct elem *y)
{
	struct elem *z = x->next;
	x->next = y;
	y->next = z;
}

char compare(struct elem *x, struct elem *y)
{
	return strlen(x->word) > strlen(y->word) ? 1 : 0;
}

void swap(struct elem* x)
{
	struct elem *a = x->next;
	struct elem *b = a->next;
	a->next = b->next;
	x->next = b;
	b->next = a;
}

struct elem *bsort(struct elem *list)
{
	struct elem *t = NULL, *bound = t, *i, *j;
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

	struct elem *list = initSingleLinkedList();
	struct elem *a = malloc(n * sizeof(struct elem));
	for(i = n - 1; i >= 0; i--) {
		a[i].word = ss[i];
		insertAfter(list, &a[i]);
	}

	list = bsort(list);

	struct elem *el = list->next;
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
