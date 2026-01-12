/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 09:31:23 by obutolin          #+#    #+#             */
/*   Updated: 2026/01/12 10:57:39 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>

# include <readline/readline.h>
# include <readline/history.h>

/*
	word = TOKEN_WORD
	|    = TOKEN_PIPE
	<    = TOKEN_REDIR_IN
	>    = TOKEN_REDIR_OUT
	<<   = TOKEN_HEREDOC,
	>>   = TOKEN_APPEND
	BONUS PART
	&&   = TOKEN_AND,
	||   = TOKEN_OR,
	(    = TOKEN_LPAREN,
	)    = TOKEN_RPAREN,
	;    = TOKEN_SEMICOLON
*/
enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND,
	//
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_SEMICOLON
};

typedef struct s_token
{
	enum e_token_type	type;
	char				*value;
	bool				isFinish;
	struct s_token		*next;
}	t_token;

t_token	*line_lexer(char *line);

#endif
