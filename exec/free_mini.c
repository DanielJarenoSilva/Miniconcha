/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfuto <kfuto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 15:02:36 by djareno           #+#    #+#             */
/*   Updated: 2026/02/02 13:24:59 by kfuto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	if (!tokens)
		return ;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

void	free_redirs(t_redir *redirs, int count)
{
	int	i;

	i = 0;
	if (!redirs)
		return ;
	while (i < count)
	{
		ft_free_matrix(redirs[i].delimiter);
		if (redirs[i].file)
			free(redirs[i].file);
		i++;
	}
	free(redirs);
}

void	free_nodes(t_node **nodes)
{
	int	i;

	i = 0;
	if (!nodes)
		return ;
	while (nodes[i])
	{
		free_tokens(nodes[i]->tokens);
		free_redirs(nodes[i]->redirs, nodes[i]->redir_count);
		free(nodes[i]);
		i++;
	}
	free(nodes);
}

void	free_env(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return ;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

void	free_mini(t_mini *mini)
{
	if (!mini)
		return ;
	free_nodes(mini->nodes);
	mini->nodes = NULL;
	free_env(mini->envp);
	mini->envp = NULL;
	if (mini->output)
	{
		free(mini->output);
		mini->output = NULL;
	}
}
