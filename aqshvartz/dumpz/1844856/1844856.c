#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pair {
    char * tag;
    int value;
} pair;

typedef struct avltree {
    pair p;
    int balance;
    struct avltree *parent;
    struct avltree *left;
    struct avltree *right;
} avltree;

avltree *InitAVLTree(avltree * t) {
    return t = NULL;
}

void Truepanic() {
    printf("You're a loser\n");
}

int MapEmpty(avltree *t) {
    return t == NULL;
}
/*
//finds min element in tree
avltree *Min_tree (avltree *t) {
    avltree *x;
    if (t == NULL)
        x = NULL;
    else {
        x = t;
        while (x->left != NULL)
            x = x->left;
    }
    return x;
}

//find max element in tree
avltree *Max_tree(avltree *t) {
    avltree *x;
    if (t == NULL)
        x = NULL;
    else {
        x = t;
        while (x->right != NULL)
            x = x->right;
    }
    return x;
}

avltree *Succ(avltree *x) {
    avltree *y;
    if (x->right != NULL)
        y = Min_tree(x->right);
    else {
        y = x->parent;
        while (y != NULL && (x == y->right))
            x = y, y = y->parent;
    }
    return y;
}
*/
avltree *Descend(avltree *t, char * key){
    avltree *x = t;
    while (x != NULL) {
        int c = strcmp(key, x->p.tag);
        if(c == 0) break;
        if (c < 0)
            x = x->left;
        else
            x = x->right;
    }
    return x;
}

int MapSearch(avltree *t, char * key) {
    return Descend(t, key) != NULL;
}

int Lookup(avltree *t, char * key) {
    avltree * x = Descend(t, key);
    if (x == NULL)
        printf("you're a loser\n");
    int value = x->p.value;
    return value;
}

//replacenode changes in the binary tree x to y
avltree *replace_node(avltree *t, avltree *x, avltree *y) {
    if (x == t) {
        t = y;
        if (y != NULL)
            y->parent = NULL;
    }
    else {
        avltree * p = x->parent;
        if (y != NULL)
            y->parent = p;
        if (p->left == x)
            p->left = y;
        else
            p->right = y;
    }
    return t;
}

avltree *RotateLeft(avltree *t, avltree * x) {
    avltree *y = x->right;
    if (y == NULL)
        Truepanic();
    replace_node(t, x, y);

    avltree *b = y->left;
    if (b != NULL)
        b->parent = x;
    x->right = b;
    x->parent = y;
    x->left = x;

    x->balance--;
    if (y->balance > 0)
        x->balance -= y->balance;
    y->balance--;
    if (x->balance < 0)
        y->balance += x->balance;
    return t;
}

avltree *RotateRight(avltree *t, avltree *x) {
    avltree *y = x->left;
    if (y == NULL)
        Truepanic();
    replace_node(t, x, y);

    avltree *b = y->right;
    if (b != NULL)
        b->parent = x;
    x->left = b;
    x->parent = y;
    x->right = b;

    x->balance++;
    if (y->balance < 0)
        x->balance -= y->balance;
    y->balance++;
    if (x->balance > 0)
        y->balance += x->balance;

    return t;
}

avltree *insert(avltree *t, char * k, int l, int v) {
    avltree *y;
    y = malloc(sizeof(avltree));
    y->p.tag = malloc(l);
    strcpy(y->p.tag, k);
    y->p.value = v;
    y->parent = NULL;
    y->left = NULL;
    y->right = NULL;
    if (t == NULL)
        t = y;
    else {
        avltree *x = t;
        while (1) {
            int c = strcmp(k, x->p.tag);
            if (c == 0) {
                Truepanic();
                break;
            }
            if (c < 0) {
                if (x->left == NULL) {
                    x->left = y;
                    y->parent = x;
                    break;
                }
                x = x->left;
            } else {
                if (x->right == NULL) {
                    x->right = y;
                    y->parent = x;
                    break;
                }
                x = x->right;
            }
        }
    }
    return t;
}

avltree *InsertAVL(avltree *t, char * k, int l, int v) {
    avltree *a = insert(t,k,l,v);
    a->balance = 0;
    while (1) {
        avltree *x = a->parent;
        if (x == NULL)
            break;
        if (a == x->left) {
            x->balance--;
            if (!x->balance)
                break;
            if (x->balance == -2) {
                if (a->balance == 1)
                    RotateLeft(t, x);
                RotateRight(t, x);
                break;
            }
        }
        else {
            x->balance++;
            if (!x->balance)
                break;
            if (x->balance == 2) {
                if (a->balance == -1)
                    RotateRight(t, a);
                RotateLeft(t, x);
                break;
            }
        }
        a = x;
    }
    return a;
}
/*
avltree *Delete(avltree *t, int k) {
    avltree *x = Descend(t, k);
    if (x == NULL)
        printf("You're a fatal loser\n");
    if (x->left == NULL && x->right == NULL)
        replace_node(t, x, NULL);
    else if (x->left == NULL)
        replace_node(t, x, x->right);
    else if (x->right == NULL)
        replace_node(t, x, x->left);
    else {
        avltree *y = Succ(x);
        replace_node(t, y, y->right);
        x->left->parent = y;
        y->left = x->left;
        if (x->right != NULL)
            x->right->parent = y;
        y->right = x->right;
        replace_node(t, x, y);
    }
    return t;
}
*/
avltree *reassign(avltree *t, int k, int v) {
    avltree *x = Descend(t, k);
    if (x == NULL)
        Truepanic();
    x->p.value = v;
    return t;
}

void Destroy(avltree * t)
{
    if(MapEmpty(t)) return;
    Destroy(t->left);
    Destroy(t->right);
    free(t->p.tag);
    free(t);
}

int is_digit(char c){return c >= '0' && c <= '9';}
int is_alpha(char c){c = toupper(c); return c >= 'A' && c <= 'Z';}
int is_spec(char c){return c >= '(' && c <= '/';}

#define CONST 1
#define IDENT 2
int main()
{
    int i, n;
    int ident_n = 0;
    int val;
    char c, type;
    char spec[50], ident[1024], l=0;
    spec['+'] = 0;
    spec['-'] = 1;
    spec['*'] = 2;
    spec['/'] = 3;
    spec['('] = 4;
    spec[')'] = 5;
    avltree * t;
    t = InitAVLTree(t);

    scanf("%d\n", &n);
    type = 0;
    for(i=-1; i<n; i++){
        scanf("%c", &c);
//printf("%d %c\n", c, c);
        switch(type){
            case CONST:
                if(is_digit(c)) val = val*10 + c - '0';
                else{
                    type = 0;
                    printf("CONST %d\n", val);
                    if(is_alpha(c)){ type = IDENT; l=0; ident[l++] = c; }
                    if(is_spec(c)) printf("SPEC %d\n", spec[c]);
                }
                break;
            case IDENT:
                if(is_digit(c) || is_alpha(c)) ident[l++] = c;
                else{
                    type = 0;
                    ident[l++] = '\0';

                    avltree * x = Descend(t, ident);
                    if(x == NULL){
                        t = InsertAVL(t, ident, l, ident_n);
                        printf("IDENT %d\n", ident_n);
                        ident_n++;
                    }else{
                        printf("IDENT %d\n", x->p.value);
                    }
                    if(is_spec(c)) printf("SPEC %d\n", spec[c]);
                }
                break;
            default:
                if(is_digit(c)){ type = CONST; val = c - '0'; }
                if(is_alpha(c)){ type = IDENT; l=0; ident[l++] = c; }
                if(is_spec(c)) printf("SPEC %d\n", spec[c]);
        }
    }
    Destroy(t);
}

