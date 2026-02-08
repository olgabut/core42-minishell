
NAME = minishell
CC = cc
CFLAGS = -g -O0 -Wall -Wextra -Werror  #-fsanitize=address

READLINE_INC = /opt/homebrew/opt/readline/include
READLINE_LIB = /opt/homebrew/opt/readline/lib

LIBFT_DIR = libft
SRC_DIR = src
BUILD = build

SRC_FILES_WITH_MAIN = minishell.c $(SRC_FILES)
SRC_FILES = lexer/lexer.c \
	lexer/line_lexer.c \
	lexer/token_list_manager.c \
	lexer/lexical_errors.c \
	lexer/need_next_line.c \
	signals/signals.c \
	parser/parse.c

TEST_NAME = tests
TEST_FILES = $(SRC_FILES) \
	test/test.c \
	test/test_lexer.c

OBJS_TEST_FILES = $(TEST_FILES:%.c=$(BUILD)/%.o)
OBJS_FILES = $(SRC_FILES_WITH_MAIN:%.c=$(BUILD)/%.o)

all: $(NAME)

$(BUILD)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I. -I$(LIBFT_DIR) -I$(READLINE_INC) -c $< -o $@

$(NAME): $(OBJS_FILES)
	@$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS_FILES) -L$(LIBFT_DIR) -L$(READLINE_LIB) -lft -lreadline -o $(NAME)

tests: $(OBJS_TEST_FILES)
	@$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS_TEST_FILES) -L$(LIBFT_DIR) -lft -lreadline -o $(TEST_NAME)

clean:
	rm -rf $(BUILD)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(TEST_NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
