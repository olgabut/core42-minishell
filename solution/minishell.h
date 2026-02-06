/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 09:31:23 by obutolin          #+#    #+#             */
/*   Updated: 2026/02/06 10:27:18 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>

# include <unistd.h>//sleep

# include <signal.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

/*
	0 word = TOKEN_WORD
	1 |    = TOKEN_PIPE
	2 <    = TOKEN_REDIR_IN
	3 >    = TOKEN_REDIR_OUT
	4 <<   = TOKEN_HEREDOC,
	5 >>   = TOKEN_APPEND
	Not supported
	6 &&   = TOKEN_AND,
	7 ||   = TOKEN_OR,
	8 (    = TOKEN_LPAREN,
	9 )    = TOKEN_RPAREN,
	10 ;    = TOKEN_SEMICOLON
	11 &    = TOKEN_AMPERSAND
*/
enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND,
	// unsupported
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_SEMICOLON,
	TOKEN_AMPERSAND
};

typedef struct s_token
{
	enum e_token_type	type;
	char				*value;
	struct s_token		*prev;
	struct s_token		*next;
}	t_token;

enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND
};

typedef struct s_redir
{
	enum e_redir_type	type;
	char				*delimiter;
	bool				delimiter_has_quots;
}	t_redir;

typedef struct s_cmd
{
	char			**argv;
	t_redir			*redir;
	int				*pipe_fd;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_pipeline
{
	t_cmd	*cmds;
	int		count;
}	t_pipeline;

// lexer
int		lexer(t_memory_info **memory_head, t_token **token_head);
int		line_lexer(t_memory_info **memory_head,
			t_token **token_head, char *line);
int		create_token(t_token **token, enum e_token_type type, char *value);
void	add_new_token(t_token **head, t_token *new_token);
void	free_tokens(t_token *head);
t_token	*get_last_token(t_token *head);
void	print_token_list(t_token *head);
bool	command_with_error(t_token *token_head);
bool	need_next_line(t_token *token_head);
// heredoc_handler
int		heredoc_handler(t_memory_info **memory_head, t_cmd *cmd_head);
// builtin
int		echo_builtin(char **argv);
// signals
void	signals(void);

#endif
