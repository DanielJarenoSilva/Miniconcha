/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 13:14:46 by djareno           #+#    #+#             */
/*   Updated: 2026/02/12 14:40:44 by djareno          ###   ########.fr       */
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
	char	*value;
	char	**fvalue;

	sort_envp(mini->envp);
	if (!tokens[1])
		return (empty_export(mini));
	i = 1;
	value = ft_strdup("");
	while (tokens[i])
	{
		if (i != 1)
			value = ft_strjoin_char_free(value, ' ');
		value = ft_strjoin_free(value, tokens[i]);
		i++;
	}
	fvalue = ft_split(value, '=');
	free(value);
	if (set_env(mini->envp, fvalue[0], fvalue[1]) == 1)
		mini->envp = new_env(mini, fvalue[0], fvalue[1]);
	ft_free_matrix(fvalue);
	mini->exit_code = 0;
}
