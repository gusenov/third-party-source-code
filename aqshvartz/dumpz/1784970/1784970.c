#include <stdio.h>
#include <string.h>
//если в строке есть только буквы
int key (char s) {
  char t = 'a';
  return ((int)s - (int)t);
}
char antikey (int x) {
  char t = 'a';
  return ((char)x + (int)t);
}

void distribution (int n, char *arr, int m)
{
  int count[m], i;
  for (i = 0; i < m; i++) count[i] = 0;
  int j = 0, k = 0;
  while (j < n) {
    k = key(arr[j]);
    //printf("%d j=%d \n", k, j);
    count[k] += 1;
    j++;
  }
 //for (int p = 0; p < m; p++)
  //  printf("%d ", count[p]);
  i = 1;
  while (i < m) {
    count[i] += count[i-1];
    i++;
  }

  int d[n];
  j = n - 1;
  while (j >= 0){
    k = key(arr[j]);
    i = count[k] - 1;
    count[k] = i;
    d[i] = key(arr[j]);
    j--;
  }
  for (i = 0; i < n; i++) printf("%c",antikey(d[i]));
  printf("\n");
}

int main()
{
  char str[100];
  gets(str);
  char *s = str;
  int m = 26;
  int n = strlen(s);
  distribution(n, str, m);

}