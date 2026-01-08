/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseutils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfuto <kfuto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:49:35 by kfuto             #+#    #+#             */
/*   Updated: 2026/01/08 19:52:19 by kfuto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	expand_tokens(t_node *node, t_mini *mini)
{
	int		i;
	char	*tmp;

	if (!node->expand)
		return ;
	i = 1;
	while (node->tokens[i])
	{
		tmp = expand_token(node->tokens[i], mini);
		free(node->tokens[i]);
		node->tokens[i] = tmp;
		i++;
	}
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

int	get_node_len(const char *s)
{
	int		len;
	char	quote;

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
	return (len);
}
