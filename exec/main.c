/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfuto <kfuto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 20:40:24 by kfuto             #+#    #+#             */
/*   Updated: 2026/02/03 22:56:10 by kfuto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/parse.h"
#include "exec.h"

static int	process_single_node(t_mini *mini, int i)
{
	pid_t	pid;
	int		status;

	if (mini->is_pipe)
	{
		run_pipes(mini);
		return (0);
	}
	if (pb(mini->nodes[i]->tokens[0]))
		exec_builtin(mini->nodes[i], mini);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			if (mini->nodes[i]->redirs)
			{
				mini->is_fork = 1;
				apply_redirs(mini->nodes[i], mini);
			}
			if (mini->nodes[i]->tokens[0]
				&& is_builtin(mini->nodes[i]->tokens[0]))
			{
				exec_builtin(mini->nodes[i], mini);
				exit(mini->exit_code);
			}
			exec_cmd(mini->nodes[i]->tokens, mini);
			exit(mini->exit_code);
		}
		else
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				mini->exit_code = WEXITSTATUS(status);
		}
	}
	return (0);
}

void	process_nodes(t_mini *mini)
{
	int	i;

	i = 0;
	if (mini->is_pipe)
	{
		process_single_node(mini, i);
		return ;
	}
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
