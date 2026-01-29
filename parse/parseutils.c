/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseutils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfuto <kfuto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 02:22:54 by kfuto             #+#    #+#             */
/*   Updated: 2026/01/11 02:22:54 by kfuto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	ft_ispipe(char c, t_mini *mini)
{
	if (c == '|')
	{
		mini->is_pipe = 1;
		return (1);
	}
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

int	ft_ischev(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
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

int	has_single_quotes(char *s)
{
	while (*s)
	{
		if (*s == '\'')
			return (0);
		s++;
	}
	return (1);
}
