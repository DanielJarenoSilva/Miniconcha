/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:43:17 by djareno           #+#    #+#             */
/*   Updated: 2025/04/22 10:36:47 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		x;
	int		y;
	int		z;
	char	*str;

	x = 0;
	z = 0;
	y = ft_strlen(s1) - 1;
	if (!s1)
		return (0);
	if (!set)
		return (ft_strdup(s1));
	while (ft_strchr(set, s1[x]) != NULL && x < y)
		x++;
	while (ft_strchr(set, s1[y]) != NULL && y >= 0)
		y--;
	if (x > y)
		return (ft_strdup(""));
	str = malloc(y - x + 2);
	if (str == NULL)
		return (0);
	while (x <= y)
		str[z++] = s1[x++];
	str[z] = '\0';
	return (str);
}
