/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 09:31:23 by obutolin          #+#    #+#             */
/*   Updated: 2026/03/04 11:24:59 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <string.h>

# include <unistd.h>//sleep, chdir, getcwd

# include <signal.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define EXIT_CMD_NOT_FOUND 127
# define EXIT_CTRL_C 130
# define EXIT_INVALID_ARG 255

/*
	0 word = TOKEN_WORD
	1 |    = TOKEN_PIPE
	2 <    = TOKEN_REDIR_IN
	3 >    = TOKEN_REDIR_OUT
	4 <<   = TOKEN_HEREDOC,
	5 >>   = TOKEN_APPEND

	Unsupported
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
}						t_token;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

// lexer
int		lexer(t_memory_info **memory_head, t_token **token_head);
int		line_lexer(t_memory_info **memory_head,
			t_token **token_head, char *line);
int		create_token(t_token **token, enum e_token_type type, char *value);
void	add_new_token(t_token **head, t_token *new_token);
void	free_token_list(t_token *head);
t_token	*get_last_token(t_token *head);
void	print_token_list(t_token *head);
bool	command_with_error(t_token *token_head);
bool	need_next_line(t_token *token_head);
// env
void	free_env_list(t_env **head);
int		pars_env_structure(char **key, char **value, char *str);
int		update_env(t_env **head, char *key, char *value);
int		update_env_sorted(t_env **head, char *key, char *value);
bool	remove_env_node(t_env **head, char *key);
bool	get_env_exist(t_env *head, char *key, char **value);
int		count_env(t_env *env);
void	print_env_list(t_env *head);
int		init_env(t_env **env_head, char **input);
bool	is_env_key_valid(char *key);

// built_in
int		print_cmd_error(char *cmd_name, char *message, int exit_code);
int		built_in_echo(char **argv);
int		built_in_pwd(char **argv);
int		built_in_exit(char **argv, int last_cmd_exit, int *need_exit);
int		built_in_env(char **argv, t_env *env);
int		built_in_export(char **argv, t_env **env);
int		built_in_unset(char **argv, t_env **env);
int		built_in_cd(char **argv, t_env **env);

#endif
