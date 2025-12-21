#include "parse.h"


int	ft_ispipe(char c)
{
	if (c == '|')
		return (1);
	return (0);
}

int	ft_isquote(char c)
{
	if (c == '\'')
		return (1);
	if (c == '\"')
		return (2);
	return (0);
}

int ft_ischev(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int	ft_count_nodes(const char *s)
{
	int count;

	if (!*s)
		return (0);
	count = 0;
	while (*s)
	{
		if (*s && (ft_isquote(*s)))
		{
			s++;
			while (*s && !ft_isquote(*s))
				s++;
			if (ft_isquote(*s))
			{
				count++;
				s++;
			}
		}
		while (*s && (ft_ispipe(*s)))
		{
			s++;
			if (*s)
				count++;
		}
		while (!ft_ispipe(*s) && *s)
			s++;
	}
	printf("Counted nodes: %d\n", count);
	return (count);
}

char	*word_dup(const char *start, int len)
{
	char *word;
	int i;

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

int	has_single_quotes(char *s)
{
	while (*s)
	{
		if (*s == '\'')
			return (1);
		s++;
	}
	return (0);
}

void	expand_tokens(t_node *node, t_mini mini)
{
	int		i;
	char	*tmp;

	if (!node->expand)
		return ;

	i = 0;
	while (node->tokens[i])
	{
		tmp = expand_token(node->tokens[i], mini);
		free(node->tokens[i]);
		node->tokens[i] = tmp;
		i++;
	}
}
