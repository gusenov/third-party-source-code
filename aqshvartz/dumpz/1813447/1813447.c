#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n;
int max(int m, int n){
    if (m > n) return m;
    else return n;
}

int min(int m, int n){
    if (m < n) return m;
    else return n;
}


typedef struct Stack{
    int * data;
    int top, cap;
}Stack;

void InitStack(Stack * s,int n)
{
    s->data = malloc(n*sizeof(n));
    s->top = 0;
    s->cap = n;
}


int StackEmpty(Stack * s)
 {
 return s->top == 0;
 }

void Push(Stack * s, int t)
{
    if(s->top == s->cap){
     s->data = realloc(s->data, 2*s->cap*sizeof(n));
     s->cap *= 2;
     }
    
    s->data[s->top++] = t;
}
int Pop(Stack * s)
{
    return s->data[--s->top];
}

void DestroyStack(Stack * s){
    free(s->data);
    s->top = 0;
}

int main(){
    
    
    Stack st;
    Stack * s = &st;
    InitStack(s, 1);
    
   int  i = 0, x = 0, a = 0, b = 0;
    scanf("%d", &n);

    
    char str[5];
    char *oper =  str;
    
    while (i < n){
        scanf("%s", oper);
        if (oper[0] == 'C') {
            scanf("%d", &x);
        }
        else if (oper[0] == 'A') {
            a = Pop(s);
            b = Pop(s);
            x = a + b;
        }
        else if (oper[0] == 'S' && oper[1] == 'U'){
            a = Pop(s);
            b = Pop(s);
            x = a - b;
        }
        else if (oper[0] == 'M' && oper[1] == 'U') {
            a = Pop(s);
            b = Pop(s);
            x = a*b;
        }
        else if (oper[0] == 'D' && oper[1] == 'I'){
            a = Pop(s);
            b = Pop(s);
            x = a/b;
        }
        else if (oper[0] == 'M' && oper[1] =='A') {
            a = Pop(s);
            b = Pop(s);
            x = max(a,b);
        }
        else if (oper[0] == 'M' && oper[1] == 'I') {
            a = Pop(s);
            b = Pop(s);
            x = min(a,b);
        }
        else if (oper[0] == 'N') {
            a = Pop(s);
            x = -a;
        }
        else if (oper[0] == 'D' && oper[1] == 'U') {
            x = Pop(s);
            Push(s, x);
        }
        else if (oper[0] == 'S') {
            a = Pop(s);
            x = Pop(s);
            Push(s, a);
        }
        Push(s, x);
        i++;
    }
    printf("%d\n", Pop(s));
    DestroyStack(s);
}