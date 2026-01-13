/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 09:31:23 by obutolin          #+#    #+#             */
/*   Updated: 2026/01/13 11:27:53 by obutolin         ###   ########.fr       */
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
	0 word = TOKEN_WORD
	1 |    = TOKEN_PIPE
	2 <    = TOKEN_REDIR_IN
	3 >    = TOKEN_REDIR_OUT
	4 <<   = TOKEN_HEREDOC,
	5 >>   = TOKEN_APPEND
	BONUS PART
	6 &&   = TOKEN_AND,
	7 ||   = TOKEN_OR,
	8 (    = TOKEN_LPAREN,
	9 )    = TOKEN_RPAREN,
	10 ;    = TOKEN_SEMICOLON
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
