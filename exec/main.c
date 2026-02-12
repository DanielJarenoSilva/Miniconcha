/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 20:40:24 by kfuto             #+#    #+#             */
/*   Updated: 2026/02/12 11:43:39 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/parse.h"
#include "exec.h"

void	process_node_aux(t_mini *mini, int i)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	mini->is_fork = 1;
	if (mini->nodes[i]->redirs && mini->nodes[i]->redir_count > 0
		&& !mini->is_pipe)
	{
		apply_redirs(mini->nodes[i], mini);
	}
	if (mini->nodes[i]->tokens[0] && is_builtin(mini->nodes[i]->tokens[0]))
	{
		exec_builtin(mini->nodes[i], mini);
		exit(mini->exit_code);
	}
	exec_cmd(mini->nodes[i]->tokens, mini);
	exit(mini->exit_code);
}

static int	process_single_node(t_mini *mini, int i)
{
	if (mini->nodes[i]->wrong_redir)
		return (0);
	if (mini->is_pipe)
		return (run_pipes(mini), 0);
	resolve_all_heredocs(mini);
	if (mini->heredoc_interrupted)
	{
		mini->exit_code = 130;
		mini->heredoc_interrupted = 0;
		return (0);
	}
	if (mini->nodes[i]->tokens[0] && pb(mini->nodes[i]->tokens[0]))
	{
		exec_pb(mini, i);
		return (0);
	}
	aux_node(mini, i);
	return (0);
}

void	process_nodes(t_mini *mini)
{
	int	i;

	i = 0;
	if (mini->heredoc_interrupted)
	{
		mini->heredoc_interrupted = 0;
		return ;
	}
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
		mini->heredoc_interrupted = 0;
		if (!handle_readline(mini, &rl))
			break ;
		if (*rl)
		{
			add_history(rl);
			free_nodes(mini->nodes);
			mini->nodes = NULL;
			parser(rl, mini);
			if (mini->is_pipe != -1)
			{
				if (mini->nodes && mini->nodes[0]
					&& mini->nodes[0]->wrong_redir == 0)
					process_nodes(mini);
			}
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
