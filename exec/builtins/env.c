/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 13:14:38 by djareno           #+#    #+#             */
/*   Updated: 2026/01/21 10:48:29 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

void	env(t_mini *mini)
{
	int	i;

	i = 0;
	if (!mini->envp)
	{
		mini->exit_code = 1;
		perror("env");
	}
	while (mini->envp[i])
	{
		ft_putstr_fd(mini->envp[i], 1);
		printf("\n");
		i++;
	}
	mini->exit_code = 0;
}
