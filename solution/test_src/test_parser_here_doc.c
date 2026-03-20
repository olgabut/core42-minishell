#include <criterion/criterion.h>
#include "minishell.h"
#include "test_parser_utils.h"

// Test: Single line heredoc - cat << EOF
Test(parser_suite_here_doc, single_line_heredoc)
{
    t_minishell ms;
    char *envp[] = {NULL};
    init_shell(&ms, envp);

    setenv("MOCK_LINES", "hello world\nEOF\n", 1);

    t_token *tokens = NULL;
    tokens = add_token(tokens, TOKEN_WORD, "cat");
    tokens = add_token(tokens, TOKEN_HEREDOC, "<<");
    tokens = add_token(tokens, TOKEN_WORD, "EOF");

    t_cmd *cmd_list = parser(&ms, tokens);

    cr_assert_not_null(cmd_list, "Command should exist.");
    cr_assert_str_eq(cmd_list->args[0], "cat", "First arg should be 'cat'");
    cr_assert_not_null(cmd_list->io_list, "IO list should exist.");
    cr_assert_eq(cmd_list->io_list->type, TOKEN_HEREDOC, "IO type should be TOKEN_HEREDOC");
    cr_assert_str_eq(cmd_list->io_list->path, "hello world\n", "Heredoc content should match");

    unsetenv("MOCK_LINES");
    free_cmd(cmd_list);
    free_test_tokens(tokens);
    free_memory_links(&(ms.memory_long));
    free_memory_links(&(ms.memory_head));
}

// Test: Multi-line heredoc
Test(parser_suite_here_doc, multi_line_heredoc)
{
    t_minishell ms;
    char *envp[] = {NULL};
    init_shell(&ms, envp);

    setenv("MOCK_LINES", "line 1\nline 2\nline 3\nEOF\n", 1);

    t_token *tokens = NULL;
    tokens = add_token(tokens, TOKEN_WORD, "cat");
    tokens = add_token(tokens, TOKEN_HEREDOC, "<<");
    tokens = add_token(tokens, TOKEN_WORD, "EOF");

    t_cmd *cmd_list = parser(&ms, tokens);

    cr_assert_not_null(cmd_list, "Command should exist.");
    cr_assert_str_eq(cmd_list->args[0], "cat", "First arg should be 'cat'");
    cr_assert_not_null(cmd_list->io_list, "IO list should exist.");
    cr_assert_eq(cmd_list->io_list->type, TOKEN_HEREDOC, "IO type should be TOKEN_HEREDOC");
    cr_assert_str_eq(cmd_list->io_list->path, "line 1\nline 2\nline 3\n", "Heredoc should have all lines");

    unsetenv("MOCK_LINES");
    free_cmd(cmd_list);
    free_test_tokens(tokens);
    free_memory_links(&(ms.memory_long));
    free_memory_links(&(ms.memory_head));
}

// Test: Immediate delimiter (empty input)
Test(parser_suite_here_doc, immediate_delimiter)
{
    t_minishell ms;
    char *envp[] = {NULL};
    init_shell(&ms, envp);

    setenv("MOCK_LINES", "EOF\n", 1);

    t_token *tokens = NULL;
    tokens = add_token(tokens, TOKEN_WORD, "cat");
    tokens = add_token(tokens, TOKEN_HEREDOC, "<<");
    tokens = add_token(tokens, TOKEN_WORD, "EOF");

    t_cmd *cmd_list = parser(&ms, tokens);

    cr_assert_not_null(cmd_list, "Command should exist.");
    cr_assert_not_null(cmd_list->io_list, "IO list should exist.");
    cr_assert_eq(cmd_list->io_list->type, TOKEN_HEREDOC, "IO type should be TOKEN_HEREDOC");
    cr_assert_str_eq(cmd_list->io_list->path, "", "Heredoc should be empty");

    unsetenv("MOCK_LINES");
    free_cmd(cmd_list);
    free_test_tokens(tokens);
    
    free_memory_links(&(ms.memory_long));
    free_memory_links(&(ms.memory_head));
}

// Test: Custom delimiter
Test(parser_suite_here_doc, custom_delimiter)
{
    t_minishell ms;
    char *envp[] = {NULL};
    init_shell(&ms, envp);

    setenv("MOCK_LINES", "some content\nCUSTOM\n", 1);

    t_token *tokens = NULL;
    tokens = add_token(tokens, TOKEN_WORD, "wc");
    tokens = add_token(tokens, TOKEN_HEREDOC, "<<");
    tokens = add_token(tokens, TOKEN_WORD, "CUSTOM");

    t_cmd *cmd_list = parser(&ms, tokens);

    cr_assert_not_null(cmd_list, "Command should exist.");
    cr_assert_str_eq(cmd_list->args[0], "wc", "First arg should be 'wc'");
    cr_assert_not_null(cmd_list->io_list, "IO list should exist.");
    cr_assert_eq(cmd_list->io_list->type, TOKEN_HEREDOC, "IO type should be TOKEN_HEREDOC");
    cr_assert_str_eq(cmd_list->io_list->path, "some content\n", "Heredoc should have content until CUSTOM");

    unsetenv("MOCK_LINES");
    free_cmd(cmd_list);
    free_test_tokens(tokens);
    
    free_memory_links(&(ms.memory_long));
    free_memory_links(&(ms.memory_head));
}

// Test: Heredoc only (no command), only redirection
Test(parser_suite_here_doc, heredoc_only_redirection)
{
    t_minishell ms;
    char *envp[] = {NULL};
    init_shell(&ms, envp);

    setenv("MOCK_LINES", "test input\nEOF\n", 1);

    t_token *tokens = NULL;
    tokens = add_token(tokens, TOKEN_HEREDOC, "<<");
    tokens = add_token(tokens, TOKEN_WORD, "EOF");

    t_cmd *cmd_list = parser(&ms, tokens);

    cr_assert_not_null(cmd_list, "Command should exist.");
    cr_assert_null(cmd_list->args, "Args should be NULL");
    cr_assert_not_null(cmd_list->io_list, "IO list should exist.");
    cr_assert_eq(cmd_list->io_list->type, TOKEN_HEREDOC, "IO type should be TOKEN_HEREDOC");

    unsetenv("MOCK_LINES");
    free_cmd(cmd_list);
    free_test_tokens(tokens);
    
    free_memory_links(&(ms.memory_long));
    free_memory_links(&(ms.memory_head));
}

// Test: Heredoc with pipe to another command
Test(parser_suite_here_doc, heredoc_with_pipe)
{
    t_minishell ms;
    char *envp[] = {NULL};
    init_shell(&ms, envp);

    setenv("MOCK_LINES", "test content\nEOF\n", 1);

    t_token *tokens = NULL;
    tokens = add_token(tokens, TOKEN_WORD, "cat");
    tokens = add_token(tokens, TOKEN_HEREDOC, "<<");
    tokens = add_token(tokens, TOKEN_WORD, "EOF");
    tokens = add_token(tokens, TOKEN_PIPE, "|");
    tokens = add_token(tokens, TOKEN_WORD, "wc");
    tokens = add_token(tokens, TOKEN_WORD, "-l");

    t_cmd *cmd_list = parser(&ms, tokens);

    cr_assert_not_null(cmd_list, "First command should exist.");
    cr_assert_str_eq(cmd_list->args[0], "cat", "First command should be 'cat'");
    cr_assert_not_null(cmd_list->io_list, "First command should have IO.");
    cr_assert_eq(cmd_list->io_list->type, TOKEN_HEREDOC, "IO type should be TOKEN_HEREDOC");

    cr_assert_not_null(cmd_list->next, "Second command should exist.");
    cr_assert_str_eq(cmd_list->next->args[0], "wc", "Second command should be 'wc'");
    cr_assert_str_eq(cmd_list->next->args[1], "-l", "Second arg should be '-l'");

    unsetenv("MOCK_LINES");
    free_cmd(cmd_list);
    free_test_tokens(tokens);
    
    free_memory_links(&(ms.memory_long));
    free_memory_links(&(ms.memory_head));
}
