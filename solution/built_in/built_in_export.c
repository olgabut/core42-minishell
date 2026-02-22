/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 16:46:19 by obutolin          #+#    #+#             */
/*   Updated: 2026/02/22 17:31:30 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_env_export_format(t_env *env)
{
	int		fd;

	fd = 1;
	while (env)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(env->key, fd);
		if (env->value)
		{
			ft_putstr_fd("=\"", fd);
			ft_putstr_fd(env->value, fd);
			ft_putchar_fd('\"', fd);
		}
		ft_putchar_fd('\n', fd);
		env = env->next;
	}
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

	return:
		(-1) - error (it's not exit status, the command wasn't completed)
		(0) - success exit status
		(1..255) - error exit status
 */
int	built_in_export(t_memory_info **memory_long, char **argv, t_env **env)
{
	t_env	*new_env;

	if (!argv || !argv[0] || ft_strcmp(argv[0], "export") != 0)
		return (-1);
	if (argv[1])
	{
		if (!is_env_key_valid(argv[1]))
		{
			ft_printf("minishell: export: `%s`: not a valid idenfitier\n", argv[1]);
			return (EXIT_FAILURE);
		}
		new_env = NULL;
		if (!create_env(&new_env, argv[1], argv[2]))
		{
			ft_putstr_fd("minishell: export: malloc error\n", 2);
			return (EXIT_FAILURE);
		}
		update_env_sorted(env, new_env);
		if (!add_new_memory_link_for_control(memory_long, new_env->key)
			|| !add_new_memory_link_for_control(memory_long, new_env->value)
			|| !add_new_memory_link_for_control(memory_long, new_env))
			return (EXIT_FAILURE);
		return (0);//
	}
	print_env_export_format(*env);
	return (EXIT_SUCCESS);
}
