/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 14:24:49 by djareno           #+#    #+#             */
/*   Updated: 2026/02/06 11:11:42 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

int	is_builtin(char *cmd)
{
	return (ft_strncmp(cmd, "cd", ft_strlen("cd")) == 0 || ft_strncmp(cmd,
			"echo", ft_strlen("echo")) == 0 || ft_strncmp(cmd, "pwd",
			ft_strlen("pwd")) == 0 || ft_strncmp(cmd, "exit",
			ft_strlen("exit")) == 0 || ft_strncmp(cmd, "export",
			ft_strlen("export")) == 0 || ft_strncmp(cmd, "unset",
			ft_strlen("unset")) == 0 || ft_strncmp(cmd, "env",
			ft_strlen("env")) == 0);
}

int	exec_builtin(t_node *node, t_mini *mini)
{
	if (!node->tokens || !node->tokens[0])
		return (1);
	if ((ft_strncmp(node->tokens[0], "pwd", ft_strlen("pwd")) == 0)
		&& (ft_strlen(node->tokens[0]) == ft_strlen("pwd")))
		return (pwd(mini), 0);
	else if ((ft_strncmp(node->tokens[0], "cd", ft_strlen("cd")) == 0)
		&& (ft_strlen(node->tokens[0]) == ft_strlen("cd")))
		return (cd(mini, node->tokens), 0);
	else if ((ft_strncmp(node->tokens[0], "exit", ft_strlen("exit")) == 0)
		&& (ft_strlen(node->tokens[0]) == ft_strlen("exit")))
		return (my_exit(mini, node->tokens), 0);
	else if ((ft_strncmp(node->tokens[0], "echo", ft_strlen("echo")) == 0)
		&& (ft_strlen(node->tokens[0]) == ft_strlen("echo")))
		return (echo(mini, node), 0);
	else if ((ft_strncmp(node->tokens[0], "env", ft_strlen("env")) == 0)
		&& (ft_strlen(node->tokens[0]) == ft_strlen("env")))
		return (env(mini), 0);
	else if ((ft_strncmp(node->tokens[0], "export", ft_strlen("export")) == 0)
		&& (ft_strlen(node->tokens[0]) == ft_strlen("export")))
		return (export(mini, node->tokens), 0);
	else if ((ft_strncmp(node->tokens[0], "unset", ft_strlen("unset")) == 0)
		&& (ft_strlen(node->tokens[0]) == ft_strlen("unset")))
		return (unset(mini, node->tokens), 0);
	print_error_cmd(node->tokens[0]);
	return (1);
}

int	pb(char *cmd)
{
	if (!cmd)
		return (0);
	return (ft_strncmp(cmd, "cd", 3) == 0 || ft_strncmp(cmd, "unset", 5) == 0
		|| ft_strncmp(cmd, "exit", 4) == 0
		|| ft_strncmp(cmd, "export", 4) == 0);
}

void	exec_pb(t_mini *mini, int i)
{
	int		save_stdin;
	int		save_stdout;

	save_stdin = dup(STDIN_FILENO);
	save_stdout = dup(STDOUT_FILENO);
	if (mini->nodes[i]->redirs && mini->nodes[i]->redir_count > 0)
		apply_redirs(mini->nodes[i], mini);
	exec_builtin(mini->nodes[i], mini);
	dup2(save_stdin, STDIN_FILENO);
	dup2(save_stdout, STDOUT_FILENO);
	close(save_stdin);
	close(save_stdout);
}
