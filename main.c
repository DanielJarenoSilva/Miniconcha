/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 10:54:49 by djareno           #+#    #+#             */
/*   Updated: 2025/12/11 12:39:30 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	/*char	*rl;
	char	**t;*/
	//char	*expanded;
	//int		pid;
	char	**menvp;
	char	*temp;

	menvp = dup_env(envp);
	temp = ft_getenv(menvp, "OLDPWD");
	printf("OLDPWD=%s\n", temp);
	set_env(menvp, "OLDPWD", "aaaaaaaaaaaa");
	temp = ft_getenv(menvp, "OLDPWD");
	printf("OLDPWD=%s\n", temp);
	argc = 0;
	argv = NULL;

	/*while (1)
	{
		rl = readline("minishell > ");
		if (!rl)
			break ;
		if (*rl)
		{
			add_history(rl);
			t = tokenizer(rl);
			pid = fork();
			if (pid == 0)
			{
				exec_cmd(rl, envp);
				exit (1);
			}
			else
				waitpid(pid, NULL, 0);
			for (int i = 0; t[i]; i++)
			{
				expanded = expand_token(t[i], envp);
				t[i] = expanded;
				printf("token %d: %s\n", i, t[i]);
			}
		}
	}*/
	return (0);
}
