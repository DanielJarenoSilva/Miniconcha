/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabalvar <pabalvar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 23:08:41 by kfuto             #+#    #+#             */
/*   Updated: 2026/01/21 12:58:16 by pabalvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	apply_redir_in(t_node *node, int i)
{
	int	fd;

	fd = open(node->redirs[i].file, O_RDONLY);
	if (fd < 0)
	{
		perror(node->redirs[i].file);
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	apply_redir_out(t_node *node, int i)
{
	int	fd;

	fd = open(node->redirs[i].file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(node->redirs[i].file);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	apply_redir_append(t_node *node, int i)
{
	int	fd;

	fd = open(node->redirs[i].file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(node->redirs[i].file);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	apply_heredoc(t_node *node, int i, t_mini *mini)
{
	int	fd;

	fd = handle_heredoc(node->redirs[i].file, node->redirs[i].expand, mini);
	if (fd < 0)
		return ;
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	empty_heredoc(t_mini *mini)
{
	if (mini)
	printf("cualquier cosa \n");
}

void	exec_heredoc_cmd(char **tokens, t_mini mini)
{
	char	**path_dirs;
	char	*path_cmd;

	if (!tokens || !tokens[0])
	{
		empty_heredoc(&mini);
	}
	// signal(SIGINT, SIG_DFL);
	// signal(SIGQUIT, SIG_DFL);
	path_dirs = get_path_dirs(mini.envp);
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
	execve(path_cmd, tokens, mini.envp);
	perror("execve");
	free(path_cmd);
}
