/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 12:31:22 by djareno           #+#    #+#             */
/*   Updated: 2026/01/27 11:38:18 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int		g_signal_state = 0;

void	sigint_heredoc(int sig)
{
	(void)sig;
	exit(130);
}

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

void	process_utils(t_mini *mini, t_node *node, int num_nodes)
{
	if (num_nodes > 1)
		run_pipes(mini);
	else
	{
		node = mini->nodes[0];
		if (!node)
			return ;
		if (node->redir_count > 0)
			apply_redirs(node, mini);
		if (node->tokens && node->tokens[0])
		{
			if (is_builtin(node->tokens[0]))
				exec_builtin(node, mini);
			else
				save_exec_cmd(node, mini);
		}
	}
}

