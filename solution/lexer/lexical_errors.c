/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:00:48 by obutolin          #+#    #+#             */
/*   Updated: 2026/02/04 14:57:44 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	print_lexical_error(char *print_string, bool result)
{
	ft_print_string(print_string);
	return (result);
}

/* Unsupported tokens:
	6 &&   = TOKEN_AND,
	7 ||   = TOKEN_OR,
	8 (    = TOKEN_LPAREN,
	9 )    = TOKEN_RPAREN,
	10 ;    = TOKEN_SEMICOLON
	11 &    = TOKEN_AMPERSAND
*/
bool	command_has_unsupported_tokens(t_token *token_head)
{
	t_token	*token;

	token = token_head;
	while (token != NULL)
	{
		if (token->type == TOKEN_AND
			|| token->type == TOKEN_OR
			|| token->type == TOKEN_LPAREN
			|| token->type == TOKEN_RPAREN
			|| token->type == TOKEN_SEMICOLON
			|| token->type == TOKEN_AMPERSAND)
			return (print_lexical_error(
					"shell> the command contains unsupported characters.\n",
					true));
		token = token->next;
	}
	return (false);
}

bool	command_error_wrong_token_sequence(t_token *token_head)
{
	t_token	*token;

	token = token_head;
	while (token->next != NULL)
	{
		if (token->type == TOKEN_REDIR_IN
			&& token->next->type != TOKEN_WORD)
			return (print_lexical_error(
					"shell> syntax error near token `<`.\n", true));
		if (token->type == TOKEN_REDIR_OUT
			&& token->next->type != TOKEN_WORD)
			return (print_lexical_error(
					"shell> syntax error near token `>`.\n", true));
		if (token->type == TOKEN_HEREDOC
			&& token->next->type != TOKEN_WORD)
			return (print_lexical_error(
					"shell> syntax error near token `<<`.\n", true));
		if (token->type == TOKEN_APPEND
			&& token->next->type != TOKEN_WORD)
			return (print_lexical_error(
					"shell> syntax error near token `>>`.\n", true));
		token = token->next;
	}
	return (false);
}

/*
	Return
	true- The command has a error
	false- The command is ok, without errors
*/
bool	command_with_error(t_token *token_head)
{
	t_token	*last_token;

	if (!token_head)
		return (true);
	if (command_has_unsupported_tokens(token_head))
		return (true);
	last_token = get_last_token(token_head);
	if (token_head->type == TOKEN_PIPE)
		return (print_lexical_error(
				"shell> syntax error near unexpected token `|`.\n", true));
	if (command_error_wrong_token_sequence(token_head))
		return (true);
	if (last_token->type == TOKEN_REDIR_IN
		|| last_token->type == TOKEN_REDIR_OUT
		|| last_token->type == TOKEN_HEREDOC
		|| last_token->type == TOKEN_APPEND)
		return (print_lexical_error(
				"shell> syntax error near unexpected token `newline`.\n",
				true));
	return (false);
}
