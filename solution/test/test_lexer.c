/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 10:13:01 by obutolin          #+#    #+#             */
/*   Updated: 2026/01/22 12:39:36 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// typedef struct s_expected
// {
// 	enum e_token_type	type;
// 	const char		*value;
// }	t_expected;

// int compare_tokens(t_token *actual, t_expected *expected, int expected_len)
// {
// 	int i = 0;

// 	while (actual && i < expected_len)
// 	{
// 		if (actual->type != expected[i].type)
// 		{
// 			printf("❌ Token %d: expected type %s, got %s\n",
// 				i,
// 				token_type_to_str(expected[i].type),
// 				token_type_to_str(actual->type));
// 			return (0);
// 		}
// 		if (expected[i].value && strcmp(actual->value, expected[i].value) != 0)
// 		{
// 			printf("❌ Token %d: expected value '%s', got '%s'\n",
// 				i, expected[i].value, actual->value);
// 			return (0);
// 		}
// 		actual = actual->next;
// 		i++;
// 	}
// 	if (actual || i != expected_len)
// 	{
// 		printf("❌ Token count mismatch\n");
// 		return (0);
// 	}
// 	return (1);
// }

// void run_lexer_test(char *input, t_expected *expected, int len)
// {
// 	t_token *tokens;

// 	printf("🔹 Test: \"%s\"\n", input);
// 	tokens = lexer(input);
// 	if (compare_tokens(tokens, expected, len))
// 		printf("✅ OK\n\n");
// 	else
// 		printf("❌ FAIL\n\n");

// 	// не забудь очистить tokens
// }

// void test_spaces(void)
// {
// 	t_expected expected1[] = {
// 		{TOKEN_WORD, "ls"},
// 		{TOKEN_WORD, "-la"},
// 	};

// 	run_lexer_test("ls   -la", expected1, 2);
// 	run_lexer_test("ls-la", expected1, 2); // если так задумано
// }

// void test_pipes(void)
// {
// 	t_expected expected[] = {
// 		{TOKEN_WORD, "echo"},
// 		{TOKEN_WORD, "hi"},
// 		{TOKEN_PIPE, "|"},
// 		{TOKEN_WORD, "cat"},
// 	};

// 	run_lexer_test("echo hi|cat", expected, 4);
// 	run_lexer_test("echo hi | cat", expected, 4);
// }

// void test_redirections(void)
// {
// 	t_expected expected[] = {
// 		{TOKEN_WORD, "echo"},
// 		{TOKEN_WORD, "hi"},
// 		{TOKEN_REDIR_OUT, ">"},
// 		{TOKEN_WORD, "file"},
// 	};

// 	run_lexer_test("echo hi>file", expected, 4);
// 	run_lexer_test("echo hi > file", expected, 4);
// }

void	line_lexer_test()
{
	t_memory_info *memory_head;
	t_token *token;
	char line[100];

	memory_head = NULL;
	token = NULL;
	printf("LINE_LEXER.c\n");

	// When (line == '') return token_head == NULL
	line[0] = '\0';
	line_lexer(&memory_head, &token, line);
	if (token == NULL)
		printf("1. OK\n");
	else
		printf("1. ERROR result token_head should be NULL\n");
	free_memory_links(memory_head);

	// Ignore spaces
	memory_head = NULL;
	token = NULL;
	ft_strlcpy(line, "   echo     hi world  ", 26);
	line_lexer(&memory_head, &token, line);
	if (token != NULL
		&& token->type == TOKEN_WORD && !strncmp(token->value, "echo", 5)
		&& token->next->type == TOKEN_WORD && !strncmp(token->next->value, "hi", 3)
		&& token->next->next->type == TOKEN_WORD && !strncmp(token->next->next->value, "world", 6)
		&& token->next->next->next == NULL)
		printf("2. OK\n");
	else printf("2. ERROR we need ignore spacis between words\n");
	free_memory_links(memory_head);

	// All types of tokens
	// ft_strlcpy(line, "a|<<<>>>&&||();", 24);
	// line_lexer(&memory_head, &token, line);
	// if (token != NULL
	// 	&& token->type == TOKEN_WORD && !strncmp(token->value, "a", 2)
	// 	&& token->next->type == TOKEN_PIPE
	// 		&& !strncmp(token->next->value, "|", 2)
	// 	&& token->next->next->type == TOKEN_HEREDOC
	// 		&& !strncmp(token->next->next->value, "<<", 3)
	// 	&& token->next->next->next->type == TOKEN_REDIR_IN
	// 		&& !strncmp(token->next->next->next->value, "<", 2)
	// 	&& token->next->next->next->next->type == TOKEN_APPEND
	// 		&& !strncmp(token->next->next->next->next->value, ">>", 3)
	// 	&& token->next->next->next->next->next->type == TOKEN_REDIR_OUT
	// 		&& !strncmp(token->next->next->next->next->next->value, ">", 2)

	// 	&& token->next->next->next->next->next->next->type == TOKEN_AND
	// 		&& !strncmp(token->next->next->next->next->next->next->value, "&&", 3))
	// 	// && token->next->next->next->next->next->type == TOKEN_OR
	// 	// 	&& !strncmp(token->next->next->value, "||", 3)
	// 	// && token->next->next->next->next->next->type == TOKEN_LPAREN
	// 	// 	&& !strncmp(token->next->next->value, "(", 2)
	// 	// && token->next->next->next->next->next->type == TOKEN_RPAREN
	// 	// 	&& !strncmp(token->next->next->value, ")", 2)
	// 	// && token->next->next->next->next->next->type == TOKEN_SEMICOLON
	// 	// 	&& !strncmp(token->next->next->value, ";", 2))
	// 	printf("2. OK\n");
	// else printf("2. ERROR we need ignore spacis between words\n");
	free_memory_links(memory_head);
}

void	test_lexer(void)
{
	// test_spaces();
	// test_pipes();
	// test_redirections();
	line_lexer_test();
}