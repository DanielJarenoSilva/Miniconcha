/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabalvar <pabalvar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 10:55:23 by djareno           #+#    #+#             */
/*   Updated: 2025/12/15 15:03:04 by pabalvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_node
{
	char	**tokens;
}			t_node;

typedef struct s_mini
{
	t_node	**nodes;
}			t_mini;

char		**get_nodes(const char *s);
int			ft_isnode(char c);
int			ft_count_nodes(const char *s);
char		*word_dup(const char *start, int len);
void		parser(const char *s);
int			ft_ispipe(char c);
int			ft_isquote(char c);
void		print_nodes(t_mini mini);
char		**tokenizer(const char *s);
void		get_tookens(t_mini *mini);

#endif