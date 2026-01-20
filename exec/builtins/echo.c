/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 13:07:10 by djareno           #+#    #+#             */
/*   Updated: 2026/01/20 12:52:49 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

static void	print_tokens(t_mini *mini, char **tokens, int expand)
{
	int		i;
	char	*value;

	i = 1;
	while (tokens[i])
	{
		if (i > 1)
			ft_putstr_fd(" ", 1);
		if (expand && tokens[i][0] == '$')
		{
			value = ft_getenv(mini->envp, tokens[i] + 1);
			if (value)
				ft_putstr_fd(value, 1);
		}
		else
			ft_putstr_fd(tokens[i], 1);
		if (!expand)
			ft_putstr_fd("\n", 1);
		i++;
	}
	if (expand)
		ft_putstr_fd("\n", 1);
}

void	echo(t_mini *mini, t_node *node)
{
	if (!node || !node->tokens)
	{
		mini->exit_code = 1;
		ft_putstr_fd("echo: argumentos inválidos\n", 2);
		return ;
	}
	print_tokens(mini, node->tokens, node->expand);
	mini->exit_code = 0;
}
