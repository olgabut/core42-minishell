/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 16:59:40 by obutolin          #+#    #+#             */
/*   Updated: 2026/02/22 17:48:55 by dprikhod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Free all envs
*/
void	free_env_list(t_env *head)
{
	t_env	*env;
	t_env	*next_env;

	env = head;
	while (env != NULL)
	{
		next_env = env->next;
		if (env->value)
		{
			free(env->key);
			free(env->value);
			env->value = NULL;
		}
		free(env);
		env = next_env;
	}
}

/*
	Creates new env by key and value
	Return
		1 - ok
		0 - malloc error
*/
int	create_env(t_env **env, char *key, char *value)
{
	t_env	*new_env;

	new_env = ft_calloc(1, sizeof(t_env));
	if (!new_env)
		return (0);
	new_env->key = key;
	new_env->value = value;
	new_env->next = NULL;
	*env = new_env;
	return (1);
}

/*
	Adds new_env or modifies an existing node with such a key
	in the list to the position,
	that the list is sorted by key
	where head is the first env
*/
void	update_env_sorted(t_env **head, t_env *new_env)
{
	t_env	*env;
	t_env	*prev;

	if (new_env == NULL)
		return ;
	if (*head == NULL)
	{
		*head = new_env;
		return ;
	}
	env = *head;
	prev = NULL;
	while (env != NULL)
	{
		if (ft_strcmp(new_env->key, env->key) < 0)
		{
			new_env->next = env;
			if (!prev)
				*head = new_env;
			else
				prev->next = new_env;
			return ;
		}
		// if (ft_strcmp(new_env->key, env->key) == 0)
		// {
		// 	prev->next = new_env;
		// 	new_env->next = env->next;
		// }
		prev = env;
		env = env->next;
	}
	prev->next = new_env;
}

char	*get_env(t_env *head, char *key)
{
	t_env	*env;

	env = head;
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	print_env_list(t_env *head)
{
	t_env	*env;
	int		fd;

	fd = 1;
	env = head;
	ft_putstr_fd("Print envs:\n", fd);
	while (env != NULL)
	{
		ft_putstr_fd("key=", fd);
		ft_putstr_fd(env->key, fd);
		ft_putstr_fd(" value=", fd);
		ft_putendl_fd(env->value, fd);
		env = env->next;
	}
}
