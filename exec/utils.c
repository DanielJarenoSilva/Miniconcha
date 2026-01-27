/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:33:51 by djareno           #+#    #+#             */
/*   Updated: 2026/01/27 12:05:59 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	**dup_env(char **envp)
{
	int		i;
	char	**copy;

	i = 0;
	while (envp[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		copy[i] = ft_strdup(envp[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

char	*ft_getenv(char **envp, char *env)
{
	int		i;
	size_t	len;

	if (!envp || !env)
		return (NULL);

	len = ft_strlen(env);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], env, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

void	ft_free_matrix(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

void	print_error_cmd(char *cmd)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 20);
}

void	update_shlvl(t_mini *mini)
{
	char	*lvl;
	char	*tmp;
	int		n;

	lvl = ft_getenv(mini->envp, "SHLVL");
	if (!lvl)
	{
		set_env(mini->envp, "SHLVL", "1");
		return ;
	}
	tmp = ft_strdup(lvl);
	n = ft_atoi(tmp);
	free(tmp);
	n++;
	tmp = ft_itoa(n);
	set_env(mini->envp, "SHLVL", tmp);
	free(tmp);
}
