/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 13:14:53 by djareno           #+#    #+#             */
/*   Updated: 2026/02/05 11:35:33 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

void	aux(t_mini *mini, int i)
{
	while (mini->envp[i])
	{
		mini->envp[i] = mini->envp[i + 1];
		i++;
	}
}

void	unset(t_mini *mini, char **tokens)
{
	int	arg;
	int	i;
	int	len;

	arg = 1;
	while (tokens[arg])
	{
		len = ft_strlen(tokens[arg]);
		i = 0;
		while (mini->envp[i])
		{
			if (ft_strncmp(mini->envp[i], tokens[arg], len) == 0
				&& mini->envp[i][len] == '=')
			{
				free(mini->envp[i]);
				aux(mini, i);
				break ;
			}
			i++;
		}
		arg++;
	}
	mini->exit_code = 0;
}
