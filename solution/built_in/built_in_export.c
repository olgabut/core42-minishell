/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 16:46:19 by obutolin          #+#    #+#             */
/*   Updated: 2026/03/03 12:42:16 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	clone_env_sorted(t_env *env, t_env **env_sorted_head)
{
	*env_sorted_head = NULL;
	while (env)
	{
		if (!update_env_sorted(env_sorted_head, env->key, env->value))
			return (0);
		env = env->next;
	}
	return (1);
}

static int	print_env_export_format(t_env *env)
{
	t_env	*env_sorted;
	t_env	*head;

	env_sorted = NULL;
	if (!clone_env_sorted(env, &env_sorted))
	{
		free_env_list(&env_sorted);
		return (0);
	}
	head = env_sorted;
	while (env_sorted)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(env_sorted->key, STDOUT_FILENO);
		if (env_sorted->value)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(env_sorted->value, STDOUT_FILENO);
			ft_putchar_fd('\"', STDOUT_FILENO);
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
		env_sorted = env_sorted->next;
	}
	free_env_list(&head);
	return (1);
}

/*
	built in EXPORT command
	The export command allows you to update and propagate the values of
	environment variables to the current session and any spawned child processes,
	ensuring that changes are immediately effective.

	export [-f] [-n] [name[=value] ...] or export -p

	FLAGS (IGNORED in minishell):
	-p To view all exported variables on current shell.
	-f The names are NOT variables, names are  functions
	name[=value] assign value before exporting
	-n Named variables (or functions, with -f) will no longer be exported.

	argv[0] = "export"
	argv[1..n] = can be null or string format: "keyName[=value]"
	return:
		(-1) - error (it's not exit status, the command wasn't completed)
		(0) - success exit status
		(1..255) - error exit status
 */
int	built_in_export(char **argv, t_env **env)
{
	int		i;
	char	*key;
	char	*value;
	int		result;

	if (!argv || !argv[0] || ft_strcmp(argv[0], "export") != 0)
		return (-1);
	i = 1;
	if (!argv[1])
	{
		print_env_export_format(*env);
		return (EXIT_SUCCESS);
	}
	result = EXIT_SUCCESS;
	while (argv[i])
	{
		if (!pars_env_structure(&key, &value, argv[i]))
			return (EXIT_FAILURE);
		if (!is_env_key_valid(key))
		{
			ft_printf("minishell: export: `%s`: not a valid identifier\n",
				argv[i]);
			result = EXIT_FAILURE;
			i++;
			free(key);
			free(value);
			continue ;
		}
		if (!update_env(env, key, value))
		{
			ft_putstr_fd("minishell: export: malloc error\n", 2);
			return (EXIT_FAILURE);
		}
		free(key);
		free(value);
		i++;
	}
	return (result);
}
