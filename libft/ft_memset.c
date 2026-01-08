/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 12:39:44 by djareno           #+#    #+#             */
/*   Updated: 2025/04/16 10:29:36 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	x;
	char	*str;

	str = s;
	x = 0;
	while (x < n)
	{
		str[x] = (unsigned char)c;
		x++;
	}
	return (s);
}
