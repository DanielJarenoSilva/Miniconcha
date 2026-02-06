/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfuto <kfuto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 20:40:24 by kfuto             #+#    #+#             */
/*   Updated: 2026/02/06 17:32:14 by kfuto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/parse.h"
#include "exec.h"

void	process_node_aux(t_mini *mini, int i)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);

	if (mini->nodes[i]->redirs && mini->nodes[i]->redir_count > 0
		&& !mini->is_pipe)
	{
		mini->is_fork = 1;
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
	pid_t	pid;
	int		status;

	if (mini->nodes[i]->wrong_redir)
		return (0);
	if (mini->is_pipe)
		return (run_pipes(mini), 0);
	if (mini->nodes[i]->tokens[0] && pb(mini->nodes[i]->tokens[0]))
		exec_pb(mini, i);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			process_node_aux(mini, i);
			exit(0);
		}
		else
		{
			waitpid(pid, &status, 0);
			if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
				write(2, "Quit (core dumped)\n", 20);
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
				if (mini->nodes[0] && mini->nodes[0]->wrong_redir == 0)
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
