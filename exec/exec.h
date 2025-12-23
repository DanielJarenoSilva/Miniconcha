
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 10:55:23 by djareno           #+#    #+#             */
/*   Updated: 2025/12/19 11:23:02 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../minishell.h"

typedef struct s_node t_node;
typedef struct s_mini t_mini;

// char	*expand_token(char *str, t_mini mini);
void	exec_cmd(char **cmdline, char **envp);
int		set_env(char **envp, const char *key, const char *value);
char	*ft_strjoin_free(char *s1, char *s2);
char	*ft_strjoin_char_free(char *s, char c);
char	**dup_env(char **envp);
char	*ft_getenv(char **envp, char *env);
void	cd(t_mini mini, char **cmd);
char    *run_pipex(t_node **nodes, t_mini mini);
void	pwd(t_mini mini);
void	env(t_mini mini);
void	my_exit(t_mini mini);
char	*save_exec_cmd(t_node *node, t_mini mini);
void	sigint_handler(int signo);
void      apply_redirs(t_node *node);
int     has_redir_out(t_node *node);
int     handle_heredoc(const char *delimiter);

#endif
