#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pair {
    int tag;
    unsigned int value;
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

avltree *Descend(avltree *t, int key){
    avltree *x = t;
    while (x != NULL && x->p.tag != key) {
        if (key < x->p.tag)
            x = x->left;
        else
            x = x->right;
    }
    return x;
}

int MapSearch(avltree *t, int key) {
    return Descend(t, key) != NULL;
}

unsigned int *Lookup(avltree *t, int key) {
    avltree * x = Descend(t, key);
    if (x == NULL)
        printf("you're a loser\n");
    unsigned int *value = &x->p.value;
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

//insertrion in tree, not avltree
avltree *insert(avltree *t, int k, int v) {
    avltree *y;
    y->p.tag = k;
    y->p.value = v;
    y->parent = NULL;
    y->left = NULL;
    y->right = NULL;
    if (t == NULL)
        t = y;
    else {
        avltree *x = t;
        while (1) {
            if (x->p.tag == k) {
                Truepanic();
                break;
            }
            if (k < x->p.tag) {
                if (x->left != NULL) {
                    x->left = y;
                    y->parent = x;
                    break;
                }
                x = x->left;
            } else {
                if (x->right != NULL) {
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

avltree *InsertAVL(avltree *t, int k, int v) {
    avltree *a = insert(t,k,v);
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
    return t;
}

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

/*void DeleteAll() {
 
}

void DestroyAvlTree(avltree *t) {
    while (MapEmpty(t)) DeleteAll(t);
}*/

avltree *reassign(avltree *t, int k, int v) {
    avltree *x = Descend(t, k);
    if (x == NULL)
        Truepanic();
    x->p.value = v;
    return t;
}


/*
//simple max of two elements
int max(int a, int b) {
    return (a < b) ? a : b;
}
//calculates max of two nodes in avltree
int height(avltree *t) {
    int hei;
    if (t == NULL)
        hei = 0;
    else
        hei = max(height(t->left), height(t->right));
    return hei;
}
*/

int main() {
    avltree * T;
    avltree * t = T;
    InitAVLTree(t);
    
    char str[10];
    char *s = str;
    int n, key, value;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", s);
        if (s[0] == 'I') {
            scanf("%d%d",&key, &value);
            InsertAVL(t, key, value);
        }
        else if (s[0] == 'R') {
            scanf("%d%d", &key, &value);
            reassign(t, key, value);
        }
        else if (s[0] == 'D') {
            scanf("%d", &key);
            Delete(t, key);
        }
    }
}