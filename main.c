/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabalvar <pabalvar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 10:54:49 by djareno           #+#    #+#             */
/*   Updated: 2025/12/04 13:22:09 by pabalvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*rl;
	char	**t;
	int		j = 0;

	t_mini mini;
	mini.nodes = malloc(sizeof(t_node) * 1024);
	mini.nodes->tokens = malloc(sizeof(char *) * 1024);
	while (1)
	{
		rl = readline("minishell > ");
		if (!rl)
			break ;
		if (*rl)
		{
			add_history(rl);
			t = parser(rl);
			for (int i = 0; t[i] && t[j]; i++)
			{
				j = 0;
				while (t[j])
				{
					mini.nodes[i].tokens[j] = ft_strdup(t[j]);
					printf("node %d: %s\n", j,	mini.nodes[i].tokens[j]);
					j++;
				}
			}
		}
	}
	return (0);
}
