/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfuto <kfuto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 11:06:25 by djareno           #+#    #+#             */
/*   Updated: 2026/01/12 02:40:58 by kfuto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	execute_node(t_mini *mini, int i)
{
	if (is_builtin(mini->nodes[i]->tokens[0]))
		exec_builtin(mini->nodes[i]->tokens, mini);
	else
		exec_cmd(mini->nodes[i]->tokens, *mini);
	exit(1);
}

static void	setup_child(t_mini *mini, int i, int in_fd, int fd[2])
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (in_fd != 0)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (mini->nodes[i]->redir_count > 0)
		apply_redirs(mini->nodes[i]);
	else if (mini->nodes[i + 1])
		dup2(fd[1], STDOUT_FILENO);
	if (mini->nodes[i + 1])
	{
		close(fd[0]);
		close(fd[1]);
	}
	execute_node(mini, i);
}

static void	setup_parent(int *in_fd, int fd[2], int has_next)
{
	if (*in_fd != 0)
		close(*in_fd);
	if (has_next)
	{
		close(fd[1]);
		*in_fd = fd[0];
	}
}

static void	wait_children(t_mini *mini)
{
	int	status;

	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			mini->exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			mini->exit_code = 128 + WTERMSIG(status);
	}
}

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
			setup_child(mini, i, in_fd, fd);
		else
			setup_parent(&in_fd, fd, mini->nodes[i + 1] != NULL);
		i++;
	}
	wait_children(mini);
}
