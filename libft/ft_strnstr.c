/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:17:48 by djareno           #+#    #+#             */
/*   Updated: 2025/04/16 10:00:04 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	x;
	size_t	y;

	x = 0;
	if (little[x] == '\0')
		return ((char *)big);
	while (big[x] != '\0')
	{
		y = 0;
		while (big[x + y] == little[y] && (x + y) < len)
		{
			if (big[x + y] == '\0' && little[y] == '\0')
				return ((char *)big + x);
			y++;
		}
		if (little[y] == '\0')
			return ((char *)big + x);
		x++;
	}
	return (0);
}
