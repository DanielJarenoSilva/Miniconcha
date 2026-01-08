/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabalvar <pabalvar@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 10:54:49 by djareno           #+#    #+#             */
/*   Updated: 2025/12/20 12:30:00 by pabalvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "../parse/parse.h"

void	print_nodes(struct s_mini mini)
{
	int	i;
	int	j;

	i = 0;
	while (mini.nodes && mini.nodes[i])
	{
		j = 0;
		printf("Node %d:\n", i);
		while (mini.nodes[i]->tokens && mini.nodes[i]->tokens[j])
		{
			printf("  Token %d: %s\n", j, mini.nodes[i]->tokens[j]);
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char			*cmd;
	char			*rl;
	struct s_mini	mini;
	int				i;

	(void)argc;
	(void)argv;

	mini.exit_code = 0;
	mini.envp = dup_env(envp);
	mini.output = NULL;
	mini.nodes = NULL;
	
	//TESTEAR $///////////////////////
	
	//mini.envp[0] = ft_strdup("TEST=42");

	/////////////////////////////////////////

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);

	while (1)
	{
		g_signal_state = 1;
		rl = readline("minishell > ");
		g_signal_state = 0;
		if (!rl)
		{
			ft_putstr_fd("exit\n", 1);
			free_mini(&mini);
			break ;
		}
		if (*rl)
		{
			add_history(rl);	
			parser(rl, &mini);
			if (ft_strchr(rl, '|'))
			{
				run_pipes(&mini);
			}
			else
			{
				// print_nodes(mini);		
				i = 0;
				while (mini.nodes && mini.nodes[i])
				{
					if (mini.nodes[i]->tokens && mini.nodes[i]->tokens[0])
					{
						cmd = save_exec_cmd(mini.nodes[i], &mini);
						if (cmd && *cmd)
						{
							ft_putstr_fd(cmd, 1);
						}
						free(cmd);
					}
					i++;
				}
			}
		}
	}
	// print_nodes(mini);
	return (0);
}
