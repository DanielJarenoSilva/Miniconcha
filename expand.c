/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 11:00:58 by djareno           #+#    #+#             */
/*   Updated: 2025/12/04 13:30:30 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*expand_var(char	*str, int *i, char **envp)
{
	char	*key;
	char	*value;
	int		start;
	int		len;
	int		j;

	(*i)++;
	if (str[*i] == '?')
	{
		(*i)++;
		printf("0");//Cambiar 0 por exit_code
		return (ft_strdup("0"));
	}
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
	value = get_env_value(envp, key);
	return (free(key), value);
}

char	*expand_token(char *str, char **envp)
{
	int		i;
	char	*result;
	char	*tmp;
	int		start;
	int		j;

	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			start = ++i;
			while (str[i] && str[i] != '\'')
				i++;
			tmp = malloc(i - start + 1);
			j = 0;
			while (j < i - start)
			{
				tmp[j] = str[start + j];
				j++;
			}
			tmp[j] = '\0';
			result = ft_strjoin(tmp, result);
			free(tmp);
		}
	}
}
