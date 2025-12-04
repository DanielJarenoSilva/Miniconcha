/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 11:09:14 by djareno           #+#    #+#             */
/*   Updated: 2025/12/04 11:17:11 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t old, size_t new)
{
	void	*new_ptr;
	size_t	copy_size;

	if (new == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (!ptr)
		return (malloc(new));
	new_ptr = malloc(new);
	if (!new_ptr)
		return (NULL);
	if (old < new)
		copy_size = old;
	else
		copy_size = new;
	ft_memcpy(new_ptr, ptr, copy_size);
	free(ptr);
	return (new_ptr);
}
