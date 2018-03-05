#include <stdio.h>
#include <stdlib.h>

int main()
{
    int * a, n, i, j, k;
    scanf("%d", &n);
    a = malloc(n*sizeof(int));
    for(i=0; i<n; i++) scanf("%d", a+i);

    k = 0;
    for(i=0; i<n; i++){
        int x = 0;
        for(j=i; j<n; j++){
            x^=a[j];
            if(!x) k++;
        }
    }
    printf("%d", k);
    free(a);
    return 0;
}
