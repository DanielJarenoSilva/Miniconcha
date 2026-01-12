/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 10:55:23 by djareno           #+#    #+#             */
/*   Updated: 2026/01/12 13:20:46 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "../exec/exec.h"
# include "../minishell.h"

typedef struct s_node	t_node;
typedef struct s_mini	t_mini;

char					**get_nodes(const char *s, struct s_mini *mini);
int						ft_isnode(char c);
int						ft_count_nodes(const char *s);
char					*word_dup(const char *start, int len);
void					parser(const char *s, t_mini *mini);
int						ft_ispipe(char c, t_mini *mini);
int						ft_isquote(char c);
char					**tokenizer(const char *s, t_node *node);
void					get_tookens(t_mini *mini);
int						has_single_quotes(char *s);
void					expand_tokens(t_node *node, t_mini *mini);
char					*expand_token(char *str, t_mini *mini);
char					*ft_strjoin_free(char *s1, char *s2);
char					*ft_strjoin_char_free(char *s, char c);
char					*get_env_value(char **envp, char *key);
char					*expand_var(char *str, int *i, t_mini *mini);
int						ft_ischev(char c);
int						handle_redir(const char *s, int *i, t_node *node);
char					*get_next_word(const char *s, int *i);
void					add_redir(t_node *node, t_redir_type type, char *file);
void					print_nodes(t_mini mini);
char					*handle_single_quote(char *str, int *i, char *result);
char					*handle_double_quote(char *str, int *i, char *result,
							t_mini *mini);
int						get_quotes(const char *s);
char					*handle_dollar_single_quote(char *str, int *i,
							char *result);

#endif