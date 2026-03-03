/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 17:54:54 by obutolin          #+#    #+#             */
/*   Updated: 2026/02/26 11:34:49 by obutolin         ###   ########.fr       */
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
	int	i;

	i = 0;
	*key = NULL;
	*value = NULL;
	if (!str)
		return (1);
	while (str[i] && str[i] != '=')
		i++;
	if (i > 0)
	{
		*key = ft_substr(str, 0, i);
		if (!(*key))
			return (0);
		if (str[i])
		{
			*value = ft_substr(str, i + 1, ft_strlen(str) - i);
			if (!*value)
			{
				free(*key);
				*key = NULL;
				return (0);
			}
		}
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
			|| !update_env(env_head, key, value))
			return (0);
		i++;
	}
	return (1);
}
