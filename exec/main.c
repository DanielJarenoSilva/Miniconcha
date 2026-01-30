/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfuto <kfuto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 20:40:24 by kfuto             #+#    #+#             */
/*   Updated: 2026/01/30 19:06:13 by kfuto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/parse.h"
#include "exec.h"

static void	process_cmd(t_mini *mini, int i)
{
	char	*cmd;

	cmd = save_exec_cmd(mini->nodes[i], mini);
	if (cmd && *cmd)
		ft_putstr_fd(cmd, 1);
	free(cmd);
}

static int	process_single_node(t_mini *mini, int i)
{
	int	stdin_backup;
	int	stdout_backup;

	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	if (mini->nodes[i]->redirs)
	{
		apply_redirs(mini->nodes[i], mini);
		if (mini->heredoc_interrupted)
		{
			mini->heredoc_interrupted = 0;
			dup_stdin(stdin_backup, stdout_backup);
			return (1);
		}
	}
	if (mini->is_pipe)
	{
		run_pipes(mini);
		dup_stdin(stdin_backup, stdout_backup);
		return (1);
	}
	if (mini->nodes[i]->tokens && mini->nodes[i]->tokens[0])
		process_cmd(mini, i);
	dup_stdin(stdin_backup, stdout_backup);
	return (0);
}

void	process_nodes(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->nodes && mini->nodes[i])
	{
		if (process_single_node(mini, i))
			break ;
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
