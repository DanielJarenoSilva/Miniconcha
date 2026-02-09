/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 11:06:25 by djareno           #+#    #+#             */
/*   Updated: 2026/02/09 12:16:16 by djareno          ###   ########.fr       */
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

void	setup_child(t_mini *mini, int i, int in_fd, int fd[2])
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
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
	close(fd[0]);
	if (mini->nodes[i]->redirs)
		apply_redirs(mini->nodes[i], mini);
	execute_node(mini, i);
}

static void	setup_parent(int *in_fd, int fd[2], int has_next)
{
	if (*in_fd != STDIN_FILENO)
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
			if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
				write(2, "Quit (core dumped)\n", 20);
			if (WIFEXITED(status))
				mini->exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				mini->exit_code = 128 + WTERMSIG(status);
		}
	}
	mini->is_pipe = 0;
}

void	run_pipes(t_mini *mini)
{
	int		i;
	int		fd[2];
	int		in_fd;
	pid_t	pid;
	pid_t	last_pid;

	last_pid = 0;
	in_fd = STDIN_FILENO;
	init_fd(fd);
	resolve_all_heredocs(mini);
	i = 0;
	while (mini->nodes[i])
	{
		if (mini->nodes[i + 1] && create_pipe(fd))
			return ;
		pid = fork();
		if (pid == 0)
			pipes_aux(mini, i, in_fd, fd);
		else
			setup_parent(&in_fd, fd, mini->nodes[i + 1] != NULL);
		if (!mini->nodes[i + 1])
			last_pid = pid;
		i++;
	}
	wait_children(mini, last_pid);
}
