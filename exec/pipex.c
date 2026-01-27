/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfuto <kfuto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 11:06:25 by djareno           #+#    #+#             */
/*   Updated: 2026/01/27 17:13:12 by kfuto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	execute_node(t_mini *mini, int i)
{
	if (!mini->nodes[i] || !mini->nodes[i]->tokens
		|| !mini->nodes[i]->tokens[0])
		exit(0);
	if (is_builtin(mini->nodes[i]->tokens[0]))
		exec_builtin(mini->nodes[i], mini);
	else
		exec_cmd(mini->nodes[i]->tokens, mini);
	exit(mini->exit_code);
}

static void	setup_child(t_mini *mini, int i, int in_fd, int fd[2])
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (mini->nodes[i]->redir_count > 0)
		apply_redirs(mini->nodes[i], mini);
	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (mini->nodes[i + 1] && !has_redir_out(mini->nodes[i]))
	{
		dup2(fd[1], STDOUT_FILENO);
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
	else
	{
		if (fd[0] != -1)
			close(fd[0]);
		if (fd[1] != -1)
			close(fd[1]);
	}
}

static void	wait_children(t_mini *mini, int last_pid)
{
	int		status;
	pid_t	pid;

	while (1)
	{
		pid = wait(&status);
		if (pid <= 0)
			break ;
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				mini->exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				mini->exit_code = 128 + WTERMSIG(status);
		}
	}
}

void	run_pipes(t_mini *mini)
{
	int		i;
	int		fd[2];
	int		in_fd;
	pid_t	pid;
	pid_t	last_pid;

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
		if (!mini->nodes[i + 1])
			last_pid = pid;
		i++;
	}
	wait_children(mini, last_pid);
}
