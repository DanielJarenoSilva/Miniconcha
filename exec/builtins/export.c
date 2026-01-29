/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 13:14:46 by djareno           #+#    #+#             */
/*   Updated: 2026/01/29 10:25:56 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

static int	env_len(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
		i++;
	return (i);
}

char	*join_key_value(char *key, char *value)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(key, "=");
	result = ft_strjoin_free(tmp, value);
	return (result);
}

char	**new_env(t_mini *mini, char *key, char *value)
{
	int		len;
	int		k;
	char	**new_env;

	len = env_len(mini->envp);
	new_env = malloc(sizeof(char *) * (len + 2));
	if (!new_env)
		return (NULL);
	k = 0;
	while (k < len)
	{
		new_env[k] = ft_strdup(mini->envp[k]);
		k++;
	}
	new_env[len] = join_key_value(key, value);
	new_env[len + 1] = NULL;
	k = 0;
	while (k < len)
	{
		free(mini->envp[k]);
		k++;
	}
	free(mini->envp);
	return (new_env);
}

void	empty_export(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->envp && mini->envp[i])
	{
		printf("declare -x \"%s\"\n", mini->envp[i]);
		i++;
	}
	return ;
}

void	export(t_mini *mini, char	**tokens)
{
	int		i;
	char	*key;
	char	*value;
	char	*eq;

	if (!tokens[1])
		return (empty_export(mini));
	i = 1;
	while (tokens[i])
	{
		eq = ft_strchr(tokens[i], '=');
		if (!eq || !*(eq + 1))
		{
			i++;
			continue ;
		}
		key = ft_substr(tokens[i], 0, eq - tokens[i]);
		value = eq + 1;
		if (set_env(mini->envp, key, value) == 1)
			mini->envp = new_env(mini, key, value);
		free(key);
		i++;
	}
}
