/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfuto <kfuto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 10:07:13 by djareno           #+#    #+#             */
/*   Updated: 2026/02/02 13:54:39 by kfuto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/parse.h"
#include "exec.h"

void	heredoc_loop(int i, t_node *node, int expand, t_mini *mini)
{
	char	*line;
	char	*expanded;
	int		k;

	k = 0;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	line = NULL;
	while (node->redirs[i].delimiter[k])
	{
		line = readline("> ");
		if (expand)
			expanded = expand_token(line, mini);
		if (!line || ft_strncmp(line, node->redirs[i].delimiter[k],
				ft_strlen(node->redirs[i].delimiter[k]) + 1) == 0)
			k++;
		if (expand)
			free(expanded);
		if (line)
			free(line);
	}
}

void	exec_heredoc(int i, int fd[], t_node *node, t_mini *mini)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	close(fd[0]);
	heredoc_loop(i, node, node->redirs[i].expand,
		mini);
	close(fd[1]);
	exit(0);
}

void	heredoc_father(int fd[], pid_t pid, t_mini *mini)
{
	int	status;

	close(fd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		mini->exit_code = 130;
		mini->heredoc_interrupted = 1;
		close(fd[0]);
		return ;
	}
	dup2(fd[0], STDIN_FILENO);
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
		exec_heredoc(i, fd, node, mini);
	else
		heredoc_father(fd, pid, mini);
}
