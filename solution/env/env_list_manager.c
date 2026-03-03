/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 16:59:40 by obutolin          #+#    #+#             */
/*   Updated: 2026/02/26 11:37:01 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Free one env node
*/
static void	free_env_node(t_env **env)
{
	free((*env)->key);
	(*env)->key = NULL;
	if ((*env)->value)
	{
		free((*env)->value);
		(*env)->value = NULL;
	}
	free(*env);
	*env = NULL;
}

/*
	Free all envs
*/
void	free_env_list(t_env **head)
{
	t_env	*env;
	t_env	*next_env;

	env = *head;
	while (env != NULL)
	{
		next_env = env->next;
		free_env_node(&env);
		env = next_env;
	}
	*head = NULL;
}

/*
	Creates new env by key and value (the value can be NULL)
	Return
		1 - ok
		0 - malloc error
*/
static int	create_env_node(t_env **new_env, char *key, char *value)
{
	t_env	*env;
	char	*new_key;
	char	*new_value;

	env = ft_calloc(1, sizeof(t_env));
	if (!env)
		return (0);
	new_key = NULL;
	new_value = NULL;
	new_key = ft_calloc(ft_strlen(key) + 1, sizeof(char));
	if (!new_key)
	{
		free(env);
		return (0);
	}
	ft_strlcpy(new_key, key, ft_strlen(key) + 1);
	env->key = new_key;
	if (value)
	{
		new_value = ft_calloc(ft_strlen(value) + 1, sizeof(char));
		if (!new_value)
		{
			free(env);
			free(new_key);
			return (0);
		}
		ft_strlcpy(new_value, value, ft_strlen(value) + 1);
	}
	env->value = new_value;
	env->next = NULL;
	*new_env = env;
	return (1);
}

/*
	Adds new_env or modifies an existing node with such a key
	in the list to the position,
	that the list is sorted by key
	where head is the first env

	Return
		1 - ok
		0 - malloc error
*/
int	update_env_sorted(t_env **head, char *key, char *value)
{
	t_env	*env;
	t_env	*prev;
	t_env	*new_env;

	new_env = NULL;
	if (!create_env_node(&new_env, key, value) || new_env == NULL)
		return (0);
	if (*head == NULL)
	{
		*head = new_env;
		return (1);
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
			return (1);
		}
		if (ft_strcmp(new_env->key, env->key) == 0)
		{
			if (new_env->value)
			{
				new_env->next = env->next;
				if (!prev)
					*head = new_env;
				else
					prev->next = new_env;
				free_env_node(&env);
			}
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
	adds new_env to the list to the last position,
	where head is the first env

	Return
		1 - ok
		0 - malloc error
*/
int	update_env(t_env **head, char *key, char *value)
{
	t_env	*env;
	t_env	*prev;
	t_env	*new_env;

	new_env = NULL;
	if (!create_env_node(&new_env, key, value) || new_env == NULL)
		return (0);
	if (*head == NULL)
	{
		*head = new_env;
		return (1);
	}
	env = *head;
	prev = NULL;
	while (env != NULL)
	{
		if (ft_strcmp(new_env->key, env->key) == 0)
		{
			if (new_env->value)
			{
				new_env->next = env->next;
				if (!prev)
					*head = new_env;
				else
					prev->next = new_env;
				free_env_node(&env);
			}
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
	return
		true - if node was find and remuved
		false - node doesn't exist
*/
bool	remove_env_node(t_env **head, char *key)
{
	t_env	*env;
	t_env	*tmp;

	if (!head || !*head)
		return (false);
	env = *head;
	if (ft_strcmp(env->key, key) == 0)
	{
		tmp = env->next;
		free_env_node(&env);
		*head = tmp;
		return (true);
	}
	while (env->next)
	{
		if (ft_strcmp(env->next->key, key) == 0)
		{
			tmp = env->next->next;
			free_env_node(&(env->next));
			env->next = tmp;
			return (true);
		}
		env = env->next;
	}
	return (false);
}
