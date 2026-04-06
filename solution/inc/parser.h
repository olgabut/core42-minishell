/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 21:35:48 by dprikhod          #+#    #+#             */
/*   Updated: 2026/04/06 10:58:33 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include <stdbool.h>

enum e_quote
{
	SINGLE = 39,
	DOUBLE = 34,
	NONE,
} ;

bool	is_redirection(enum e_token_type type);
void	add_arg(t_minishell *mshell, t_list **word_list, char *token_word);
int		add_io(t_minishell *mshell, t_cmd *cmd, t_token **token);
int		add_here_doc(t_minishell *mshell, t_cmd *cmd, t_token **token);
void	beginning_of_str(char **substr, char *str, int len);
char	*combine_str_from_list(t_list **head_list);
void	print_list(t_list *head, char *message);
void	update_content(t_list **node, char *new_content);
t_list	*apply_ifs(t_minishell *mshell, char *word);
char	*check_word(t_minishell *mshell, char *word);
void	expand(t_minishell *mshell, t_list **substr_list);

#endif
