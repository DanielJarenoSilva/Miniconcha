
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

typedef enum e_redir_type
{
    REDIR_IN,
    REDIR_OUT,
    REDIR_APPEND,
    HEREDOC
} t_redir_type;

typedef struct s_redir
{
    t_redir_type   type;
    char           *file;
} t_redir;


typedef struct s_node
{
    char    **tokens;    
    t_redir *redirs;       
    int     redir_count;
    int     expand;
} t_node;

typedef struct s_mini
{
	t_node	**nodes;
	int		exit_code;
	char	*output;
	char	**envp;
}			t_mini;

#endif
