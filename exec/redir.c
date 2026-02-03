/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfuto <kfuto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 22:47:40 by kfuto             #+#    #+#             */
/*   Updated: 2026/02/03 13:36:12 by kfuto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	apply_redir_in(t_node *node, int i)
{
	int	fd;

	fd = open(node->redirs[i].file, O_RDONLY);
	if (fd < 0)
	{
		perror(node->redirs[i].file);
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	apply_redir_out(t_node *node, int i)
{
	int	fd;

	fflush(stdout);
	fd = open(node->redirs[i].file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(node->redirs[i].file);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	apply_redir_append(t_node *node, int i)
{
	int	fd;

	fflush(stdout);
	fd = open(node->redirs[i].file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(node->redirs[i].file);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
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
		if (node->redirs[i].type == HEREDOC)
		{
			if (!node->tokens[0])
			{
				heredoc_loop(i, node, node->redirs->expand, mini);
				exit(0);
			}
			apply_heredoc(node, i, mini);
		}
		else if (node->redirs[i].type == REDIR_IN)
			apply_redir_in(node, i);
		else if (node->redirs[i].type == REDIR_OUT)
			apply_redir_out(node, i);
		else if (node->redirs[i].type == REDIR_APPEND)
			apply_redir_append(node, i);
		i++;
	}
	return (0);
}
