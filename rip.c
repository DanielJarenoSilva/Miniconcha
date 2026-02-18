#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int	my_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

static char	*remove_char(const char *s, int pos)
{
	int		n;
	char	*t;

	n = my_strlen(s);
	t = malloc(n);
	if (!t)
		return (NULL);
	int i, k = 0;
	for (i = 0; i < n; ++i)
	{
		if (i == pos)
			continue ;
		t[k++] = s[i];
	}
	t[k] = '\0';
	return (t);
}

static char	*str_reverse(const char *s)
{
	int		n;
	char	*t;
	int		i;

	n = my_strlen(s);
	t = malloc(n + 1);
	if (!t)
		return (NULL);
	for (i = 0; i < n; ++i)
		t[i] = s[n - 1 - i];
	t[n] = '\0';
	return (t);
}

static void	remove_invalid(char *s, int last_i, int last_j, char par0,
		char par1)
{
	int		stack;
	int		j;
	char	*t;
	char	*rev;
	int		i;
	int		n;

	stack = 0;
	n = my_strlen(s);
	for (i = last_i; i < n; ++i)
	{
		if (s[i] == par0)
			stack++;
		if (s[i] == par1)
			stack--;
		if (stack >= 0)
			continue ;
		for (j = last_j; j <= i; ++j)
		{
			if (s[j] == par1 && (j == last_j || s[j - 1] != par1))
			{
				t = remove_char(s, j);
				if (t)
				{
					remove_invalid(t, i, j, par0, par1);
					free(t);
				}
			}
		}
		return ;
	}
	rev = str_reverse(s);
	if (!rev)
		return ;
	if (par0 == '(')
		remove_invalid(rev, 0, 0, ')', '(');
	else
		puts(rev);
	free(rev);
}

int	main(int argc, char **argv)
{
	char	*s;
	int		i;

	if (argc != 2)
		return (1);
	s = argv[1];
	i = 0;
	while (s[i])
	{
		if (s[i] != '(' && s[i] != ')' && s[i] != ' ')
			return (1);
		i++;
	}
	remove_invalid(s, 0, 0, '(', ')');
	return (0);
}
