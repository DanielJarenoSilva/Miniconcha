/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 13:14:13 by djareno           #+#    #+#             */
/*   Updated: 2026/01/20 12:38:36 by djareno          ###   ########.fr       */
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

static char	*get_cd_path(char **cmd)
{
	char	*path;

	if (!cmd[1])
	{
		path = ft_getenv(NULL, "HOME");
		if (!path)
		{
			write(2, "cd: HOME not set\n", 17);
			return (NULL);
		}
	}
	else
		path = cmd[1];
	return (path);
}

static int	change_dir(char *path, t_mini *mini)
{
	char	*oldpwd;

	oldpwd = ft_getenv(mini->envp, "PWD");
	if (chdir(path) == -1)
	{
		perror("cd");
		free(oldpwd);
		return (1);
	}
	set_env(mini->envp, "OLDPWD", oldpwd);
	free(oldpwd);
	return (0);
}

static int	update_pwd(t_mini *mini)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("cd");
		return (1);
	}
	set_env(mini->envp, "PWD", cwd);
	free(cwd);
	return (0);
}

void	cd(t_mini *mini, char **cmd)
{
	char	*path;

	path = get_cd_path(cmd);
	if (!path)
	{
		mini->exit_code = 1;
		return ;
	}
	if (change_dir(path, mini))
	{
		if (!cmd[1])
			free(path);
		mini->exit_code = 1;
		return ;
	}
	if (update_pwd(mini))
	{
		if (!cmd[1])
			free(path);
		mini->exit_code = 1;
		return ;
	}
	if (!cmd[1])
		free(path);
	mini->exit_code = 0;
}
