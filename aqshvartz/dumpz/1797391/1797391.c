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

void f_2()
{
	int counters[m_alp + m_digit];
	int i;
	int k;

	char c;

	for (i = 0; i < m; i++)
	{
		counters[i] = 0;
	}

	while ((c = getchar()) != '\n')
	{
		counters[key(c)]++;
	}


	k = 0;
	for (i = 0; i < m; i++)
	for (int j = 0; j < counters[i]; j++)
	{
		putchar(inv_key(i));
	}
}

void main()
{
	f_2();

	puts("");
	//system("pause");
}