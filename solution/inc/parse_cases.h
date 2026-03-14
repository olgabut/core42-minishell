/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cases.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprikhod <dprikhod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 15:04:19 by dprikhod          #+#    #+#             */
/*   Updated: 2026/02/24 10:34:48 by dprikhod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_CASES_H
# define PARSE_CASES_H

# include "minishell.h"
# include <stdbool.h>

enum e_quote 
{
SINGLE = 39,
DOUBLE = 34,
NONE,
} ;

bool	is_redirection(enum e_token_type type);
void	add_arg(t_minishell *mshell, t_list **word_list, char *arg);
void	add_io(t_minishell *mshell, t_cmd *cmd, t_token **token);
void	add_here_doc(t_minishell *mshell, t_cmd *cmd, t_token **token);

#endif
