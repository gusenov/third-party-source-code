#include <stdio.h>
#include <stdlib.h>
//количество пиков подпоследовательности
int n;
int peak (int *arr, int i)
{
    int count = 0;
    if ((i == 0) && (arr[i] >= arr[i+1])) count += 1;
    else if ((i > 0) && (i < n - 1) && (arr[i] >= arr[i-1]) && (arr[i] >= arr[i+1])) count += 1;
    else if ((i == n - 1) && (arr[i] >= arr[i - 1])) count += 1;
    else count = 0;


    return count;
}

void update(int j, int val, int i, int a,int b, int *T, int *arr)
{
    int m = 0;
    if (a == b)
        T[i] = peak(arr,a);
    else {
        m = (a+b)/2;
        if (j <= m) {
            update(j, val, 2*i+1, a, m, T, arr);
        } else
        {
            update(j, val, 2*i+2,m+1, b, T, arr);
        }
        T[i] = T[2*i+1] + T[2*i+2];
    }
}

void SegmentTree_update(int j, int val, int n, int *T, int *arr)
{
    update(j, val, 0, 0, n-1, T,arr);
}

void build(int *arr, int i, int a, int b, int *tree)
{
    if (a == b) {
        tree[i] = peak(arr, a);
    }
    else {
        int m = (a+b)/2;
        build(arr, 2*i + 1, a, m, tree);
        build(arr, 2*i + 2, m+1, b, tree);
        tree[i] = tree[2*i+1] + tree[2*i + 2];
    }
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
                u = query(T, l, m, 2*i+1, a, m) + query(T, m + 1, r, 2*i+2, m + 1, b);
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
    scanf("%d", &n);
    int i = 0;
    int *arr = calloc(n + 1, sizeof(int));
    for (i = 0; i < n; i++) scanf("%d", &arr[i]);

    int *T = calloc(4*n, sizeof(int));

    SegmentTree_Build(arr, n, T);
    printf("\n");

    int count = 0, j = 0;
    scanf("%d", &count);
    char opred[100];
    char *s = opred;
    int ind = 0, val = 0, l = 0, r = 0;
    i = 0;
    while (i < count) {
        scanf("%s", s);
        if (s[0] == 'P') {
            scanf("%d %d", &l, &r);
            printf("%d\n", SegmentTree_Query(T, n, l, r));
        } else if (s[0] == 'U') {
            scanf("%d%d", &ind, &val);
            arr[ind] = val;
            for (j = ind -1; j <= ind + 1; j++) {
            SegmentTree_update(j, val, n, T,arr);
          }
        }
        i++;
    }
    free(arr);
    free(T);
}
