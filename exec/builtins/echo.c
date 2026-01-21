/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 13:07:10 by djareno           #+#    #+#             */
/*   Updated: 2026/01/21 12:43:57 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

static void	print_tokens(t_mini *mini, char **tokens, int expand, int i)
{
	char	*value;
	int		aux;
	int		i_start;

	i_start = i;
	aux = 0;
	if (i > 1)
		aux = 1;
	while (tokens[i])
	{
		if (i > i_start)
			ft_putstr_fd(" ", 1);
		if (expand && tokens[i][0] == '$')
		{
			value = ft_getenv(mini->envp, tokens[i] + 1);
			if (value)
				ft_putstr_fd(value, 1);
		}
		else
			ft_putstr_fd(tokens[i], 1);
		if (!expand && aux == 0)
			ft_putstr_fd("\n", 1);
		i++;
	}
	if (expand && aux == 0)
		ft_putstr_fd("\n", 1);
}

int	check_tokens(t_node *node)
{
	int	x;

	x = 1;
	while (node->tokens[x])
	{
		if (node->tokens[x][0] != '-' && node->tokens[x][1] != 'n'
			&& node->tokens[x][x] != 'n')
		{
			x--;
			break ;
		}
		x++;
	}
	return (x);
}

void	echo(t_mini *mini, t_node *node)
{
	int	x;

	x = 0;
	if (!node || !node->tokens)
	{
		mini->exit_code = 1;
		ft_putstr_fd("echo: argumentos inválidos\n", 2);
		return ;
	}
	x = 1;
	x = check_tokens(node);
	print_tokens(mini, node->tokens, node->expand, x);
	mini->exit_code = 0;
}
