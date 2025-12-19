/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 11:06:25 by djareno           #+#    #+#             */
/*   Updated: 2025/12/19 11:23:43 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	**create_pipes(int n)
{
	int	**pipes;
	int	i;

	i = 0;
	pipes = malloc(sizeof(int *) * n);
	while (i < n)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (pipe(pipes[i]) == -1)
			return (perror("pipe"), NULL);
		i++;
	}
	return (pipes);
}

char	*run_pipex(char **cmd, t_mini mini)
{
	int		i;
	int		fd[2];
	int		prev_fd;
	pid_t	pid;
	char	*res;

	i = 0;
	res = NULL;
	prev_fd = STDIN_FILENO;
	while (cmd[i])
	{
		if (cmd[i + 1])
			pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			if (prev_fd != STDIN_FILENO)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (cmd[i + 1])
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[0]);
				close(fd[1]);
			}
			res = save_exec_cmd(cmd[i], mini);
			perror("exec");
			exit(1);
		}
		if (prev_fd != STDIN_FILENO)
			close(prev_fd);
		if (cmd[i + 1])
		{
			close(fd[1]);
			prev_fd = fd[0];
		}
		i++;
	}
	while (wait(NULL) > 0)
		;
	return (res);
}

char	*get_path(char **envp)
{
	int		i;
	char	*path;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = envp[i] + 5;
			return (path);
		}
		i++;
	}
	return (NULL);
}

/*void	start_pipex(char **cmd, char **envp)
{

}*/
