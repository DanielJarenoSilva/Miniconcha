/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirparseutils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfuto <kfuto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 03:11:22 by kfuto             #+#    #+#             */
/*   Updated: 2026/01/25 22:22:56 by kfuto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	is_quoted_delimiter(const char *s, int i)
{
	while (s[i] && ft_isspace(s[i]))
		i++;
	return (s[i] == '\'' || s[i] == '"');
}

void	add_delimiter(t_redir *redir, char *delim)
{
	int	i;

	i = 0;
	if (!redir->delimiter)
	{
		redir->delimiter = malloc(sizeof(char *) * 2);
		redir->delimiter[0] = delim;
		redir->delimiter[1] = NULL;
		return ;
	}
	while (redir->delimiter[i])
		i++;
	redir->delimiter = realloc(redir->delimiter,
			sizeof(char *) * (i + 2));
	redir->delimiter[i] = delim;
	redir->delimiter[i + 1] = NULL;
}
