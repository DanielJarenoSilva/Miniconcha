#include "exec.h"
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	handle_heredoc(const char *delimiter)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	while (1)
	{
		line = readline("> "); // Prompt heredoc
		if (!line)             // Ctrl+D
			break ;
		if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd[1], line, strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	close(fd[1]); // Cerramos el extremo de escritura
	return (fd[0]); // Devolvemos el extremo de lectura
}

int	has_redir_out(t_node *node)
{
	for (int i = 0; i < node->redir_count; i++)
		if (node->redirs[i].type == REDIR_OUT
			|| node->redirs[i].type == REDIR_APPEND)
			return (1);
	return (0);
}

void	apply_redirs(t_node *node)
{
	int	fd;

	for (int i = 0; i < node->redir_count; i++)
	{
		if (node->redirs[i].type == REDIR_IN)
		{
			fd = open(node->redirs[i].file, O_RDONLY);
			if (fd < 0)
			{
				perror(node->redirs[i].file);
				exit(1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (node->redirs[i].type == REDIR_OUT)
		{
			fd = open(node->redirs[i].file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd < 0)
			{
				perror(node->redirs[i].file);
				exit(1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (node->redirs[i].type == REDIR_APPEND)
		{
			fd = open(node->redirs[i].file, O_CREAT | O_WRONLY | O_APPEND,
					0644);
			if (fd < 0)
			{
				perror(node->redirs[i].file);
				exit(1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (node->redirs[i].type == HEREDOC)
		{
			int heredoc_fd = handle_heredoc(node->redirs[i].file);
				// file = delimitador
			dup2(heredoc_fd, STDIN_FILENO);
			close(heredoc_fd);
		}
	}
}
