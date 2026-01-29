/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirparseutils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 10:08:14 by djareno           #+#    #+#             */
/*   Updated: 2026/01/29 10:08:22 by djareno          ###   ########.fr       */
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
