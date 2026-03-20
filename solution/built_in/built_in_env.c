/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 10:28:20 by obutolin          #+#    #+#             */
/*   Updated: 2026/03/20 21:55:04 by dprikhod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	built in ENV command
	It can print all the current environment variables, set new ones,
	or run a command within a custom environment.

	env [OPTION]... [-][NAME=VALUE]... [COMMAND [ARG]...]

	NAME=VALUE (IGNORED in minishell):
		Defines environment variables and their values.
	COMMAND [ARG] (IGNORED in minishell):
		Specifies the command to be executed with the modified environment.

	return:
		(-1) - error (it's not exit status, the command wasn't completed)
		(0) - success exit status
		(1..255) - error exit status
 */
int	built_in_env(char **argv, t_env *env)
{
	if (!argv || !argv[0] || ft_strcmp(argv[0], "env") != 0)
		return (-1);
	if (argv[1])
		return (print_cmd_error("env", "too many arguments"), EXIT_FAILURE);
	while (env)
	{
		if (env->value)
			ft_fprintf(STDOUT_FILENO, "%s=%s", env->key, env->value);
		env = env->next;
	}
	return (EXIT_SUCCESS);
}
