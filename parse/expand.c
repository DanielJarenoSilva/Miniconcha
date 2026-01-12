/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 11:00:58 by djareno           #+#    #+#             */
/*   Updated: 2026/01/12 15:18:51 by djareno          ###   ########.fr       */
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

char	*expand_token(char *str, t_mini *mini)
{
	int		i;
	char	*result;

	i = 0;
	result = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '\'')
			result = handle_single_quote(str, &i, result);
		else if (str[i] == '"')
			result = handle_double_quote(str, &i, result, mini);
		else if (str[i] == '$' && str[i + 1] && (ft_isalnum(str[i + 1])
				|| str[i + 1] == '_' || str[i + 1] == '?'))
			result = ft_strjoin_free(result, expand_var(str, &i, mini));
		else
			result = ft_strjoin_char_free(result, str[i++]);
	}
	return (result);
}
