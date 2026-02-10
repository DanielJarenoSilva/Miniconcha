/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfuto <kfuto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 12:31:22 by djareno           #+#    #+#             */
/*   Updated: 2026/02/10 01:28:41 by kfuto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int		g_signal_state = 0;

void	sigint_heredoc(int sig)
{
	int fd;

	(void)sig;
	fd = 3;
	while (fd < 20)
		close(fd++);
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
	mini->is_fork = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

int	ft_strcmp_exact(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (s1[i] == '\0' && s2[i] == '\0')
		return (1);
	else
		return (0);
}
