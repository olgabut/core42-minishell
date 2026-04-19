/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 21:35:48 by dprikhod          #+#    #+#             */
/*   Updated: 2026/04/14 22:27:17 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "minishell.h"

int		parse_word(t_minishell *sh, t_cmd *cmd, char *word);
int		parse_here_doc(t_minishell *sh, t_cmd *cmd, char *eof);
int		parse_redirection(t_minishell *sh, t_cmd *cmd,
			enum e_token_type redir_type, char *word);

#endif