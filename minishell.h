/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 10:55:23 by djareno           #+#    #+#             */
/*   Updated: 2025/12/01 13:03:34 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_node
{
    char			**tokens;
}   t_node;

typedef struct s_mini
{
    t_node			*nodes;
}   t_mini;

char	**parser(const char *s);
int        ft_isnode(char c);
int        ft_count_nodes(const char *s);
char    *word_dup(const char *start, int len);


#endif