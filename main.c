/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabalvar <pabalvar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 10:54:49 by djareno           #+#    #+#             */
/*   Updated: 2025/12/15 15:10:04 by pabalvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_nodes(t_mini mini)
{
	int i = 0;
	int j;

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

int	main(void)
{
	char	*rl;

	while (1)
	{
		rl = readline("minishell > ");
		if (!rl)
			break ;
		if (*rl)
		{
			add_history(rl);
			parser(rl);
		}
	}
	return (0);
}
