/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:27:09 by djareno           #+#    #+#             */
/*   Updated: 2025/04/16 10:32:16 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	while (dst[x] != '\0' && x < size)
		x++;
	y = x;
	while (src[x - y] != '\0' && x + 1 < size)
	{
		dst[x] = src[x - y];
		x++;
	}
	if (y < size)
		dst[x] = '\0';
	return (y + ft_strlen(src));
}
