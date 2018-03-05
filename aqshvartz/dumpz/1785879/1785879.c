#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void build(char *string, int *tree, int n) {
    for (int i = 0; i < n; i++) {
        tree[i + n] = 1 << (string[i] - 'a');
    }
    for (int i = n - 1; i > 0; i--) {
        tree[i] = tree[i << 1] ^ tree[i << 1 | 1];
    }
}

void modify(char *string, int *tree, int l, int r, int n) {
    while (l < r) {
        int i = l + n;
        tree[i] = 1 << (string[l++] - 'a');
        while (i > 1) {
            tree[i >> 1] = tree[i] ^ tree[i ^ 1];
            i >>= 1;
        }
    }
}

int query(int *tree, int l, int r, int n) {
    int answer = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) {
            answer ^= tree[l++];
        }
        if (r & 1) {
            answer ^= tree[--r];
        }
    }
    return answer;
}

int main() {
    char *string = malloc((1000000 + 1) * sizeof(char));
    scanf("%s", string);
    int n = strlen(string);
    int *tree = malloc(2 * n * sizeof(int));
    build(string, tree, n);
    int m;
    scanf("%d", &m);
    while (m--) {
        char command[4];
        scanf("%s", command);
        if (strcmp(command, "HD") == 0) {
            int l, r;
            scanf("%d%d", &l, &r);
            int answer = query(tree, l, r + 1, n);
            printf("%s\n", !(answer & (answer - 1)) ? "YES" : "NO");
        } else {
            int start, end;
            scanf("%d ", &start);
            end = start;
            for (; ;) {
                char c = getchar();
                if (isspace(c)) {
                    break;
                }
                string[end++] = c;
            }
            modify(string, tree, start, end, n);
        }
    }
    free(string);
    free(tree);
    return 0;
}