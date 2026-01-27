/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfuto <kfuto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 00:44:34 by kfuto             #+#    #+#             */
/*   Updated: 2026/01/27 17:29:08 by kfuto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	handle_in_redir(const char *s, int *i, t_node *node)
{
	char	*delim;
	int		expand;

	if (s[*i + 1] == '<')
	{
		*i += 2;
		expand = !is_quoted_delimiter(s, *i);
		delim = get_next_word(s, i);
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
	}
	else
	{
		(*i)++;
		add_redir(node, REDIR_IN, 0);
		node->redirs[node->redir_count - 1].file = get_next_word(s, i);
	}
}

static void	handle_out_redir(const char *s, int *i, t_node *node)
{
	char	*file;

	if (s[*i + 1] == '>')
	{
		*i += 2;
		add_redir(node, REDIR_APPEND, 0);
	}
	else
	{
		(*i)++;
		add_redir(node, REDIR_OUT, 0);
	}
	file = get_next_word(s, i);
	node->redirs[node->redir_count - 1].file = file;
}

int	handle_redir(const char *s, int *i, t_node *node)
{
	if (!ft_ischev(s[*i]))
		return (0);
	if (s[*i] == '<')
		handle_in_redir(s, i, node);
	else if (s[*i] == '>')
		handle_out_redir(s, i, node);
	else
		return (0);
	return (1);
}

char	*get_next_word(const char *s, int *i)
{
	int		start;
	char	quote;

	while (s[*i] && ft_isspace(s[*i]))
		(*i)++;
	start = *i;
	if (s[*i] == '\'' || s[*i] == '"')
	{
		quote = s[(*i)++];
		start = *i;
		while (s[*i] && s[*i] != quote)
			(*i)++;
		return (ft_substr(s, start, (*i)++ - start));
	}
	while (s[*i] && !ft_isspace(s[*i]))
		(*i)++;
	return (ft_substr(s, start, *i - start));
}

void	add_redir(t_node *node, t_redir_type type, int expand)
{
	node->redirs = realloc(node->redirs, sizeof(t_redir) * (node->redir_count
				+ 1));
	node->redirs[node->redir_count].type = type;
	node->redirs[node->redir_count].delimiter = NULL;
	node->redirs[node->redir_count].expand = expand;
	node->redir_count++;
}
