#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define DBG 0

typedef struct Elem{
    struct Elem *next;
    int key, val;
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

void Insert(List * l, int key, int val)
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

Elem * ListSearch(List * l, int key){
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
    int m;
    List * l;
}HashTable;

void InitHashTable(HashTable * h, int m){
    h->l = malloc(m * sizeof(List));
    h->m = m;
    int i;
    for(i=0; i<m; i++) InitSingleLinkedList(h->l+i);
}

void DestroyHashTable(HashTable * h){
    int i;
    for(i=0; i<h->m; i++) DestroySingleLinkedList(h->l+i);
    free(h->l);
    h->m = 0;
}

/*
 SingleList * Reassign (hash * t, int key, int val) {
 //int num = ha(key);
 SingleList * p = ListSearch(&t->arr[ha(key)], key);
 if (p == NULL && val != 0) t->arr[ha(key)] = * Insert(t, key, val);
 else if (p != NULL && (!val)) t->arr[ha(key)] = * Delete(t, key, ha(key));
 else if (p != NULL)
 p->val = val;
 return &t->arr[ha(key)];
 }
 */
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

void Assign(HashTable * h, int key, int val){
    int i = key % h->m;
    Elem * x = ListSearch(h->l+i, key);
    if (x == NULL){
        if(val) Insert(h->l+i, key, val);
    }else{
        if(val == 0) Delete(h->l+i, x);
        else x->val = val;
    }
}

int At(HashTable * h, int key){
    int i = key % h->m;
    Elem * x = ListSearch(h->l+i, key);
    return x == NULL ? 0 : x->val;
}

FILE *f1, *f2;

int main()
{
    int n, m, i;
    if(DBG){
        f1 = fopen("d:\\test.txt", "rt");
        f2 = fopen("d:\\text1.txt", "wt");
    }
    DBG ? fscanf(f1, "%d%d", &n, &m) : scanf("%d%d", &n, &m);
    HashTable H;
    HashTable * h = &H;
    InitHashTable(h, m);

    char str[40];
    int key, val;
    for(i=0; i<n; i++){
/*
if(i==6869){
        printf("sdf");
}
if(i==6870){    printf("%d", At(h, 900473962));exit(0);}
if(i==9013){    printf("sdf");}
*/
        DBG ? fscanf(f1, "%s", str) : scanf("%s", str);
        if (str[1] == 'S') {
            DBG ? fscanf(f1,"%d%d", &key, &val) : scanf("%d%d", &key, &val);
//            if(DBG)fprintf(f2, "%d\t%s %d %d\n", i+3, str, key, val);
            Assign(h, key, val);
        }
        if (str[1] == 'T') {
            DBG ? fscanf(f1,"%d", &key) : scanf("%d", &key);
//            if(DBG)fprintf(f2, "%d\t%s %d\n", i+3, str, key);
            DBG ? fprintf(f2,"%d\n", At(h, key)) : printf("%d\n", At(h, key));
        }
    }
    DestroyHashTable(h);
    if(DBG){
        fclose(f1);
        fclose(f2);
    }
    return 0;
}
