/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 12:31:22 by djareno           #+#    #+#             */
/*   Updated: 2025/12/19 10:51:30 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	g_signal_state = 0;

void	sigint_handler(int sign)
{
	(void)sign;
	write(1, "\n", 1);
	if (g_signal_state == 1)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
