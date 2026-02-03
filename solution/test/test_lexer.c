/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 10:13:01 by obutolin          #+#    #+#             */
/*   Updated: 2026/02/03 11:34:10 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	line_lexer_test()
{
	t_memory_info *memory_head;
	t_token *token;
	char line[100];

	printf("\nLINE_LEXER.c\n");

	// When (line == '') return token_head == NULL
	memory_head = NULL;
	token = NULL;
	line[0] = '\0';
	line_lexer(&memory_head, &token, line);
	if (token == NULL)
		printf("1. OK\n");
	else
		printf("1. ERROR result token_head should be NULL\n");
	free_memory_links(memory_head);

	// One word
	memory_head = NULL;
	token = NULL;
	ft_strlcpy(line, "ls", 3);
	line_lexer(&memory_head, &token, line);
	if (token != NULL
		&& token->type == TOKEN_WORD && !strncmp(token->value, "ls", 3)
		&& token->next == NULL)
		printf("2. OK\n");
	else
		printf("2. ERROR one word\n");
	free_memory_links(memory_head);

	// Ignore spaces
	memory_head = NULL;
	token = NULL;
	ft_strlcpy(line, "   echo     hi world  ", 23);
	line_lexer(&memory_head, &token, line);
	if (token != NULL
		&& token->type == TOKEN_WORD && !strncmp(token->value, "echo", 5)
		&& token->next->type == TOKEN_WORD && !strncmp(token->next->value, "hi", 3)
		&& token->next->next->type == TOKEN_WORD && !strncmp(token->next->next->value, "world", 6)
		&& token->next->next->next == NULL)
		printf("3. OK\n");
	else printf("3. ERROR we need ignore spacis between words\n");
	free_memory_links(memory_head);

	// PIPE
	memory_head = NULL;
	token = NULL;
	ft_strlcpy(line, "ls |wc", 7);
	line_lexer(&memory_head, &token, line);
	if (token != NULL
		&& token->type == TOKEN_WORD && !strncmp(token->value, "ls", 3)
		&& token->next->type == TOKEN_PIPE && !strncmp(token->next->value, "|", 2)
		&& token->next->next->type == TOKEN_WORD && !strncmp(token->next->next->value, "wc", 3)
		&& token->next->next->next == NULL)
		printf("4. OK\n");
	else printf("4. ERROR we need ignore spacis between words\n");
	free_memory_links(memory_head);

	// combination "cat< in.txt>     out.txt"
	memory_head = NULL;
	token = NULL;
	ft_strlcpy(line, "cat< in.txt>     out.txt", 25);
	line_lexer(&memory_head, &token, line);
	if (token != NULL
		&& token->type == TOKEN_WORD && !strncmp(token->value, "cat", 4)
		&& token->next->type == TOKEN_REDIR_IN && !strncmp(token->next->value, "<", 2)
		&& token->next->next->type == TOKEN_WORD && !strncmp(token->next->next->value, "in.txt", 7)
		&& token->next->next->next->type == TOKEN_REDIR_OUT && !strncmp(token->next->next->next->value, ">", 2)
		&& token->next->next->next->next->type == TOKEN_WORD && !strncmp(token->next->next->next->next->value, "out.txt", 8)
		&& token->next->next->next->next->next == NULL)
		printf("5. OK\n");
	else printf("5. ERROR combintation redir_in and redir_out\n");
	free_memory_links(memory_head);

	// Parenthesis "(echo hi && echo ok) | cat >> out.txt"
	memory_head = NULL;
	token = NULL;
	ft_strlcpy(line, "(echo hi && echo ok) | cat >> out.txt", 38);
	line_lexer(&memory_head, &token, line);
	if (token != NULL
		&& token->type == TOKEN_LPAREN && !strncmp(token->value, "(", 2)
		&& token->next->type == TOKEN_WORD && !strncmp(token->next->value, "echo", 5)
		&& token->next->next->type == TOKEN_WORD && !strncmp(token->next->next->value, "hi", 3)
		&& token->next->next->next->type == TOKEN_AND && !strncmp(token->next->next->next->value, "&&", 3)
		&& !strncmp(token->next->next->next->next->value, "echo", 5)
				 && token->next->next->next->next->type == TOKEN_WORD
		&& !strncmp(token->next->next->next->next->next->value, "ok", 3)
				 && token->next->next->next->next->next->type == TOKEN_WORD
		&& !strncmp(token->next->next->next->next->next->next->value, ")", 2)
				 && token->next->next->next->next->next->next->type == TOKEN_RPAREN
		&& !strncmp(token->next->next->next->next->next->next->next->value, "|", 2)
				 && token->next->next->next->next->next->next->next->type == TOKEN_PIPE
		&& !strncmp(token->next->next->next->next->next->next->next->next->value, "cat", 4)
				 && token->next->next->next->next->next->next->next->next->type == TOKEN_WORD
		&& !strncmp(token->next->next->next->next->next->next->next->next->next->value, ">>", 3)
				 && token->next->next->next->next->next->next->next->next->next->type == TOKEN_APPEND
		&& !strncmp(token->next->next->next->next->next->next->next->next->next->next->value, "out.txt", 8)
				 && token->next->next->next->next->next->next->next->next->next->next->type == TOKEN_WORD
		&& token->next->next->next->next->next->next->next->next->next->next->next == NULL)
		printf("6. OK\n");
	else printf("6. ERROR parenthesis ()\n");
	free_memory_links(memory_head);
}

void	need_next_line_test()
{
	char line[100];
	t_token *token_head;
	t_token *new_token;

	printf("\nNEED_NEXT_LINE   need_wait_for_closing_quote\n");
	// token is null
	token_head = NULL;
	if (!need_next_line(token_head))
		printf("1. OK\n");
	else printf("1. ERROR token is null");

	// Don't need next line (common word on the last token)
	ft_strlcpy(line, "Hello world", 12);
	create_token(&new_token, TOKEN_WORD, line);
	add_new_token(&token_head, new_token);
	if (!strncmp(get_last_token(token_head)->value, line, 12)
		&& !need_next_line(token_head))
		printf("2. OK\n");
	else printf("2. ERROR common line");

	// Need next line (only one single quote ')
	ft_strlcpy(line, "\'Hello", 7);
	create_token(&new_token, TOKEN_WORD, line);
	add_new_token(&token_head, new_token);
	if (!strncmp(get_last_token(token_head)->value, line, 7)
		&& need_next_line(token_head))
		printf("3. OK\n");
	else printf("3. ERROR one single quote");

	// Need next line (only one double quote)
	ft_strlcpy(line, "He\"llo", 7);
	create_token(&new_token, TOKEN_WORD, line);
	add_new_token(&token_head, new_token);
	if (!strncmp(get_last_token(token_head)->value, line, 7)
		&& need_next_line(token_head))
		printf("4. OK\n");
	else printf("4. ERROR one double quote");

	// Don't need next line (mix quotes (double quotes are external))
	ft_strlcpy(line, "\"1\'2\'3\'\"", 9);
	create_token(&new_token, TOKEN_WORD, line);
	add_new_token(&token_head, new_token);
	if (!strncmp(get_last_token(token_head)->value, line, 9)
		&& !need_next_line(token_head))
		printf("5. OK\n");
	else printf("5. ERROR mix quotes (double quotes are external)");

	// Don't need next line (mix quotes (single quotes are external))
	ft_strlcpy(line, "\'1\"2\'", 6);
	create_token(&new_token, TOKEN_WORD, line);
	add_new_token(&token_head, new_token);
	if (!strncmp(get_last_token(token_head)->value, line, 6)
		&& !need_next_line(token_head))
		printf("6. OK\n");
	else printf("6. ERROR mix quotes (single quotes are external)");

	// Need next line (include next line character)
	ft_strlcpy(line, "AB\'AB\nAB", 9);
	create_token(&new_token, TOKEN_WORD, line);
	add_new_token(&token_head, new_token);
	if (!strncmp(get_last_token(token_head)->value, line, 9)
		&& need_next_line(token_head))
		printf("7. OK\n");
	else printf("7. ERROR need next line single quotes (include next line character)");

	// Need next line (include next line character)
	ft_strlcpy(line, "ABAB\"\nAB", 9);
	create_token(&new_token, TOKEN_WORD, line);
	add_new_token(&token_head, new_token);
	if (!strncmp(get_last_token(token_head)->value, line, 9)
		&& need_next_line(token_head))
		printf("8. OK\n");
	else printf("8. ERROR need next line double quotes (include next line character)");

	// Don't need next line (include next line character)
	ft_strlcpy(line, "AB\'AB\nA\nB\'", 11);
	create_token(&new_token, TOKEN_WORD, line);
	add_new_token(&token_head, new_token);
	if (!strncmp(get_last_token(token_head)->value, line, 11)
		&& !need_next_line(token_head))
		printf("9. OK\n");
	else printf("9. ERROR don't need next lint single quotes (include next line character)");

	// Don't need next line (include next line character)
	ft_strlcpy(line, "\"ABAB\n\"A\nB", 11);
	create_token(&new_token, TOKEN_WORD, line);
	add_new_token(&token_head, new_token);
	if (!strncmp(get_last_token(token_head)->value, line, 11)
		&& !need_next_line(token_head))
		printf("10. OK\n");
	else printf("10. ERROR don't need next lint double quotes (include next line character)");

	//-----------------------------------------------------------------
	printf("\nNEED_NEXT_LINE   need_wait_for_continuation_of_command\n");
	// Need next line (last token is AND)
	ft_strlcpy(line, "&&", 3);
	create_token(&new_token, TOKEN_AND, line);
	add_new_token(&token_head, new_token);
	if (!strncmp(get_last_token(token_head)->value, line, 3)
		&& need_next_line(token_head))
		printf("11. OK\n");
	else printf("11. ERROR last token is AND");

	// Need next line (last token is AND)
	ft_strlcpy(line, "||", 3);
	create_token(&new_token, TOKEN_AND, line);
	add_new_token(&token_head, new_token);
	if (!strncmp(get_last_token(token_head)->value, line, 3)
		&& need_next_line(token_head))
		printf("12. OK\n");
	else printf("12. ERROR last token is OR");
}

void	test_lexer(void)
{
	line_lexer_test();
	need_next_line_test();
}