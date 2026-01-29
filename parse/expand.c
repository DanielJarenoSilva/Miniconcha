/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 11:00:58 by djareno           #+#    #+#             */
/*   Updated: 2026/01/29 10:34:26 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	*get_env_value(char **envp, char *key)
{
	int		i;
	size_t	key_len;

	i = 0;
	key_len = ft_strlen(key);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, key_len) == 0 && envp[i][key_len] == '=')
			return (ft_strdup(envp[i] + key_len + 1));
		i++;
	}
	return (ft_strdup(""));
}

static int	expand_exit_code(char *str, int *i)
{
	if (str[*i] == '?')
	{
		(*i)++;
		return (1);
	}
	return (0);
}

char	*expand_var(char *str, int *i, t_mini *mini)
{
	char	*key;
	char	*value;
	int		start;
	int		len;
	int		j;

	(*i)++;
	if (expand_exit_code(str, i))
		return (ft_itoa((*mini).exit_code));
	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	len = *i - start;
	key = malloc(len + 1);
	if (!key)
		return (NULL);
	j = 0;
	while (j < len)
	{
		key[j] = str[start + j];
		j++;
	}
	key[len] = '\0';
	value = get_env_value((*mini).envp, key);
	return (free(key), value);
}

char	*join_expanded_var(char *str, int *i, char *res, t_mini *mini)
{
	char	*tmp;
	char	*val;

	val = expand_var(str, i, mini);
	if (!val)
		return (NULL);
	tmp = ft_strjoin_free(res, val);
	free(val);
	return (tmp);
}

char	*expand_token(char *str, t_mini *mini)
{
	int		i;
	char	*res;
	char	*tmp;

	i = 0;
	res = ft_strdup("");
	if (!res)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'')
			tmp = handle_single_quote(str, &i, res);
		else if (str[i] == '"')
			tmp = handle_double_quote(str, &i, res, mini);
		else if (str[i] == '$' && str[i + 1]
			&& (ft_isalnum(str[i + 1])
				|| str[i + 1] == '_' || str[i + 1] == '?'))
			tmp = join_expanded_var(str, &i, res, mini);
		else
			tmp = ft_strjoin_char_free(res, str[i++]);
		if (!tmp)
			return (free(res), NULL);
		res = tmp;
	}
	return (res);
}
