/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfuto <kfuto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 13:14:46 by djareno           #+#    #+#             */
/*   Updated: 2026/01/23 17:44:22 by kfuto            ###   ########.fr       */
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

void	empty_export(t_mini *mini)
{
	char	**sorted;
	int		i;

	if (!mini->envp)
		return ;
	sorted = copy_envp(mini->envp);
	if (!sorted)
		return ;
	sort_envp(sorted);
	i = 0;
	while (sorted[i])
	{
		printf("declare -x \"%s\"\n", sorted[i]);
		free(sorted[i]);
		i++;
	}
	free(sorted);
}

void	export(t_mini *mini, char **tokens)
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
		if (!*(eq + 1))
			break ;
		if (!eq)
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
