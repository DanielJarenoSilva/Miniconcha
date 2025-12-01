/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 11:32:59 by djareno           #+#    #+#             */
/*   Updated: 2025/04/20 11:40:46 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	buffer[11];
	int		i;

	i = 0;
	if (n == 0)
		write(fd, "0", 1);
	if (n < 0)
		write(fd, "-", 1);
	if (n == -2147483648)
	{
		write (fd, "2147483648", 10);
		return ;
	}
	while (n)
	{
		if (n < 0)
			n = n * -1;
		buffer[i++] = (n % 10) + '0';
		n /= 10;
	}
	while (i--)
	{
		write (fd, &buffer[i], 1);
	}
}
