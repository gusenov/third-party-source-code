#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int kadane (int *mas, int n)
{
    int l = 0, r = 0, maxsum = mas[0];
    int start = 0, sum = 0;
    int i = 0;
    while (i < n) {
        sum += mas[i];
        if (sum > maxsum){
            maxsum = sum;
            l = start;
            r = i;
        }
        i++;
        if (sum < 0){
            sum = 0;
            start = i;
        }
    }
    printf("%d\n", l);
    printf("%d\n", r);
    return 0;
}


int main()
{
    int n;
    scanf("%d", &n);
    int a[n], i = 0;
    for (i = 0; i < n; i++) scanf("%d", &a[i]);
    int *uk = a;
    kadane(uk, n);
}