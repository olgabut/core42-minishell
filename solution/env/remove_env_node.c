/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_env_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 09:29:58 by obutolin          #+#    #+#             */
/*   Updated: 2026/03/20 21:51:04 by dprikhod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Free one env node
*/
void	free_env_node(t_env **env)
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
