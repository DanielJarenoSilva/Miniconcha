/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabalvar <pabalvar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 22:47:40 by kfuto             #+#    #+#             */
/*   Updated: 2026/01/21 15:43:25 by pabalvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/parse.h"
#include "exec.h"

void	heredoc_loop(const char *delimiter, int expand, t_mini *mini)
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
		if (expand)
			free(expanded);
	}
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
