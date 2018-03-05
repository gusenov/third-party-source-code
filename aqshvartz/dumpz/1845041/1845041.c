#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct SingleList {
    int key;
    int val;
    struct SingleList *next;
}SingleList;

typedef  struct hash {
    SingleList * arr;
}hash;
int m = 1;

SingleList * InitSingleList (SingleList *l) {
    return l = NULL;
}

int ListEmpty (SingleList * l) {
    return l == NULL;
}

SingleList * ListSearch(SingleList * l, int val) {
    SingleList * x = l;
    if (x == NULL)
        return NULL;
    while (x != NULL && x->val != val)
        x = x->next;
    return x;
}

SingleList * InsertBeforeHead (SingleList * l, SingleList * y) {
    y->next = l;
    l = y;
    return l;
}

SingleList * DeleteHead(SingleList * l) {
    SingleList * y = l;
    l = y->next;
    y->next = NULL;
    return l;
}

void DeleteAfter(SingleList * l) {
    SingleList * y = l->next;
    l->next = y->next;
    y->next = NULL;
}

SingleList *SearchAndDelete (SingleList * l, int val ) {
    SingleList *y = NULL;
    SingleList *x = l;
    while ( x != NULL) {
        if (x->val == val) {
            if (y == NULL)
                DeleteHead(l);
            else
                DeleteAfter(y);
            return l;
        }
        y = x;
        x = x->next;
    }
    return l;
}

int ha(int i) {
    return (i % m);
}

hash * InitHashTable(hash * h, int m) {
    h = malloc(m*sizeof(SingleList*));
    for (int i = 0; i < m; i++)
        InitSingleList(&h->arr[i]);
    return h;
}

int MapEmpty(hash * h, int m) {
    int i = 0;
    while (i < m) {
        if (!ListEmpty(&h->arr[i]))
            return 0;
        i++;
    }
    return 0;
}

void Truepanic() {
    printf("You're a loser\n");
}

int MapSearch(hash * h, int key) {
    return ListSearch(&h->arr[ha(key)], key) == NULL;
}

int Lookup (hash * t, int key) {
    SingleList * p = ListSearch(&t->arr[ha(key)], key);
    if (p == NULL)
        Truepanic();
    int v = p->val;
    return v;
}

SingleList * Insert(hash * t, int key, int val) {
    int i = ha(key);
    if (ListSearch(&t->arr[i], key) != NULL)
        Truepanic();
    SingleList * y = malloc(m*sizeof(SingleList));
    y->key = key;
    y->val = val;
    y->next = NULL;
    InsertBeforeHead(&t->arr[i], y);
    return &t->arr[i];
}

SingleList * Delete(hash * t, int key) {
    int num = ha(key);
    SearchAndDelete(&t->arr[num], key);
    return &t->arr[num];
}

SingleList * Reassign (hash * t, int key, int val) {
    int num = ha(key);
    SingleList * p = ListSearch(&t->arr[num], key);
    if (p == NULL && val != 0) t->arr[num] = * Insert(t, key, val);
    else if (p != NULL && (!val)) t->arr[num] = * Delete(t, key);
    else if (p != NULL)
        p->val = val;
    return &t->arr[ha(key)];
}

int At(hash * t, int key){
    SingleList * x = ListSearch(&t->arr[ha(key)], key);
    return x == NULL ? 0 : x->val;
}

int main() {
    int n, i;
    scanf("%d%d", &n, &m);
    hash H;
    hash *h = &H;
    InitHashTable(h, m);
    
    char str[40];
    int key, val;
    for(i=0; i<n; i++){
        scanf("%s", str);
        if (!strcmp(str,"ASSIGN")) {
            scanf("%d%d", &key, &val);
            Reassign(h, key, val);
        }
        else if (!strcmp(str, "AT")) {
            scanf("%d", &key);
            printf("%d\n", At(h, key));
        }
    }
    //DestroyHashTable(h);
    return 0;
}