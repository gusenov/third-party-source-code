#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n;

typedef struct Queue{
    int *data;
    int cap, count, head, tail;
}Queue;

void InitQueue(Queue *q) {
    q->data = malloc(n*sizeof(n));
    q->cap = n;
    q->count = q->head = q->tail = 0;
}

int QueueEmpty(Queue *q) {
    int count = 0;
    if (q->count == 0) {
        printf("true\n");
        count = 0;
    } else {
        printf ("false\n");
        count = 1;
    }
    return count;
}

void Enqueue(Queue *q, int x) {
    if (q->count == q->cap) {
        q->data = realloc(q->data, 2*q->cap * sizeof(n));
        q->cap *= 2;
    }
    q->data[q->tail] = x;
    q->tail++;
    if (q->tail == q->cap) {
        q->tail = 0;
    }
    q->count++;
}

int Dequeue(Queue *q) {
    int x = 0;
    x = q->data[q->head];
    q->head++;
    if (q->head == q->cap) q->head = 0;
    q->count--;
    return x;
}

void DestroyQueue(Queue *q){
    free(q->data);
}

int main(){
    
    Queue Qu;
    Queue *Q = &Qu;
    InitQueue(Q);
    
    int i = 0, x = 0;
    char str[10];
    char *s = str;
    scanf("%d", &n);
    while (i < n) {
        scanf("%s", s);
        if (s[0] == 'E' && s[1] == 'M') QueueEmpty(Q);
        else if (s[0] == 'E' && s[1] == 'N') {
            scanf("%d",&x);
            Enqueue(Q, x);
        }
        else if (s[0] == 'D') {
            printf("%d\n", Dequeue(Q));
        }
        i++;
    }
    DestroyQueue(Q);
}