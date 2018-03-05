#include <stdio.h>
#include <stdlib.h>

int max (int s, int d)
{
    if (s < d) return d;
    else return s;
}

int* update(int j, int val, int i, int a,int b, int *T)
{
    int m = 0;
    if (a == b)
        T[i] = val;
    else {
        m = (a+b)/2;
        if (j <= m) {
            update(j, val,2*i+1, a, m, T);
        } else
        {
            update(j, val, 2*i+2,m+1, b, T);
        }
            T[i] = max(T[2*i+1], T[2*i+2]);}
    //}
    int *t = T;
    return t;
}

void SegmentTree_update(int j, int val, int n, int *T)
{
    update(j, val, 0, 0, n-1, T);
}



int* build(int *arr, int i, int a, int b, int *tree)
{
    if (a == b) {
        tree[i] = arr[a];
    }
    else {
        int m = (a+b)/2;
        build(arr, 2*i + 1, a, m, tree);
        build(arr, 2*i + 2, m+1, b, tree);
        tree[i] = max (tree[2*i+1],tree[2*i + 2]);
    }
    int *T = tree;
    return T;
}

int query(int *T, int l, int r, int i, int a, int b)
{
    int u = 0, m = 0;
    if  ((l == a) && (r == b))
    {
        u = T[i];
    }
    else {
        m = (a+b)/2;
        
        if (r <= m) u = query(T, l, r, 2*i+1, a, m);
        else
            if (l > m)
                u = query(T, l, r, 2*i+2, m+1, b);
            else
                u = max(query(T, l, m, 2*i+1, a, m),query(T, m + 1, r, 2*i+2, m + 1, b));
    }
    return u;
}

int SegmentTree_Query(int *T,int n, int l, int r)
{
    return query(T, l, r, 0, 0, n-1);
}

void SegmentTree_Build(int *arr, int n, int * T)
{
    build(arr, 0, 0, n-1, T);
}

int main()
{
    int n;
    scanf("%d", &n);
    int i = 0;
    int *arr = (int *) malloc(n*sizeof(int));
    for (i = 0; i < n; i++) scanf("%d", &arr[i]);
    
    int *T = (int *) malloc(4*n*(sizeof(int)));
    
    int l, r;
    SegmentTree_Build(arr, n, T);
    //for (i = 0; i < 4*n; i++) printf("%d ", T[i]);
    //printf("\n");
    int count = 0;
    scanf("%d", &count);
    char opred[100];
    char *s = opred;
    int ind = 0, val = 0;
    i = 0;
    while (i < count) {
        scanf("%s", s);
        if (s[0] == 'M') {
            scanf("%d %d", &l, &r);
            printf("%d\n", SegmentTree_Query(T, n, l, r));
        } else if (s[0] == 'U') {
            scanf("%d %d", &ind, &val);
            SegmentTree_update(ind, val, n, T);
            //for (i = 0; i < 4*n; i++) printf("%d ", T[i]);
        }
        i++;
    }
    free(arr);
    free(T);
}