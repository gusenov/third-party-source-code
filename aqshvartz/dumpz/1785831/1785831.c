#include <stdio.h>
#include <stdlib.h>

int main() {
    
    int n;
    scanf("%d", &n);
    int a[n][n], i, j, k, id, max;
    for (i = 0; i < n; i++) {
        for (j=0; j<n; j++) {
            a[i][j] = rand()%10;
            printf("%d\t", a[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    k = n - 1;
    while (k > 0) {
        id = 0;
        for (j = 1; j <= k; j++)
            if (a[j][0] > a[id][0])
                id = j;
        for (i = 0; i < n; i++) {
            max = a[id][i];
            a[id][i] = a[k][i];
            a[k][i] = max;
        }
        k--;
    }
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%d\t", a[i][j]);
        }
        printf("\n");
    }
}