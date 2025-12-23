/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 11:06:25 by djareno           #+#    #+#             */
/*   Updated: 2025/12/23 15:35:01 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	run_pipes(t_mini *mini)
{
	int		i;
	int		fd[2];
	int		in_fd;
	pid_t	pid;

	i = 0;
	in_fd = 0;
	while (mini->nodes[i])
	{
		if (mini->nodes[i + 1] && pipe(fd) == -1)
		{
			perror("pipe");
			exit(1);
		}
		pid = fork();
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			if (in_fd != 0)
			{
				dup2(in_fd, STDIN_FILENO);
				close(in_fd);
			}
			if (mini->nodes[i + 1])
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[0]);
				close(fd[1]);
			}
			exec_cmd(mini->nodes[i]->tokens, *mini);
			exit(1);
		}
		else
		{
			if (in_fd != 0)
				close(in_fd);
			if (mini->nodes[i + 1])
			{
				close(fd[1]);
				in_fd = fd[0];
			}
		}
		i++;
	}
	while (wait(NULL) > 0)
		;
}
