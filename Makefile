NAME = minishell

LIBFT_DIR = ./libft

CFLAGS = -Wall -Wextra -Werror
CC = cc

SRCS = main.c \
		tokenizer.c \
		expand.c \
		cmd.c \
		builtins.c \
		utils.c \
		pipex.c \
		./gnl/get_next_line.c \
		./gnl/get_next_line_utils.c \
		signals.c \

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