/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 09:39:21 by obutolin          #+#    #+#             */
/*   Updated: 2026/04/21 12:37:26 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "built_in.h"

/*
	built in EXIT command
	The exit command exits the shell with a status of N.

	exit [n]

		where n specifies the exit status code to be returned upon exiting
	the shell.
		If no parameter is provided, the command returns the exit status
	of the last executed command.

	return:
		(0..255) - n % 256 or exit status of the last executed command
*/
int	built_in_exit(char **argv, bool *need_exit)
{
	int	num_argv;

	*need_exit = true;
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (!argv[1])
		return (g_info.exit_code);
	if (!ft_strtoint(&num_argv, argv[1]))
	{
		msh_error("exit", "numeric argument required");
		return (2);
	}
	if (argv[2])
	{
		*need_exit = false;
		msh_error("exit", "too many arguments");
		return (EXIT_FAILURE);
	}
	return (num_argv % 256);
}
