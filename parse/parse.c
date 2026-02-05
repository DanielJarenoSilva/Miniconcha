/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 12:37:33 by djareno           #+#    #+#             */
/*   Updated: 2026/02/05 11:58:15 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	**tokenizer(const char *s, t_node *node, t_mini mini)
{
	char	**tokens;
	int		i;
	int		j;
	int		start;

	tokens = (char **)ft_calloc(1024, sizeof(char *));
	if (!tokens)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (ft_isspace(s[i]))
			i++;
		if (ft_ischev(s[i]) && handle_redir(s, &i, node) == 0)
		{
			ft_free_matrix(tokens);
			return (NULL);
		}
		start = i;
		skip_token_quotes(s, &i, &mini);
		if (i > start)
			tokens[j++] = word_dup_no_quotes(s + start, i - start);
	}
	return (tokens[j] = NULL, tokens);
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
		if (len > 0)
			nodes[(*i)++] = word_dup(start, len);
		s += len;
	}
}

char	**get_nodes(const char *s, struct s_mini *mini)
{
	int		i;
	char	**nodes;

	if (!get_quotes(s))
	{
		printf("Error: unmatched quotes\n");
		return (NULL);
	}
	nodes = (char **)ft_calloc(1024, sizeof(char *));
	if (!nodes)
		return (NULL);
	i = 0;
	do_nodes(nodes, s, &i, mini);
	nodes[i] = NULL;
	return (nodes);
}

static int	init_nodes(char **cmds, struct s_mini *mini, int num_cmds)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < num_cmds)
	{
		if (ft_strlen(cmds[i]) == 0)
		{
			printf("Error: invalid pipe sequence\n");
			return (mini->exit_code = 2, 0);
		}
		mini->nodes[j] = (t_node *)malloc(sizeof(t_node));
		mini->nodes[j]->redirs = NULL;
		mini->nodes[j]->redir_count = 0;
		mini->nodes[j]->tokens = tokenizer(cmds[i], mini->nodes[j], *mini);
		mini->nodes[j]->expand = has_single_quotes(cmds[i]);
		mini->nodes[j]->wrong_redir = 0;
		if (mini->nodes[j]->tokens)
			expand_tokens(mini->nodes[j], mini);
		i++;
		j++;
	}
	return (mini->nodes[j] = NULL, 1);
}

void	parser(const char *s, t_mini *mini)
{
	char	**cmds;
	int		num_cmds;

	if (!check_pipe_syntax(s))
	{
		mini->is_pipe = -1;
		mini->exit_code = 2;
		printf("Error: invalid pipe sequence\n");
		return ;
	}
	mini->is_pipe = 0;
	cmds = get_nodes(s, mini);
	if (!cmds)
		return ;
	num_cmds = 0;
	while (cmds[num_cmds])
		num_cmds++;
	mini->nodes = (t_node **)ft_calloc(num_cmds + 1, sizeof(t_node *));
	if (!mini->nodes)
		return (ft_free_matrix(cmds));
	if (!init_nodes(cmds, mini, num_cmds))
		return (ft_free_matrix(cmds));
	ft_free_matrix(cmds);
}
