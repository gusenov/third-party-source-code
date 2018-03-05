#include <stdio.h>
#include <math.h>
#include <stdlib.h>
//наибольший общий делитель

int nod(int a, int b)
{
    while (a && b) {
        if (a >= b)
           a %= b;
        else
           b %= a;
         }
    return a | b;
}

int main()
{
  int m, n;
  scanf("%d %d", &m, &n);
  printf("%d",nod (m,n);
}