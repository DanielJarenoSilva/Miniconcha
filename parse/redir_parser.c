/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 00:44:34 by kfuto             #+#    #+#             */
/*   Updated: 2026/01/29 12:08:35 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	*get_next_word(const char *s, int *i)
{
	int		start;
	char	quote;

	while (s[*i] && ft_isspace(s[*i]))
		(*i)++;
	if (!s[*i])
		return (NULL);
	if (s[*i] == '\'' || s[*i] == '"')
	{
		quote = s[(*i)++];
		start = *i;
		while (s[*i] && s[*i] != quote)
			(*i)++;
		return (ft_substr(s, start, (*i)++ - start));
	}
	start = *i;
	while (s[*i] && !ft_isspace(s[*i]) && !ft_ischev(s[*i]) && s[*i] != '|')
		(*i)++;
	if (start == *i)
		return (NULL);
	return (ft_substr(s, start, *i - start));
}

static int	handle_in_redir(const char *s, int *i, t_node *node)
{
	char	*file;

	if (s[*i + 1] == '<')
	{
		*i += 2;
		file = get_next_word(s, i);
		if (!file)
		{
			printf("minishell: syntax error near unexpected token <<\n");
			return (0);
		}
		add_redir(node, HEREDOC, 1);
		add_delimiter(&node->redirs[node->redir_count - 1], file);
		return (1);
	}
	(*i)++;
	file = get_next_word(s, i);
	if (!file)
	{
		printf("minishell: syntax error near unexpected token <\n");
		return (0);
	}
	add_redir(node, REDIR_IN, 0);
	node->redirs[node->redir_count - 1].file = file;
	return (1);
}

static int	handle_out_redir(const char *s, int *i, t_node *node)
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
	node->redirs = realloc(node->redirs, sizeof(t_redir) * (node->redir_count
				+ 1));
	node->redirs[node->redir_count].type = type;
	node->redirs[node->redir_count].delimiter = NULL;
	node->redirs[node->redir_count].expand = expand;
	node->redir_count++;
}
