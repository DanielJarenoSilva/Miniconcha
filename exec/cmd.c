/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 11:55:22 by djareno           #+#    #+#             */
/*   Updated: 2025/12/23 15:36:40 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	is_builtin(char *cmd)
{
	return (ft_strncmp(cmd, "cd", ft_strlen("cd")) == 0
		|| ft_strncmp(cmd, "echo", ft_strlen("echo")) == 0
		|| ft_strncmp(cmd, "pwd", ft_strlen("pwd")) == 0
		|| ft_strncmp(cmd, "exit", ft_strlen("exit")) == 0
		|| ft_strncmp(cmd, "export", ft_strlen("export")) == 0
		|| ft_strncmp(cmd, "unset", ft_strlen("unset")) == 0);
}

int	exec_builtin(char **tokens, t_mini mini)
{
	if (ft_strncmp(tokens[0], "pwd", ft_strlen("pwd")) == 0)
		return (pwd(mini), 0);
	else if (ft_strncmp(tokens[0], "cd", ft_strlen("cd")) == 0)
		return (cd(mini, tokens), 0);
	else if (ft_strncmp(tokens[0], "exit", ft_strlen("exit")) == 0)
		return (my_exit(mini), 0);
	return (1);
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
	char	*res = ft_strdup(""); 
	char	*tmp;

	if (!res)
		return NULL;

	while ((line = get_next_line(fd)))
	{
		tmp = ft_strjoin_free(res, line); 
		if (!tmp)
		{
			free(res);
			return NULL;
		}
		res = tmp;
	}
	close(fd);
	return (res);
}


void	exec_cmd(char **tokens, t_mini mini)
{
	char	**path_dirs;
	char	*path_cmd;

	if (!tokens || !tokens[0])
		exit(0);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (is_builtin(tokens[0]))
	{
		exec_builtin(tokens, mini);
		exit(0);
	}
	path_dirs = get_path_dirs(mini.envp);
	path_cmd = find_cmd(tokens[0], path_dirs);
	if (path_dirs)
		ft_free_matrix(path_dirs);
	if (!path_cmd)
	{
		print_error_cmd(tokens[0]);
		exit(127);
	}
	execve(path_cmd, tokens, mini.envp);
	perror("execve");
	free(path_cmd);
	exit(1);
}

char	*save_exec_cmd(char **tokens, t_mini mini)
{
	int		fd[2];
	pid_t	pid;
	char	*res;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (NULL);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		close(fd[0]);
		close(fd[1]);
		return (NULL);
	}
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		dup2(fd[1], STDERR_FILENO);
		close(fd[1]);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		exec_cmd(tokens, mini);
		exit(1);
	}
	close(fd[1]);
	res = read_fd(fd[0]);
	waitpid(pid, NULL, 0);
	return (res);
}
