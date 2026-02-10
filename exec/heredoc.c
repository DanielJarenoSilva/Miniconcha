/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 10:07:13 by djareno           #+#    #+#             */
/*   Updated: 2026/02/10 11:03:26 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/parse.h"
#include "exec.h"

void	exec_heredoc(int i, int fd[], t_node *node, t_mini *mini)
{
	signal(SIGINT, sigint_heredoc);
	signal(SIGQUIT, SIG_DFL);
	close(fd[0]);
	heredoc_loop(i, node, mini, fd[1]);
	close(fd[1]);
	exit(0);
}

void	wait_heredoc_father(pid_t pid, int fd[], t_mini *mini)
{
	int		status;

	status = 0;
	close(fd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		mini->exit_code = 130;
		mini->heredoc_interrupted = 1;
		close(fd[0]);
		return ;
	}
}

void	heredoc_father(int fd[], t_node *node, int i, t_mini *mini)
{
	int		tmp_fd;
	char	*tmp_filename;
	char	*index_str;
	char	buffer[4096];
	ssize_t	bytes;

	wait_heredoc_father(node->redirs[i].heredoc_index, fd, mini);
	index_str = ft_itoa(node->redirs[i].heredoc_index);
	tmp_filename = ft_strjoin("/tmp/.heredoc_", index_str);
	free(index_str);
	tmp_fd = open(tmp_filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	bytes = read(fd[0], buffer, sizeof(buffer));
	while (bytes > 0)
	{
		write(tmp_fd, buffer, bytes);
		bytes = read(fd[0], buffer, sizeof(buffer));
	}
	close(fd[0]);
	close(tmp_fd);
	free(tmp_filename);
}

void	apply_heredoc(t_node *node, int i, t_mini *mini)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return ;
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		mini->is_fork = 1;
		exec_heredoc(i, fd, node, mini);
	}
	else
		heredoc_father(fd, node, i, mini);
}
