/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabalvar <pabalvar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 10:55:23 by djareno           #+#    #+#             */
/*   Updated: 2026/02/12 01:07:20 by pabalvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../minishell.h"

typedef struct s_node	t_node;
typedef struct s_mini	t_mini;

void					apply_heredoc_file(int heredoc_index);
void					apply_heredoc_in(t_node *node, int i);
int						resolve_all_heredocs(t_mini *mini);
int						handle_out_redir(const char *s, int *i, t_node *node);
int						ft_strcmp_exact(const char *s1, const char *s2);
int						handle_readline(t_mini *mini, char **rl);
void					dup_stdin(int stdin_backup, int stdout_backup);
void					heredoc_loop(int i, t_node *node, t_mini *mini, int fd);
void					exec_heredoc(int i, int fd[], t_node *node,
							t_mini *mini);
char					**copy_envp(char **envp);
void					sort_envp(char **env);
void					exec_heredoc_cmd(char **tokens, t_mini *mini);
void					heredoc_father(int fd[], t_node *node, int i,
							t_mini *mini, pid_t pid);
void					exec_cmd(char **tokens, t_mini *mini);
int						set_env(char **envp, const char *key,
							const char *value);
char					*ft_strjoin_free(char *s1, char *s2);
char					*ft_strjoin_char_free(char *s, char c);
char					**dup_env(char **envp);
char					*ft_getenv(char **envp, char *env);
void					cd(t_mini *mini, char **cmd);
void					run_pipes(t_mini *mini);
void					pwd(t_mini *mini);
void					env(t_mini *mini);
int						my_exit(t_mini *mini, char **args);
char					*save_exec_cmd(t_node *node, t_mini *mini);
void					sigint_handler(int signo);
int						apply_redirs(t_node *node, t_mini *mini);
int						has_redir_out(t_node *node);
int						handle_heredoc(const char *delimiter, int expand,
							t_mini *mini);
void					ft_free_matrix(char **strs);
void					print_error_cmd(char *cmd);
int						is_builtin(char *cmd);
int						exec_builtin(t_node *node, t_mini *mini);
void					echo(t_mini *mini, t_node *node);
char					*read_fd(int fd);
char					**get_path_dirs(char **envp);
char					*find_cmd(char *cmd, char **path_dirs);
void					free_mini(t_mini *mini);
void					export(t_mini *mini, char **tokens);
void					unset(t_mini *mini, char **tokens);
void					apply_redir_in(t_node *node, int i);
void					apply_redir_out(t_node *node, int i);
void					apply_redir_append(t_node *node, int i);
void					apply_heredoc(t_node *node, int i, t_mini *mini);
void					update_shlvl(t_mini *mini);
void					sigint_heredoc(int sig);
void					free_nodes(t_node **nodes);
void					execute_node(t_mini *mini, int i);
int						pb(char *cmd);
void					process_utils(t_mini *mini, t_node *node,
							int num_nodes);
void					print_nodes(t_mini mini);
void					init_mini(t_mini *mini, char **envp);
int						create_pipe(int fd[2]);
void					init_fd(int fd[2]);
void					*ft_realloc(void *ptr, size_t size, size_t old_size);
void					setup_child(t_mini *mini, int i, int in_fd, int fd[2]);
void					exec_pb(t_mini *mini, int i);
void					wait_node(t_mini *mini, pid_t pid, int status);

#endif
