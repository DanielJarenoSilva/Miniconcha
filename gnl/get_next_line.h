/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfuto <kfuto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 09:44:33 by djareno           #+#    #+#             */
/*   Updated: 2026/01/10 20:59:38 by kfuto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_gnlist
{
	char			*content;
	struct s_gnlist	*next;
}					t_gnllist;
char				*get_next_line(int fd);
t_gnllist			*ft_lstlast_gnl(t_gnllist *lst);
void				ft_lstadd_back_gnl(t_gnllist **lst, t_gnllist *new);
int					ft_find_next_line(t_gnllist *list);
int					ft_str_size(t_gnllist *list);
char				*ft_make_str(t_gnllist *list, char *new_line);

#endif