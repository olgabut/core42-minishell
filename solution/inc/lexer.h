/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 23:42:09 by obutolin          #+#    #+#             */
/*   Updated: 2026/04/06 10:47:01 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

int			line_lexer(t_memory_info **memory_head,
				t_token **token_head, char *line);
int			create_token(t_token **token, enum e_token_type type, char *value);
void		add_new_token(t_token **head, t_token *new_token);
void		free_token_list(t_token *head);
t_token		*get_last_token(t_token *head);
void		print_token_list(t_token *head);
bool		command_with_error(t_token *token_head);
bool		need_next_line(t_token *token_head);

#endif
