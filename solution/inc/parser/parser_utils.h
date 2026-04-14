/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 21:35:48 by dprikhod          #+#    #+#             */
/*   Updated: 2026/04/14 22:27:45 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_UTILS_H
# define PARSER_UTILS_H

# include "minishell.h"

enum e_quote
{
	SINGLE = 39,
	DOUBLE = 34,
	NONE,
} ;

void	beginning_of_str(char **substr, char *str, int len);
char	*combine_str_from_list(t_list **head_list);
void	update_content(t_list **node, char *new_content);
void	print_list(t_list *head, char *message);

#endif