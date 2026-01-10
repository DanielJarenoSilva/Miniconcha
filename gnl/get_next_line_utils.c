/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfuto <kfuto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 09:44:19 by djareno           #+#    #+#             */
/*   Updated: 2026/01/10 20:59:27 by kfuto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_gnllist	*ft_lstlast_gnl(t_gnllist *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_gnl(t_gnllist **lst, t_gnllist *new)
{
	t_gnllist	*last;

	if (lst && new)
	{
		if (*lst)
		{
			last = ft_lstlast_gnl(*lst);
			last->next = new;
		}
		else
			*lst = new;
	}
}

int	ft_find_next_line(t_gnllist *list)
{
	int	x;

	if (!list)
		return (0);
	while (list)
	{
		x = 0;
		while (list->content && list->content[x])
		{
			if (list->content[x] == '\n')
				return (1);
			x++;
		}
		list = list->next;
	}
	return (0);
}

int	ft_str_size(t_gnllist *list)
{
	int	i;
	int	len;

	if (!list)
		return (0);
	len = 0;
	while (list)
	{
		i = 0;
		while (list->content[i])
		{
			if (list->content[i] == '\n')
				return (len + 1);
			++i;
			++len;
		}
		list = list->next;
	}
	return (len);
}

char	*ft_make_str(t_gnllist *list, char *new_line)
{
	int	x;
	int	y;

	if (!list || !new_line)
		return (NULL);
	y = 0;
	while (list)
	{
		x = 0;
		while (list->content[x])
		{
			if (list->content[x] == '\n')
			{
				new_line[y++] = '\n';
				new_line[y] = '\0';
				return (new_line);
			}
			new_line[y++] = list->content[x++];
		}
		list = list->next;
	}
	new_line[y] = '\0';
	return (new_line);
}
