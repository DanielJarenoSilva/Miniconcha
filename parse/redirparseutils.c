/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirparseutils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabalvar <pabalvar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 10:08:14 by djareno           #+#    #+#             */
/*   Updated: 2026/02/04 13:10:16 by pabalvar         ###   ########.fr       */
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
	redir->delimiter = ft_realloc(redir->delimiter,
			sizeof(char *) * (i + 2), sizeof(char *) * i);
	redir->delimiter[i] = delim;
	redir->delimiter[i + 1] = NULL;
}

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
