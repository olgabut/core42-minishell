/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprikhod <dprikhod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 15:55:11 by dprikhod          #+#    #+#             */
/*   Updated: 2026/02/20 15:58:20 by dprikhod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLE_DOLLAR_H
# define HANDLE_DOLLAR_H

#include "minishell.h"

char	*handle_dollar(t_minishell *mshell, char *result, const char *word,
		size_t *i);

#endif
