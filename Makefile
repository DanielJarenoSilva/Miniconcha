NAME = minishell

LIBFT_DIR = ./libft

CFLAGS = -Wall -Wextra -Werror -g3
CC = cc

SRCS =  ./exec/main.c \
        ./parse/parse.c \
        ./parse/expand.c \
        ./parse/parseutils.c \
        ./parse/parseutils2.c \
        ./exec/exec_cmd/cmd.c \
        ./exec/exec_cmd/exec_utils.c \
        ./exec/pipex.c \
        ./exec/signals.c \
        ./exec/utils.c \
        ./gnl/get_next_line.c \
        ./gnl/get_next_line_utils.c \
        ./exec/redir.c \
        ./exec/heredoc.c \
        ./parse/redir_parser.c \
        ./exec/builtins/echo.c \
        ./exec/builtins/pwd.c \
        ./exec/builtins/cd.c \
        ./exec/builtins/export.c \
        ./exec/builtins/sort_export.c \
        ./exec/builtins/unset.c \
        ./exec/builtins/env.c \
        ./exec/builtins/exit.c \
        ./exec/builtins/exec_builtin.c \
        ./exec/free_mini.c \
        ./parse/expand_helper.c \
        ./parse/print_nodes.c \
        ./parse/redirparseutils.c


OBJS = $(SRCS:.c=.o)

LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -lhistory -lncurses -o $(NAME)

%.o:%.c
		$(CC) $(CFLAGS) -I$(LIBFT_DIR)/include -I. -c $< -o $@

$(LIBFT):
		$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all