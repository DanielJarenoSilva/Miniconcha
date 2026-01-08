/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 13:14:46 by djareno           #+#    #+#             */
/*   Updated: 2026/01/07 15:48:00 by djareno          ###   ########.fr       */
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

char	**new_env(t_mini *mini, char *key, char *value)
{
	int		len;
	int		k;
	char	**new_env;

	k = 0;
	len = env_len(mini->envp);
	new_env = malloc(sizeof(char *) * (len + 2));
	while (k < len)
	{
		new_env[k] = mini->envp[k];
		k++;
	}
	new_env[len] = ft_strjoin(key, "=");
	new_env[len] = ft_strjoin_free(new_env[len], ft_strdup(value));
	new_env[len + 1] = NULL;
	free(mini->envp);
	return (new_env);
}

void	export(t_mini *mini, char	**tokens)
{
	int		i;
	char	*key;
	char	*value;
	char	*eq;

	i = 1;
	while (tokens[i])
	{
		eq = ft_strchr(tokens[i], '=');
		if (!eq)
		{
			i++;
			continue ;
		}
		key = ft_substr(tokens[i], 0,
				eq - tokens[i]);
		value = eq + 1;
		if (set_env(mini->envp, key, value) == 1)
			mini->envp = new_env(mini, key, value);
		free(key);
		i++;
	}
}
