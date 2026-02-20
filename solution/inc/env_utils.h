/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprikhod <dprikhod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 16:22:01 by dprikhod          #+#    #+#             */
/*   Updated: 2026/02/20 16:25:19 by dprikhod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_UTILS_H
# define ENV_UTILS_H

# include "minishell.h"

/*
 * # DESCRIPTION
 * Search for environment variable `key` in `env_list`, makes a copy of its
 * value with `ft_strdup`.
 * # RETURN VALUE
 * On success, the `get_env_value()` returns a pointer to a duplicated 
 * variable's value. It returens empty string ("") on failure.
 */
char	*get_env_value(t_env *env_list, const char *key);

#endif
