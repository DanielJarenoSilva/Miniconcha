/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 13:14:53 by djareno           #+#    #+#             */
/*   Updated: 2026/01/07 15:48:47 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

void	aux(t_mini *mini)
{
	int	k;

	k = 0;
	while (mini->envp[k])
	{
		mini->envp[k] = mini->envp[k + 1];
		k++;
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
				aux(mini);
				break ;
			}
			i++;
		}
		arg++;
	}
}
