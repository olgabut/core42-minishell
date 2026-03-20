/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 16:59:40 by obutolin          #+#    #+#             */
/*   Updated: 2026/03/20 21:50:33 by dprikhod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Creates new env by key and value (the value can be NULL)
	Return
		1 - ok
		0 - malloc error
*/
static int	create_env_node(t_env **new_env, char *key, char *value)
{
	t_env	*env;

	env = ft_calloc(1, sizeof(t_env));
	if (!env)
		return (0);
	env->key = ft_strdup(key);
	if (!env->key)
	{
		free(env);
		return (0);
	}
	if (value)
	{
		env->value = ft_strdup(value);
		if (!env->value)
		{
			free(env->key);
			free(env);
			return (0);
		}
	}
	env->next = NULL;
	*new_env = env;
	return (1);
}

static void	replace_env_node(t_env **head,
	t_env *prev, t_env *env, t_env *new_env)
{
	new_env->next = env->next;
	if (!prev)
		*head = new_env;
	else
		prev->next = new_env;
	free_env_node(&env);
}

static void	insert_before(t_env **head,
	t_env *prev, t_env *env, t_env *new_env)
{
	new_env->next = env;
	if (!prev)
		*head = new_env;
	else
		prev->next = new_env;
}

static int	update_env_loop(t_env **head, t_env *new_env, bool sorted)
{
	t_env	*env;
	t_env	*prev;

	env = *head;
	prev = NULL;
	while (env)
	{
		if (sorted && ft_strcmp(new_env->key, env->key) < 0)
			return (insert_before(head, prev, env, new_env), 1);
		if (ft_strcmp(new_env->key, env->key) == 0)
		{
			if (new_env->value)
				replace_env_node(head, prev, env, new_env);
			else
				free_env_node(&new_env);
			return (1);
		}
		prev = env;
		env = env->next;
	}
	prev->next = new_env;
	return (1);
}

/*
	Updates exising env with the same key or
	adds new_env to the list
		to the last position (sorted == false) or sorted
	where head is the first env

	Return
		1 - ok
		0 - malloc error
*/
int	update_env(t_env **head, char *key, char *value, bool sorted)
{
	t_env	*new_env;

	new_env = NULL;
	if (!create_env_node(&new_env, key, value))
		return (0);
	if (!*head)
	{
		*head = new_env;
		return (1);
	}
	return (update_env_loop(head, new_env, sorted));
}
