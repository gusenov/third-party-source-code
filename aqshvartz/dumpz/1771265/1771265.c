#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int words (char *src);
void csort (char *scr, char *dest);
char dest[100];
//char stroka[100];
int main ()
{
    char stroka[100];
    gets (stroka);
    char *src = stroka;
    unsigned long nel = strlen(stroka);
    
    int i = 0,j = 0;
    while (src[i] == ' ') i++;
    char secstr[100];
    secstr[0] = stroka[0];
    while (i < nel){
        if ((src[i] == ' ') && (src[i + 1] == ' '))
        {
            i++;
        }
        else {
            secstr[j] = src[i];
            i++;
            j++;
        }
    }
    secstr[j] = '\0';
    //printf("%s\n", secstr);
    //printf("%ld\n", strlen(secstr));
    char *srcc = secstr;
    csort(srcc, dest);
    for (i = 0;i < nel; i++) printf("%c", dest[i]);
    printf("\n");
}
int words (char *s){
    int count = 0, i = 0;
    
    while (s[i] != '\0') {
        if (((s[i] >= '0') && (s[i] <= '9')) || ((s[i] >= 'a') && (s[i]<= 'z')))
        {
            while ((s[i] != ' ') && (i < strlen(s))) i++;
            count++;
        }
        else i++;
    }
    return count;
}

void csort(char *sr, char *dest)
{
    unsigned long size = strlen(sr);
    
    int count = words(sr);
    
    int masforlen[count], q = 0, j = 0;
    int i = 0;
    while ((i < strlen(sr)) && (i < size) && (q < count)) {
        j = 0;
        if ((sr[i] != ' ') &&    (((sr[i] >= '0') && (sr[i] <= '9')) || (((sr[i] >= 'a') && (sr[i]<= 'z')) && (q < count)))) {
            while ((sr[++i] != ' ') && (sr[i] != '\0'))
                j++;
        }
        i++;
        masforlen[q] = j + 1;
        q++;
    }
    
    int counting[count];
    for (i = 0; i < count; i++) counting[i] = 0;
    j = 0;
    while (j < count - 1) {
        i = j + 1;
        while (i < count) {
            if (masforlen[i] < masforlen[j]) counting[j] += masforlen[i] + 1;
            else counting[i] += masforlen[j] + 1;
            i++;
        }
        j++;
    }
    int z = 0;
    for (i = 0; i < count; i++) {
        for (j = 0; j < masforlen[i]; j++) {
            dest[counting[i] + j] = sr[j + z];
        }
        dest[j+counting[i]] = ' ';
        z += masforlen[i] + 1;
    }
}