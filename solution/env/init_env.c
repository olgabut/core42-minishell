/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 17:54:54 by obutolin          #+#    #+#             */
/*   Updated: 2026/03/05 11:43:56 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	The function gets one env (str == "key[=value]")
	and writes the key and value from str
	Return
	0 - malloc error
	1 - ok
*/
int	pars_env_structure(char **key, char **value, char *str)
{
	char	*eq;

	*key = NULL;
	*value = NULL;
	if (!str)
		return (1);
	eq = ft_strchr(str, '=');
	if (!eq)
		*key = ft_strdup(str);
	else
		*key = ft_substr(str, 0, eq - str);
	if (!*key)
		return (0);
	if (eq)
		*value = ft_strdup(eq + 1);
	if (eq && !*value)
	{
		free(*key);
		*key = NULL;
		return (0);
	}
	return (1);
}

/*
	Put init env to env list
	Return
		0 - malloc error
		1 - ok
*/
int	init_env(t_env **env_head, char **input)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	while (input[i])
	{
		key = NULL;
		value = NULL;
		if (!pars_env_structure(&key, &value, input[i])
			|| !update_env(env_head, key, value, false))
			return (0);
		i++;
	}
	return (1);
}
