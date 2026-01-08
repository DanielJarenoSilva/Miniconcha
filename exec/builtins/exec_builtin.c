/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 14:24:49 by djareno           #+#    #+#             */
/*   Updated: 2026/01/07 15:50:49 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

int	is_builtin(char *cmd)
{
	return (ft_strncmp(cmd, "cd", ft_strlen("cd")) == 0
		|| ft_strncmp(cmd, "echo", ft_strlen("echo")) == 0
		|| ft_strncmp(cmd, "pwd", ft_strlen("pwd")) == 0
		|| ft_strncmp(cmd, "exit", ft_strlen("exit")) == 0
		|| ft_strncmp(cmd, "export", ft_strlen("export")) == 0
		|| ft_strncmp(cmd, "unset", ft_strlen("unset")) == 0
		|| ft_strncmp(cmd, "env", ft_strlen("env")) == 0);
}

int	exec_builtin(char **tokens, t_mini *mini)
{
	if (ft_strncmp(tokens[0], "pwd", ft_strlen("pwd")) == 0)
		return (pwd(mini), 0);
	else if (ft_strncmp(tokens[0], "cd", ft_strlen("cd")) == 0)
		return (cd(mini, tokens), 0);
	else if (ft_strncmp(tokens[0], "exit", ft_strlen("exit")) == 0)
		return (my_exit(mini, tokens), 0);
	else if (ft_strncmp(tokens[0], "echo", ft_strlen("echo")) == 0)
		return (echo(mini, tokens), 0);
	else if (ft_strncmp(tokens[0], "env", ft_strlen("env")) == 0)
		return (env(mini), 0);
	else if (ft_strncmp(tokens[0], "export", ft_strlen("export")) == 0)
		return (export(mini, tokens), 0);
	else if (ft_strncmp(tokens[0], "unset", ft_strlen("unset")) == 0)
		return (unset(mini, tokens), 0);
	return (1);
}
