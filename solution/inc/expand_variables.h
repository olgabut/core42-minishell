/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 13:55:25 by dprikhod          #+#    #+#             */
/*   Updated: 2026/04/01 22:55:39 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_VARIABLE_H
# define EXPAND_VARIABLE_H

# include "minishell.h"

void	expand(t_minishell *mshell, t_list **substr_list);
// char	*expand_variables(t_minishell *mshell, const char *word);

#endif
