/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_word.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 14:49:03 by dprikhod          #+#    #+#             */
/*   Updated: 2026/04/02 17:37:22 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECK_WORD_H
# define CHECK_WORD_H

#include "minishell.h"

t_list	*apply_ifs(t_minishell *mshell, char *word);
char	*check_word(t_minishell *mshell, char *word);

#endif
