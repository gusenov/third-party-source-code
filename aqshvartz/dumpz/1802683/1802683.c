#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int** delta1(char *s)
{
    int l = strlen(s), size = 123, k = 0;
    int **del = calloc(l, sizeof(int * ));
    for (int i = 0; i < l; i++) {
      del[i] = calloc(size, sizeof(int));
    }

    for (int i = 0; i < l; i++) {
      for (int j = 0; j < size; j++)
      {
        del[i][j] = l;
      }
      for (int j = k = 0; j < l - k; j++, k++)
      del[i][(int)j] = l - j - 1;
    }

    return del;
}

int BMSubst(char *s, char *t)
{
    int i = 0;
    int **del = delta1(s);
    int n = strlen(s), m = strlen(t);
    int k = n - 1;
    while (k < m) {
        i = n - 1;
        while (t[k] == s[i]) {
            if (i == 0)
            {
              for (i = 0; i < n; i++)
              free(del[i]);
              free(del);
              return k;
            }
            i--;
            k--;
        }
        k+= del[n - i - 1][(int)t[k]];
        i = n - 1;
    }

    for (i = 0; i < n; i++)
    free(del[i]);
    free(del);
    return m;
}

int main(int argc, char **argv)
{
char * str1 = argv[1], * str2 = argv[2];
    printf("%d\n", BMSubst(str1, str2));
    return 0;
}
