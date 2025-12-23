/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:33:51 by djareno           #+#    #+#             */
/*   Updated: 2025/12/23 12:08:29 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	**dup_env(char **envp)
{
	int		i;
	char	**copy;

	i = 0;
	while (envp[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		copy[i] = strdup(envp[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

char	*ft_getenv(char **envp, char *env)
{
	int			i;
	char		*tmp;
	size_t		y;
	int			x;

	i = 0;
	x = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], env, ft_strlen(env)) == 0)
		{
			y = ft_strlen(env) + 2;
			tmp = malloc(ft_strlen(envp[i]) - ft_strlen(env) + 1);
			while (y < ft_strlen(envp[i]))
			{
				tmp[x] = envp[i][y];
				x++;
				y++;
			}
			tmp[x] = '\0';
			return (tmp);
		}
		i++;
	}
	return (NULL);
}

void	ft_free_matrix(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

void	print_error_cmd(char *cmd)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 20);
}
