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

char	**parser(const char *s)
{
	int			words;
	char		**nodes;
	int			i;
	const char	*start;
	int			len;

	words = ft_count_nodes(s);
	nodes = malloc(sizeof(char *) * (words + 1));
	i = 0;
	if (!nodes)
		return (NULL);
	while (*s)
	{
		while (*s && (ft_isspace(*s) || ft_isnode(*s)))
			s++;
		if (*s && !ft_isspace(*s) && !ft_isnode(*s))
		{
			start = s;
			len = 0;
			while (s[len] && !ft_isnode(s[len]))
				len++;
			nodes[i++] = word_dup(start, len);
			s += len;
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