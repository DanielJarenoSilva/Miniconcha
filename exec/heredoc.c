/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 11:29:34 by djareno           #+#    #+#             */
/*   Updated: 2026/01/27 11:41:41 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/parse.h"
#include "exec.h"

int	heredoc_loop(char *delimiter, int expand, t_mini *mini)
{
	int		fd[2];
	pid_t	pid;
	char	*line;
	int		status;

	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
		close(fd[0]);
		while (1)
		{
			line = readline("> ");
			if (!line)
				break ;
			if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
			{
				free(line);
				break ;
			}
			if (expand)
				line = expand_token(line, mini);
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
			free(line);
		}
		close(fd[1]);
		exit(0);
	}
	close(fd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		close(fd[0]);
		mini->exit_code = 130;
		mini->heredoc_interrupted = 1;
		return (-1);
	}
	return (fd[0]);
}

int	apply_heredoc(t_node *node, int i, t_mini *mini)
{
	int	j;
	int	fd;

	j = 0;
	fd = -1;
	while (node->redirs[i].delimiter[j])
	{
		if (fd != -1)
			close(fd);
		fd = heredoc_loop(node->redirs[i].delimiter[j], node->redirs[i].expand,
				mini);
		if (fd == -1)
			return (-1);
		j++;
	}
	node->redirs[i].heredoc_fd = fd;
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}
