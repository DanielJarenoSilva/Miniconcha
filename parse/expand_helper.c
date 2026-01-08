/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfuto <kfuto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 17:17:25 by kfuto             #+#    #+#             */
/*   Updated: 2026/01/08 19:30:52 by kfuto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*str;
	size_t	i;

	if (!s1)
		s1 = ft_strdup("");
	if (!s2)
		s2 = ft_strdup("");
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	i = 0;
	if (!str)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		str[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < ft_strlen(s2))
	{
		str[ft_strlen(s1) + i] = s2[i];
		i++;
	}
	str[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	return (free(s1), free(s2), str);
}

char	*ft_strjoin_char_free(char *s, char c)
{
	char	*s2;

	s2 = malloc(2);
	s2[0] = c;
	s2[1] = '\0';
	return (ft_strjoin_free(s, s2));
}

char	*handle_single_quote(char *str, int *i, char *result)
{
	int		start;
	char	*tmp;

	start = ++(*i);
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	tmp = ft_substr(str, start, *i - start);
	result = ft_strjoin_free(result, tmp);
	if (str[*i] == '\'')
		(*i)++;
	return (result);
}

char	*handle_double_quote(char *str, int *i, char *result, t_mini *mini)
{
	(*i)++;
	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '$' && str[*i + 1] && (ft_isalnum(str[*i + 1])
				|| str[*i + 1] == '_' || str[*i + 1] == '?'))
			result = ft_strjoin_free(result, expand_var(str, i, mini));
		else
			result = ft_strjoin_char_free(result, str[(*i)++]);
	}
	if (str[*i] == '"')
		(*i)++;
	return (result);
}
