/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseutils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfuto <kfuto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:49:35 by kfuto             #+#    #+#             */
/*   Updated: 2026/01/12 16:45:36 by kfuto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	*handle_single_quote(char *str, int *i, char *result)
{
	int	start;

	start = ++(*i);
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	result = ft_strjoin_free(result, ft_substr(str, start, *i - start));
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

char	*word_dup_no_quotes(const char *s, int len)
{
	char	*out;
	int		i;
	int		j;
	char	quote;

	quote = 0;
	out = malloc(len + 1);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (!quote && (s[i] == '"' || s[i] == '\''))
			quote = s[i++];
		else if (quote && s[i] == quote)
		{
			quote = 0;
			i++;
		}
		else
			out[j++] = s[i++];
	}
	out[j] = '\0';
	return (out);
}

void	skip_token_quotes(const char *s, int *i, struct s_mini *mini)
{
	char	quote;

	quote = 0;
	while (s[*i] && (quote || (!ft_isspace(s[*i]) && !ft_ischev(s[*i]))))
	{
		if (!quote && (s[*i] == '"' || s[*i] == '\''))
			quote = s[*i];
		else if (quote && s[*i] == quote)
			quote = 0;
		(*i)++;
	}
	if (quote != 0)
		mini->builtin_quote = 1;
}
