/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 19:33:40 by obutolin          #+#    #+#             */
/*   Updated: 2026/03/27 22:16:53 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_env_array(t_memory_info **memory, t_env *env)
{
	int		count;
	char	*tmp;
	char	**env_array;
	int		i;

	count = count_env(env);
	env_array = ft_calloc(count + 1, sizeof(char *));
	if (!env_array)
		return (NULL);
	add_new_memory_link_for_control(memory, env_array);
	i = 0;
	while (i < count)
	{
		tmp = ft_straddchar(env->key, '=');
		env_array[i] = ft_strjoin(tmp, env->value);
		add_new_memory_link_for_control(memory, env_array[i]);
		free(tmp);
		env = env->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}

// void	print_env_array(char **env)
// {
// 	int i;

// 	i = 0;
// 	while (env[i] != NULL)
// 	{
// 		printf("%s\n", env[i]);
// 		i++;
// 	}
// }
