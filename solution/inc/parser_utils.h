/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 23:43:49 by obutolin          #+#    #+#             */
/*   Updated: 2026/04/02 00:42:39 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_UTILS_H
# define PARSER_UTILS_H

# include "minishell.h"

void	beginning_of_str(char **substr, char *str, int len);
char	*combine_str_from_list(t_list **head_list);
void	print_list(t_list *head);

#endif