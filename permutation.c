
#include <stdio.h>
#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	index;

	index = 0;
	while (str[index])
		index++;
	return (index);
}

void	ft_sort(char *str)
{
	int		x;
	int		y;
	char	t;

	x = 0;
	while (str[x])
	{
		y = x + 1;
		while (str[y])
		{
			if (str[x] > str[y])
			{
				t = str[x];
				str[x] = str[y];
				str[y] = t;
			}
			y++;
		}
		x++;
	}
}

void	permutations(char *str, char *res, int len, int pos, int *used)
{
	int	index;

	if (pos == len)
	{
		res[pos] = '\0';
		puts(res);
		return ;
	}
	index = 0;
	while (str[index])
	{		
		if (!used[index])
		{		
			used[index] = 1;
		
			res[pos] = str[index];
			permutations(str, res, len, pos + 1, used);
			used[index] = 0;
		}
		index++;
	}
}

int	main(int argc, char *argv[])
{
	char	*str;
	char	*res;
	char	len;
	int		*used;

	if (argc != 2)
		return (1);
	str = argv[1];
	len = ft_strlen(str);
	res = (char *)malloc(len * sizeof(char));
	used = calloc(len, sizeof(int));
	ft_sort(str);
	permutations(str, res, len, 0, used);
	free(res);
	free(used);
	return (0);
}
