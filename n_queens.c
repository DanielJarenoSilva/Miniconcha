#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_N 15

static int	cols[MAX_N]; 

static int	safe(int c, int r)
{
	int	i;
	int	diff;

	for (i = 0; i < c; ++i)
	{
		if (cols[i] == r)
			return (0);
		diff = cols[i] - r;
		if (diff < 0)
			diff = -diff;
		if (diff == (c - i))
			return (0);
	}
	return (1);
}

static void	print_solution(int n)
{
	int		i;
	char	buf[4 * MAX_N];
	int		p;
	int		x;
	char	tmp[16];
	int		t;
	int		xx;
	char	rev[16];
	int		rv;
	int		j;

	p = 0;
	for (i = 0; i < n; ++i)
	{
		x = cols[i];
		t = 0;
		if (x == 0)
			tmp[t++] = '0';
		else
		{
			xx = x;
			rv = 0;
			while (xx > 0)
			{
				rev[rv++] = '0' + (xx % 10);
				xx /= 10;
			}
			while (rv > 0)
				tmp[t++] = rev[--rv];
		}
		tmp[t] = '\0';
		j = 0;
		while (tmp[j])
			buf[p++] = tmp[j++];
		if (i + 1 < n)
			buf[p++] = ' ';
	}
	buf[p++] = '\n';
	write(1, buf, p);
}

static void	solve(int c, int n)
{
	int	r;

	if (c == n)
	{
		print_solution(n);
		return ;
	}
	for (r = 0; r < n; ++r)
	{
		if (safe(c, r))
		{
			cols[c] = r;
			solve(c + 1, n);
		}
	}
}

int	main(int argc, char **argv)
{
	int	n;

	if (argc != 2)
		return (0);
	n = atoi(argv[1]);
	if (n <= 0 || n > MAX_N)
		return (0);
	solve(0, n);
	return (0);
}
