/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfuto <kfuto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 12:31:22 by djareno           #+#    #+#             */
/*   Updated: 2026/01/30 19:02:50 by kfuto            ###   ########.fr       */
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

void	exec_heredoc(int i, int fd[], t_node *node, t_mini *mini)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	close(fd[0]);
	heredoc_loop(i, node, node->redirs[i].expand,
		mini);
	close(fd[1]);
	exit(0);
}

void	dup_stdin(int stdin_backup, int stdout_backup)
{
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
}

void	init_mini(t_mini *mini, char **envp)
{
	mini->exit_code = 0;
	mini->envp = dup_env(envp);
	update_shlvl(mini);
	mini->output = NULL;
	mini->nodes = NULL;
	mini->is_pipe = 0;
	mini->builtin_quote = 0;
	mini->heredoc_interrupted = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
