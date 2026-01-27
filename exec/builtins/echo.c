/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 13:07:10 by djareno           #+#    #+#             */
/*   Updated: 2026/01/27 12:04:03 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

static void	print_tokens(t_mini *mini, char **tokens, int start, int print_nl)
{
	int		i;
	char	*value;

	i = start;
	while (tokens[i])
	{
		if (i > start)
			ft_putstr_fd(" ", 1);
		if (tokens[i][0] == '$')
		{
			value = ft_getenv(mini->envp, tokens[i] + 1);
			if (value)
				ft_putstr_fd(value, 1);
		}
		else
			ft_putstr_fd(tokens[i], 1);
		i++;
	}
	if (print_nl)
		ft_putstr_fd("\n", 1);
}

static int	is_n_flag(char *str)
{
	int	i;

	if (str[0] != '-')
		return (0);
	i = 1;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	check_tokens(t_node *node)
{
	int	i;

	i = 1;
	while (node->tokens[i] && is_n_flag(node->tokens[i]))
		i++;
	return (i);
}

void	echo(t_mini *mini, t_node *node)
{
	int	i;
	int	print_nl;

	if (!node || !node->tokens)
		return ;
	i = check_tokens(node);
	print_nl = (i == 1);
	print_tokens(mini, node->tokens, i, print_nl);
	mini->exit_code = 0;
}
