/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 16:46:19 by obutolin          #+#    #+#             */
/*   Updated: 2026/03/04 21:14:09 by obutolin         ###   ########.fr       */
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
		return (EXIT_FAILURE);
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
	return (EXIT_SUCCESS);
}

statuc int	update_env_by_argv(char *argv, t_env **env,
	char **key, char **value)
{
	if (!pars_env_structure(&key, &value, argv[i]))
		return (print_cmd_error("export", "malloc error", EXIT_FAILURE));
	if (!is_env_key_valid(key))
	{
		ft_fprintf(STDERR_FILENO,
			"minishell: export: `%s`: not a valid identifier\n", argv[i]);
		return (EXIT_FAILURE);
	}
	if (!update_env(env, key, value))
		return (print_cmd_error("export", "malloc error", EXIT_FAILURE));
	return (EXIT_SUCCESS);
}

static int	update_env_by_mult_argv(char **argv, t_env **env)
{
	int		i;
	char	*key;
	char	*value;
	int		exit_code;

	i = 1;
	exit_code = EXIT_SUCCESS;
	while (argv[i])
	{
		if (!pars_env_structure(&key, &value, argv[i]))
			return (print_cmd_error("export", "malloc error", EXIT_FAILURE));
		if (!is_env_key_valid(key))
		{
			ft_fprintf(STDERR_FILENO,
				"minishell: export: `%s`: not a valid identifier\n", argv[i]);
			exit_code = EXIT_FAILURE;
		}
		else
		{
			if (!update_env(env, key, value))
			{
				free(key);
				free(value);
				return (print_cmd_error("export", "malloc error", EXIT_FAILURE));
			}
		}
		free(key);
		free(value);
		i++;
	}
	return (exit_code);
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

	if (!argv || !argv[0] || ft_strcmp(argv[0], "export") != 0)
		return (-1);
	if (!argv[1])
		return (print_env_export_format(*env));
	return (update_env_by_mult_argv(argv, env));
}
