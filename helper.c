#include "minishell.h"

static int ft_ispipe(char c)
{
    if (c == '|')
        return (1);
    return (0);
}

static int ft_isquote(char c)
{
    if (c == '\'' || c == '"')
        return (1);
    return (0);
}

int ft_isnode(char c)
{
    if (ft_ispipe(c) || ft_isquote(c))
        return (1);
    return (0);
}

int	ft_count_nodes(const char *s)
{
	int	count;

	if (!*s)
		return (0);
	count = 0;
	while (*s)
	{
		while (*s && (ft_isnode(*s)))
			s++;
		if (*s)
			count++;
		while (!ft_isnode(*s) && *s)
			s++;
	}
	return (count);
}

char	*word_dup(const char *start, int len)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = start[i];
		i++;
	}
	word[len] = '\0';
	return (word);
}