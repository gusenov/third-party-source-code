#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void palindrom(char *str)
{
    unsigned long len = strlen(str);
    int i = 0,k = 0;
    while(i < len) {
        if (str[i] == str[len - i - 1]) k++;
        i++;
    }
    if(k == i) printf("Yes\n");
    else printf ("No\n");
}

int main()
{
    char *str = (char *) malloc(10 * sizeof(char));
    scanf("%s", str);
    palindrom(str);
    free(str);
    return 0;
}