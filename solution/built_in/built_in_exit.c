/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 09:39:21 by obutolin          #+#    #+#             */
/*   Updated: 2026/02/11 12:33:04 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_last_exit_code(void)
{
	return (1);
}

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
int	built_in_exit(char **argv) //TODO NOT FINISH AND TESTED
{
	int	n;

	if (!argv || !argv[0] || ft_strcmp(argv[0], "exit") != 0)
		return (-1);
	ft_putstr_fd("exit\n", 1);
	if (!argv[1])
		exit(get_last_exit_code()); //todo
	if (!ft_strtoint(&n, argv[1]))
	{
		ft_putstr_fd("minishell: exit: numeric argument required",
			STDERR_FILENO);
		exit(255);
	}
	if (argv[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	exit(n % 256);
	return (EXIT_SUCCESS);
}
