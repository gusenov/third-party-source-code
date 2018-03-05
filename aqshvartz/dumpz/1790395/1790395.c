#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int nod(int x, int y)
{
    int a = abs(x), b = abs(y);
    while (a && b) {
        if (a >= b)
            a %= b;
        else
            b %= a;
    }
    return a | b;
}

int* compite_log (int m)
{
    int size = (1 << (m + 1)), i = 1, j = 0;
    int *lg = calloc(size, sizeof(int));

    while (i <= m) {
        while (j < (1 << i)) {
            lg[j] = i - 1;
            j++;
        }
        i++;
    }
    return lg;
}

int sparse_table_query(int **st, int l, int r, int *lg)
{
    int j = lg[r-l+1], u = 0;
    return u = nod(st[l][j], st[r-(1<<j) + 1][j]);
}

int** sparse_table_build (int *arr, int  *lg, int n)
{
    int m = lg[n] + 1;
    int **st = malloc (n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        st[i] = malloc (n * sizeof(int));
    }
    int i = 0;
    while (i < n) {
        st[i][0] = arr[i];
        i++;
    }
    int j = 1;
    while (j < m)
    {
        i = 0;
        while (i <= n - (1 << j)) {
            st[i][j] = nod (st[i][j-1], st[i + (1 << (j - 1))][j - 1]);
            i++;
        }
        j++;
    }
    return st;
}

int main ()
{
    int n;
    scanf("%d", &n);
    int *arr = (int *) malloc (n * sizeof(int));
    int m = log2(n);
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
    int *lg = compite_log(m + 1);
    int **st  = sparse_table_build(arr, lg, n);
    int l, r, count, i = 0; //count - количество операций, l - левая граница, r - правая граница
    scanf("%d", &count);
    //printf("count = %d", count);
    while (i < count) {
        scanf("%d%d", &l, &r);
        printf("%d\n", sparse_table_query(st, l, r, lg));
        i++;
    }
    free(arr);
    free(lg);
    for (int i = 0; i < n; i++)
        free(st[i]);
    free(st);
}