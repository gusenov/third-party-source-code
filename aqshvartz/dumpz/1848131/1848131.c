#include <stdio.h>
#include <stdlib.h>
#define D 0
typedef struct Elem{
    struct Elem *next;
    unsigned int key, val;
}Elem;

typedef struct List{
    Elem * first, * last;
}List;

List * InitSingleLinkedList(List * l)
{
    l->first = l->last = NULL;
    return l;
}

int ListEmpty(List * l)
{
    return l->first == NULL;
}

void Insert(List * l, unsigned int key, unsigned int val)
{
    Elem * p = malloc(sizeof(Elem));
    p->key = key;
    p->val = val;
    p->next = NULL;
    if(ListEmpty(l)){
        l->first = l->last = p;
    } else {
        l->last->next = p;
        l->last = p;
    }
}

Elem * ListSearch(List * l, unsigned int key){
    Elem * x = l->first;
    while(x != NULL && x->key != key) x = x->next;
    return x;
}

void DeleteFirst(List * l)
{
    Elem * p = l->first->next;
    free(l->first);
    l->first = p;
}

void DestroySingleLinkedList(List * l)
{
    while(!ListEmpty(l)) DeleteFirst(l);
}

/*
 void ListPrint(Elem * l)
 {
 if(ListEmpty(l)) return;
 printf("%s ", l->word);
 ListPrint(l->next);
 }
 */

typedef struct HashTable{
    unsigned int m;
    List * l;
}HashTable;

void InitHashTable(HashTable * h, unsigned int m){
    h->l = malloc(m * sizeof(List));
    h->m = m;
    unsigned int i;
    for(i=0; i<m; i++) InitSingleLinkedList(h->l+i);
}

void DestroyHashTable(HashTable * h){
    unsigned int i;
    for(i=0; i<h->m; i++) DestroySingleLinkedList(h->l+i);
    free(h->l);
    h->m = 0;
}

void Delete(List * l, Elem * x){
    Elem * p = l->first;
    if(p == x){
        l->first = p->next;
        if(p->next == NULL) l->last = NULL;
        free(p);
    }else{
        while(p->next != x) p = p->next;
        p->next = x->next;
        if(x->next == NULL) l->last = p;
        free(x);
    }
}

void Assign(HashTable * h, unsigned int key, unsigned int val){
    unsigned int i = key % h->m;
    Elem * x = ListSearch(h->l+i, key);
    if (x == NULL){
        if(val) Insert(h->l+i, key, val);
    }else{
        if(val == 0) Delete(h->l+i, x);
        else x->val = val;
    }
}

Elem * At(HashTable * h, unsigned int key){
    unsigned int i = key % h->m;
    Elem * x = ListSearch(h->l+i, key);
    return x;
}

FILE * f1, *f2;
int main()
{
    HashTable H;
    HashTable * h = &H;
    InitHashTable(h, 10000);

    unsigned int a, *c, n, i, x;
    long long int r;
    Elem * e;
    if(D){
        f1 = fopen("d:\\test6.txt", "rt");
        f2 = fopen("d:\\res.txt", "wt");
    }
    D ? fscanf(f1, "%d", &n) : scanf("%d", &n);
    c = malloc(n*sizeof(unsigned int));
    x = 0;
    r = 0;
    for(i=0; i<n; i++){
//printf("%d\n", i);
        D ? fscanf(f1, "%d", &a) : scanf("%d", &a);
        x^=a;
        e = At(h, x);
        if(e == NULL){
            c[i] = x ? 0 : 1;
            Assign(h, x, i+1);
        }else{
            c[i] = c[e->val-1] + 1;
            e->val = i+1;
        }
        r += c[i];
    }
    D ? fprintf(f2, "%d", r) : printf("%d", r);
    free(c);
    DestroyHashTable(h);
    return 0;
}
