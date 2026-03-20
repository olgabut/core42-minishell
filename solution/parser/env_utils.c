/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprikhod <dprikhod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 16:18:56 by dprikhod          #+#    #+#             */
/*   Updated: 2026/02/20 16:21:13 by dprikhod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_utils.h"

char	*get_env_value(t_env *env_list, const char *key)
{
	while (env_list)
	{
		if (ft_strncmp(env_list->key, key, ft_strlen(key) + 1) == 0)
			return (ft_strdup(env_list->value));
		env_list = env_list->next;
	}
	return (ft_strdup("")); 
}
