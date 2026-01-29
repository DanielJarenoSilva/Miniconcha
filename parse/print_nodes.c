/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 10:08:59 by djareno           #+#    #+#             */
/*   Updated: 2026/01/29 12:27:45 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	print_nodes(t_mini mini)
{
	int	i;
	int	j;

	i = 0;
	while (mini.nodes[i])
	{
		j = 0;
		printf("Node %d:\n", i);
		while (mini.nodes[i]->tokens[j])
		{
			printf("  Token %d: %s\n", j, mini.nodes[i]->tokens[j]);
			j++;
		}
		i++;
	}
}

int	check_pipe_syntax(const char *s)
{
	int	i;
	int	prev_pipe;

	i = 0;
	prev_pipe = 0;
	while (s[i] && ft_isspace(s[i]))
		i++;
	if (s[i] == '|')
		return (0);
	while (s[i])
	{
		if (s[i] == '|')
		{
			if (prev_pipe)
				return (0);
			prev_pipe = 1;
		}
		else if (!ft_isspace(s[i]))
			prev_pipe = 0;
		i++;
	}
	while (i && ft_isspace(s[i - 1]))
		i--;
	return (!(i && s[i - 1] == '|'));
}
