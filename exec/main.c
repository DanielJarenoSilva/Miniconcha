/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfuto <kfuto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 20:40:24 by kfuto             #+#    #+#             */
/*   Updated: 2026/01/12 16:37:46 by kfuto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/parse.h"
#include "exec.h"

static void	init_mini(t_mini *mini, char **envp)
{
	mini->exit_code = 0;
	mini->envp = dup_env(envp);
	update_shlvl(mini);
	mini->output = NULL;
	mini->nodes = NULL;
	mini->is_pipe = 0;
	mini->builtin_quote = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

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

static void	process_nodes(t_mini *mini)
{
	char	*cmd;
	int		i;

	i = 0;
	if (mini->is_pipe == 1)
	{
		run_pipes(mini);
		mini->is_pipe = 0;
		return ;
	}
	else
	{
		while (mini->nodes && mini->nodes[i])
		{
			if (mini->nodes[i]->tokens && mini->nodes[i]->tokens[0])
			{
				cmd = save_exec_cmd(mini->nodes[i], mini);
				if (cmd && *cmd)
					ft_putstr_fd(cmd, 1);
				free(cmd);
			}
			i++;
		}
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
