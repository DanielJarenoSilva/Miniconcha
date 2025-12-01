/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:47:08 by djareno           #+#    #+#             */
/*   Updated: 2025/04/22 10:41:47 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(const char *s, char c)
{
	size_t	count;

	if (!*s)
		return (0);
	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s != c && *s)
			s++;
	}
	return (count);
}

static char	**ft_free_matrix(const char **split, size_t len)
{
	while (len--)
		free ((void *) split[len]);
	free (split);
	return (NULL);
}

static int	ft_split_loop(const char **split, char const *s, char c, int len)
{
	int		x;
	size_t	word_l;

	x = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			if (ft_strchr(s, c))
				word_l = ft_strchr(s, c) - s;
			else
				word_l = ft_strlen(s);
			split[x] = ft_substr(s, 0, word_l);
			if (!split[x])
				return (ft_free_matrix(split, len), 0);
			x++;
			s += word_l;
		}
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	const char	**split;
	int			len;

	if (!s)
		return (0);
	len = ft_count_words(s, c);
	split = (const char **)ft_calloc(len + 1, sizeof(char *));
	if (!split)
		return (0);
	if (!ft_split_loop(split, s, c, len))
		return (0);
	return ((char **)split);
}
