/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfuto <kfuto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 22:47:40 by kfuto             #+#    #+#             */
/*   Updated: 2026/01/10 23:20:03 by kfuto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	handle_heredoc(const char *delimiter)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd[1], line, strlen(line));
		write(fd[1], "\n", 1);
		free(line);
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

void	apply_redirs(t_node *node)
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
			apply_heredoc(node, i);
		}
		i++;
	}
}
