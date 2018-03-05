#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void kadane (double *mas, int n)
{
    double maxsum = mas[0];
    int start = 0, sum = 0, l = 0, r = 0, i = 0;
    while (i < n) {
        sum += mas[i];
        if (sum > maxsum) {
            maxsum = sum;
            l = start;
            r = i;
        }
        if (sum < 0) {
            sum = 0;
        start = i + 1;
        }
        i++;
    }
    printf("%d\n%d\n", l, r);
}


int main()
{
    int n, i = 0;
    scanf("%d", &n);
    double *arr = calloc(n, sizeof(double));
    double a,b;
    for (i = 0; i < n; i++)  {
        scanf("%lf/%lf", &a, &b);
        arr[i] = log2(a/b);
    }
    //printf("\n");
    //for (i = 0; i < n; i++) printf("%lf", arr[i]);
    kadane(arr, n);
    free(arr);
}