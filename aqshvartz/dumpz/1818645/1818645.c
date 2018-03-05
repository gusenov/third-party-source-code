#include <stdio.h>
#include <stdlib.h>

typedef struct tree{
    int item;
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

tree *search_tree(tree *l, int x) {
    if (l == NULL) return NULL;
    if (l->item == x) return l;
    if (x < l->item)
        return search_tree(l->left, x);
    else return search_tree(l->right, x);
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

void traverse_tree(tree *l) {
    if (l != NULL){
        traverse_tree(l->left);
        //process_item(l->item);
        traverse_tree(l->right);
    }
}

void insert_tree(tree **l, int x, tree *parent) {
    tree *p;
    if (*l == NULL) {
        p = malloc(sizeof(tree));
        p->item = x;
        p->left = p->right = NULL;
        p->parent = parent;
        *l = p;
        return ;
    }
    if (x < (*l)->item)
        insert_tree(&((*l)->left), x, *l);
    else
        insert_tree(&((*l)->right), x, *l);
}

tree *delete_tree(tree *t, int x) {
    tree *d;
    tree *p;
    int new_key;
    tree *child;
    tree *search_tree();
    d= search_tree(t, x);
    
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
    int d;
    tree *l;
    tree *tmp;
    tree *search_tree();
    void insert_tree();
    
    l = init_binary_tree();
    char *str = c;
    int n, i = 0, x;
    scanf("%d", &n);
    while (i < n) {
        scanf("%s", str);
        if (str[0] == 'p') {
            print_tree(l);
            printf("\n");
        } else
            if (str[0] == 'i') {
                scanf("%d", &x);
                insert_tree(&l, x, NULL);
            } else
                if (str[0] == 's') {
                    scanf("%d", &x);
                    tmp = search_tree(l,d);
                    if (tmp == NULL)
                        printf("item %d not found\n", x);
                    else
                        printf("item %d found\n", x);
                } else
                    if (str[0] == 'd') {
                        scanf("%d", &x);
                        l = delete_tree(l, d);
                        printf("\n");
                    } else
                        if (str[0] == 'e') {
                            printf("%d", empty_tree(l));
                        }
        i++;
    }
}