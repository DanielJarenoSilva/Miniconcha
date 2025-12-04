/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 10:54:49 by djareno           #+#    #+#             */
/*   Updated: 2025/12/01 13:06:46 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*rl;
	char	**t;

	t_token	token;
	(void)token;
	token.cmnds = malloc(sizeof(char *) * 1024);
	while (1)
	{
		rl = readline("minishell > ");
		if (!rl)
			break ;
		if (*rl)
		{
			add_history(rl);
			t = tokenizer(rl);
			for (int i = 0; t[i]; i++)
			{
				token.cmnds[i] = ft_strdup(t[i]);
				printf("token %d: %s\n", i,	token.cmnds[i]);
			}
		}
	}
	return (0);
}
