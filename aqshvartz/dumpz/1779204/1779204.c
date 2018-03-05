#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int max (int s, int d)
{
    if (s > d) return s;
    else return d;
}
int* delta1(char *s)
{
    int l = strlen(s), size = 200;
    int *del = calloc(size, sizeof(int));
    int a = 0;
    while (a < size) {
        del[a]=l;
        a++;
    }
    int j = 0;
    while (j < l) {
        del[(int)s[j]] = l - j - 1;
        j++;
    }
    return del;
}

int* sufff(char *s){


    int siz = strlen(s);
    int t = 0, i = 0;
    int *letter = calloc(siz, sizeof(int));
    for (i = 0; i < siz; i++) letter[i] = i;

    letter[siz - 1] =  siz - 1;
    t = siz - 1;
    i = siz - 2;
    while (i >= 0) {
        while ((t < siz -1) && (s[t] != s[i])) {
            t = letter[t+1];
        }
        if (s[t] == s[i]) {
            t--;
        }
        letter[i] = t;
        i--;
    }

    //int *let = letter;
    return letter;
}

int* delta2(char *s)
{
    int si = strlen(s);
    int *delt = calloc(si, sizeof(int));
    int i = 0;
    int *suf = sufff(s);
    i = 0;
    int t = suf[0];

    while (i < si){
        while (t < i) {
            t = suf[t+1];}
        delt[i] = -i + t + si;
        i++;
    }

    i = 0;
    while (i < si - 1){
        t = i;
        while (t < si - 1) {
            t = suf[t+1];
            if (s[i] != s[t]) {
                delt[t] = - (i + 1) + si;
            }
        }
        i++;
    }
    free (suf);
    return delt;
}
void BMSubst(char *s, char *t)
{
    int i = 0;
    int *del = delta1(s);
    int *dell = delta2(s);
    int k = strlen(s) - 1;
    while (k < strlen(t)){
        i = strlen(s) - 1;
        while (t[k] == s[i]) {
            if (i == 0)
            {
                printf("%d\n", k);
                break;
            }
            i--;
            k--;
        }
        k+= max(del[(int)t[k]],dell[i]);
    }
    free(del);
    free(dell);

}

int main(int argc, char **argv)
{
char * str1 = argv[1], * str2 = argv[2];
    BMSubst(str1, str2);
    return 0;
}