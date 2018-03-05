#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DoubleStack{
    struct New *data;
    int cap, top1, top2;
}DoubleStack;

typedef struct New {
    int a,b;
}New;

void InitDoubleStack(DoubleStack *s, int n) {
    s->data = malloc(n*sizeof(struct New));
    s->cap = n;
    s->top1 = 0;
    s->top2 = n - 1;
}

int max(int x, int y) {
    if (x < y) return y;
    else return x;
}

void InitQueueOnStack(DoubleStack *s, int n){
    InitDoubleStack(s, n);
}

int StackEmpty1(DoubleStack *s){
    return s->top1 == 0;
}

int StackEmpty2(DoubleStack *s) {
    return (s->top2 == s->cap - 1);
}

int QueueEmpty(DoubleStack *s) {
    return (StackEmpty1(s) && StackEmpty2(s));
}

void QueueEmptyInterface(DoubleStack *s) {
    if (StackEmpty1(s) && StackEmpty2(s)) printf("true\n");
    else printf("false\n");
}

void Push1(DoubleStack *s, int x) {
    if (s->top2 < s->top1) printf("переполнение 1\n");
    s->data[s->top1].a = x;
    //s->mx = max(s->data[s->top1], s->data[s->top1 - 1]);
    s->data[s->top1].b = max(s->data[s->top1].a, s->data[s->top1 - 1].b);
    s->top1++;
}

void Push2(DoubleStack *s, int x) {
    if (s->top2 < s->top1) printf("переполнение 2\n");
    s->data[s->top2].a = x;
    //s->mx = max(s->data[s->top2], s->data[s->top2 + 1]);
    s->data[s->top2].b = max(s->data[s->top2].a, s->data[s->top2 + 1].b);
    s->top2--;
}

int maxinter(DoubleStack *s) {
    if (StackEmpty1(s)) return s->data[s->top2 + 1].b;
    else if (StackEmpty2(s)) return s->data[s->top1 - 1].b;
    else return max(s->data[s->top2 + 1].b, s->data[s->top1 - 1].b);
}

//(76 6 86 7 56|5 6 6 7 7 8 3 2)

int Pop1(DoubleStack *s) {
    if (StackEmpty1(s)) {
        printf("error\n");
        exit(1);
    }
    s->top1--;
    int x = s->data[s->top1].a;
    return x;
}

int Pop2(DoubleStack *s) {
    if (StackEmpty2(s)) {
        printf("error\n");
        exit(2);
    }
    s->top2++;
    int x = s->data[s->top2].a;
    return x;
}

void Enqueue(DoubleStack *s, int x) {
    Push1 (s, x);
}

int Dequeue (DoubleStack *s) {
    if (StackEmpty2(s)) {
        while  (!StackEmpty1(s)) {
            Push2(s, Pop1(s));
        }
    }
    int x = Pop2(s);
    return x;
}

void DestroyDoubleStack(DoubleStack *s) {
    free(s->data);
}

int main() {
    
    int n,i = 0, x;
    scanf("%d", &n);
    
    DoubleStack St;
    DoubleStack *s = &St;
    InitDoubleStack(s, n);
    
    char str[10];
    char *oper = str;
    while (i < n) {
        scanf("%s", oper);
        if (oper[0] == 'E' && oper[1] == 'N'){
            scanf("%d", &x);
            Enqueue(s, x);
        }
        else if (oper[0] == 'D') {
            printf("%d\n", Dequeue(s));
        }
        else if (oper[0] == 'M' && oper[1] == 'A') printf("%d\n", maxinter(s));
        else if (oper[0] == 'E' && oper[1] == 'M') {
            QueueEmptyInterface(s);
        }
        i++;
    }
    DestroyDoubleStack(s);
    return 0;
}