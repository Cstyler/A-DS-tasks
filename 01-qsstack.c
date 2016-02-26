
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int low, high;
} task_t;

typedef struct {
        task_t* data;
        int cap, top;
} stack_t;

stack_t initStack(n)
{
        stack_t s;
        s.data = (task_t*)malloc(n * sizeof(task_t));
        s.cap = n;
        s.top = 0;
        return s;
}

stackEmpty(stack_t s)
{
        return s.top == 0;
}

void push(stack_t *s, task_t x)
{
        s->data[s->top] = x;
        s->top++;
}

task_t pop(stack_t *s)
{
        s->top--;
        return s->data[s->top];
}

int compare(int *a, int *b)
{
        return *a - *b;
}

void swap(int *a, int *b)
{
        int t = *a;
        *a = *b;
        *b = t;
}

int partition(int low, int high, int *base, int (*compare)(int *a, int *b))
{
        int i, j;
        for(i = low, j = low; j < high; j++)
                if(compare(base + j, base + high) < 0) {
                        swap(base + i, base + j);
                        ++i;
                }
        swap(base + i, base + high);
        return i;
}

void quickSortRec(int low, int high, int *base, int (*compare)(int *a, int *b))
{
        stack_t st = initStack(high - low + 1);
        task_t starttask;
        starttask.low = low;
        starttask.high = high;
        push(&st, starttask);
        while(!stackEmpty(st)) {
                task_t task = pop(&st);
                if(task.low < task.high) {
                        int q = partition(task.low, task.high, base, compare);
                        task_t t1, t2;
                        t1.low = task.low;
                        t1.high = q - 1;
                        t2.low = q + 1;
                        t2.high = task.high;
                        push(&st, t2);
                        push(&st, t1);
                }
        }
        free(st.data);
}

void quickSort(int nel, int *base, int (*compare)(int *a, int *b))
{
        quickSortRec(0, nel - 1, base, compare);
}

int main()
{
        int i, n;
        scanf("%d", &n);
        int* arr = (int*)malloc(n * sizeof(int));
        for(i = 0; i < n; i++)
                scanf("%d", arr + i);
        quickSort(n, arr, compare);
        for(i = 0; i < n; i++)
                printf("%d ", arr[i]);
        printf("\n");
        free(arr);
        return 0;
}
