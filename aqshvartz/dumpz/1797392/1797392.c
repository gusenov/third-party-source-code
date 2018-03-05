#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define m_alp 26
#define m_digit 10
#define m 36

int key(char c)
{
	if (isdigit(c))
		return c - '0';
	else if (isalpha(c))
		return c - 'a' + m_digit;
	else
		return 0;
}

char inv_key(int i) //i - key
{
	if (i < m_digit)
		return '0' + i;
	else
		return i - m_digit + 'a';
}

void f(char *s, int n, char *sout)
{
	int counters[m_alp + m_digit];
	int i;
	int k;

	for (i = 0; i < m; i++)
	{
		counters[i] = 0;
	}

	for (i = 0; i < n; i++)
	{
		counters[key(s[i])]++;
	}

	k = 0;
	for (i = 0; i < m; i++)
	for (int j = 0; j < counters[i]; j++)
	{
		sout[k++] = inv_key(i);
	}

	sout[k] = '\0';
}

void main()
{
	char buf[1000], bufout[1000];
	gets(buf);

	f(buf, strlen(buf), bufout);

	puts("");

	puts(bufout);
}