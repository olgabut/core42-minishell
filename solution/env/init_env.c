/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 17:54:54 by obutolin          #+#    #+#             */
/*   Updated: 2026/02/14 20:29:50 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	The function gets one env (str == "key=value")
	and writes the key and value from str
	Return
	0 - malloc error
	1 - ok
*/
static int	pars_input_env(char **key, char **value, char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != '=')
		i++;
	if (str && str[i] && i > 0)
	{
		*key = ft_substr(str, 0, i);
		if (!key)
			return (0);
		*value = ft_substr(str, i + 1, ft_strlen(str) - i);
		if (!value)
		{
			free(key);
			return (0);
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
int	init_env(t_memory_info **memory_head,
	t_env **env_head, char **input)
{
	int		i;
	char *key;
	char *value;
	t_env *new_env;

	(void)memory_head;
	(void)env_head;
	i = 0;
	while (input[i])
	{
		key = NULL;
		value = NULL;
		printf("input[%d] = '%s'\n", i, input[i]);
		if (!pars_input_env(&key, &value, input[i])
			|| !create_env(&new_env, key, value))
			return (0);
		add_new_env(env_head, new_env);
		if (!add_new_memory_link_for_control(memory_head, key)
			|| !add_new_memory_link_for_control(memory_head, value)
			|| !add_new_memory_link_for_control(memory_head, new_env))
			return (0);
		i++;
	}
	print_env_list(*env_head);
	return (1);
}