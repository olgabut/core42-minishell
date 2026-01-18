/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:00:48 by obutolin          #+#    #+#             */
/*   Updated: 2026/01/18 18:25:20 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool print_lexical_error(char *print_string, bool result)
{
	ft_print_string(print_string);
	return (result);
}

bool command_error_close_brace_before_open(t_token *token_head)
{
	int open_braces;
	t_token *token;

	token = token_head;
	open_braces = 0;
	while(token != NULL)
	{
		if (token->type == TOKEN_RPAREN)
		{
			if (open_braces == 0)
				return (true);
			open_braces--;
		}
		else if (token->type == TOKEN_LPAREN)
			open_braces++;
		token = token->next;
	}
	return (false);
}

bool command_error_wrong_token_sequence(t_token *token_head)
{
	t_token *token;

	token = token_head;
	while (token->next != NULL)
	{
		if (token->type == TOKEN_HEREDOC
			&& (token->next->type == TOKEN_REDIR_OUT
				|| token->next->type == TOKEN_PIPE
				|| token->next->type == TOKEN_REDIR_IN))
			return (true);
		if (token->type == TOKEN_APPEND
			&& token->next->type == TOKEN_REDIR_OUT)
			return (true);
		if (token->type == TOKEN_SEMICOLON
			&& token->next->type == TOKEN_SEMICOLON)
			return (true);
		if (token->type == TOKEN_AND
			&& token->next->type == TOKEN_OR)
			return (true);
		if (token->type == TOKEN_OR
			&& token->next->type == TOKEN_AND)
			return (true);
		token = token->next;
	}
	return (false);
}

/*
	Return
	1- The command has a error
	0- The command is ok, without errors
*/
bool	command_with_error(t_token *token_head)
{
	t_token	*last_token;

	if (token_head == NULL)
		return (true);
	printf("start to check errors in command\n");
	last_token = get_last_token(token_head);
	printf("last token = %s\n", last_token->value);
	if (token_head->type == TOKEN_PIPE)
		return (print_lexical_error(
				"ERROR near unexpected token `|`.\n", true));
	if (token_head->type == TOKEN_SEMICOLON
		|| last_token->type == TOKEN_SEMICOLON)
		return (print_lexical_error(
				"ERROR near unexpected token `;`.\n", true));
	if (token_head->type == TOKEN_AND)
		return (print_lexical_error(
				"ERROR near unexpected token `&&`.\n", true));
	if (token_head->type == TOKEN_OR)
		return (print_lexical_error(
				"ERROR near unexpected token `||`.\n", true));
	if (last_token->type == TOKEN_HEREDOC || last_token->type == TOKEN_PIPE)
		return (print_lexical_error(
				"ERROR near unexpected token `newline`.\n",
				true));
	if (command_error_close_brace_before_open(token_head))
		return (print_lexical_error(
				"ERROR near unexpected token `)`.\n", true));
	if (command_error_wrong_token_sequence(token_head))
		return (print_lexical_error(
				"ERROR with a token sequence.\n", true));
	return (false);
}
