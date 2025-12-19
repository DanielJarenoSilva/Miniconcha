/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 10:54:49 by djareno           #+#    #+#             */
/*   Updated: 2025/12/19 11:16:45 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*rl;
	char	**t;
	//char	*expanded;
	//char	*temp;
	t_mini	mini;
	char	*cmd;

	argc = 0;
	argv = NULL;
	mini.exit_code = 0;
	mini.envp = dup_env(envp);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		g_signal_state = 1;
		rl = readline("minishell > ");
		g_signal_state = 0;
		if (!rl)
			break ;
		if (*rl)
		{
			add_history(rl);
			t = tokenizer(rl);
			if (ft_strncmp(t[0], "cd", 2) == 0)
				cd(mini, t);
			else if (ft_strncmp(t[0], "pwd", 3) == 0)
				pwd(mini);
			else if (ft_strncmp(t[0], "env", 3) == 0)
				env(mini);
			else if (ft_strncmp(t[0], "exit", 4) == 0)
				my_exit(mini);
			else
			{
				cmd = save_exec_cmd(rl, mini);
				//ft_putstr_fd(cmd, 1);
			}
			/*
			for (int i = 0; t[i]; i++)
			{
				expanded = expand_token(t[i], envp);
				t[i] = expanded;
				printf("token %d: %s\n", i, t[i]);
			}*/
		}
	}
	return (0);
}
