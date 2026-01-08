/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 12:37:33 by djareno           #+#    #+#             */
/*   Updated: 2026/01/07 15:25:31 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

// static int	count_tokens(const char *s)
// {
// 	int	count;
// 	int	quote;

// 	count = 0;
// 	while (*s)
// 	{
// 		while (*s && (ft_isspace(*s) || ft_ischev(*s)))
// 			s++;
// 		if (!*s)
// 			break ;
// 		count++;
// 		quote = 0;
// 		while (*s)
// 		{
// 			if (!quote && ft_isquote(*s))
// 				quote = *s;
// 			else if (quote && *s == quote)
// 			{
// 				s++;
// 				break ;
// 			}
// 			else if (!quote && ft_isspace(*s))
// 				break ;
// 			s++;
// 		}
// 	}
// 	return (count);
// }

char **tokenizer(const char *s, t_node *node)
{
    char    **tokens;
    int     i;
    int     j;
    int     start;

    i = 0;
    j = 0;
    tokens = malloc(sizeof(char *) * 1024);
    if (!tokens)
        return (NULL);

    while (s[i])
    {
        if (ft_isspace(s[i]))
        {
            i++;
            continue;
        }
        if (handle_redir(s, &i, node))
            continue;
        start = i;
        while (s[i] && !ft_isspace(s[i]) && !ft_ischev(s[i]))
            i++;
        tokens[j++] = word_dup(s + start, i - start);
    }
    tokens[j] = NULL;
    return (tokens);
}

int	get_quotes(const char *s)
{
	char	quote;
	int		i;

	quote = 0;
	i = 0;
	while (s[i])
	{
		if (!quote && ft_isquote(s[i]))
			quote = s[i];
		else if (quote && s[i] == quote)
			quote = 0;
		i++;
	}
	if (quote)
		return (0);
	return (1);
}

char	**get_nodes(const char *s)
{
	int			i;
	int			len;
	char		quote;
	char		**nodes;
	const char	*start;

	i = 0;
	nodes = malloc(sizeof(char *) * 1024);
	if (!nodes)
		return (NULL);
	if (get_quotes((char *)s) == 0)
	{
		printf("Error: Unmatched quotes\n");
		return (NULL);
	}
	while (*s)
	{
		while (*s && ft_isspace(*s))
			s++;
		if (!*s)
			break ;
		if (*s == '|')
			s++;
		start = s;
		len = 0;
		quote = 0;
		while (s[len])
		{
			if (!quote && ft_isquote(s[len]))
				quote = s[len];
			else if (quote && s[len] == quote)
				quote = 0;
			else if (!quote && s[len] == '|')
				break ;
			len++;
		}
		nodes[i++] = word_dup(start, len);
		s += len;
	}
	nodes[i] = NULL;
	return (nodes);
}

void parser(const char *s, struct s_mini *mini)
{
    char    **cmds;
    int     i;

    cmds = get_nodes(s);
    if (!cmds)
        return ;
    int num_cmds = 0;
    while (cmds[num_cmds])
        num_cmds++;
    mini->nodes = malloc(sizeof(struct s_node *) * (num_cmds + 1));
    if (!mini->nodes)
		return (ft_free_matrix(cmds));
        

    i = 0;
    while (cmds[i])
    {
        mini->nodes[i] = malloc(sizeof(struct s_node));
        if (!mini->nodes[i])
            return (ft_free_matrix(cmds));
        mini->nodes[i]->redirs = NULL;
		mini->nodes[i]->redir_count = 0;
		mini->nodes[i]->tokens = tokenizer(cmds[i], mini->nodes[i]);
        mini->nodes[i]->expand = has_single_quotes(cmds[i]);
        expand_tokens(mini->nodes[i], mini);
        i++;
    }
    mini->nodes[i] = NULL;
	return (ft_free_matrix(cmds));
	// print_nodes(*mini); //opcional eh(borrar luego)
}
