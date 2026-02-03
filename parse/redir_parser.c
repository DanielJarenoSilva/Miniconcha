/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 00:44:34 by kfuto             #+#    #+#             */
/*   Updated: 2026/02/03 17:20:53 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	handle_add_heredoc(int expand, char *delim, t_node *node)
{
	if (!delim)
		return (0);
	if (node->redir_count > 0 && node->redirs[node->redir_count
			- 1].type == HEREDOC)
	{
		add_delimiter(&node->redirs[node->redir_count - 1], delim);
	}
	else
	{
		add_redir(node, HEREDOC, expand);
		add_delimiter(&node->redirs[node->redir_count - 1], delim);
	}
	return (1);
}

static int	handle_in_redir(const char *s, int *i, t_node *node)
{
	char	*delim;
	int		expand;

	if (s[*i + 1] == '<')
	{
		*i += 2;
		expand = is_quoted_delimiter(s, *i);
		delim = get_next_word(s, i);
		return (handle_add_heredoc(expand, delim, node));
	}
	else
	{
		(*i)++;
		delim = get_next_word(s, i);
		if (!delim)
			return (0);
		add_redir(node, REDIR_IN, 0);
		node->redirs[node->redir_count - 1].file = delim;
		return (1);
	}
}


int	handle_out_redir(const char *s, int *i, t_node *node)
{
	char	*file;

	if (s[*i + 1] == '>')
	{
		*i += 2;
		file = get_next_word(s, i);
		if (!file)
		{
			printf("minishell: syntax error near unexpected token `>>`\n");
			return (0);
		}
		add_redir(node, REDIR_APPEND, 0);
	}
	else
	{
		(*i)++;
		file = get_next_word(s, i);
		if (!file)
		{
			printf("minishell: syntax error near unexpected token `>`\n");
			return (0);
		}
		add_redir(node, REDIR_OUT, 0);
	}
	return (node->redirs[node->redir_count - 1].file = file, 1);
}

int	handle_redir(const char *s, int *i, t_node *node)
{
	if (!ft_ischev(s[*i]))
		return (0);
	if (s[*i] == '<')
		return (handle_in_redir(s, i, node));
	if (s[*i] == '>')
		return (handle_out_redir(s, i, node));
	return (0);
}

void	add_redir(t_node *node, t_redir_type type, int expand)
{
	node->redirs = ft_realloc(node->redirs, sizeof(t_redir) * (node->redir_count
				+ 1));
	node->redirs[node->redir_count].type = type;
	node->redirs[node->redir_count].delimiter = NULL;
	node->redirs[node->redir_count].expand = expand;
	node->redirs[node->redir_count].file = NULL;
	node->redir_count++;
}
