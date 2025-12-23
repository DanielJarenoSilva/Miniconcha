/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabalvar <pabalvar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 12:37:33 by djareno           #+#    #+#             */
/*   Updated: 2025/12/15 11:35:49 by pabalvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	ft_count_words(const char *s)
{
	int	count;

	if (!*s)
		return (0);
	count = 0;
	while (*s)
	{
		while (*s &&ft_isspace(*s))
			s++;
		if (*s)
			count++;
		while (!ft_isspace(*s) && *s)
			s++;
	}
	return (count);
}

static char	*word_dup(const char *start, int len)
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
