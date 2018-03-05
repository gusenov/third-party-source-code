#include <stdio.h>
#include <stdlib.h>

typedef struct Task{
    int low, high;
}Task;

typedef struct Stack{
    Task * data;
    int cap, top;
}Stack;

void InitStack(Stack * s,int n)
{
    s->data = malloc(n*sizeof(Task));
    s->cap = n;
    s->top = 0;
}
int StackEmpty(Stack * s)
{
    return s->top == 0;
}
void Push(Stack * s, Task t)
{
    if(s->top == s->cap){
        s->data = realloc(s->data, 2*s->cap*sizeof(Task));
        s->cap *= 2;
    }
    s->data[s->top++] = t;
}
Task Pop(Stack * s)
{
    if(StackEmpty(s)){
        printf("stack is Empty");
        exit(2);
    }
    return s->data[--s->top];
}
void DestroyStack(Stack * s){
//printf("\n%d\n", s->cap);
    free(s->data);
    s->cap = s->top = 0;
}
void qSort(int * m, int n){
    Stack st;
    Stack * s = &st;
    Task t;
    InitStack(s, 1);

    t.low = 0; t.high = n-1;
    Push(s, t);

    while(!StackEmpty(s)){
        t = Pop(s);
        int b = m[(t.low+t.high)/2];
        int i = t.low, j = t.high;
        while(i <= j){
            while(m[i] < b)i++;
            while(m[j] > b)j--;
            if(i <= j){
                int tmp = m[i];
                m[i] = m[j];
                m[j] = tmp;
                i++; j--;
            }
        }
        if(t.low < j){
            Task tmp = {t.low, j};
            Push(s, tmp);
        }
        if(i < t.high){
            Task tmp = {i, t.high};
            Push(s, tmp);
        }
    }

    DestroyStack(s);
}
int main()
{
    int i, n, *m;
    scanf("%d", &n);
    m = malloc(n*sizeof(int));
    for(i=0; i<n; i++) scanf("%d", m+i);

    qSort(m, n);

    for(i=0; i<n; i++) printf("%d ", m[i]);
    free(m);
    return 0;
}
