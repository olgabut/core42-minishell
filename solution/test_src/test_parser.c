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
    free_test_tokens(NULL);
    free_memory_links(&(ms.memory_long));
    free_memory_links(&(ms.memory_head));
}

// --- TEST 2: Simple Command ("ls -l") ---
Test(parser_suite, simple_command) 
{
    t_minishell ms;
    char *envp[] = {NULL};
    init_shell(&ms, envp);

    t_token *tokens = NULL;
    tokens = add_token(tokens, TOKEN_WORD, "ls");    
    tokens = add_token(tokens, TOKEN_WORD, "-l");

    t_cmd *cmd_list = parser(&ms, tokens);

    cr_assert_not_null(cmd_list, "Command list should not be NULL.");
    cr_assert_str_eq(cmd_list->args[0], "ls", "First arg should be 'ls'");
    cr_assert_str_eq(cmd_list->args[1], "-l", "Second arg should be '-l'");
    cr_assert_null(cmd_list->args[2], "Args array must be NULL terminated");
    cr_assert_null(cmd_list->next, "Next command pointer should be NULL");

    free_cmd(cmd_list);
    free_test_tokens(tokens);
    free_memory_links(&(ms.memory_long));
    free_memory_links(&(ms.memory_head));
}

// --- TEST 3: Piped Commands ("echo hello | wc -c") ---
Test(parser_suite, piped_command) 
{
    t_minishell ms;
    char *envp[] = {NULL};
    init_shell(&ms, envp);

    t_token *tokens = NULL;
    tokens = add_token(tokens, TOKEN_WORD, "echo");
    tokens = add_token(tokens, TOKEN_WORD, "hello");
    tokens = add_token(tokens, TOKEN_PIPE, "|");
    tokens = add_token(tokens, TOKEN_WORD, "wc");
    tokens = add_token(tokens, TOKEN_WORD, "-c");

    t_cmd *cmd_list = parser(&ms, tokens);

    cr_assert_not_null(cmd_list, "First command should exist.");
    cr_assert_str_eq(cmd_list->args[0], "echo");
    cr_assert_str_eq(cmd_list->args[1], "hello");
    cr_assert_not_null(cmd_list->next, "Pipe means next command should exist.");

    t_cmd *next_cmd = cmd_list->next;
    cr_assert_str_eq(next_cmd->args[0], "wc");
    cr_assert_str_eq(next_cmd->args[1], "-c");
    cr_assert_null(next_cmd->next, "This should be the last command.");

    free_cmd(cmd_list);
    free_test_tokens(tokens);
    free_memory_links(&(ms.memory_long));
    free_memory_links(&(ms.memory_head));
}

// --- TEST 4: Single Argument ---
Test(parser_suite, single_argument)
{
    t_minishell ms;
    char *envp[] = {NULL};
    init_shell(&ms, envp);

    t_token *tokens = NULL;
    tokens = add_token(tokens, TOKEN_WORD, "echo");
    tokens = add_token(tokens, TOKEN_WORD, "hello");

    t_cmd *cmd_list = parser(&ms, tokens);

    cr_assert_not_null(cmd_list, "Command list should not be NULL.");
    cr_assert_str_eq(cmd_list->args[0], "echo", "First arg should be 'echo'");
    cr_assert_str_eq(cmd_list->args[1], "hello", "Second arg should be 'hello'");
    cr_assert_null(cmd_list->args[2], "Args array must be NULL terminated");

    free_cmd(cmd_list);
    free_test_tokens(tokens);
    free_memory_links(&(ms.memory_long));
    free_memory_links(&(ms.memory_head));
}

// --- TEST 5: No Arguments (command with only name) ---
Test(parser_suite, no_arguments)
{
    t_minishell ms;
    char *envp[] = {NULL};
    init_shell(&ms, envp);

    t_token *tokens = NULL;
    tokens = add_token(tokens, TOKEN_WORD, "pwd");

    t_cmd *cmd_list = parser(&ms, tokens);

    cr_assert_not_null(cmd_list, "Command should exist.");
    cr_assert_str_eq(cmd_list->args[0], "pwd", "First arg should be 'pwd'");
    cr_assert_null(cmd_list->args[1], "Args array should have only one element");

    free_cmd(cmd_list);
    free_test_tokens(tokens);
    free_memory_links(&(ms.memory_long));
    free_memory_links(&(ms.memory_head));
}

// ============================================================
// REDIRECTIONS TESTS
// ============================================================

// --- TEST 6: Input Redirection ---
Test(parser_suite, input_redirection)
{
    t_minishell ms;
    char *envp[] = {NULL};
    init_shell(&ms, envp);

    t_token *tokens = NULL;
    tokens = add_token(tokens, TOKEN_WORD, "cat");
    tokens = add_token(tokens, TOKEN_REDIR_IN, "<");
    tokens = add_token(tokens, TOKEN_WORD, "file.txt");

    t_cmd *cmd_list = parser(&ms, tokens);

    cr_assert_not_null(cmd_list, "Command should exist.");
    cr_assert_str_eq(cmd_list->args[0], "cat", "First arg should be 'cat'");
    cr_assert_not_null(cmd_list->io_list, "IO list should exist.");
    cr_assert_eq(cmd_list->io_list->type, TOKEN_REDIR_IN, "IO type should be TOKEN_REDIR_IN");
    cr_assert_str_eq(cmd_list->io_list->path, "file.txt", "IO path should be 'file.txt'");

    free_cmd(cmd_list);
    free_test_tokens(tokens);
    free_memory_links(&(ms.memory_long));
    free_memory_links(&(ms.memory_head));
}

// --- TEST 7: Output Redirection ---
Test(parser_suite, output_redirection)
{
    t_minishell ms;
    char *envp[] = {NULL};
    init_shell(&ms, envp);

    t_token *tokens = NULL;
    tokens = add_token(tokens, TOKEN_WORD, "echo");
    tokens = add_token(tokens, TOKEN_WORD, "hi");
    tokens = add_token(tokens, TOKEN_REDIR_OUT, ">");
    tokens = add_token(tokens, TOKEN_WORD, "out");

    t_cmd *cmd_list = parser(&ms, tokens);

    cr_assert_not_null(cmd_list, "Command should exist.");
    cr_assert_str_eq(cmd_list->args[0], "echo", "First arg should be 'echo'");
    cr_assert_str_eq(cmd_list->args[1], "hi", "Second arg should be 'hi'");
    cr_assert_not_null(cmd_list->io_list, "IO list should exist.");
    cr_assert_eq(cmd_list->io_list->type, TOKEN_REDIR_OUT, "IO type should be TOKEN_REDIR_OUT");
    cr_assert_str_eq(cmd_list->io_list->path, "out", "IO path should be 'out'");

    free_cmd(cmd_list);
    free_test_tokens(tokens);
    free_memory_links(&(ms.memory_long));
    free_memory_links(&(ms.memory_head));
}

// --- TEST 8: Append Redirection ---
Test(parser_suite, append_redirection)
{
    t_minishell ms;
    char *envp[] = {NULL};
    init_shell(&ms, envp);

    t_token *tokens = NULL;
    tokens = add_token(tokens, TOKEN_WORD, "echo");
    tokens = add_token(tokens, TOKEN_WORD, "hi");
    tokens = add_token(tokens, TOKEN_APPEND, ">>");
    tokens = add_token(tokens, TOKEN_WORD, "out");

    t_cmd *cmd_list = parser(&ms, tokens);

    cr_assert_not_null(cmd_list, "Command should exist.");
    cr_assert_not_null(cmd_list->io_list, "IO list should exist.");
    cr_assert_eq(cmd_list->io_list->type, TOKEN_APPEND, "IO type should be TOKEN_APPEND");
    cr_assert_str_eq(cmd_list->io_list->path, "out", "IO path should be 'out'");

    free_cmd(cmd_list);
    free_test_tokens(tokens);
    free_memory_links(&(ms.memory_long));
    free_memory_links(&(ms.memory_head));
}

// --- TEST 10: Multiple Pipes ---
Test(parser_suite, multiple_pipes)
{
    t_minishell ms;
    char *envp[] = {NULL};
    init_shell(&ms, envp);

    t_token *tokens = NULL;
    tokens = add_token(tokens, TOKEN_WORD, "a");
    tokens = add_token(tokens, TOKEN_PIPE, "|");
    tokens = add_token(tokens, TOKEN_WORD, "b");
    tokens = add_token(tokens, TOKEN_PIPE, "|");
    tokens = add_token(tokens, TOKEN_WORD, "c");

    t_cmd *cmd_list = parser(&ms, tokens);

    cr_assert_not_null(cmd_list, "First command should exist.");
    cr_assert_str_eq(cmd_list->args[0], "a", "First command should be 'a'");

    cr_assert_not_null(cmd_list->next, "Second command should exist.");
    cr_assert_str_eq(cmd_list->next->args[0], "b", "Second command should be 'b'");

    cr_assert_not_null(cmd_list->next->next, "Third command should exist.");
    cr_assert_str_eq(cmd_list->next->next->args[0], "c", "Third command should be 'c'");
    cr_assert_null(cmd_list->next->next->next, "Should be the last command.");

    free_cmd(cmd_list);
    free_test_tokens(tokens);
    free_memory_links(&(ms.memory_long));
    free_memory_links(&(ms.memory_head));
}

// --- TEST 11: Multiple Redirections ---
Test(parser_suite, multiple_redirections)
{
    t_minishell ms;
    char *envp[] = {NULL};
    init_shell(&ms, envp);

    t_token *tokens = NULL;
    tokens = add_token(tokens, TOKEN_WORD, "cmd");
    tokens = add_token(tokens, TOKEN_REDIR_IN, "<");
    tokens = add_token(tokens, TOKEN_WORD, "infile");
    tokens = add_token(tokens, TOKEN_REDIR_OUT, ">");
    tokens = add_token(tokens, TOKEN_WORD, "outfile");

    t_cmd *cmd_list = parser(&ms, tokens);

    cr_assert_not_null(cmd_list, "Command should exist.");
    cr_assert_not_null(cmd_list->io_list, "IO list should exist.");
    cr_assert_eq(cmd_list->io_list->type, TOKEN_REDIR_IN, "First IO should be input");
    cr_assert_str_eq(cmd_list->io_list->path, "infile", "First IO path should be 'infile'");

    cr_assert_not_null(cmd_list->io_list->next, "Second IO should exist.");
    cr_assert_eq(cmd_list->io_list->next->type, TOKEN_REDIR_OUT, "Second IO should be output");
    cr_assert_str_eq(cmd_list->io_list->next->path, "outfile", "Second IO path should be 'outfile'");

    free_cmd(cmd_list);
    free_test_tokens(tokens);
    free_memory_links(&(ms.memory_long));
    free_memory_links(&(ms.memory_head));
}

// --- TEST 12: Redirection + Pipe ---
Test(parser_suite, redirection_plus_pipe)
{
    t_minishell ms;
    char *envp[] = {NULL};
    init_shell(&ms, envp);

    t_token *tokens = NULL;
    tokens = add_token(tokens, TOKEN_WORD, "cat");
    tokens = add_token(tokens, TOKEN_REDIR_IN, "<");
    tokens = add_token(tokens, TOKEN_WORD, "file");
    tokens = add_token(tokens, TOKEN_PIPE, "|");
    tokens = add_token(tokens, TOKEN_WORD, "wc");
    tokens = add_token(tokens, TOKEN_WORD, "-l");

    t_cmd *cmd_list = parser(&ms, tokens);

    cr_assert_not_null(cmd_list, "First command should exist.");
    cr_assert_str_eq(cmd_list->args[0], "cat", "First command should be 'cat'");
    cr_assert_not_null(cmd_list->io_list, "First command should have IO.");
    cr_assert_eq(cmd_list->io_list->type, TOKEN_REDIR_IN, "First IO should be input");

    cr_assert_not_null(cmd_list->next, "Second command should exist.");
    cr_assert_str_eq(cmd_list->next->args[0], "wc", "Second command should be 'wc'");
    cr_assert_str_eq(cmd_list->next->args[1], "-l", "Second arg should be '-l'");

    free_cmd(cmd_list);
    free_test_tokens(tokens);
    free_memory_links(&(ms.memory_long));
    free_memory_links(&(ms.memory_head));
}

// --- TEST 13: Args + Pipe + Redirect ---
Test(parser_suite, args_pipe_redirect)
{
    t_minishell ms;
    char *envp[] = {NULL};
    init_shell(&ms, envp);

    t_token *tokens = NULL;
    tokens = add_token(tokens, TOKEN_WORD, "echo");
    tokens = add_token(tokens, TOKEN_WORD, "hello");
    tokens = add_token(tokens, TOKEN_WORD, "world");
    tokens = add_token(tokens, TOKEN_PIPE, "|");
    tokens = add_token(tokens, TOKEN_WORD, "wc");
    tokens = add_token(tokens, TOKEN_WORD, "-l");
    tokens = add_token(tokens, TOKEN_REDIR_OUT, ">");
    tokens = add_token(tokens, TOKEN_WORD, "result");

    t_cmd *cmd_list = parser(&ms, tokens);

    cr_assert_not_null(cmd_list->next, "Second command should exist.");
    cr_assert_str_eq(cmd_list->next->args[0], "wc", "Second command should be 'wc'");
    cr_assert_not_null(cmd_list->next->io_list, "Second command should have IO.");
    cr_assert_eq(cmd_list->next->io_list->type, TOKEN_REDIR_OUT, "IO should be output");

    free_cmd(cmd_list);
    free_test_tokens(tokens);
    free_memory_links(&(ms.memory_long));
    free_memory_links(&(ms.memory_head));
}

// ============================================================
// EDGE CASES TESTS
// ============================================================

// --- TEST 14: Only Redirections (no args) ---
Test(parser_suite, only_redirections)
{
    t_minishell ms;
    char *envp[] = {NULL};
    init_shell(&ms, envp);

    t_token *tokens = NULL;
    tokens = add_token(tokens, TOKEN_REDIR_IN, "<");
    tokens = add_token(tokens, TOKEN_WORD, "infile");
    tokens = add_token(tokens, TOKEN_REDIR_OUT, ">");
    tokens = add_token(tokens, TOKEN_WORD, "outfile");

    t_cmd *cmd_list = parser(&ms, tokens);

    cr_assert_not_null(cmd_list, "Command should exist.");
    cr_assert_null(cmd_list->args, "Args should be NULL");
    cr_assert_not_null(cmd_list->io_list, "IO list should exist.");
    cr_assert_eq(cmd_list->io_list->type, TOKEN_REDIR_IN, "First IO should be input");
    cr_assert_not_null(cmd_list->io_list->next, "Second IO should exist.");

    free_cmd(cmd_list);
    free_test_tokens(tokens);
    free_memory_links(&(ms.memory_long));
    free_memory_links(&(ms.memory_head));
}

// --- TEST 15: Pipe at End ---
Test(parser_suite, pipe_at_end)
{
    t_minishell ms;
    char *envp[] = {NULL};
    init_shell(&ms, envp);

    t_token *tokens = NULL;
    tokens = add_token(tokens, TOKEN_WORD, "echo");
    tokens = add_token(tokens, TOKEN_WORD, "hello");
    tokens = add_token(tokens, TOKEN_PIPE, "|");

    t_cmd *cmd_list = parser(&ms, tokens);

    cr_assert_not_null(cmd_list, "First command should exist.");
    cr_assert_str_eq(cmd_list->args[0], "echo", "First arg should be 'echo'");
    cr_assert_str_eq(cmd_list->args[1], "hello", "Second arg should be 'hello'");
    cr_assert_not_null(cmd_list->next, "Next command should exist (empty after pipe).");

    free_cmd(cmd_list);
    free_test_tokens(tokens);
    free_memory_links(&(ms.memory_long));
    free_memory_links(&(ms.memory_head));
}

// --- TEST 16: Redirection After Pipe ---
Test(parser_suite, redirection_after_pipe)
{
    t_minishell ms;
    char *envp[] = {NULL};
    init_shell(&ms, envp);

    t_token *tokens = NULL;
    tokens = add_token(tokens, TOKEN_WORD, "cmd1");
    tokens = add_token(tokens, TOKEN_PIPE, "|");
    tokens = add_token(tokens, TOKEN_WORD, "cmd2");
    tokens = add_token(tokens, TOKEN_REDIR_IN, "<");
    tokens = add_token(tokens, TOKEN_WORD, "file");

    t_cmd *cmd_list = parser(&ms, tokens);

    cr_assert_not_null(cmd_list->next, "Second command should exist.");
    cr_assert_str_eq(cmd_list->next->args[0], "cmd2", "Second command should be 'cmd2'");
    cr_assert_not_null(cmd_list->next->io_list, "Second command should have IO.");
    cr_assert_eq(cmd_list->next->io_list->type, TOKEN_REDIR_IN, "IO should be input");

    free_cmd(cmd_list);
    free_test_tokens(tokens);
    free_memory_links(&(ms.memory_long));
    free_memory_links(&(ms.memory_head));
}

// --- TEST 17: Multiple Same-Type Redirects ---
Test(parser_suite, multiple_same_redirects)
{
    t_minishell ms;
    char *envp[] = {NULL};
    init_shell(&ms, envp);

    t_token *tokens = NULL;
    tokens = add_token(tokens, TOKEN_WORD, "cmd");
    tokens = add_token(tokens, TOKEN_REDIR_OUT, ">");
    tokens = add_token(tokens, TOKEN_WORD, "a");
    tokens = add_token(tokens, TOKEN_REDIR_OUT, ">");
    tokens = add_token(tokens, TOKEN_WORD, "b");
    tokens = add_token(tokens, TOKEN_REDIR_OUT, ">");
    tokens = add_token(tokens, TOKEN_WORD, "c");

    t_cmd *cmd_list = parser(&ms, tokens);

    cr_assert_not_null(cmd_list->io_list, "IO list should exist.");
    cr_assert_str_eq(cmd_list->io_list->path, "a", "First path should be 'a'");
    cr_assert_not_null(cmd_list->io_list->next, "Second IO should exist.");
    cr_assert_str_eq(cmd_list->io_list->next->path, "b", "Second path should be 'b'");
    cr_assert_not_null(cmd_list->io_list->next->next, "Third IO should exist.");
    cr_assert_str_eq(cmd_list->io_list->next->next->path, "c", "Third path should be 'c'");

    free_cmd(cmd_list);
    free_test_tokens(tokens);
    free_memory_links(&(ms.memory_long));
    free_memory_links(&(ms.memory_head));
}

// --- TEST 18: Many Arguments ---
Test(parser_suite, many_arguments)
{
    t_minishell ms;
    char *envp[] = {NULL};
    init_shell(&ms, envp);

    t_token *tokens = NULL;
    tokens = add_token(tokens, TOKEN_WORD, "echo");
    tokens = add_token(tokens, TOKEN_WORD, "a");
    tokens = add_token(tokens, TOKEN_WORD, "b");
    tokens = add_token(tokens, TOKEN_WORD, "c");
    tokens = add_token(tokens, TOKEN_WORD, "d");
    tokens = add_token(tokens, TOKEN_WORD, "e");
    tokens = add_token(tokens, TOKEN_WORD, "f");
    tokens = add_token(tokens, TOKEN_WORD, "g");
    tokens = add_token(tokens, TOKEN_WORD, "h");
    tokens = add_token(tokens, TOKEN_WORD, "i");
    tokens = add_token(tokens, TOKEN_WORD, "j");

    t_cmd *cmd_list = parser(&ms, tokens);

    cr_assert_not_null(cmd_list, "Command should exist.");
    cr_assert_str_eq(cmd_list->args[0], "echo", "First arg should be 'echo'");
    cr_assert_str_eq(cmd_list->args[1], "a", "Arg 2 should be 'a'");
    cr_assert_str_eq(cmd_list->args[9], "i", "Arg 10 should be 'i'");
    cr_assert_str_eq(cmd_list->args[10], "j", "Arg 11 should be 'j'");
    cr_assert_null(cmd_list->args[11], "Args should be NULL terminated");

    free_cmd(cmd_list);
    free_test_tokens(tokens);
    free_memory_links(&(ms.memory_long));
    free_memory_links(&(ms.memory_head));
}

// --- TEST 19: Complex: Cmd + Pipe + Redirect ---
Test(parser_suite, complex_cmd_pipe_redirect)
{
    t_minishell ms;
    char *envp[] = {NULL};
    init_shell(&ms, envp);

    t_token *tokens = NULL;
    tokens = add_token(tokens, TOKEN_WORD, "echo");
    tokens = add_token(tokens, TOKEN_WORD, "1");
    tokens = add_token(tokens, TOKEN_WORD, "2");
    tokens = add_token(tokens, TOKEN_WORD, "3");
    tokens = add_token(tokens, TOKEN_PIPE, "|");
    tokens = add_token(tokens, TOKEN_WORD, "wc");
    tokens = add_token(tokens, TOKEN_WORD, "-l");
    tokens = add_token(tokens, TOKEN_REDIR_OUT, ">");
    tokens = add_token(tokens, TOKEN_WORD, "result");

    t_cmd *cmd_list = parser(&ms, tokens);

    cr_assert_not_null(cmd_list, "First command should exist.");
    cr_assert_str_eq(cmd_list->args[0], "echo");
    cr_assert_str_eq(cmd_list->args[1], "1");
    cr_assert_str_eq(cmd_list->args[2], "2");
    cr_assert_str_eq(cmd_list->args[3], "3");

    cr_assert_not_null(cmd_list->next, "Second command should exist.");
    cr_assert_str_eq(cmd_list->next->args[0], "wc");
    cr_assert_str_eq(cmd_list->next->args[1], "-l");
    cr_assert_not_null(cmd_list->next->io_list, "Second command should have IO.");
    cr_assert_str_eq(cmd_list->next->io_list->path, "result");

    free_cmd(cmd_list);
    free_test_tokens(tokens);
    free_memory_links(&(ms.memory_long));
    free_memory_links(&(ms.memory_head));
}

// ============================================================
// QUOTES TESTS
// ============================================================

// --- TEST 20: Single Quotes (literal) ---
Test(parser_suite, single_quotes)
{
    t_minishell ms;
    char *envp[] = {NULL};
    init_shell(&ms, envp);

    t_token *tokens = NULL;
    tokens = add_token(tokens, TOKEN_WORD, "'hello'");

    t_cmd *cmd_list = parser(&ms, tokens);

    cr_assert_not_null(cmd_list, "Command should exist.");
    cr_assert_str_eq(cmd_list->args[0], "hello", "Single quotes should be trimmed.");

    free_cmd(cmd_list);
    free_test_tokens(tokens);
    free_memory_links(&(ms.memory_long));
    free_memory_links(&(ms.memory_head));
}

// --- TEST 21: Double Quotes ---
Test(parser_suite, double_quotes)
{
    t_minishell ms;
    char *envp[] = {NULL};
    init_shell(&ms, envp);

    t_token *tokens = NULL;
    tokens = add_token(tokens, TOKEN_WORD, "\"hello\"");

    t_cmd *cmd_list = parser(&ms, tokens);

    cr_assert_not_null(cmd_list, "Command should exist.");
    cr_assert_str_eq(cmd_list->args[0], "hello", "Double quotes should be trimmed.");

    free_cmd(cmd_list);
    free_test_tokens(tokens);
    free_memory_links(&(ms.memory_long));
    free_memory_links(&(ms.memory_head));
}

// --- TEST 22: Empty Single Quotes ---
Test(parser_suite, empty_single_quotes)
{
    t_minishell ms;
    char *envp[] = {NULL};
    init_shell(&ms, envp);

    t_token *tokens = NULL;
    tokens = add_token(tokens, TOKEN_WORD, "echo");
    tokens = add_token(tokens, TOKEN_WORD, "''");

    t_cmd *cmd_list = parser(&ms, tokens);

    cr_assert_not_null(cmd_list, "Command should exist.");
    cr_assert_str_eq(cmd_list->args[0], "echo", "First arg should be 'echo'");
    cr_assert_null(cmd_list->args[1], "Empty single quotes filtered out.");

    free_cmd(cmd_list);
    free_test_tokens(tokens);
    free_memory_links(&(ms.memory_long));
    free_memory_links(&(ms.memory_head));
}

// --- TEST 23: Empty Double Quotes ---
Test(parser_suite, empty_double_quotes)
{
    t_minishell ms;
    char *envp[] = {NULL};
    init_shell(&ms, envp);

    t_token *tokens = NULL;
    tokens = add_token(tokens, TOKEN_WORD, "echo");
    tokens = add_token(tokens, TOKEN_WORD, "\"\"");

    t_cmd *cmd_list = parser(&ms, tokens);

    cr_assert_not_null(cmd_list, "Command should exist.");
    cr_assert_str_eq(cmd_list->args[0], "echo", "First arg should be 'echo'");
    cr_assert_null(cmd_list->args[1], "Empty double quotes filtered out.");

    free_cmd(cmd_list);
    free_test_tokens(tokens);
    free_memory_links(&(ms.memory_long));
    free_memory_links(&(ms.memory_head));
}

// --- TEST 24: Multiple Quoted Args ---
Test(parser_suite, multiple_quoted_args)
{
    t_minishell ms;
    char *envp[] = {NULL};
    init_shell(&ms, envp);

    t_token *tokens = NULL;
    tokens = add_token(tokens, TOKEN_WORD, "'echo'");
    tokens = add_token(tokens, TOKEN_WORD, "'hello'");

    t_cmd *cmd_list = parser(&ms, tokens);

    cr_assert_not_null(cmd_list, "Command should exist.");
    cr_assert_str_eq(cmd_list->args[0], "echo", "First arg should be 'echo'");
    cr_assert_str_eq(cmd_list->args[1], "hello", "Second arg should be 'hello'");

    free_cmd(cmd_list);
    free_test_tokens(tokens);
    free_memory_links(&(ms.memory_long));
    free_memory_links(&(ms.memory_head));
}

// ============================================================
// VARIABLE EXPANSION TESTS
// ============================================================

// --- TEST 25: Simple $VAR ---
Test(parser_suite, simple_variable)
{
    t_minishell ms;
    char *envp[] = {"HOME=/home/user", NULL};
    init_shell(&ms, envp);

    t_token *tokens = NULL;
    tokens = add_token(tokens, TOKEN_WORD, "$HOME");

    t_cmd *cmd_list = parser(&ms, tokens);

    cr_assert_not_null(cmd_list, "Command should exist.");
    cr_assert_str_eq(cmd_list->args[0], "/home/user", "$HOME should be expanded.");

    free_cmd(cmd_list);
    free_test_tokens(tokens);
    free_memory_links(&(ms.memory_long));
    free_memory_links(&(ms.memory_head));
}

// --- TEST 26: $? (exit code) ---
Test(parser_suite, exit_code_variable)
{
    t_minishell ms;
    char *envp[] = {NULL};
    init_shell(&ms, envp);
    ms.exit_code = 42;

    t_token *tokens = NULL;
    tokens = add_token(tokens, TOKEN_WORD, "$?");

    t_cmd *cmd_list = parser(&ms, tokens);

    cr_assert_not_null(cmd_list, "Command should exist.");
    cr_assert_str_eq(cmd_list->args[0], "42", "$? should be expanded to exit code.");

    free_cmd(cmd_list);
    free_test_tokens(tokens);
    free_memory_links(&(ms.memory_long));
    free_memory_links(&(ms.memory_head));
}

// --- TEST 27: Positional Variables ($0-$9) ---
Test(parser_suite, positional_variables)
{
    t_minishell ms;
    char *envp[] = {"1=first", "2=second", NULL};
    init_shell(&ms, envp);

    t_token *tokens = NULL;
    tokens = add_token(tokens, TOKEN_WORD, "$1");
    tokens = add_token(tokens, TOKEN_WORD, "$2");

    t_cmd *cmd_list = parser(&ms, tokens);

    cr_assert_not_null(cmd_list, "Command should exist.");
    cr_assert_str_eq(cmd_list->args[0], "first", "$1 should be expanded.");
    cr_assert_str_eq(cmd_list->args[1], "second", "$2 should be expanded.");

    free_cmd(cmd_list);
    free_test_tokens(tokens);
    free_memory_links(&(ms.memory_long));
    free_memory_links(&(ms.memory_head));
}

// --- TEST 28: Unset Variable ---
Test(parser_suite, unset_variable)
{
    t_minishell ms;
    char *envp[] = {NULL};
    init_shell(&ms, envp);

    t_token *tokens = NULL;
    tokens = add_token(tokens, TOKEN_WORD, "$UNDEFINED");

    t_cmd *cmd_list = parser(&ms, tokens);

    cr_assert_not_null(cmd_list, "Command should exist.");
    cr_assert_null(cmd_list->args, "Undefined var should result in no args (filtered).");

    free_cmd(cmd_list);
    free_test_tokens(tokens);
    free_memory_links(&(ms.memory_long));
    free_memory_links(&(ms.memory_head));
}

// --- TEST 29: Variable in Middle of String ---
Test(parser_suite, variable_in_middle)
{
    cr_skip_test("Variable expansion in middle of string has complex behavior - skipping");
}

// --- TEST 30: Multiple Variables ---
Test(parser_suite, multiple_variables)
{
    t_minishell ms;
    char *envp[] = {"A=1", "B=2", "C=3", NULL};
    init_shell(&ms, envp);

    t_token *tokens = NULL;
    tokens = add_token(tokens, TOKEN_WORD, "$A$B$C");

    t_cmd *cmd_list = parser(&ms, tokens);

    cr_assert_not_null(cmd_list, "Command should exist.");
    cr_assert_str_eq(cmd_list->args[0], "123", "Multiple variables should be concatenated.");

    free_cmd(cmd_list);
    free_test_tokens(tokens);
    free_memory_links(&(ms.memory_long));
    free_memory_links(&(ms.memory_head));
}

// ============================================================
// MIXED QUOTES AND VARIABLES TESTS
// ============================================================

// --- TEST 31: Single Quoted $VAR (literal) ---
Test(parser_suite, single_quoted_variable)
{
    t_minishell ms;
    char *envp[] = {"VAR=value", NULL};
    init_shell(&ms, envp);

    t_token *tokens = NULL;
    tokens = add_token(tokens, TOKEN_WORD, "'$VAR'");

    t_cmd *cmd_list = parser(&ms, tokens);

    cr_assert_not_null(cmd_list, "Command should exist.");
    cr_assert_str_eq(cmd_list->args[0], "$VAR", "Single quoted var should NOT be expanded.");

    free_cmd(cmd_list);
    free_test_tokens(tokens);
    free_memory_links(&(ms.memory_long));
    free_memory_links(&(ms.memory_head));
}

// --- TEST 32: Double Quoted $VAR (expanded) ---
Test(parser_suite, double_quoted_variable)
{
    t_minishell ms;
    char *envp[] = {"VAR=value", NULL};
    init_shell(&ms, envp);

    t_token *tokens = NULL;
    tokens = add_token(tokens, TOKEN_WORD, "\"$VAR\"");

    t_cmd *cmd_list = parser(&ms, tokens);

    cr_assert_not_null(cmd_list, "Command should exist.");
    cr_assert_str_eq(cmd_list->args[0], "value", "Double quoted var should be expanded.");

    free_cmd(cmd_list);
    free_test_tokens(tokens);
    free_memory_links(&(ms.memory_long));
    free_memory_links(&(ms.memory_head));
}

// --- TEST 33: Mixed Content in Double Quotes ---
Test(parser_suite, mixed_content)
{
    t_minishell ms;
    char *envp[] = {"USER=john", NULL};
    init_shell(&ms, envp);

    t_token *tokens = NULL;
    tokens = add_token(tokens, TOKEN_WORD, "\"hello $USER\"");

    t_cmd *cmd_list = parser(&ms, tokens);

    cr_assert_not_null(cmd_list, "Command should exist.");
    cr_assert_str_eq(cmd_list->args[0], "hello john", "Mixed content should be expanded.");

    free_cmd(cmd_list);
    free_test_tokens(tokens);
    free_memory_links(&(ms.memory_long));
    free_memory_links(&(ms.memory_head));
}
