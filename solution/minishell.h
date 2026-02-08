/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 09:31:23 by obutolin          #+#    #+#             */
/*   Updated: 2026/02/08 15:09:04 by dprikhod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h> //sleep

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
enum					e_token_type
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
	struct s_token		*next;
}						t_token;

typedef struct s_io
{
	enum e_token_type	type;
	char				*path;
	char				**exp_args;
	struct s_io			*next;
}						t_io;

typedef struct s_cmd
{
	char				**args;
	char				*path;
	t_io				*io_list;
	struct s_cmd		*next;
}						t_cmd;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_minishell
{
	t_env				*env_list;
	t_cmd				*cmd_list;
	int					exit_code;
	int					stdin_backup;
	int					stdout_backup;
}						t_minishell;

// lexer
int						lexer(t_memory_info **memory_head,
							t_token **token_head);
int						line_lexer(t_memory_info **memory_head,
							t_token **token_head, char *line);
int						create_token(t_token **token, enum e_token_type type,
							char *value);
void					add_new_token(t_token **head, t_token *new_token);
void					free_tokens(t_token *head);
t_token					*get_last_token(t_token *head);
void					print_token_list(t_token *head);
bool					command_with_error(t_token *token_head);
bool					need_next_line(t_token *token_head);

void					signals(void);

// parser
t_cmd	*parser(t_token *tokens);
bool	is_redirection(enum e_token_type type);
void	add_arg(t_list **word_list, char *arg);
void	add_io(t_cmd *cmd, t_token **token);

#endif
