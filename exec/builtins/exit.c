/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 13:14:43 by djareno           #+#    #+#             */
/*   Updated: 2026/02/05 12:04:45 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

void	free_exit(t_mini *mini, int exitcode)
{
	free_mini(mini);
	exit(exitcode);
}

int	my_exit(t_mini *mini, char	**args)
{
	if (!args[1])
		free_exit(mini, mini->exit_code);
	if (!ft_isnum(args[1]))
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		free_exit(mini, 255);
	}
	if (args[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		(*mini).exit_code = 1;
		return (1);
	}
	free_exit(mini, ft_atoi(args[1]));
	return (0);
}
