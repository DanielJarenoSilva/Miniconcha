/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfuto <kfuto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 22:47:40 by kfuto             #+#    #+#             */
/*   Updated: 2026/01/27 20:09:26 by kfuto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/parse.h"
#include "exec.h"

void	heredoc_loop(int i, t_node *node, int expand, t_mini *mini)
{
	char	*line;
	char	*expanded;
	int		k;

	k = 0;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	while (node->redirs[i].delimiter[k])
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, node->redirs[i].delimiter[k],
				ft_strlen(node->redirs[i].delimiter[k]) + 1) == 0)
			k++;
		if (expand)
		{
			expanded = expand_token(line, mini);
			free(line);
		}
		else
			expanded = line;
		if (expand)
			free(expanded);
	}
}

void	apply_heredoc(t_node *node, int i, t_mini *mini)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return ;
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
		exec_heredoc(i, fd, node, mini);
	else
		heredoc_father(fd, pid, mini);
}

void	heredoc_father(int fd[], pid_t pid, t_mini *mini)
{
	int	status;

	close(fd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		mini->exit_code = 130;
		mini->heredoc_interrupted = 1;
		close(fd[0]);
		return ;
	}
	dup2(fd[0], STDIN_FILENO);
}

void	exec_heredoc_cmd(char **tokens, t_mini *mini)
{
	char	**path_dirs;
	char	*path_cmd;

	if (is_builtin(tokens[0]))
	{
		exec_builtin(mini->nodes[0], mini);
		return ;
	}
	path_dirs = get_path_dirs(mini->envp);
	if (!path_dirs)
	{
		print_error_cmd(tokens[0]);
		exit(127);
	}
	path_cmd = find_cmd(tokens[0], path_dirs);
	if (path_dirs)
		ft_free_matrix(path_dirs);
	if (!path_cmd)
	{
		print_error_cmd(tokens[0]);
		exit(127);
	}
	execve(path_cmd, tokens, mini->envp);
	perror("execve");
	free(path_cmd);
}
