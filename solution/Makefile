NAME = minishell
CC = cc
MODE ?= debug
CFLAGS = -Wall -Wextra -Werror  
DFLAGS = -g -O0 -fsanitize=address,undefined
ifeq ($(MODE),debug)
	CFLAGS += $(DFLAGS)
endif


READLINE_INC = /opt/homebrew/opt/readline/include
READLINE_LIB = /opt/homebrew/opt/readline/lib

LIBFT_DIR = libft
INC_DIR = inc
BUILD = build

LINKER_FLAGS = -L$(LIBFT_DIR) -L$(READLINE_LIB) -L$(INC_DIR) -lft -lreadline
PREPROC_FLAGS = -I. -I$(LIBFT_DIR) -I$(READLINE_INC) -I$(INC_DIR)

SRC_FILES_WITH_MAIN = minishell.c $(SRC_FILES)
SRC_FILES = lexer/lexer.c \
	lexer/line_lexer.c \
	lexer/token_list_manager.c \
	lexer/lexical_errors.c \
	lexer/need_next_line.c \
	signals/signals.c \
	parser/parse.c \
	parser/parser_cases.c \
	parser/check_word.c \
	parser/expand_variables.c \
	parser/handle_dollar.c \
	parser/env_utils.c \
	parser/print_parsed_commands.c \
	utils/init.c \
	env/init_env.c \
	env/env_list_manager.c

TEST_NAME = tests
TEST_DIR = test
TEST_FILES = $(SRC_FILES) \
	test/test.c \
	test/test_lexer.c

SRC_TEST_PARSER = $(SRC_FILES) \
	$(addprefix $(TEST_DIR)/, \
	test_parser.c \
	test_parser_utils.c \
	)
OBJ_TEST_PARSER = $(SRC_TEST_PARSER:%.c=$(BUILD)/%.o)
TEST_FLAGS = -I$(TEST_DIR) -lcriterion

OBJS_TEST_FILES = $(TEST_FILES:%.c=$(BUILD)/%.o)
OBJS_FILES = $(SRC_FILES_WITH_MAIN:%.c=$(BUILD)/%.o)

all: $(NAME)

$(BUILD)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(PREPROC_FLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) MODE=$(MODE)

$(NAME): $(OBJS_FILES) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_FILES) $(LINKER_FLAGS) -o $(NAME)

tests: $(OBJS_TEST_FILES) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_TEST_FILES) $(LINKER_FLAGS) -o $(TEST_NAME)

test_parser: $(OBJ_TEST_PARSER) $(LIBFT)
	$(CC) $(CFLAGS) $(TEST_FLAGS) $(OBJ_TEST_PARSER) $(LINKER_FLAGS) -o $(TEST_NAME)
	./$(TEST_NAME)

clean:
	rm -rf $(BUILD)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(TEST_NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
