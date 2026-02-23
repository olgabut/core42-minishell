/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 16:59:40 by obutolin          #+#    #+#             */
/*   Updated: 2026/02/23 09:00:02 by obutolin         ###   ########.fr       */
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
			if (env->value)
				free(env->value);
			env->value = NULL;
		}
		free(env);
		env = next_env;
	}
}

/*
	Creates new env by key and value (the value can be NULL)
	Return
		1 - ok
		0 - malloc error
*/
int	create_env(t_env **new_env, char *key, char *value)
{
	t_env	*env;
	char	*new_key;
	char	*new_value;

	env = ft_calloc(1, sizeof(t_env));
	new_key = NULL;
	new_value = NULL;
	new_key = ft_calloc(ft_strlen(key) + 1, sizeof(char));
	if (!new_env || !new_key)
		return (0);
	ft_strlcpy(new_key, key, ft_strlen(key) + 1);
	env->key = new_key;
	if (value)
	{
		new_value = ft_calloc(ft_strlen(value) + 1, sizeof(char));
		if (!new_value)
			return (0);
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
		if (ft_strcmp(new_env->key, env->key) == 0)
		{
			if (new_env->value)
			{
				new_env->next = env->next;
				if (!prev)
					*head = new_env;
				else
					prev->next = new_env;
			}
			return ;
		}
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

int	count_env(t_env *env)
{
	int		i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
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
		if (env->value)
			ft_putstr_fd(env->value, fd);
		else
			ft_putstr_fd("null", fd);
		ft_putchar_fd('\n', fd);
		env = env->next;
	}
}
