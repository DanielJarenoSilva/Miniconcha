/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 11:00:58 by djareno           #+#    #+#             */
/*   Updated: 2025/12/09 11:28:53 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	size_t		len1;
	size_t		len2;
	char		*str;
	size_t		i;

	if (!s1)
		s1 = ft_strdup("");
	if (!s2)
		s2 = ft_strdup("");
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = malloc(len1 + len2 + 1);
	i = 0;
	if (!str)
		return (NULL);
	while (i < len1)
	{
		str[i] = s1[i];
		i++;
	}
	i = 0;

	while (i < len2)
	{
		str[len1 + i] = s2[i];
		i++;
	}
	str[len1 + len2] = '\0';
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
			tmp[i - start] = '\0';
			result = ft_strjoin_free(result, tmp);
			if (str[i] == '\'')
				i++;
			continue ;
		}
		if (str[i] == '"')
		{
			i++;
			while (str[i] && str[i] != '"')
			{
				if (str[i] == '$')
					result = ft_strjoin_free(result, expand_var(str, &i, envp));
				else
					result = ft_strjoin_char_free(result, str[i++]);
			}
			if (str[i] == '"')
				i++;
			continue ;
		}
		if (str[i] == '$')
		{
			result = ft_strjoin_free(result, expand_var(str, &i, envp));
			continue ;
		}
		result = ft_strjoin_char_free(result, str[i++]);
	}
	return (result);
}
