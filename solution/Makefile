
NAME = minishell
CC = cc
CFLAGS = -g -O0 -Wall -Wextra -Werror  #-fsanitize=address

READLINE_INC = /opt/homebrew/opt/readline/include
READLINE_LIB = /opt/homebrew/opt/readline/lib

LIBFT_DIR = libft
SRC_DIR = src

SRC_FILES = minishell.c \
	lexer/lexer.c \
	lexer/line_lexer.c \
	lexer/token_list_manager.c \
	lexer/lexical_errors.c \
	lexer/need_next_line.c \
	signals/signals.c

OBJS_FILES = $(SRC_FILES:%.c=%.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I. -I$(LIBFT_DIR) -I$(READLINE_INC) -c $< -o $@

$(NAME): $(OBJS_FILES)
	@$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS_FILES) -L$(LIBFT_DIR) -L$(READLINE_LIB) -lft -lreadline -o $(NAME)

clean:
	rm -f $(OBJS_FILES)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
