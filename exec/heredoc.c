/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 10:07:13 by djareno           #+#    #+#             */
/*   Updated: 2026/02/03 17:31:48 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/parse.h"
#include "exec.h"

// void	heredoc_loop(int i, t_node *node, int expand, t_mini *mini)
// {
// 	char	*line;
// 	int		k;

// 	k = 0;
// 	signal(SIGINT, SIG_DFL);
// 	signal(SIGQUIT, SIG_IGN);
// 	line = NULL;
// 	while (node->redirs[i].delimiter[k])
// 	{
// 		line = readline("> ");
// 		if (!line)
// 			break ;
// 		if (expand)
// 			line = expand_token(line, mini);
// 		if (ft_strncmp(line, node->redirs[i].delimiter[k],
// 				ft_strlen(node->redirs[i].delimiter[k] + 1)) == 0)
// 		{
// 			free(line);
// 			k++;
// 		}
// 	}
// }

void	heredoc_loop(int i, t_node *node, int expand, t_mini *mini)
{
	char	*line;
	char	*expanded;
	char	*str;
	int		k;

	str = ft_strdup("");
	k = 0;
	while (node->redirs[i].delimiter[k])
	{
		line = readline("> ");
		ft_strjoin_free(str, line);
		ft_strjoin_char_free(str, '\n');
		if (!line)
			break ;
		if (ft_strncmp(line, node->redirs[i].delimiter[k],
				ft_strlen(line)) == 0)
		{
			free(line);
			k++;
			continue ;
		}
		if (expand)
			expanded = expand_token(line, mini);
		if (expand)
			free(expanded);
	}
	printf("str : %s\n",str);
	k = 0;
	while (node->tokens[k])
		k++;
	node->tokens[k] = str;
}

void	exec_heredoc(int i, int fd[], t_node *node, t_mini *mini)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	close(fd[0]);
	heredoc_loop(i, node, node->redirs[i].expand, mini);
	close(fd[1]);
	exit(0);
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
		exit(130);
	}
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
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
