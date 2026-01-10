/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfuto <kfuto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 13:07:10 by djareno           #+#    #+#             */
/*   Updated: 2026/01/10 20:41:01 by kfuto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

void	echo(t_mini *mini, char **tokens)
{
	int		i;
	char	*value;

	i = 1;
	while (tokens[i])
	{
		if (i > 1)
			ft_putstr_fd(" ", 1);
		if (tokens[i][0] == '$')
		{
			value = ft_getenv(mini->envp, tokens[i] + 1);
			if (value)
				ft_putstr_fd(value, 1);
		}
		else
			ft_putstr_fd(tokens[i], 1);
		i++;
	}
	ft_putstr_fd("\n", 1);
	mini->exit_code = 0;
}
