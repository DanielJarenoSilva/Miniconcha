/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabalvar <pabalvar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 22:47:40 by kfuto             #+#    #+#             */
/*   Updated: 2026/01/21 13:00:56 by pabalvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/parse.h"
#include "exec.h"

// int	handle_heredoc(const char *delimiter)
// {
// 	int		fd[2];
// 	char	*line;

// 	if (pipe(fd) == -1)
// 		exit(1);
// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (!line)
// 			break ;
// 		if (strcmp(line, delimiter) == 0)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		write(fd[1], line, strlen(line));
// 		write(fd[1], "\n", 1);
// 		free(line);
// 	}
// 	close(fd[1]);
// 	return (fd[0]);
// }

static void	heredoc_loop(const char *delimiter, int expand, t_mini *mini,
		int write_fd)
{
	char	*line;
	char	*expanded;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, (char *)delimiter, ft_strlen(delimiter)
				+ 1) == 0)
			break ;
		if (expand)
		{
			expanded = expand_token(line, mini);
			free(line);
		}
		else
			expanded = line;
		write(write_fd, expanded, ft_strlen(expanded));
		write(write_fd, "\n", 1);
		if (expand)
			free(expanded);
	}
}

int	handle_heredoc(const char *delimiter, int expand, t_mini *mini)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (pipe(fd) == -1)
	exit(1);
	close(fd[0]);
	heredoc_loop(delimiter, expand, mini, fd[1]);
	if (!mini->nodes[0]->tokens || !mini->nodes[0]->tokens[0])
	{
		empty_heredoc(&mini);
	}
	exec_heredoc_cmd(mini->nodes[0]->tokens, *mini);
	exit(0);
	close(fd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		mini->exit_code = 130;
		mini->heredoc_interrupted = 1;
		close(fd[0]);
		return (-1);
	}
	return (fd[0]);
}

int	has_redir_out(t_node *node)
{
	int	i;

	i = 0;
	while (i < node->redir_count)
	{
		if (node->redirs[i].type == REDIR_OUT
			|| node->redirs[i].type == REDIR_APPEND)
			return (1);
		i++;
	}
	return (0);
}

int	apply_redirs(t_node *node, t_mini *mini)
{
	int	i;

	i = 0;
	while (i < node->redir_count)
	{
		if (node->redirs[i].type == REDIR_IN)
			apply_redir_in(node, i);
		else if (node->redirs[i].type == REDIR_OUT)
			apply_redir_out(node, i);
		else if (node->redirs[i].type == REDIR_APPEND)
			apply_redir_append(node, i);
		else if (node->redirs[i].type == HEREDOC)
		{
			apply_heredoc(node, i, mini);
			if (mini->heredoc_interrupted)
				return (-1);
		}
		i++;
	}
	return (0);
}
