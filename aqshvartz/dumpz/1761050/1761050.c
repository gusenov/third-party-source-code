#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void heapify (int i, int n, int *items);
void swap(int *a, int i, int j);

int array[5000];

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
        swap(array,0,i);
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
        swap(array,i,j);
    }
}

void swap(int *a, int i, int j)
{
    int t = a[i];
    a[i] = a[j];
    a[j] = t;
}


int main()
{
    int n;
    scanf("%d ", &n);
    char arr[n][100];
    char* s[n];
    int i = 0;
    for (i = 0; i < n; i++){
        gets(arr[i]);
        s[i] = arr[i];
    }

    
    int count[n], c = 0;
    int l = 0;
    for (i = 0; i < n; i++) {
        for (l = 0; l < strlen(s[i]); l++) {
            if (arr[i][l] == 'a')
                c++;
        }
        count[i] = c;
        c = 0;
    }
  
    
    int *p = count;
    int k = 0;
    for (k = 0; k < n; k++) array[k] = k;
    
    heaps(n, p);
    for (i = 0; i < n; i++) printf("%s\n", s[array[i]]);
}
