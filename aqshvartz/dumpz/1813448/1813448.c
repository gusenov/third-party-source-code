#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Queue{
    int *data;
    int cap, count, head, tail;
}Queue;

void InitQueue(Queue *q, int n) {
    q->data = malloc(n*sizeof(n));
    q->cap = n;
    q->count = q->head = q->tail = 0;
}

int QueueEmpty(Queue *q) {
     return q->count == 0;
}

void QueueEmptyInterface(Queue *q) {
    if (QueueEmpty(q)) {
        printf("true\n");
    } else {
        printf ("false\n");
    }
}

void Enqueue(Queue *q, int x) {
    if (q->count == q->cap) {
        q->data = realloc(q->data, 2*q->cap * sizeof(int));
        if(q->head < q->cap / 2){
            memcpy(q->data + q->cap, q->data, q->head * sizeof(int));
            q->tail += q->cap;
        }else{
            memcpy(q->data + q->head + q->cap, q->data + q->head, (q->cap - q->head) * sizeof(int));
            q->head += q->cap;
        }
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
    if (QueueEmpty(q)) {
        printf("m\n");
        exit(1);
    }
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
    InitQueue(Q, 4);

    int n, i = 0, x;
    char str[10];
    char *s = str;
//FILE * f = fopen("d:\\in.txt", "rt");
//fscanf(f, "%d", &n);
    scanf("%d", &n);
//int l = 1;
    while (i < n) {
//l++;
//fscanf(f, "%s", s);
//printf("l = %d\n", l);
        scanf("%s", s);
        if (s[0] == 'E' && s[1] == 'M') QueueEmptyInterface(Q);
        else if (s[0] == 'E' && s[1] == 'N') {
//fscanf(f, "%d",&x);
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