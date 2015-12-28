
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STACKSIZE 100000

typedef struct {
        int* data;
        int cap, top;
} stack_t;

stack_t initStack(n)
{
        stack_t s;
        s.data = (int*)malloc(n * sizeof(int));
        s.cap = n;
        s.top = 0;
        return s;
}

stackEmpty(stack_t s)
{
        return s.top == 0;
}

void push(stack_t *s, int x)
{
        s->data[s->top] = x;
        s->top++;
}

int pop(stack_t *s)
{
        s->top--;
        return s->data[s->top];
}

int main()
{
        int n, i;
        scanf("%u", &n);
        stack_t st = initStack(STACKSIZE);
        for(i = 0; i < n; i++) {
                char s[6];
                scanf("%s", s);
                if(!strcmp("CONST", s)) {
                        int x;
                        scanf("%d", &x);
                        push(&st, x);
                        continue;
                }
                if(!strcmp("ADD", s)) {
                        push(&st, pop(&st) + pop(&st));
                        continue;
                }
                if(!strcmp("SUB", s)) {
                        push(&st, pop(&st) - pop(&st));
                        continue;
                }
                if(!strcmp("MUL", s)) {
                        push(&st, pop(&st) * pop(&st));
                        continue;
                }
                if(!strcmp("DIV", s)) {
                        push(&st, pop(&st) / pop(&st));
                        continue;
                }
                if(!strcmp("MAX", s)) {
                        int a = pop(&st), b = pop(&st);
                        push(&st, a > b ? a : b);
                        continue;
                }
                if(!strcmp("MIN", s)) {
                        int a = pop(&st), b = pop(&st);
                        push(&st, a < b ? a : b);
                        continue;
                }
                if(!strcmp("NEG", s)) {
                        push(&st, -pop(&st));
                        continue;
                }
                if(!strcmp("DUP", s)) {
                        int a = pop(&st);
                        push(&st, a);
                        push(&st, a);
                        continue;
                }
                if(!strcmp("SWAP", s)) {
                        int a = pop(&st), b = pop(&st);
                        push(&st, a);
                        push(&st, b);
                        continue;
                }
        }
        printf("%d\n", pop(&st));
        free(st.data);
}
