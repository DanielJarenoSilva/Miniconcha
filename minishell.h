/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 10:55:23 by djareno           #+#    #+#             */
/*   Updated: 2025/12/11 12:39:11 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <dirent.h>

char	**tokenizer(const char *s);
char	*expand_token(char *str, char **envp);
void	exec_cmd(const char *cmdline, char **envp);
int		set_env(char **envp, const char *key, const char *value);
char	*ft_strjoin_free(char *s1, char *s2);
char	*ft_strjoin_char_free(char *s, char c);
char	**dup_env(char **envp);
char	*ft_getenv(char **envp, char *env);
#endif