/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 16:59:40 by obutolin          #+#    #+#             */
/*   Updated: 2026/02/12 17:33:34 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

	new_env = malloc(sizeof(t_env));
	if (!new_env)
		return (0);
	new_env->key = key;
	new_env->value = value;
	new_env->next = NULL;
	*env = new_env;
	return (1);
}

/*
	Adds new_env to the list to the last position,
	where head is the first env
*/
void	add_new_env(t_env **head, t_env *new_env)
{
	t_env	*env;

	if (new_env == NULL)
		return ;
	if (*head == NULL)
	{
		*head = new_env;
		return ;
	}
	env = *head;
	while (env->next != NULL)
		env = env->next;
	env->next = new_env;
}

char *get_env(t_env *head, char *key)
{
	t_env *env;

	env = head;
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
}