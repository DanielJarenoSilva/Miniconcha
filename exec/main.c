/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfuto <kfuto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 20:40:24 by kfuto             #+#    #+#             */
/*   Updated: 2026/01/27 17:35:02 by kfuto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/parse.h"
#include "exec.h"

static int	handle_readline(t_mini *mini, char **rl)
{
	g_signal_state = 1;
	*rl = readline("minishell > ");
	g_signal_state = 0;
	if (!*rl)
	{
		ft_putstr_fd("exit\n", 1);
		free_mini(mini);
		return (0);
	}
	return (1);
}

static void	process_cmd(t_mini *mini, int i)
{
	char	*cmd;

	cmd = save_exec_cmd(mini->nodes[i], mini);
	if (cmd && *cmd)
		ft_putstr_fd(cmd, 1);
	free(cmd);
}

void	process_nodes(t_mini *mini)
{
	int	i;
	int	stdin_backup;
	int	stdout_backup;

	i = 0;
	while (mini->nodes && mini->nodes[i])
	{
		stdin_backup = dup(STDIN_FILENO);
		stdout_backup = dup(STDOUT_FILENO);
		if (mini->nodes[i]->redirs)
			apply_redirs(mini->nodes[i], mini);
		if (mini->is_pipe)
		{
			run_pipes(mini);
			dup_stdin(stdin_backup, stdout_backup);
			break ;
		}
		if (mini->nodes[i]->tokens && mini->nodes[i]->tokens[0])
			process_cmd(mini, i);
		dup_stdin(stdin_backup, stdout_backup);
		i++;
	}
}

static void	mini_loop(t_mini *mini)
{
	char	*rl;

	while (1)
	{
		if (!handle_readline(mini, &rl))
			break ;
		if (*rl)
		{
			add_history(rl);
			free_nodes(mini->nodes);
			mini->nodes = NULL;
			parser(rl, mini);
			process_nodes(mini);
		}
		free(rl);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;

	(void)argc;
	(void)argv;
	init_mini(&mini, envp);
	mini_loop(&mini);
	return (0);
}
