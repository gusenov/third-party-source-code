#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tree{
    int item;
    char * word;
    int count;
    struct tree *parent;
    struct tree *left;
    struct tree *right;
} tree;

tree * init_binary_tree(tree *t) {
    return NULL;
}

int empty_tree(tree *t) {
    return t == NULL;
}
tree * lookupfirst(tree * t, int key)
{
    if(empty_tree(t)) return NULL;
    if(key == t->item) return t;
    if(key < t->item) {
        t->count--;
        return lookupfirst(t->left, key);
    }
    else {
        t->count--;
        return lookupfirst(t->right, key);
    }
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
int m = 0;
tree * search_tree(tree *l, int x) {
    /*if (l == NULL) return NULL;
    tree * p;
    p = search_tree(l->left, x);
    if (p) return p;
    p = search_tree(l->right, x);
    if (p) return p;
    return NULL;
     */
    
    if (l->left == NULL)
        m = 0;
    else
        m = (l->left->count) + 1;
    if (x == (m + 1))
        return l;
    else
        if (x > (m + 1))
        return search_tree(l->right, x - m - 1);
        else
          return search_tree(l->left, x);
}

tree *find_min(tree *t) {
    tree *min;
    if (t == NULL) return NULL;
    min = t;
    while (min->left != NULL)
        min = min->left;
    return min;
}

tree *find_max(tree *t) {
    tree *max;
    if (t == NULL) return NULL;
    max = t;
    while (max->right != NULL)
        max = max->right;
    return max;
}

void print_tree(tree *l){
    if (l != NULL) {
        print_tree(l->left);
        printf("%d ", l->item);
        print_tree(l->right);
    }
}

tree * minim(tree * t) {
    tree * x;
    if (t == NULL)
        x = NULL;
    else {
        x = t;
        while (x->left != NULL)
            x->count--;
            x = x->left;
    }
    return x;
}
/*
tree *succ(tree *t) {
    tree *succ;
    if (t->right == NULL) return NULL;
    succ = t->right;
    while (succ->left != NULL)
        succ = succ->left;
    return succ;
}
 */

tree *succ(tree *x) {
    tree *y;
    if (x->right != NULL)
        y = minim(x->right);
    else {
        y = x->parent;
        while (y != NULL && (x == y->right)) {
            x = y;
            y = y->parent;
        }
    }
    return y;
}

tree *pred(tree *t) {
    tree *pred;
    if (t->left == NULL) return NULL;
    pred = t->left;
    while (pred->right != NULL)
        pred = pred->right;
    return pred;
}

void traverse_tree(tree *l) {
    if (l != NULL){
        traverse_tree(l->left);
        traverse_tree(l->right);
    }
}

tree * insert_tree(tree *t, int k, char * s) {
    tree * y;
    y = malloc(sizeof(tree));
    y->word = malloc(100 * sizeof(char*));
    y->item = k;
    strcpy(y->word, s);
    y->count = 0;
    y->parent = y->left = y->right = NULL;
    if (t == NULL)
        t = y;
    else {
        tree *x = t;
        x->count++;
        while (1) {
            if (x->item == k) {
                printf("lol2\n"); break;
            }
            if (k < x->item) {
                if (x->left == NULL) {
                    x->left = y;
                    y->parent = x;
                    break;
                }
                x = x->left;
            }
            else {
                if (x->right == NULL) {
                    x->right = y;
                    y->parent = x;
                    break;
                }
                x = x->right;
            }
            x->count++;
        }
    }
    return t;
}

/*void insert_tree(tree **l, int x, char * s, tree *parent) {
    tree *p;
    if (*l == NULL) {
        p = malloc(sizeof(tree));
        p->item = x;
        p->count = 0;
        strcpy(p->word, s);
        p->left = p->right = NULL;
        p->parent = parent;
        *l = p;
        return ;
    } else {
        (*l)->count++;
    }
    if (x < (*l)->item)
        insert_tree(&((*l)->left), x, s, *l);
    else
        insert_tree(&((*l)->right), x, s, *l);
}
*/
/*
tree *destroy_tree(tree *t, int x) {
    tree *d;
    tree *p;
    int new_key;
    tree *child;
    d = lookupfirst(t, x);
    
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
    }
    else
    {
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
    destroy_tree(t, p->item);
    d->item = new_key;
    return t;
}
*/


tree *Descend(tree *t, int k) {
    tree * x = t;
    while (x != NULL && (x->item != k)) {
        if (k < x->item) {
            x->count--;
            x = x->left;
        }
        else {
            x->count--;
            x = x->right;
        }
    }
    return x;
}

tree *ReplaceNode(tree *t, tree * x, tree * y) {
    if (x == t) {
        t = y;
        if (y == NULL)
            y->parent = NULL;
    }
    else {
        tree * p = x->parent;
        if (y != NULL)
            y->parent = p;
        if (p->left == x)
            p->left = y;
        else
            p->right = y;
    }
    return t;
}

tree *delete_tree(tree *t, int k) {
    tree * x = Descend(t, k);
    if (x == NULL)
        printf("lol1\n");
    
    if (x->left == NULL && x->right == NULL)
        t = ReplaceNode(t, x, NULL);
    
    else if (x->left == NULL)
        t = ReplaceNode(t, x, x->right);
    
    else if (x->right == NULL)
        t = ReplaceNode(t, x, x->left);
    
    else {
        tree * y = succ(x);
        t = ReplaceNode(t, y, y->right);
        x->left->parent = y;
        y->left = x->left;
        
        if (x->right != NULL)
            x->right->parent = y;
        
        y->right = x->right;
        t = ReplaceNode(t, x, y);
        y->count = x->count;
    }
    free(x->word);
    free(x);
    return t;
}

void delete(tree *t) {
    if (t != NULL) {
        free(t->word);
        delete(t->left);
        delete(t->right);
        free(t);
    }
}

int main() {
    
    char c[10];
    tree *l;
    //tree *t = l;
    
    l = init_binary_tree(l);
    
    char *str = c;
    int n, i = 0, x;
    int j;
    scanf("%d", &n);
    while (i < n) {
        scanf("%s", str);
        if (str[0] == 'P') {
            print_tree(l);
            printf("\n");
        } else if (str[0] == 'I') {
            char s[10];
            scanf("%d%s", &x, s);
            l = insert_tree(l,x,s);
        } else if (str[0] == 'S') {
            scanf("%d", &j);
            j = j + 1;
            printf("%s\n",search_tree(l, j)->word);
        } else if (str[0] == 'D') {
            scanf("%d", &x);
            l = delete_tree(l, x);
            //printf("%d", );
        } else if (str[0] == 'L') {
            scanf("%d", &x);
            printf("%s\n", lookup(l, x)->word);
        } else if (str[0] == 'E') {
            printf("%d", empty_tree(l));
        }
        i++;
    }
    delete(l);
}