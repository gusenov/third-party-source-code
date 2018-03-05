#include <stdio.h>
#include <stdlib.h>

typedef struct PriorityQueue{
    int *heap, size, max_size;
}PriorityQueue;

void swap(PriorityQueue * q, int i, int j)
{
    int z = q->heap[i];
    q->heap[i] = q->heap[j];
    q->heap[j] = z;
}
void InitPriorityQueue(PriorityQueue * q, int s)
{
    q->heap = malloc(s * sizeof(int));
    q->max_size = s;
    q->size = 0;
}

void DestroyPriorityQueue(PriorityQueue *q) {
        free(q->heap);
        q->max_size = 0;
        q->size = 0;
}

void Insert(PriorityQueue * q, int a)
{
    int i;
    q->heap[i=q->size++] = a;
    while (i != 0 && q->heap[i] < q->heap[(i - 1) / 2]) {
        swap(q, i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

int ExtractMax(PriorityQueue * q)
{
    int res = q->heap[0];
    q->heap[0] = q->heap[--q->size];
    int i = 0;
    while (i < q->size / 2) {
        int maxI = 2 * i + 1;
        if (2 * i + 2 < q->size && q->heap[2 * i + 2] < q->heap[2 * i + 1])
            maxI = 2 * i + 2;
        if (q->heap[i] <= q->heap[maxI])
            return res;
        swap(q, i, maxI);
        i = maxI;
    }
    return res;
}

int main()
{
    PriorityQueue Q;
    PriorityQueue * q = &Q;

    int k, i, a, n;
    scanf("%d", &k);
    n = 0;
    for(i=0; i<k; i++){
        scanf("%d", &a);
        n += a;
    }
    InitPriorityQueue(q, n);
    for(i=0; i<n; i++){
        scanf("%d", &a);
        Insert(q, a);
    }
    for(i=0; i<n; i++){
        printf("%d ", ExtractMax(q));
    }
    
    DestroyPriorityQueue(q);

//int j; for(j=0; j<q->size; j++) printf("%d ", q->heap[j]); printf("\n");
    return 0;
}
