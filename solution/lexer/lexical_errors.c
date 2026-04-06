/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:00:48 by obutolin          #+#    #+#             */
/*   Updated: 2026/04/06 11:20:46 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

/* Unsupported tokens:
	6 &&   = TOKEN_AND,
	7 ||   = TOKEN_OR,
	8 (    = TOKEN_LPAREN,
	9 )    = TOKEN_RPAREN,
	10 ;    = TOKEN_SEMICOLON
	11 &    = TOKEN_AMPERSAND
*/
static bool	command_has_unsupported_tokens(t_token *token_head)
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
		{
			msh_error(NULL, "the command contains unsupported characters");
			return (true);
		}
		token = token->next;
	}
	return (false);
}

char	*get_token_by_type(enum e_token_type type)
{
	if (type == TOKEN_PIPE)
		return ("|");
	else if (type == TOKEN_REDIR_IN)
		return ("<");
	else if (type == TOKEN_REDIR_OUT)
		return (">");
	else if (type == TOKEN_HEREDOC)
		return ("<<");
	else if (type == TOKEN_APPEND)
		return (">>");
	else if (type == TOKEN_AND)
		return ("&&");
	else if (type == TOKEN_OR)
		return ("||");
	else if (type == TOKEN_LPAREN)
		return ("(");
	else if (type == TOKEN_RPAREN)
		return (")");
	else if (type == TOKEN_SEMICOLON)
		return (";");
	return (NULL);
}

static bool	command_error_wrong_token_sequence(t_token *tkn)
{
	char	*message;

	while (tkn && tkn->next != NULL)
	{
		if ((tkn->type == TOKEN_REDIR_IN && tkn->next->type != TOKEN_WORD)
			|| (tkn->type == TOKEN_REDIR_OUT && tkn->next->type != TOKEN_WORD)
			|| (tkn->type == TOKEN_HEREDOC && tkn->next->type != TOKEN_WORD)
			|| (tkn->type == TOKEN_APPEND && tkn->next->type != TOKEN_WORD)
			|| (tkn->type == TOKEN_PIPE && tkn->next->type == TOKEN_PIPE))
		{
			message = ft_strjoin("syntax error near unexpected token `",
					get_token_by_type(tkn->next->type));
			message = ft_strjoin_free(message, "`");
			msh_error(NULL, message);
			free(message);
			return (true);
		}
		tkn = tkn->next;
	}
	return (false);
}

/*
	Return
	true  - The command has a error
	false - The command is ok, without errors
*/
bool	command_with_error(t_token *token_head)
{
	t_token	*last_token;

	if (!token_head)
		return (true);
	if (command_has_unsupported_tokens(token_head))
		return (true);
	if (token_head->type == TOKEN_PIPE)
	{
		msh_error(NULL, "syntax error near unexpected token `|`");
		return (true);
	}
	if (command_error_wrong_token_sequence(token_head))
		return (true);
	last_token = get_last_token(token_head);
	if (last_token->type == TOKEN_REDIR_IN
		|| last_token->type == TOKEN_REDIR_OUT
		|| last_token->type == TOKEN_HEREDOC
		|| last_token->type == TOKEN_APPEND)
	{
		msh_error(NULL, "syntax error near unexpected token `newline`");
		return (true);
	}
	return (false);
}
