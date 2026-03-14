#include <criterion/criterion.h>
#include "minishell.h"
#include "test_parser_utils.h"

// --- TEST 1: Empty Input ---
Test(parser_suite, empty_tokens) 
{
    t_minishell ms;
    char *envp[] = {NULL};
    init_shell(&ms, envp);

    t_cmd *cmd_list = parser(&ms, NULL);

    cr_assert_null(cmd_list, "Parser should return NULL for empty token list.");
	free_memory_links(&(ms.memory_head));
}

// --- TEST 2: Simple Command ("ls -l") ---
Test(parser_suite, simple_command) 
{
    t_minishell ms;
    char *envp[] = {NULL};
    init_shell(&ms, envp);

    // Mocking tokens: [TOKEN_WORD: "ls"] -> [WORD: "-l"]
    t_token *tokens = NULL;
    tokens = add_token(tokens, TOKEN_WORD, "ls");    // Adjust 'WORD' to your actual enum name
    tokens = add_token(tokens, TOKEN_WORD, "-l");

    t_cmd *cmd_list = parser(&ms, tokens);

    cr_assert_not_null(cmd_list, "Command list should not be NULL.");
    cr_assert_str_eq(cmd_list->args[0], "ls", "First arg should be 'ls'");
    cr_assert_str_eq(cmd_list->args[1], "-l", "Second arg should be '-l'");
    cr_assert_null(cmd_list->args[2], "Args array must be NULL terminated");
    cr_assert_null(cmd_list->next, "Next command pointer should be NULL");

	free_memory_links(&(ms.memory_head));
}

// --- TEST 3: Piped Commands ("echo hello | wc -c") ---
Test(parser_suite, piped_command) 
{
    t_minishell ms;
    char *envp[] = {NULL};
    init_shell(&ms, envp);

    // Mocking tokens: [TOKEN_WORD:"echo"] -> [WORD:"hello"] -> [TOKEN_PIPE:"|"] -> [WORD:"wc"] -> [WORD:"-c"]
    t_token *tokens = NULL;
    tokens = add_token(tokens, TOKEN_WORD, "echo");
    tokens = add_token(tokens, TOKEN_WORD, "hello");
    tokens = add_token(tokens, TOKEN_PIPE, "|");
    tokens = add_token(tokens, TOKEN_WORD, "wc");
    tokens = add_token(tokens, TOKEN_WORD, "-c");

    t_cmd *cmd_list = parser(&ms, tokens);

    // Assert first command: echo hello
    cr_assert_not_null(cmd_list, "First command should exist.");
    cr_assert_str_eq(cmd_list->args[0], "echo");
    cr_assert_str_eq(cmd_list->args[1], "hello");
    cr_assert_not_null(cmd_list->next, "Pipe means next command should exist.");

    // Assert second command: wc -c
    t_cmd *next_cmd = cmd_list->next;
    cr_assert_str_eq(next_cmd->args[0], "wc");
    cr_assert_str_eq(next_cmd->args[1], "-c");
    cr_assert_null(next_cmd->next, "This should be the last command.");

	free_memory_links(&(ms.memory_head));
}
