/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfuto <kfuto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 22:47:40 by kfuto             #+#    #+#             */
/*   Updated: 2026/01/16 03:58:17 by kfuto            ###   ########.fr       */
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

int	handle_heredoc(const char *delimiter, int expand, t_mini *mini)
{
	int		fd[2];
	char	*line;
	char	*expanded;

	if (pipe(fd) == -1)
		exit(1);
	signal(SIGINT, sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, (char *)delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			free(line);
			break ;
		}
		if (expand)
		{
			expanded = expand_token(line, mini);
			free(line);
		}
		else
			expanded = line;
		write(fd[1], expanded, ft_strlen(expanded));
		write(fd[1], "\n", 1);
		if (expand)
			free(expanded);
	}
	close(fd[1]);
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

void	apply_redirs(t_node *node, t_mini *mini)
{
	int	i;

	i = 0;
	while (i < node->redir_count)
	{
		if (node->redirs[i].type == REDIR_IN)
		{
			apply_redir_in(node, i);
		}
		else if (node->redirs[i].type == REDIR_OUT)
		{
			apply_redir_out(node, i);
		}
		else if (node->redirs[i].type == REDIR_APPEND)
		{
			apply_redir_append(node, i);
		}
		else if (node->redirs[i].type == HEREDOC)
		{
			apply_heredoc(node, i, mini);
		}
		i++;
	}
}
