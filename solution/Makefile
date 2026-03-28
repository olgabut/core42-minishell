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
LIBFT		= $(LIBFT_DIR)/libft.a
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
	env/update_env.c \
	env/remove_env_node.c \
	env/init_env.c \
	env/env_utils.c \
	env/env_array.c \
	built_in/built_in.c \
	built_in/built_in_echo.c \
	built_in/built_in_pwd.c \
	built_in/built_in_exit.c \
	built_in/built_in_env.c \
	built_in/built_in_export.c \
	built_in/built_in_unset.c \
	built_in/built_in_cd.c \
	signals/signals.c \
	parser/parse.c \
	parser/parser_cases.c \
	parser/check_word.c \
	parser/expand_variables.c \
	parser/handle_dollar.c \
	parser/print_parsed_commands.c \
	parser/free_cmd.c \
	utils/init.c \
	executor/redirection.c \
	executor/execute.c \
	executor/cmd_path.c \
	executor/external_cmd.c

TEST_NAME = tests
TEST_DIR = test_src
TEST_MODE ?= test_parser
TEST_FILES = $(SRC_FILES) \
	$(TEST_DIR)/test_built_in.c \
	$(TEST_DIR)/test.c \
	$(TEST_DIR)/test_lexer.c

SRC_TEST_PARSER = $(SRC_FILES) \
	$(addprefix $(TEST_DIR)/, \
	test_parser.c \
	test_parser_utils.c \
	test_parser_here_doc.c \
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

test_parser: $(OBJ_TEST_PARSER) $(LIBFT) readline_mock
	$(CC) $(CFLAGS) $(TEST_FLAGS) $(OBJ_TEST_PARSER) $(LINKER_FLAGS) -o $(TEST_NAME)

readline_mock:
	gcc -shared -fPIC -o $(BUILD)/libreadline_mock.so $(TEST_DIR)/readline_mock.c -ldl

test_parser_with_mock: test_parser readline_mock

run_test: $(TEST_MODE)
	export LD_PRELOAD="/usr/lib/libasan.so.8:$(PWD)/$(BUILD)/libreadline_mock.so"
	./$(TEST_NAME)
	unset LD_PRELOAD

clean:
	unset LD_PRELOAD
	rm -rf $(BUILD)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(TEST_NAME)
	rm -f $(TEST_DIR)/libreadline_mock.so
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re tests test_parser readline_mock test_parser_with_mock 
