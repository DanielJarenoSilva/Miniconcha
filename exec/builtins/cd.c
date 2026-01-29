/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 13:14:13 by djareno           #+#    #+#             */
/*   Updated: 2026/01/29 12:18:28 by djareno          ###   ########.fr       */
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

char	*get_cd_path(char **cmd, char **envp)
{
	char	*home;
	char	*oldpwd;

	if (!cmd[1] || ft_strncmp(cmd[1], "~", 2) == 0)
	{
		home = ft_getenv(envp, "HOME");
		if (!home)
			return (NULL);
		return (home);
	}
	else if (ft_strncmp(cmd[1], "-", 2) == 0)
	{
		oldpwd = ft_getenv(envp, "OLDPWD");
		if (!oldpwd)
			return (NULL);
		return (oldpwd);
	}
	else
		return (ft_strdup(cmd[1]));
}

static int	change_dir(char *path, t_mini *mini)
{
	char	*oldpwd;
	char	*oldpwd_dup;

	oldpwd = ft_getenv(mini->envp, "PWD");
	if (!oldpwd)
		oldpwd_dup = ft_strdup("");
	else
		oldpwd_dup = ft_strdup(oldpwd);
	if (chdir(path) == -1)
	{
		perror("cd");
		free(oldpwd_dup);
		return (1);
	}
	set_env(mini->envp, "OLDPWD", oldpwd_dup);
	free(oldpwd_dup);
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

	path = get_cd_path(cmd, mini->envp);
	if (!path)
	{
		mini->exit_code = 1;
		return ;
	}
	if (change_dir(path, mini) || update_pwd(mini))
	{
		if (path && path != ft_getenv(mini->envp, "HOME")
			&& path != ft_getenv(mini->envp, "OLDPWD"))
			free(path);
		mini->exit_code = 1;
		return ;
	}
	if (path && path != ft_getenv(mini->envp, "HOME")
		&& path != ft_getenv(mini->envp, "OLDPWD"))
		free(path);
	mini->exit_code = 0;
}
