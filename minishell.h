
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

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include "parse/parse.h"
# include "gnl/get_next_line.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include <dirent.h>

extern int	g_signal_state;

char	**tokenizer(const char *s);
char	*expand_token(char *str, t_mini mini);
void	exec_cmd(const char *cmdline, char **envp);
int		set_env(char **envp, const char *key, const char *value);
char	*ft_strjoin_free(char *s1, char *s2);
char	*ft_strjoin_char_free(char *s, char c);
char	**dup_env(char **envp);
char	*ft_getenv(char **envp, char *env);
void	cd(t_mini mini, char **cmd);
char	*run_pipex(char **cmd, t_mini mini);
void	pwd(t_mini mini);
void	env(t_mini mini);
void	my_exit(t_mini mini);
char	*save_exec_cmd(const char *cmdline, t_mini mini);
void	sigint_handler(int signo);
#endif
