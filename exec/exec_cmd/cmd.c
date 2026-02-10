/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfuto <kfuto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 11:55:22 by djareno           #+#    #+#             */
/*   Updated: 2026/02/11 00:35:00 by kfuto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

void	exec_cmd(char **tokens, t_mini *mini)
{
	char	**path_dirs;
	char	*path_cmd;

	if (!tokens || !tokens[0])
		exit(0);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	path_dirs = get_path_dirs(mini->envp);
	path_cmd = find_cmd(tokens[0], path_dirs);
	if (path_dirs)
		ft_free_matrix(path_dirs);
	if (!path_cmd)
	{
		print_error_cmd(tokens[0]);
		exit(127);
	}
	execve(path_cmd, tokens, mini->envp);
	perror("execve");
	exit(126);
}

void	child(t_node *node, t_mini *mini, int *fd)
{
	if (node->redir_count > 0)
		apply_redirs(node, mini);
	if (mini->is_pipe && !has_redir_out(node))
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
	exec_cmd(node->tokens, mini);
	perror("execve");
	exit(1);
}

void	error_child(int *fd)
{
	perror("fork");
	if (fd[0] != -1)
		close(fd[0]);
	if (fd[1] != -1)
		close(fd[1]);
}

char	*exec_child(t_node *node, t_mini *mini, int *fd)
{
	pid_t	pid;
	char	*res;
	int		status;

	res = NULL;
	pid = fork();
	if (pid < 0)
		return (error_child(fd), NULL);
	if (pid == 0)
		child(node, mini, fd);
	if (fd[0] >= 0 && fd[1] >= 0 && !has_redir_out(node))
	{
		close(fd[1]);
		res = read_fd(fd[0]);
		close(fd[0]);
	}
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
		write(2, "Quit (core dumped)\n", 20);
	if (WIFEXITED(status))
		mini->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		mini->exit_code = 128 + WTERMSIG(status);
	return (res);
}

char	*save_exec_cmd(t_node *node, t_mini *mini)
{
	int		fd[2];
	char	*res;

	fd[0] = -1;
	fd[1] = -1;
	res = NULL;
	if (!has_redir_out(node) && mini->is_pipe)
	{
		if (pipe(fd) == -1)
		{
			perror("pipe");
			return (NULL);
		}
	}
	if (is_builtin(node->tokens[0]) && !mini->is_pipe && !mini->builtin_quote
		&& node->redir_count == 0)
	{
		exec_builtin(node, mini);
		return (NULL);
	}
	res = exec_child(node, mini, fd);
	return (res);
}
