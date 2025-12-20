/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 11:55:22 by djareno           #+#    #+#             */
/*   Updated: 2025/12/19 11:18:19 by djareno          ###   ########.fr       */
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

char	*read_fd(int fd)
{
	char	*line;
	char	*res;

	res = NULL;
	line = get_next_line(fd);
	while (line)
	{
		res = ft_strjoin_free(res, line);
		line = get_next_line(fd);
	}
	return (res);
}

void exec_cmd(char **tokens, char **envp)
{
    char **path_dirs = get_path_dirs(envp);
    char *path_cmd = find_cmd(tokens[0], path_dirs);
    if (!path_cmd)
    {
        fprintf(stderr, "Command not found: %s\n", tokens[0]);
        exit(127);
    }
    execve(path_cmd, tokens, envp);
    perror("execve");
    exit(1);
}

char *save_exec_cmd(char **tokens, t_mini mini)
{
    int fd[2];
    pid_t pid;
    int status;
    char *res;

    if (pipe(fd) == -1)
        return NULL;
    pid = fork();
    if (pid == 0)
    {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        exec_cmd(tokens, mini.envp);
        perror("execve");
        exit(1);
    }
    close(fd[1]);
    res = read_fd(fd[0]);
    close(fd[0]);
    waitpid(pid, &status, 0);
    return res;
}
