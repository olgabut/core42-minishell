/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 10:13:01 by obutolin          #+#    #+#             */
/*   Updated: 2026/02/01 19:13:12 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	line_lexer_test()
{
	t_memory_info *memory_head;
	t_token *token;
	char line[100];

	printf("LINE_LEXER.c\n");

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

	// combination
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
	
	// all tokens
	
}

void	test_lexer(void)
{
	line_lexer_test();
}