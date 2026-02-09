/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfuto <kfuto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 17:06:33 by kfuto             #+#    #+#             */
/*   Updated: 2026/02/09 03:56:35 by kfuto            ###   ########.fr       */
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

int resolve_all_heredocs(t_mini *mini)
{
    int i;

    i = 0;
    while (mini->nodes && mini->nodes[i])
    {
        for (int j = 0; j < mini->nodes[i]->redir_count; j++)
        {
            if (mini->nodes[i]->redirs[j].type == HEREDOC)
            {
                apply_heredoc(mini->nodes[i], j, mini);
                if (mini->heredoc_interrupted)
                    return (1);
            }
        }
        i++;
    }
    return (0);
}
