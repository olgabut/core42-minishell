/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 13:44:08 by obutolin          #+#    #+#             */
/*   Updated: 2026/03/06 10:47:03 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_env_key_valid(char *key)
{
	int	i;

	if (!((key[0] >= 'a' && key[0] <= 'z')
			|| (key[0] >= 'A' && key[0] <= 'Z')
			|| key[0] == '_'))
		return (false);
	i = 1;
	while (key[i] != '\0')
	{
		if (!((key[i] >= 'a' && key[i] <= 'z')
				|| (key[i] >= 'A' && key[i] <= 'Z')
				|| (key[i] >= '0' && key[i] <= '9')
				|| key[i] == '_'))
			return (false);
		i++;
	}
	return (true);
}

/*
	if env with key exists - return true, value has the found value of interest
	else return false
	The value can be NULL
*/
char	*get_env_value(t_env *head, char *key)
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
		ft_putstr_fd(env->key, fd);
		ft_putstr_fd(" = ", fd);
		if (env->value)
			ft_putstr_fd(env->value, fd);
		else
			ft_putstr_fd("null", fd);
		ft_putchar_fd('\n', fd);
		env = env->next;
	}
}
