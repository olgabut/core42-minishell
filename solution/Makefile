
NAME = minishell
CC = cc
CFLAGS = #-Wall -Wextra -Werror -g -O0
LIBFT_DIR = libft
SRC_DIR = src

SRC_FILES = minishell.c \
	lexer/lexer.c

OBJS_FILES = $(SRC_FILES:%.c=%.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I. -I$(LIBFT_DIR) -c $< -o $@

$(NAME): $(OBJS_FILES)
	@$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS_FILES) -L$(LIBFT_DIR) -lft -lreadline -o $(NAME)

clean:
	rm -f $(OBJS_FILES)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
