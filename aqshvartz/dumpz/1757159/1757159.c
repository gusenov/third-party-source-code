#include <stdio.h>
#include <stdlib.h>

void heaps(int n, int *items);
void swap (int *items, int i, int j);
void buildheap (int n,int *items);
void heapify (int i, int n, int *items);
void buildheap (int n, int *items);

int main()
{
    int n;
    scanf("%d",&n);
    int a[n];
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    int *p = a;
    heaps(n,p);
    for (int res = 0; res < n; res++) printf("%d ", a[res]);
}
void buildheap (int n, int *items){
    int i = n/2-1;
    while (i >= 0){
        heapify(i, n, items);
        i--;
    }
}
void heaps(int n, int *items){
    buildheap(n, items);
    int i = n - 1;
    while (i > 0) {
        swap (items, 0, i);
        heapify(0, i, items);
        i--;
    }
    
}

void heapify (int i, int n, int *items)
{
    for (;;) {
    int l = 2*i + 1;
    int r = l + 1;
    int j = i;
    if ((l<n) && (items[i] < items[l]))
        i = l;
    if  ((r<n) && (items[i] < items[r]))
        i = r;
    if (i == j) break;
    swap(items, i,j);
    }
}

void swap(int *a, int i, int j)
{
    int t = a[i];
    a[i] = a[j];
    a[j] = t;
}