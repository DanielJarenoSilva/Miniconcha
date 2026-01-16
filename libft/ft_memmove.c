/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:56:46 by djareno           #+#    #+#             */
/*   Updated: 2025/04/16 10:44:45 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				x;

	x = 0;
	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	if (src == NULL && dst == NULL)
		return (0);
	if (d > s && d < s + n)
	{
		while (n--)
			d[n] = s[n];
	}
	else
	{
		while (x < n)
		{
			d[x] = s[x];
			x++;
		}
	}
	return (dst);
}
