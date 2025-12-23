NAME = minishell

LIBFT_DIR = ./libft

CFLAGS = -Wall -Wextra -Werror
CC = cc

SRCS =  ./exec/main.c \
        ./parse/parse.c \
        ./parse/expand.c \
        ./parse/parseutils.c \
        ./exec/builtins.c \
        ./exec/cmd.c \
        ./exec/pipex.c \
        ./exec/signals.c \
        ./exec/utils.c \
        ./gnl/get_next_line.c \
        ./gnl/get_next_line_utils.c \
        ./exec/redir.c \
        ./parse/redir_parser.c 



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