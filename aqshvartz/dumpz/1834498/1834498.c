#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

typedef struct Elem{
    struct Elem *next;
    char *word;
    int len;
}Elem;

Elem * last;

typedef Elem* List;

List InitSingleLinkedList()
{
    last = NULL;
    return NULL;
}

int ListEmpty(List l)
{
    return l == NULL;
}

List Insert(List l, char * w, int len)
{
    Elem * p = malloc(sizeof(Elem));
    p->word = malloc(len+1);
    strcpy(p->word, w);
    p->len = len;
    p->next = NULL;
    if(ListEmpty(l)){
        last = p;
        return p;
    }else{
        last->next = p;
        last = p;
        return l;
    }
}

List Delete(Elem * l)
{
    Elem * p = l->next;
    free(l->word);
    free(l);
    return p;
}

void DestroySingleLinkedList(List l)
{
    while(!ListEmpty(l)) l = Delete(l);
}

void ListPrint(List l)
{
    if(ListEmpty(l)) return;
    printf("%s ", l->word);
    ListPrint(l->next);
}
int ListBubble(List l)
{
    Elem * n;
    int change = 0;
    while(n = l->next){
        if(n->len < l->len){
            char *w;
            int len;
            w = l->word;
            l->word = n->word;
            n->word = w;
            len = l->len;
            l->len = n->len;
            n->len = len;
            change++;
        }
        l = n;
    }
    return change;
}
void ListBSort(List l)
{
    while(ListBubble(l));
}

int main()
{
    List l;
    l = InitSingleLinkedList();

    char c, w[1024];
    int len;

    len = 0;
    do{
        scanf("%c", &c);
        if(c == ' ' || c == 10 || c == 13){
            if(len){
                w[len] = '\0';
                l = Insert(l, w, len);
                len = 0;
            }
        }else{
            w[len++] = c;
        }
//printf("%c %d\n", c, c);
    }while(c != 10 && c != 13);
    ListBSort(l);
    ListPrint(l);
    DestroySingleLinkedList(l);
    return 0;
}