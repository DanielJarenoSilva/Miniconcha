/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 13:14:50 by djareno           #+#    #+#             */
/*   Updated: 2026/01/08 10:58:38 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

void	pwd(t_mini *mini)
{
	char	*tmp;

	tmp = ft_getenv(mini->envp, "PWD");
	printf("%s\n", tmp);
	free(tmp);
	mini->exit_code = 0;
}
