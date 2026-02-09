/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabalvar <pabalvar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 17:06:33 by kfuto             #+#    #+#             */
/*   Updated: 2026/02/09 18:58:11 by pabalvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	handle_readline(t_mini *mini, char **rl)
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

void	*ft_realloc(void *ptr, size_t size, size_t old_size)
{
	void	*new_ptr;

	if (ptr == NULL)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(size);
	if (new_ptr == NULL)
		return (NULL);
	ft_memcpy(new_ptr, ptr, old_size);
	free(ptr);
	return (new_ptr);
}

void	pipes_aux(t_mini *mini, int i, int in_fd, int *fd)
{
	setup_child(mini, i, in_fd, fd);
}

int	resolve_all_heredocs(t_mini *mini)
{
	int	i;
	int	j;
	int	global_index;

	i = 0;
	global_index = 0;
	while (mini->nodes && mini->nodes[i])
	{
		j = 0;
		while (j < mini->nodes[i]->redir_count)
		{
			if (mini->nodes[i]->redirs[j].type == HEREDOC)
			{
				mini->nodes[i]->redirs[j].heredoc_index = global_index;
				apply_heredoc(mini->nodes[i], j, mini);
				if (mini->heredoc_interrupted)
					return (1);
				global_index++;
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	wait_node(t_mini *mini, pid_t pid, int status)
{
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
		write(2, "Quit (core dumped)\n", 20);
	if (WIFEXITED(status))
		mini->exit_code = WEXITSTATUS(status);
}

void	apply_heredoc_in(t_node *node, int i)
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