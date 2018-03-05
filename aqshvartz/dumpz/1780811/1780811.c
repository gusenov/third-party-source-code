#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int kadane (int *mas, int n, int l, int r)
{
    int max = mas[l];
    
    while (l <= r) {
        if (mas[l] > max)
            max = mas[l];
        l++;
    }
    
    return max;
}


int main()
{
    int n;
    scanf("%d", &n);
    int a[n], i = 0;
    for (i = 0; i < n; i++) scanf("%d", &a[i]);
    int *uk = a;
    int l, r, j = 0;
    char stroka[100];
    char *str = stroka;
    
    int count; //сколько операций
    scanf("%d", &count);
 
    while (j < count) {
        scanf("%s",str);
        if (str[0] == 'M') {
            scanf("%d %d", &l, &r);
            printf("%d\n",kadane(uk,n,l,r));
        }
        else
            if (str[0] == 'U') {
                int v;
                scanf("%d %d", &i, &v);
                uk[i] = v;
            } 
        j++;
    }
}