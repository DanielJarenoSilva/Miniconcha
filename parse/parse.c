/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfuto <kfuto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 12:37:33 by djareno           #+#    #+#             */
/*   Updated: 2026/01/11 02:51:14 by kfuto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	**tokenizer(const char *s, t_node *node)
{
	char	**tokens;
	int		i;
	int		j;
	int		start;

	i = 0;
	j = 0;
	tokens = malloc(sizeof(char *) * 1024);
	if (!tokens)
		return (NULL);
	while (s[i])
	{
		if (ft_isspace(s[i]))
			i++;
		if (handle_redir(s, &i, node))
			continue ;
		start = i;
		while (s[i] && !ft_isspace(s[i]) && !ft_ischev(s[i]))
			i++;
		tokens[j++] = word_dup(s + start, i - start);
	}
	tokens[j] = NULL;
	return (tokens);
}

static void	do_nodes(char **nodes, const char *s, int *i, struct s_mini *mini)
{
	const char	*start;
	int			len;
	char		quote;

	while (*s)
	{
		while (*s && ft_isspace(*s))
			s++;
		if (ft_ispipe(*s, mini))
			s++;
		start = s;
		len = 0;
		quote = 0;
		while (s[len] && !(s[len] == '|' && !quote))
		{
			if (!quote && ft_isquote(s[len]))
				quote = s[len];
			else if (quote && s[len] == quote)
				quote = 0;
			len++;
		}
		nodes[(*i)++] = word_dup(start, len);
		s += len;
	}
}

char	**get_nodes(const char *s, struct s_mini *mini)
{
	int		i;
	char	**nodes;

	i = 0;
	nodes = malloc(sizeof(char *) * 1024);
	if (!nodes)
		return (NULL);
	if (get_quotes((char *)s) == 0)
	{
		printf("Error: Unmatched quotes\n");
		return (NULL);
	}
	do_nodes(nodes, s, &i, mini);
	nodes[i] = NULL;
	return (nodes);
}

static int	init_nodes(char **cmds, struct s_mini *mini, int num_cmds)
{
	int	i;

	i = 0;
	while (i < num_cmds)
	{
		mini->nodes[i] = malloc(sizeof(struct s_node));
		if (!mini->nodes[i])
			return (0);
		mini->nodes[i]->redirs = NULL;
		mini->nodes[i]->redir_count = 0;
		mini->nodes[i]->tokens = tokenizer(cmds[i], mini->nodes[i]);
		mini->nodes[i]->expand = has_single_quotes(cmds[i]);
		expand_tokens(mini->nodes[i], mini);
		i++;
	}
	mini->nodes[i] = NULL;
	return (1);
}

void	parser(const char *s, struct s_mini *mini)
{
	char	**cmds;
	int		num_cmds;

	cmds = get_nodes(s, mini);
	if (!cmds)
		return ;
	num_cmds = 0;
	while (cmds[num_cmds])
		num_cmds++;
	mini->nodes = malloc(sizeof(struct s_node *) * (num_cmds + 1));
	if (!mini->nodes)
		return (ft_free_matrix(cmds));
	if (!init_nodes(cmds, mini, num_cmds))
		return (ft_free_matrix(cmds));
	ft_free_matrix(cmds);
}
