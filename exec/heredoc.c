/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfuto <kfuto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 10:07:13 by djareno           #+#    #+#             */
/*   Updated: 2026/02/05 02:32:09 by kfuto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/parse.h"
#include "exec.h"

// void	heredoc_loop(int i, t_node *node, int expand, t_mini *mini)
// {
// 	char	*line;
// 	int		k;

// 	k = 0;
// 	signal(SIGINT, SIG_DFL);
// 	signal(SIGQUIT, SIG_IGN);
// 	line = NULL;
// 	while (node->redirs[i].delimiter[k])
// 	{
// 		line = readline("> ");
// 		if (!line)
// 			break ;
// 		if (expand)
// 			line = expand_token(line, mini);
// 		if (ft_strncmp(line, node->redirs[i].delimiter[k],
// 				ft_strlen(node->redirs[i].delimiter[k] + 1)) == 0)
// 		{
// 			free(line);
// 			k++;
// 		}
// 	}
// }

// void	heredoc_loop(int i, t_node *node, int expand, t_mini *mini, int fd)
// {
// 	char	*line;
// 	char	*expanded;

// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (!line)
// 			break ;
// 		if (ft_strcmp_exact(line, node->redirs[i].delimiter[0]))
// 		{
// 			free(line);
// 			break ;
// 		}
// 		if (expand)
// 		{
// 			expanded = expand_token(line, mini);
// 			free(line);
// 			write(fd, expanded, ft_strlen(expanded));
// 			free(expanded);
// 		}
// 		else
// 		{
// 			write(fd, line, ft_strlen(line));
// 			free(line);
// 		}
// 		write(fd, "\n", 1);
// 	}
// }

void	exec_heredoc(int i, int fd[], t_node *node, t_mini *mini)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	close(fd[0]);
	heredoc_loop(i, node, mini, fd[1]);
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
		exit(130);
	}
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
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
