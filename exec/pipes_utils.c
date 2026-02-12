/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfuto <kfuto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 10:45:49 by djareno           #+#    #+#             */
/*   Updated: 2026/02/12 16:27:24 by kfuto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <unistd.h>

void	init_fd(int fd[2])
{
	fd[0] = -1;
	fd[1] = -1;
}

int	create_pipe(int fd[2])
{
	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (1);
	}
	return (0);
}

int ft_strcmp_strict(char *str, char *std)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (std[i] == '\0' || std[i] != str[i])
			return (0);
		i++;
	}
	return (1);
}
