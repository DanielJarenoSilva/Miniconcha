/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 20:40:24 by kfuto             #+#    #+#             */
/*   Updated: 2026/01/27 12:53:18 by djareno          ###   ########.fr       */
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

void	process_nodes(t_mini *mini)
{
	int		i;
	int		stdin_backup;
	int		stdout_backup;

	if (!mini->nodes || !mini->nodes[0])
		return ;
	if (mini->is_pipe)
		return (run_pipes(mini));
	i = 0;
	while (mini->nodes[i])
	{
		stdin_backup = dup(STDIN_FILENO);
		stdout_backup = dup(STDOUT_FILENO);

		if (mini->nodes[i]->redir_count > 0)
		{
			if (apply_redirs(mini->nodes[i], mini) == -1)
			{
				dup2(stdin_backup, STDIN_FILENO);
				dup2(stdout_backup, STDOUT_FILENO);
				close(stdin_backup);
				close(stdout_backup);
				return ;
			}
		}
		if (mini->nodes[i]->tokens && mini->nodes[i]->tokens[0]
			&& pb(mini->nodes[i]->tokens[0]))
			exec_builtin(mini->nodes[i], mini);
		else if (mini->nodes[i]->tokens && mini->nodes[i]->tokens[0])
			save_exec_cmd(mini->nodes[i], mini);

		dup2(stdin_backup, STDIN_FILENO);
		dup2(stdout_backup, STDOUT_FILENO);
		close(stdin_backup);
		close(stdout_backup);

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
