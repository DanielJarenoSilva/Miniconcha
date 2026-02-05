/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 02:30:58 by kfuto             #+#    #+#             */
/*   Updated: 2026/02/05 12:16:55 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/parse.h"
#include "exec.h"

static char	*loop_aux(char *line, t_mini *mini, int fd)
{
	char	*expanded;

	expanded = expand_token(line, mini);
	write(fd, expanded, ft_strlen(expanded));
	return (expanded);
}

static void	process_heredoc_line(t_node *node, t_mini *mini,
								int fd, int *idx)
{
	char	*line;
	char	*expanded;

	line = readline("> ");
	if (ft_strncmp(line, node->redirs[idx[0]].delimiter[idx[1]],
			ft_strlen(line)) == 0 && ft_strncmp(line, "> ", ft_strlen(line)))
	{
		free(line);
		idx[1]++;
		return ;
	}
	if (!node->redirs[idx[0]].delimiter[idx[1] + 1])
	{
		if (node->redirs[idx[0]].expand)
			expanded = loop_aux(line, mini, fd);
		else
			write(fd, line, ft_strlen(line));
		if (node->redirs[idx[0]].expand)
			free(expanded);
		write(fd, "\n", 1);
	}
	if (line)
		free(line);
}

void	heredoc_loop(int i, t_node *node, t_mini *mini, int fd)
{
	int	idx[2];

	idx[0] = i;
	idx[1] = 0;
	while (node->redirs[i].delimiter[idx[1]])
		process_heredoc_line(node, mini, fd, idx);
}
