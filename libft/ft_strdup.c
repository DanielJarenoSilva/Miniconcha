/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:26:08 by djareno           #+#    #+#             */
/*   Updated: 2025/04/16 10:14:35 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	*ft_strdup(const char *s)
{
	char	*c;
	size_t	size;
	size_t	x;

	size = ft_strlen(s);
	c = malloc(sizeof(char) * (size + 1));
	if (c == NULL)
		return (0);
	x = 0;
	while (x < size)
	{
		c[x] = s[x];
		x++;
	}
	c[x] = '\0';
	return (c);
}
