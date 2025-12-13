/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabalvar <pabalvar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 12:37:33 by djareno           #+#    #+#             */
/*   Updated: 2025/12/04 13:36:23 by pabalvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void parser(const char *s)
{
	char	**t;
	int		j = 0;

	t_mini mini;
	mini.nodes = malloc(sizeof(t_node) * 1024);
	mini.nodes->tokens = malloc(sizeof(char *) * 1024);
	
	t = get_nodes(s);
	for (int i = 0; t[i] && t[j]; i++)
	{
		j = 0;
		while (t[j])
		{
			mini.nodes[i].tokens[j] = ft_strdup(t[j]);
			printf("node %d: %s\n", j,	mini.nodes[i].tokens[j]);
			j++;
		}
	}
}

static int ft_count_words(const char *s)
{
	int	count;

	if (!*s)
		return (0);
	count = 0;
	while (*s)
	{
		while (*s && ft_isspace(*s))
			s++;
		if (*s)
			count++;
		while (!ft_isspace(*s) && *s)
			s++;
	}
	return (count);
}

int get_quotes(char *s)
{
	int quote = 0;
	int i = 0;
	while (s[i])
	{
		if (ft_isquote(s[i]))
			{
				quote++;
				i++;
			}
		i++;
	}
	if (quote == 0)
		return -1;
	if (quote != 0 && quote % 2 == 0)
		return 1;
	return 0;
}



char	**get_nodes(const char *s)
{
	int i = 0;
	char **nodes;
	const char *start;
	int len;
	nodes = malloc(sizeof(char *) * 1024);
	if (!nodes)
		return (NULL);
	if (get_quotes((char *)s) == 1)
	{
		while (*s)
		{
			while (*s && ft_isquote(*s))
				s++;
			if (*s && !ft_isquote(*s))
			{	
				start = s;
				len = 0;
				while (s[len] && !ft_isquote(s[len]))
					len++;
				nodes[i++] = word_dup(start, len);
				s += len;
			}
			}
	}
	else
	{
	while (*s)
	{
		while (*s && (ft_isspace(*s) || ft_ispipe(*s)))
			s++;
		if (*s && !ft_isspace(*s) && !ft_ispipe(*s))
		{
			start = s;
			len = 0;
			while (s[len] && !ft_ispipe(s[len]))
				len++;
			nodes[i++] = word_dup(start, len);
			s += len;
		}
	}
	}
	nodes[i] = NULL;
	return (nodes);
}

char	**tokenizer(const char *s)
{
	int			words;
	char		**tokens;
	int			i;
	const char	*start;
	int			len;

	words = ft_count_words(s);
	tokens = malloc(sizeof(char *) * (words + 1));
	i = 0;
	if (!tokens)
		return (NULL);
	while (*s)
	{
		while (*s && ft_isspace(*s))
			s++;
		if (*s && !ft_isspace(*s))
		{
			start = s;
			len = 0;
			while (s[len] && !ft_isspace(s[len]))
				len++;
			tokens[i++] = word_dup(start, len);
			s += len;
		}
	}
	tokens[i] = NULL;
	return (tokens);
}

//Hacer que divida por pipes etc y demas, pipex????????¿¿¿¿¿¿