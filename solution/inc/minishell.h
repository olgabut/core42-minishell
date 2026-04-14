/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 09:31:23 by obutolin          #+#    #+#             */
/*   Updated: 2026/04/12 10:08:52 by obutolin         ###   ########.fr       */
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
# include <unistd.h>

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define EXIT_PERMISSION_DENIED 126
# define EXIT_CMD_NOT_FOUND 127
# define EXIT_SIGINT 130
# define EXIT_SIGQUIT 131
# define EXIT_INVALID_ARG 255
# define EXIT_SYNTAX_ERROR 258

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
	TOKEN_SEMICOLON,
	TOKEN_AMPERSAND
};

enum					e_stage
{
	STAGE_READLINE,
	STAGE_COMMON
};

typedef struct s_token
{
	struct s_token		*next;
	enum e_token_type	type;
	char				*value;
}						t_token;

typedef struct s_io
{
	struct s_io			*next;
	enum e_token_type	type;
	char				*path;
}						t_io;

typedef struct s_cmd
{
	struct s_cmd		*next;
	char				**args;
	char				*path;
	t_io				*io_list;
}						t_cmd;

typedef struct s_env
{
	struct s_env		*next;
	char				*key;
	char				*value;
}						t_env;

typedef struct s_minishell
{
	t_env				*env_list;
	t_cmd				*cmd_list;
	t_memory_info		*memory_head;
	int					stdin_backup;
	int					stdout_backup;
}						t_minishell;

typedef struct s_global
{
	int					sigint;
	int					exit_code;
	enum e_stage		stage;
}						t_global;

extern t_global	g_info;

// print_error
void	msh_error(char *reason, char *message);

// signals
void	set_signals_for_common_code(void);
void	set_signals_for_child_proces(void);
int		heredoc_rl_getc(FILE *stream);

// lexer
int		lexer(t_minishell *sh, t_token **token_head);

// env
void	free_env_list(t_env **head);
int		pars_env_structure(char **key, char **value, char *str);
int		update_env(t_env **head, char *key, char *value, bool sorted);
bool	remove_env_node(t_env **head, char *key);
char	*get_env_value(t_env *head, char *key);
int		init_env(t_env **env_head, char **input);
bool	is_env_key_valid(char *key);
char	**get_env_array(t_memory_info **memory, t_env *env);

// parser
int		parse(t_minishell *mshell, t_token *tokens);

// built_in
bool	is_built_in_cmd(char *cmd_name);
int		execute_built_in_cmd(t_cmd *cmd, t_minishell *sh);

// executor
/*
*	# RETURN VALUE
*
*	returns exit code of executed command, in case of empty 's' returns 1
*/
int		execute(t_minishell *sh);

#endif
