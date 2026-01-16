/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 13:14:13 by djareno           #+#    #+#             */
/*   Updated: 2026/01/07 15:41:10 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

int	set_env(char **envp, const char *key, const char *value)
{
	int		i;
	int		key_len;
	char	*new_entry;

	i = 0;
	key_len = ft_strlen(key);
	new_entry = malloc(key_len + 1 + strlen(value) + 1);
	if (!new_entry)
		return (-1);
	strcpy(new_entry, key);
	new_entry[key_len] = '=';
	strcpy(new_entry + key_len + 1, value);
	while (envp[i])
	{
		if (strncmp(envp[i], key, key_len) == 0 && envp[i][key_len] == '=')
		{
			free(envp[i]);
			envp[i] = new_entry;
			return (0);
		}
		i++;
	}
	free(new_entry);
	return (1);
}

void	cd(t_mini *mini, char **cmd)
{
	char	*tmp;

	if (!cmd[1])
	{
		tmp = ft_getenv(mini->envp, "PWD");
		set_env(mini->envp, "OLDPWD", tmp);
		free(tmp);
		tmp = ft_getenv(mini->envp, "HOME");
		tmp = ft_strjoin("/", tmp);
		chdir(tmp);
		set_env(mini->envp, "PWD", tmp);
		free(tmp);
	}
	else
	{
		tmp = ft_getenv(mini->envp, "PWD");
		set_env(mini->envp, "OLDPWD", tmp);
		free(tmp);
		chdir(cmd[1]);
		tmp = malloc(1024);
		getcwd(tmp, 1024);
		set_env(mini->envp, "PWD", tmp);
		free(tmp);
	}
	mini->exit_code = 0;
}
