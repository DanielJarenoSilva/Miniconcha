/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfuto <kfuto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 00:44:34 by kfuto             #+#    #+#             */
/*   Updated: 2026/01/16 03:32:01 by kfuto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	handle_in_redir(const char *s, int *i, t_node *node)
{
	int		expand;
	char	*delim;

	if (s[*i + 1] == '<')
	{
		*i += 2;
		expand = !is_quoted_delimiter(s, *i);
		delim = get_next_word(s, i);
		add_redir(node, HEREDOC, delim, expand);
	}
	else
	{
		(*i)++;
		add_redir(node, REDIR_IN, get_next_word(s, i), 0);
	}
}

static void	handle_out_redir(const char *s, int *i, t_node *node)
{
	if (s[*i + 1] == '>')
	{
		*i += 2;
		add_redir(node, REDIR_APPEND, get_next_word(s, i), 0);
	}
	else
	{
		(*i)++;
		add_redir(node, REDIR_OUT, get_next_word(s, i), 0);
	}
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

void	add_redir(t_node *node, t_redir_type type, char *file, int expand)
{
	node->redirs = realloc(node->redirs,
			sizeof(t_redir) * (node->redir_count + 1));
	node->redirs[node->redir_count].type = type;
	node->redirs[node->redir_count].file = file;
	node->redirs[node->redir_count].expand = expand;
	node->redir_count++;
}
