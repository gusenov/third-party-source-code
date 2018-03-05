#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Elem{
    struct Elem *prev, *next;
    int v;
}Elem;

typedef Elem DoubleLinkedList;

void InitDoubleLinkedList(DoubleLinkedList * l)
{
    l->next = l->prev = l;
    l->v = INT_MIN;
    return l;
}

int ListEmpty(DoubleLinkedList * l)
{
    return l->next == l->prev;
}

int Delete(Elem * l)
{
    l->prev->next = l->next;
    l->next->prev = l->prev;
    int res = l->v;
    free(l);
    return res;
}

void DestroyDoubleLinkedList(DoubleLinkedList * l)
{
    while(!ListEmpty(l)) Delete(l->next);
}

void Insert(DoubleLinkedList * l, int a)
{
    Elem * e = malloc(sizeof(Elem));
    e->v = a;
    e->next = l;
    e->prev = l->prev;
    l->prev->next = e;
    l->prev = e;
    while(e->prev->v > e->v){
        int z = e->prev->v;
        e->prev->v = e->v;
        e->v = z;
        e = e->prev;
    }
}

int main()
{
    DoubleLinkedList L;
    DoubleLinkedList * l = &L;
    InitDoubleLinkedList(l);
    int n, i, a;
    scanf("%d", &n);

    for(i=0; i<n; i++){
        scanf("%d", &a);
        Insert(l, a);
    }

    for(i=0; i<n; i++){
        printf("%d ", Delete(l->next));
    }

//    DestroyDoubleLinkedList(l);
    return 0;
}
