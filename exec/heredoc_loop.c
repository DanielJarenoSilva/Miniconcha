/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 02:30:58 by kfuto             #+#    #+#             */
/*   Updated: 2026/02/12 11:48:45 by djareno          ###   ########.fr       */
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

void	line_aux(char *line, int fd)
{
	if (!line)
	{
		close(fd);
		exit(0);
	}
}

static void	process_heredoc_line(t_node *node, t_mini *mini, int fd, int *idx)
{
	char	*line;
	char	*expanded;

	line = readline("> ");
	line_aux(line, fd);
	if (ft_strncmp(line, node->redirs[idx[0]].delimiter[idx[1]],
			ft_strlen(line)) == 0 && ft_strncmp(line, "> ", ft_strlen(line)))
	{
		free(line);
		idx[1]++;
		return ;
	}
	node->redirs[idx[0]].expand = 1;
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

void	apply_heredoc_file(int heredoc_index)
{
	int		fd;
	char	*tmp_filename;
	char	*index_str;

	index_str = ft_itoa(heredoc_index);
	tmp_filename = ft_strjoin("/tmp/.heredoc_", index_str);
	free(index_str);
	fd = open(tmp_filename, O_RDONLY);
	if (fd < 0)
	{
		perror(tmp_filename);
		free(tmp_filename);
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	unlink(tmp_filename);
	free(tmp_filename);
}
