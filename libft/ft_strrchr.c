/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:09:25 by djareno           #+#    #+#             */
/*   Updated: 2025/04/16 10:03:32 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		x;
	char	y;

	x = ft_strlen(s);
	y = c;
	if (y == 0)
		return ((char *) &s[x]);
	while (x >= 0)
	{
		if (s[x] == y)
			return ((char *)&s[x]);
		x--;
	}
	return (0);
}
