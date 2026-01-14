/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 13:07:10 by djareno           #+#    #+#             */
/*   Updated: 2026/01/14 12:31:02 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

void	echo_expand(t_mini *mini, t_node *node)
{
	int	i;

	i = 1;
	while (node->tokens[i])
	{
		ft_putstr_fd(node->tokens[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
	mini->exit_code = 0;
}

void	echo(t_mini *mini, t_node *node)
{
	int		i;
	char	*value;

	if (node->expand == 0)
	{
		echo_expand(mini, node);
		return ;
	}
	i = 1;
	while (node->tokens[i])
	{
		if (i > 1)
			ft_putstr_fd(" ", 1);
		if (node->tokens[i][0] == '$')
		{
			value = ft_getenv(mini->envp, node->tokens[i] + 1);
			if (value)
				ft_putstr_fd(value, 1);
		}
		else
			ft_putstr_fd(node->tokens[i], 1);
		i++;
	}
	ft_putstr_fd("\n", 1);
	mini->exit_code = 0;
}
