#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tree{
    int item;
    char word[10];
    struct tree *parent;
    struct tree *left;
    struct tree *right;
} tree;

tree *init_binary_tree() {
    return NULL;
}

int empty_tree(tree *t) {
    return t == NULL;
}
tree * lookup(tree * t, int key)
{
    if(empty_tree(t)) return NULL;
    if(key == t->item) return t;
    if(key < t->item)
        return lookup(t->left, key);
    else
        return lookup(t->right, key);
}

tree * search_tree(tree *l, int * x) {
    if (l == NULL) return NULL;
    tree * p;
    p = search_tree(l->left, x);
    if(p) return p;
    p = search_tree(l->right, x);
    if(p) return p;
    (*x)--;
    if(!*x) return l;
    return NULL;
}

void print_tree(tree *l){
    if (l != NULL) {
        print_tree(l->left);
        printf("%d ", l->item);
        print_tree(l->right);
    }
}

tree *succ(tree *t) {
    tree *succ;
    if (t->right == NULL) return NULL;
    succ = t->right;
    while (succ->left != NULL)
        succ = succ->left;
    return succ;
}

tree *pred(tree *t) {
    tree *pred;
    if (t->left == NULL) return NULL;
    pred = t->left;
    while (pred->right != NULL)
        pred = pred->right;
    return pred;
}

void insert_tree(tree **l, int x, char * s, tree *parent) {
    tree *p;
    if (*l == NULL) {
        p = malloc(sizeof(tree));
        p->item = x;
        strcpy(p->word, s);
        p->left = p->right = NULL;
        p->parent = parent;
        *l = p;
        return ;
    }
    if (x < (*l)->item)
        insert_tree(&((*l)->left), x, s, *l);
    else
        insert_tree(&((*l)->right), x, s, *l);
}

tree *delete_tree(tree *t, int x) {
    tree *d;
    tree *p;
    int new_key;
    tree *child;
    d = lookup(t, x);
    
    if (d == NULL) {
        printf("error\n");
        return t;
    }
    
    if (d->parent == NULL) {
        if ((d->left == NULL) && (d->right == NULL)) {
            free(d);
            return NULL;
        }
        
        if (d->left != NULL)
            p = pred(d);
        else
            p = succ(d);
    } else {
        if ((d->left == NULL) || (d->right == NULL)) {
            if (d->left != NULL)
                child = d->left;
            else
                child = d->right;
            
            if ((d->parent)->left == d) {
                d->parent->left = child;
            }
            else {
                d->parent->right = child;
            }
            if (child != NULL) child->parent = d->parent;
            
            free(d);
            return t;
        }
        else {
            p = succ(d);
        }
    }
    
    new_key = p->item;
    delete_tree(t, p->item);
    d->item = new_key;
    return t;
}

int main() {
    
    char c[10];
    tree *l;
    tree *tmp;
    tree *search_tree();
    
    l = init_binary_tree();
    char *str = c;
    int n, i = 0, x;
    scanf("%d", &n);
    while (i < n) {
        scanf("%s", str);
        if (str[0] == 'P') {
            print_tree(l);
            printf("\n");
        } else if (str[0] == 'I') {
            char s[10];
            scanf("%d%s", &x, s);
            insert_tree(&l, x, s, NULL);
        } else if (str[0] == 'S') {
            scanf("%d", &x);
            tmp = search_tree(l,&x);
            if (tmp == NULL)
                ;//printf("item %d not found\n", x);
            else
                printf("%s\n", tmp->word);
        } else if (str[0] == 'D') {
            scanf("%d", &x);
            l = delete_tree(l, x);
        } else if (str[0] == 'L') {
            scanf("%d", &x);
            tmp = lookup(l, x);
            printf("%s\n", tmp->word);
        } else if (str[0] == 'E') {
            printf("%d", empty_tree(l));
        }
        i++;
    }
}