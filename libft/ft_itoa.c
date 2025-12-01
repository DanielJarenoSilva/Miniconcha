/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 12:02:34 by djareno           #+#    #+#             */
/*   Updated: 2025/04/20 10:52:34 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nlen(int n)
{
	int	l;

	l = 0;
	if (n < 0)
	{
		n *= -1;
		l++;
	}
	while (n != 0)
	{
		n /= 10;
		l++;
	}
	return (l);
}

static char	*ft_convert(char *str, long int nb, int l)
{
	while (nb != 0)
	{
		str[l--] = nb % 10 + '0';
		nb /= 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			l;
	long int	nb;

	nb = n;
	l = ft_nlen(nb);
	if (nb == 0)
	{
		str = ft_calloc(2, sizeof(char));
		if (!str)
			return (0);
		str[0] = '0';
		return (str);
	}
	str = ft_calloc(l + 1, sizeof(char));
	if (!str)
		return (0);
	str[l--] = 0;
	if (nb < 0)
	{
		str[0] = '-';
		nb *= -1;
	}
	str = ft_convert(str, nb, l);
	return (str);
}
