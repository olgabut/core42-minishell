/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 09:31:23 by obutolin          #+#    #+#             */
/*   Updated: 2026/03/07 08:59:18 by dprikhod         ###   ########.fr       */
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
	t_memory_info		*memory_long;
	int					exit_code;
	int					stdin_backup;
	int					stdout_backup;
}						t_minishell;

void					init_shell(t_minishell *sh, char **envp);

void					signals(void);

int						lexer(t_memory_info **memory_head,
							t_token **token_head);
int						line_lexer(t_memory_info **memory_head,
							t_token **token_head, char *line);
int						create_token(t_token **token, enum e_token_type type,
							char *value);
void					add_new_token(t_token **head, t_token *new_token);
void					free_token_list(t_token *head);
t_token					*get_last_token(t_token *head);
void					print_token_list(t_token *head);
bool					command_with_error(t_token *token_head);
bool					need_next_line(t_token *token_head);

// env
void	free_env_node(t_env **env);
void	free_env_list(t_env **head);
int		pars_env_structure(char **key, char **value, char *str);
int		update_env(t_env **head, char *key, char *value, bool sorted);
bool	remove_env_node(t_env **head, char *key);
char	*get_env_value(t_env *head, char *key);
int		count_env(t_env *env);
void	print_env_list(t_env *head);
int		init_env(t_env **env_head, char **input);
bool	is_env_key_valid(char *key);

// built_in
void	print_cmd_error(char *cmd_name, char *message);
int		built_in_echo(char **argv);
int		built_in_pwd(char **argv);
int		built_in_exit(char **argv, int last_cmd_exit, bool *need_exit);
int		built_in_env(char **argv, t_env *env);
int		built_in_export(char **argv, t_env **env);
int		built_in_unset(char **argv, t_env **env);
int		built_in_cd(char **argv, t_env **env);

#endif
