/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfuto <kfuto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 23:08:41 by kfuto             #+#    #+#             */
/*   Updated: 2026/01/10 23:21:25 by kfuto            ###   ########.fr       */
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

	fd = open(node->redirs[i].file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(node->redirs[i].file);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	apply_heredoc(t_node *node, int i)
{
	int	heredoc_fd;

	heredoc_fd = handle_heredoc(node->redirs[i].file);
	dup2(heredoc_fd, STDIN_FILENO);
	close(heredoc_fd);
}
