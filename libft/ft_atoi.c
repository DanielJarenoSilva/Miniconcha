/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:47:52 by djareno           #+#    #+#             */
/*   Updated: 2025/04/16 10:45:56 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *n)
{
	int	x;
	int	signo;
	int	num;

	num = 0;
	x = 0;
	signo = 1;
	while (*n == 32 || (*n >= 9 && *n <= 13))
		n++;
	if (*n == '-')
		signo *= -1;
	if (*n == '+' || *n == '-')
		n++;
	while (*n >= '0' && *n <= '9')
	{
		num = num * 10 + (n[x] - '0');
		n++;
	}
	return (num * signo);
}
