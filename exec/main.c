/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 20:40:24 by kfuto             #+#    #+#             */
/*   Updated: 2026/01/21 10:54:16 by djareno          ###   ########.fr       */
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
	int		num_nodes;
	int		i;
	t_node	*node;

	if (!mini->nodes || !mini->nodes[0])
		return ;
	num_nodes = 0;
	while (mini->nodes[num_nodes])
		num_nodes++;
	node = mini->nodes[0];
	if (num_nodes > 1 && node->tokens && node->tokens[0] && pb(node->tokens[0]))
	{
		if (node->redir_count > 0)
			apply_redirs(node, mini);
		exec_builtin(node, mini);
		i = 1;
		while (mini->nodes[i])
		{
			mini->nodes[i - 1] = mini->nodes[i];
			i++;
		}
		mini->nodes[i - 1] = NULL;
		num_nodes--;
	}
	process_utils(mini, node, num_nodes);
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
