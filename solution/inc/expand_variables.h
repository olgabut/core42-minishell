/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprikhod <dprikhod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 13:55:25 by dprikhod          #+#    #+#             */
/*   Updated: 2026/02/20 16:42:43 by dprikhod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_VARIABLE_H
# define EXPAND_VARIABLE_H

# include "minishell.h"

char	*expand_variables(t_minishell *mshell, const char *word);

#endif
