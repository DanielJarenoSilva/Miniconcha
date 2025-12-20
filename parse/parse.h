/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabalvar <pabalvar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 10:55:23 by djareno           #+#    #+#             */
/*   Updated: 2025/12/19 15:23:38 by pabalvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include "../libft/libft.h"
# include "../minishell.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_node t_node;
typedef struct s_mini t_mini;

char		**get_nodes(const char *s);
int			ft_isnode(char c);
int			ft_count_nodes(const char *s);
char		*word_dup(const char *start, int len);
void		parser(const char *s, t_mini	*mini);
int			ft_ispipe(char c);
int			ft_isquote(char c);
char		**tokenizer(const char *s);
void		get_tookens(t_mini *mini);
int			has_single_quotes(char *s);
void		expand_tokens(t_node *node, t_mini mini);
char		*expand_token(char *str, t_mini mini);
char		*ft_strjoin_free(char *s1, char *s2);
char		*ft_strjoin_char_free(char *s, char c);
char		*get_env_value(char **envp, char *key);
char		*expand_var(char *str, int *i, t_mini mini);

void 		print_nodes(t_mini mini); 		//opcional eh(borrar luego)

#endif