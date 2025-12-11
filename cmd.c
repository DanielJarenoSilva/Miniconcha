/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 11:55:22 by djareno           #+#    #+#             */
/*   Updated: 2025/12/10 10:44:37 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_path(char *dir, char *cmd)
{
	char	*temp;
	char	*full;

	temp = ft_strjoin(dir, "/");
	full = ft_strjoin(temp, cmd);
	free(temp);
	return (full);
}

char	**get_path_dirs(char **envp)
{
	int		i;
	char	**dirs;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	dirs = ft_split(envp[i] + 5, ':');
	return (dirs);
}

char	*find_cmd(char *cmd, char **path_dirs)
{
	char	*full_path;
	int		i;

	i = 0;
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	while (path_dirs[i])
	{
		full_path = join_path(path_dirs[i], cmd);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

void	exec_cmd(const char *cmdline, char **envp)
{
	char	**split;
	char	**path_dirs;
	char	*path_cmd;

	split = ft_split(cmdline, ' ');
	path_dirs = get_path_dirs(envp);
	path_cmd = find_cmd(split[0], path_dirs);
	if (!path_cmd)
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putstr_fd(split[0], 2);
		ft_putstr_fd("\n", 2);
		exit(127);
	}
	execve(path_cmd, split, envp);
	perror("execve");
	exit(1);
}
