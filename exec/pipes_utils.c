/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 10:45:49 by djareno           #+#    #+#             */
/*   Updated: 2026/01/29 10:49:08 by djareno          ###   ########.fr       */
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
