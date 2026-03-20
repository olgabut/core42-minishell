/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 16:46:19 by obutolin          #+#    #+#             */
/*   Updated: 2026/03/20 21:55:07 by dprikhod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	clone_env_sorted(t_env *env, t_env **env_sorted_head)
{
	*env_sorted_head = NULL;
	while (env)
	{
		if (!update_env(env_sorted_head, env->key, env->value, true))
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

static void	process_export_arg(char *arg, t_env **env, int *exit_code)
{
	char	*key;
	char	*value;

	if (!pars_env_structure(&key, &value, arg))
	{
		*exit_code = EXIT_FAILURE;
		print_cmd_error("export", "malloc error");
		return ;
	}
	if (!is_env_key_valid(key))
	{
		ft_fprintf(STDERR_FILENO,
			"minishell: export: `%s`: not a valid identifier\n", arg);
		*exit_code = EXIT_FAILURE;
	}
	else
	{
		if (!update_env(env, key, value, false))
		{
			*exit_code = EXIT_FAILURE;
			print_cmd_error("export", "malloc error");
		}
	}
	free(key);
	free(value);
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
	int	i;
	int	exit_code;

	if (!argv || !argv[0] || ft_strcmp(argv[0], "export") != 0)
		return (-1);
	if (!argv[1])
		return (print_env_export_format(*env));
	i = 1;
	exit_code = EXIT_SUCCESS;
	while (argv[i])
	{
		process_export_arg(argv[i], env, &exit_code);
		i++;
	}
	return (exit_code);
}
