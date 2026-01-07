/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 14:30:56 by djareno           #+#    #+#             */
/*   Updated: 2026/01/07 14:31:27 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

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

char	*join_path(char	*dir, char *cmd)
{
	int		len_dir;
	int		len_cmd;
	int		add_slash;
	char	*full_path;

	len_dir = ft_strlen(dir);
	len_cmd = ft_strlen(cmd);
	add_slash = (dir[len_dir - 1] != '/');
	full_path = malloc(len_dir + len_cmd + add_slash + 1);
	if (!full_path)
		return (NULL);
	ft_strlcpy(full_path, dir, len_dir + 1);
	if (add_slash)
		full_path[len_dir] = '/';
	ft_strlcpy(full_path + len_dir + add_slash, cmd, len_cmd + 1);
	return (full_path);
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

char	*read_fd(int fd)
{
	char	*line;
	char	*res;
	char	*tmp;

	res = ft_strdup("");
	if (!res)
		return (NULL);

	while ((line = get_next_line(fd)))
	{
		tmp = ft_strjoin_free(res, line);
		if (!tmp)
		{
			free(res);
			return (NULL);
		}
		res = tmp;
	}
	close(fd);
	return (res);
}