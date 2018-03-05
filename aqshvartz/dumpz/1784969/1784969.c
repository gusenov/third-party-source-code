#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//сортировка распределением
void distribution (int n, int *arr, int m)
{
  int count[m], i;
  for (i = 0; i < m; i++) count[i] = 0;
  int j = 0, k = 0;
  while (j < n) {
    k = arr[j];
    count[k] += 1;
    j++;
  }

  i = 1;
  while (i < m) {
    count[i] += count[i-1];
    i++;
  }

  int d[n];
  j = n - 1;
  while (j >= 0){
    k = arr[j];
    i = count[k] - 1;
    count[k] = i;
    d[i] = arr[j];
    j--;
  }
  for (i = 0; i < n; i++) printf("%d ", d[i]);
}

int main(int argc, char **argv)
{
  int n;
  scanf("%d", &n);//количество элементов в исходном массиве
  int a[n], i;
  //элементы массива
  for (i = 0; i < n; i++) scanf("%d", &a[i]);
  int *arr = a;
  int m = 100;
  distribution(n, arr, m);
}