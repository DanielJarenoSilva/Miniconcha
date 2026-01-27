/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseutils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:49:35 by kfuto             #+#    #+#             */
/*   Updated: 2026/01/27 12:00:36 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	*handle_single_quote(char *str, int *i, char *result)
{
	int		start;
	char	*tmp;

	start = ++(*i);
	while (str[*i] && str[*i] != '\'')
		(*i)++;

	tmp = ft_substr(str, start, *i - start);
	result = ft_strjoin_free(result, tmp);
	free(tmp);

	if (str[*i] == '\'')
		(*i)++;
	return (result);
}

char	*handle_double_quote(char *str, int *i, char *result, t_mini *mini)
{
	char	*tmp;

	(*i)++;
	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '$' && str[*i + 1] &&
			(ft_isalnum(str[*i + 1]) || str[*i + 1] == '_'
				|| str[*i + 1] == '?'))
		{
			tmp = expand_var(str, i, mini);
			result = ft_strjoin_free(result, tmp);
			free(tmp);
		}
		else
			result = ft_strjoin_char_free(result, str[(*i)++]);
	}
	if (str[*i] == '"')
		(*i)++;
	return (result);
}

int	get_quotes(const char *s)
{
	char	quote;
	int		i;

	quote = 0;
	i = 0;
	while (s[i])
	{
		if (!quote && ft_isquote(s[i]))
			quote = s[i];
		else if (quote && s[i] == quote)
			quote = 0;
		i++;
	}
	if (quote)
		return (0);
	return (1);
}
