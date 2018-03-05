#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int* prefix(char *s)
{
  int size = strlen(s), i = 0, k = 0;
  int *pi = calloc(size, sizeof(int));

  for (i = 0; i < size; i++) pi[i] = i;

  pi[0] = 0;
  int t = 0;
  i = 1;

  while (i < size) {
      k = i;
      while ((t > 0) && (s[t] != s[i])) {
          t = pi[t-1];
      }
      if (s[t] == s[i]) {
          t++;
      }
      pi[i] = t;
      i++;
  }
  //for (i = 0; i < size; i++) printf("%d ", pi[i]);
  return pi;
}


int main(int argc, char **argv)
{
    char *str = argv[1];
    //prefix(str);
    int len = strlen(str), *pi, size = 0, answer = 0, i = 0;
    pi = prefix(str);
    for (i = 1; i < len; i++) {
      if ((pi[i] > 0) && ((i + 1) % (i + 1 - pi[i]) == 0)) {
        size = i + 1;
        answer = (i + 1)/(i + 1 - pi[i]);
        printf("%d %d\n", size, answer);
      }
    }
    free(pi);
    return 0;
}