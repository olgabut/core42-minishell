/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 09:39:21 by obutolin          #+#    #+#             */
/*   Updated: 2026/03/06 13:46:00 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	built in EXIT command
	The exit command exits the shell with a status of N.

	exit [n]

		where n specifies the exit status code to be returned upon exiting
	the shell.
		If no parameter is provided, the command returns the exit status
	of the last executed command.

	return:
		(-1) - error (it's not exit status, the command wasn't completed)
		(0..255) - n % 256 or exit status of the last executed command
*/
int	built_in_exit(char **argv, int last_cmd_exit, bool *need_exit)
{
	int	num_argv;

	*need_exit = false;
	if (!argv || !argv[0] || ft_strcmp(argv[0], "exit") != 0)
		return (-1);
	*need_exit = true;
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (!argv[1])
		return (last_cmd_exit);
	if (!ft_strtoint(&num_argv, argv[1]))
		return (print_cmd_error("exit", "numeric argument required"),
			EXIT_INVALID_ARG);
	if (argv[2])
	{
		*need_exit = false;
		return (print_cmd_error("exit", "too many arguments"), EXIT_FAILURE);
	}
	return (num_argv % 256);
}
