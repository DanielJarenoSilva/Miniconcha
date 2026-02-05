/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 13:14:50 by djareno           #+#    #+#             */
/*   Updated: 2026/02/05 11:34:07 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

void	pwd(t_mini *mini)
{
	char	*tmp;

	tmp = ft_getenv(mini->envp, "PWD");
	if (tmp)
		printf("%s\n", tmp);
	mini->exit_code = 0;
}
