/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 09:43:59 by djareno           #+#    #+#             */
/*   Updated: 2026/01/08 11:47:22 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	ft_clean(t_gnllist **list, t_gnllist *new_node, char *buffer)
{
	t_gnllist	*temp;

	if (!list || !*list)
		return ;
	while (*list)
	{
		temp = (*list)->next;
		free((*list)->content);
		free((*list));
		*list = temp;
	}
	*list = NULL;
	if (new_node && new_node->content && new_node->content[0])
		*list = new_node;
	else
	{
		free(buffer);
		free(new_node);
	}
}

static void	ft_clean_list(t_gnllist **list)
{
	t_gnllist	*last;
	t_gnllist	*new;
	int		x;
	int		y;
	char	*buffer;

	if (!list || !*list)
		return ;
	last = ft_lstlast_gnl(*list);
	buffer = malloc(BUFFER_SIZE + 1);
	new = malloc(sizeof(t_gnllist));
	if (!buffer || !new || !last || !last->content)
		return (free(buffer), free(new));
	x = 0;
	y = 0;
	while (last->content[x] && last->content[x] != '\n')
		x++;
	if (last->content[x] == '\n')
		x++;
	while (last->content[x] && y < BUFFER_SIZE)
		buffer[y++] = last->content[x++];
	buffer[y] = '\0';
	new->content = buffer;
	new->next = NULL;
	ft_clean(list, new, buffer);
}

static char	*ft_make_newline(t_gnllist *list)
{
	int		len;
	char	*new_line;

	if (!list)
		return (NULL);
	len = ft_str_size(list);
	new_line = (char *)malloc(len + 1);
	if (!new_line)
		return (NULL);
	new_line = ft_make_str(list, new_line);
	if (!new_line)
		return (NULL);
	return (new_line);
}

static void	ft_make_lst(int fd, t_gnllist **list)
{
	char	*buffer;
	int		bytes;
	t_gnllist	*lst;

	while (!ft_find_next_line(*list))
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return ;
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes <= 0)
		{
			free (buffer);
			return ;
		}
		buffer[bytes] = '\0';
		lst = malloc(sizeof(t_gnllist));
		if (!lst)
			return (free(buffer));
		lst->content = buffer;
		lst->next = NULL;
		ft_lstadd_back_gnl(list, lst);
	}
}

char	*get_next_line(int fd)
{
	static t_gnllist	*list;
	char				*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ft_make_lst(fd, &list);
	if (!list)
		return (ft_clean_list(&list), NULL);
	next_line = ft_make_newline(list);
	if (!next_line)
		return (NULL);
	ft_clean_list(&list);
	return (next_line);
}
