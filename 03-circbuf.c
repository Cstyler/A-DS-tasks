
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STACKSIZE 4

typedef struct {
        int* data;
        int cap, count, head, tail;
} queue_t;

queue_t initQueue(int n)
{
        queue_t q;
        q.data = (int*)malloc(n * sizeof(int));
        q.cap = n;
        q.count = 0;
        q.head = 0;
        q.tail = 0;
        return q;
}

char queueEmpty(queue_t q)
{
        return q.count == 0;
}

void enqueue(queue_t *q, int x)
{
        if(q->count == q->cap) {
                q->data = (int*)realloc(q->data, q->cap * 2 * sizeof(int));
                int i, j;
                for(i = q->head, j = q->cap + q->head; i < q->cap; i++, j++)
                        q->data[j] = q->data[i];
                q->head += q->cap;
                q->cap *= 2;
        }
        q->data[q->tail] = x;
        q->tail++;
        if(q->tail == q->cap) q->tail = 0;
        q->count++;
}

int dequeue(queue_t *q)
{
        int x = q->data[q->head];
        q->head++;
        if(q->head == q->cap) q->head = 0;
        q->count--;
        return x;
}

int main()
{
        int n, i;
        scanf("%u", &n);
        queue_t q = initQueue(STACKSIZE);
        for(i = 0; i < n; i++) {
                char s[6];
                scanf("%s", s);
                if(!strcmp("ENQ", s)) {
                        int x;
                        scanf("%d", &x);
                        enqueue(&q, x);
                        continue;
                }
                if(!strcmp("DEQ", s)) {
                        printf("%d\n", dequeue(&q));
                        continue;
                }
                if(!strcmp("EMPTY", s)) {
                        char f = queueEmpty(q);
                        if(f) printf("true\n");
                        else printf("false\n");
                        continue;
                }
        }
        free(q.data);
}
