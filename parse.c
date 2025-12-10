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

//Hacer que divida por pipes etc y demas, pipex????????¿¿¿¿¿¿