/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabalvar <pabalvar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 10:55:23 by djareno           #+#    #+#             */
/*   Updated: 2026/02/09 18:55:00 by pabalvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "gnl/get_next_line.h"
# include "libft/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>

extern int			g_signal_state;

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC
}					t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*file;
	char			**delimiter;
	int				expand;
	int				heredoc_index;
}					t_redir;

typedef struct s_node
{
	char			**tokens;
	t_redir			*redirs;
	int				redir_count;
	int				expand;
	int				wrong_redir;
}					t_node;

typedef struct s_mini
{
	t_node			**nodes;
	int				exit_code;
	int				is_pipe;
	int				builtin_quote;
	char			*output;
	char			**envp;
	int				heredoc_interrupted;
	int				is_fork;

}					t_mini;

#endif
